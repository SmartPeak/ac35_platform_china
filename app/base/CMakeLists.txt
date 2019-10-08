##########################################################################
# Shanghai Basewin Technology Co.,Ltd.
# All Rights Reserved 2017
##########################################################################
AUX_SOURCE_DIRECTORY(src/utils APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/utils)

AUX_SOURCE_DIRECTORY(src/emv APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/emv)

AUX_SOURCE_DIRECTORY(src/app APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/app/inc)

AUX_SOURCE_DIRECTORY(src/logger APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/logger)

AUX_SOURCE_DIRECTORY(src/systemUI APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/systemUI)

AUX_SOURCE_DIRECTORY(src/version APP_SRC_LIST)
INCLUDE_DIRECTORIES(src/version)

IF (${PRODUCT_MODEL} STREQUAL "P90")
INCLUDE(src/esign/esign.cmake)
ENDIF ()

#lib
ADD_LIBRARY(${CUSTOMER_NAME} ${APP_SRC_LIST})


