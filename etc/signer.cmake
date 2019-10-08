##################################################################
# Signer Config
##################################################################

# 定义签名工具的路径
SET(HEADERSTUB "${SCATTER_PATH}/HeaderStub.bin")
SET(SIGNER "${PROJECT_SOURCE_DIR}/tools/MercurySign.exe")
SET(FROMELF "${TOOLCHAIN_ROOT_PATH}/bin/fromelf.exe")

# 定义次级应用签名工具包
IF (${APP_BOOT_STAGE} STREQUAL "SubApp")
SET(IMG_SIGNER_JAR "${CMAKE_SOURCE_DIR}/tools/security/SignImg.jar")
SET(IMG_SIGNER_KEY "${CMAKE_SOURCE_DIR}/tools/security/smartpeak_qr.key")
SET(IMG_SIGNER_KEY_SECRET "smartpeak")
SET(SIGNED_SUBAPP_IMG "${PROJECT_BINARY_DIR}/${APP_NAME}_signed.img")

# 将xxx.bin路径从cygwin格式转换为Windows路径
# 因为签名工具不识别cygwin路径        
EXECUTE_PROCESS(COMMAND $ENV{CYGPATH} -w "${IMG_SIGNER_JAR}"
        OUTPUT_VARIABLE NATIVE_IMG_SIGNER_JAR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        
EXECUTE_PROCESS(COMMAND $ENV{CYGPATH} -w "${IMG_SIGNER_KEY}"
        OUTPUT_VARIABLE NATIVE_IMG_SIGNER_KEY
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        
EXECUTE_PROCESS(COMMAND $ENV{CYGPATH} -w "${SIGNED_IMG}"
        OUTPUT_VARIABLE NATIVE_SIGNED_IMG
        OUTPUT_STRIP_TRAILING_WHITESPACE)  
        
EXECUTE_PROCESS(COMMAND $ENV{CYGPATH} -w "${SIGNED_SUBAPP_IMG}"
        OUTPUT_VARIABLE NATIVE_SIGNED_SUBAPP_IMG
        OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF()

# 将xxx.bin路径从cygwin格式转换为Windows路径
# 因为签名工具不识别cygwin路径
EXECUTE_PROCESS(COMMAND $ENV{CYGPATH} -w "${BIN_PATH}"
        OUTPUT_VARIABLE BIN_NATIVE_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

# xxx.axf -> xxx.raw -> xxx.bin -> xxx.img
IF (${APP_BOOT_STAGE} STREQUAL "SubApp")
ADD_CUSTOM_TARGET(BIN ALL
        COMMAND ${FROMELF} -c --bin ${ELF_PATH} --output ${RAW_PATH}
        COMMAND cat ${HEADERSTUB} ${RAW_PATH} > ${BIN_PATH}
        COMMAND ${SIGNER} "${BIN_NATIVE_PATH}" showApp 1 6 2 3014656 3014656 "SmartPeak Technology"
        COMMAND java -jar ${NATIVE_IMG_SIGNER_JAR} ${NATIVE_IMG_SIGNER_KEY} ${CUSTOMER_NAME} ${NATIVE_SIGNED_IMG} ${NATIVE_SIGNED_SUBAPP_IMG} ${IMG_SIGNER_KEY_SECRET}
        DEPENDS ${APP_NAME})
ELSE()
ADD_CUSTOM_TARGET(BIN ALL
        COMMAND ${FROMELF} -c --bin ${ELF_PATH} --output ${RAW_PATH}
        COMMAND cat ${HEADERSTUB} ${RAW_PATH} > ${BIN_PATH}
        COMMAND ${SIGNER} "${BIN_NATIVE_PATH}" showApp 1 6 2 2949120 2949120 "SmartPeak Technology"
        DEPENDS ${APP_NAME})
ENDIF()
