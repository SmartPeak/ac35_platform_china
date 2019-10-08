##########################################################################
# Shanghai Basewin Technology Co.,Ltd.
# All Rights Reserved 2017
##########################################################################
SET(ESIGN_PATH src/esign)

ADD_DEFINITIONS(-DENABLE_ESIGN)

AUX_SOURCE_DIRECTORY(${ESIGN_PATH} APP_SRC_LIST)
INCLUDE_DIRECTORIES(${ESIGN_PATH})
