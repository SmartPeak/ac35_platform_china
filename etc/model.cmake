########################################
# model config
########################################

# path
set(MODEL_CFG_PATH "${PROJECT_SOURCE_DIR}/etc/model")

# load model config file
if (EXISTS "${MODEL_CFG_PATH}/${PRODUCT_MODEL}_cfg.cmake")
	include ("${MODEL_CFG_PATH}/${PRODUCT_MODEL}_cfg.cmake")
endif ()
