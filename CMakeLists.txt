##########################################################################
# 上海盛本智能科技股份有限公司
# Shanghai Basewin Technology Co.,Ltd.
# All Rights Reserved 2017
##########################################################################
cmake_minimum_required(VERSION 3.5)

# 默认编译次级应用
SET(APP_BOOT_STAGE "SubApp")

# 如果在CMAKE命令中没有定义APP启动阶段，则这里自动定义为SingleMainApp
IF (NOT DEFINED APP_BOOT_STAGE)
    SET(APP_BOOT_STAGE "SingleMainApp")
ENDIF()

# 如果在CMAKE命令中没有定义编译类型，则这里自动定义为Release
IF (NOT DEFINED CMAKE_QR_BUILD_TYPE)
    SET(CMAKE_QR_BUILD_TYPE "Release")
ENDIF()

# 如果在CMAKE命令中没有定义APP名称，则这里自动定义为showAPP
IF (NOT DEFINED APP_NAME)
    SET(APP_NAME showAPP)
ENDIF ()

# 如果在CMAKE命令中没有定义BUILD_TARGET，则这里自动定义为APP
IF (NOT DEFINED BUILD_TARGET)
    SET(BUILD_TARGET APP)
ENDIF()

# 如果在CMAKE命令中没有定义PRODUCT_MODEL，则这里自动定义为QR100
IF (NOT DEFINED PRODUCT_MODEL)
    SET(PRODUCT_MODEL QR100)
ENDIF()

# 如果在CMAKE命令中没有定义CUSTOMER_NAME，则这里自动定义为ums
IF (NOT DEFINED CUSTOMER_NAME)
    SET(CUSTOMER_NAME ums)
ENDIF()

# 编译APP时开启
IF (${BUILD_TARGET} STREQUAL "APP")
SET(BWSDK_BASED_APP_TARGET YES)
ENDIF()

# 需要AliyunIOT时开启，注释掉即关闭
#SET(ALIYUN_IOT_TARGET YES)

# 需要MQ时开启，注释掉即关闭
SET(ALIYUN_MQ_TARGET YES)

# 需要开启Sensor触发远程解锁时开启，注释掉关闭
SET(SECURITY_WITH_AR YES)


include("tmp_config.cmake")


# 将配置信息输出方便查验
MESSAGE("##############################################")
MESSAGE("# CMAKE_QR_BUILD_TYPE: ${CMAKE_QR_BUILD_TYPE}")
MESSAGE("#      BUILD_TARGET: ${BUILD_TARGET}")
MESSAGE("#     PRODUCT_MODEL: ${PRODUCT_MODEL}")
MESSAGE("#          APP_NAME: ${APP_NAME}")
MESSAGE("#    CUSTOMER_NAME : ${CUSTOMER_NAME}")
MESSAGE("# CUSTOMER_SUBNAME : ${CUSTOMER_SUBNAME}")
MESSAGE("##############################################")

# 定义工程名称
PROJECT(${APP_NAME} C)

# 设置C语言标准 C90 (=C89)
SET(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_STANDARD 11)

# 设置可执行文件后缀
SET(CMAKE_EXECUTABLE_SUFFIX ".axf")

# 设置静态库的默认前缀（没有lib）
SET(CMAKE_STATIC_LIBRARY_PREFIX_C "")

# 调试设置(Release编译时，不开调试LOG)
IF (${CMAKE_QR_BUILD_TYPE} STREQUAL "Release")
	STRING(APPEND CMAKE_C_FLAGS " -DLOG_DISABLE ")
ENDIF()

#====================================================================
# 设置路径
include (${PROJECT_SOURCE_DIR}/etc/path.cmake)

# 设置机型配置
include (${PROJECT_SOURCE_DIR}/etc/model.cmake)

# 设置SDK库搜索路径
include (${PROJECT_SOURCE_DIR}/etc/sdk.cmake)

# 设置applib库搜索路径
include (${PROJECT_SOURCE_DIR}/etc/applib.cmake)

# 设置EMV库搜索路径
IF (DEFINED EMV_VER)
	include (${PROJECT_SOURCE_DIR}/etc/emvlib.cmake)
ENDIF()

# 设置第三方库搜索路径
IF (DEFINED USER_LIBS)
	include (${PROJECT_SOURCE_DIR}/etc/userlib.cmake)
ENDIF()
#====================================================================

# 将产品名传到C编译器中
IF (DEFINED PRODUCT_MODEL)
	STRING(APPEND CMAKE_C_FLAGS " -D_PRODUCT_NAME=\\\"${PRODUCT_MODEL}\\\" ")
	STRING(APPEND CMAKE_C_FLAGS " -D${PRODUCT_MODEL} ")
ELSE()
	MESSAGE(FATAL_ERROR "未指定产品型号!")
ENDIF()

# 将环境变量中的版本号及编译时间传到C编译器中
STRING(APPEND CMAKE_C_FLAGS " -D_CUSTOMER_NAME=\\\"${CUSTOMER_NAME}\\\" ")
STRING(APPEND CMAKE_C_FLAGS " -D_CUSTOMER_SUBNAME=\\\"${CUSTOMER_SUBNAME}\\\" ")
STRING(APPEND CMAKE_C_FLAGS " -D_APP_VERSION=\\\"$ENV{APP_VERSION}\\\" ")
STRING(APPEND CMAKE_C_FLAGS " -D_APP_BUILD_DATE=\\\"$ENV{APP_BUILD_DATE}\\\" ")

# 定义触发时支持简单解锁还是远程解锁
IF (NOT DEFINED SECURITY_WITH_AR)
STRING(APPEND CMAKE_C_FLAGS " -DFEATURE_SIMPLE_UNLOCK_SP")
ENDIF ()

# 定义切换客户时Release远程解锁，Debug时本地密码解锁
IF ( NOT (${CMAKE_QR_BUILD_TYPE} STREQUAL "Release") )
STRING(APPEND CMAKE_C_FLAGS " -DFEATURE_SIMPLE_UNLOCK_INVALID_CUSTOMER ")
ENDIF ()

################## 连接脚本文件 #################################################
# 路径
IF (${APP_BOOT_STAGE} STREQUAL "SingleMainApp")
# 单个主应用，使用所有ROM和RAM
SET(SCATTER "${SCATTER_PATH}/scatter_SingaleMainApp.scl")
ELSEIF (${APP_BOOT_STAGE} STREQUAL "MainApp")
# 主应用，使用部分ROM和RAM
SET(SCATTER "${SCATTER_PATH}/scatter_MainApp.scl")
ELSEIF (${APP_BOOT_STAGE} STREQUAL "SubApp")
# 子应用，使用剩余部分的ROM和RAM
SET(SCATTER "${SCATTER_PATH}/scatter_SubApp.scl")
ENDIF()
###################### END ######################################################

# 目标符号文件
SET(MAP_FILE "${PROJECT_BINARY_DIR}/${APP_NAME}.map")

# 添加C编译器参数
IF (${CMAKE_C_COMPILER_ID} STREQUAL "ARMCC")
    STRING(APPEND CMAKE_C_FLAGS " --c99 --cpu=ARM926EJ-S --fpu=softvfp ")
    STRING(APPEND CMAKE_C_FLAGS " --apcs=/interwork --thumb --enum_is_int --loose_implicit_cast --li --diag_suppress=174,870 ")
IF (${CMAKE_QR_BUILD_TYPE} STREQUAL "Release")
    STRING(APPEND CMAKE_C_FLAGS " -O2 --no_debug -DNDEBUG")
ENDIF ()
IF (${CMAKE_QR_BUILD_TYPE} STREQUAL "Debug")
    STRING(APPEND CMAKE_C_FLAGS " -O2 -g")
ENDIF ()
    STRING(APPEND CMAKE_C_FLAGS " -DDUMMY_MACRO -DTEST_MACRO1 -DTEST_MACRO2 -DPROJECT_STUB_FLAG ")
    STRING(APPEND CMAKE_C_FLAGS " -DPLATFORM_OS=QR -DPLATFORM_OS_QR ")
ENDIF ()

IF (DEFINED BWSDK_BASED_APP_TARGET)
    STRING(APPEND CMAKE_C_FLAGS " -DBWSDK_BASED_APP_TARGET ")
ENDIF ()

# 添加连接器参数
IF (${CMAKE_C_COMPILER_ID} STREQUAL "ARMCC")
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --cpu=ARM926EJ-S --fpu=softvfp ")
IF (${CMAKE_QR_BUILD_TYPE} STREQUAL "Release")
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --no_debug ")
ENDIF ()
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --entry Mercury_Entry --map --symbols --no_merge ")
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --scatter ${SCATTER} --list ${MAP_FILE} --info sizes ")
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --userlibpath ${SDK_LIB_PATH} ${SDK_LIBS} ")
    STRING(APPEND CMAKE_EXE_LINKER_FLAGS " --userlibpath ${SYSTEM_PATH} ${SYSTEM_LIBS} ")
ENDIF ()

#添加子目录
ADD_SUBDIRECTORY(${APP_PATH})

# Target
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/etc/src SRC_LIST)
ADD_EXECUTABLE(${APP_NAME} ${SRC_LIST})

# 将用户库加入到连接中
TARGET_LINK_LIBRARIES(${APP_NAME} ${CUSTOMER_NAME})

# 定义中间文件的路径
SET(ELF_PATH "${PROJECT_BINARY_DIR}/${APP_NAME}${CMAKE_EXECUTABLE_SUFFIX}") # xxx.axf
SET(RAW_PATH "${PROJECT_BINARY_DIR}/${APP_NAME}.raw") # xxx.raw
SET(BIN_PATH "${PROJECT_BINARY_DIR}/${APP_NAME}.bin") # xxx.bin
SET(SIGNED_IMG "${PROJECT_BINARY_DIR}/${APP_NAME}.img") # xxx.img

# 签名
include (${PROJECT_SOURCE_DIR}/etc/signer.cmake)

# 打印出编译器和连接器选项
MESSAGE("##############################################")
MESSAGE("CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
MESSAGE("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
MESSAGE("ELF_PATH: ${ELF_PATH}")
MESSAGE("SIGNED_IMG: ${SIGNED_IMG}")
MESSAGE("APP_BOOT_STAGE: ${APP_BOOT_STAGE}")
MESSAGE("##############################################")
