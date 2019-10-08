#################### Set Path ######################
SET(_PATH_ "${PROJECT_SOURCE_DIR}/libs")

#sdk path
IF (${PRODUCT_MODEL} STREQUAL "P90")
SET(__SDK_PATH__ "${_PATH_}/sdk_p90")
ELSE ()
SET(__SDK_PATH__ "${_PATH_}/sdk_qr")
ENDIF ()

#scatter path
SET(SCATTER_PATH "${__SDK_PATH__}/${SDK_VER}/libs")

#system lib path
SET(SYSTEM_PATH "${__SDK_PATH__}/${SDK_VER}")

