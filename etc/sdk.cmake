##################################################################
# SDK CONFIG
##################################################################
SET(__SDK_INC_PATH__ "${__SDK_PATH__}/${SDK_VER}/include")
SET(__SDK_LIB_PATH__ "${__SDK_PATH__}/${SDK_VER}/libs")

# Mercury System Path
SET(MSYS_INC_PATH "${__SDK_INC_PATH__}")

# SDK Path
SET(SDK_LIB_INC_PATH "${__SDK_INC_PATH__}")
SET(SDK_LIB_PATH "${__SDK_LIB_PATH__}/${PLATFORM_VER}")
SET(SDK_IOT_PATH "${__SDK_LIB_PATH__}/iot")
SET(SDK_CIT_PATH "${__SDK_LIB_PATH__}/cit")
SET(SDK_MQ_PATH "${__SDK_LIB_PATH__}/mq")

###################### 系统头文件搜索目录 ########################################
# Mercury System
INCLUDE_DIRECTORIES("${MSYS_INC_PATH}")
INCLUDE_DIRECTORIES("${MSYS_INC_PATH}/${PLATFORM_VER}")

# SDK中已包含阿里云http/json/...
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot/exports")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot/imports")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot/utils")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot/utils/digest")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/iot/utils/misc")
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/aliyun/paho_mqtt")
# SDK中已包含mbedtls
INCLUDE_DIRECTORIES("${SDK_LIB_INC_PATH}/mbedtls")

######################## Set SDK LIB ############################################
# SDK LIB
SET(SDK_LIBS " ")
STRING(APPEND SDK_LIBS " system.a ")
STRING(APPEND SDK_LIBS " main_entry.o ")

IF (DEFINED BWSDK_BASED_APP_TARGET)
IF (DEFINED PRODUCT_MODEL)
	STRING(APPEND SDK_LIBS " ${PRODUCT_MODEL}_bwsdk_${CMAKE_QR_BUILD_TYPE}.a ")
ELSE()
	MESSAGE(FATAL_ERROR "Do not specify product model!!!")
ENDIF()
ENDIF()

# SYSTEM LIB
SET(SYSTEM_LIBS " ")
STRING(APPEND SYSTEM_LIBS " ${SDK_IOT_PATH}/aliyun_iot_platform_${CMAKE_QR_BUILD_TYPE}.a ")
STRING(APPEND SYSTEM_LIBS " ${SDK_IOT_PATH}/aliyun_iot_sdk_${CMAKE_QR_BUILD_TYPE}.a ")
STRING(APPEND SYSTEM_LIBS " ${SDK_MQ_PATH}/paho-mqtt3_${CMAKE_QR_BUILD_TYPE}.a ")
IF (NOT (${PRODUCT_MODEL} STREQUAL "QR150" ))
IF (NOT (${PRODUCT_MODEL} STREQUAL "QR150BT" ))
STRING(APPEND SYSTEM_LIBS " ${SDK_CIT_PATH}/${PRODUCT_MODEL}_bwcit.a ")
ENDIF ()
ENDIF ()

###################### END ######################################################

