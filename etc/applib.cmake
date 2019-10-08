########################################
# applib config
########################################

# path
SET(__APPLIB_PATH__ "${_PATH_}/applib")
SET(APPLIB_LIB_PATH "${__APPLIB_PATH__}/${APPLIB_VER}")
SET(APPLIB_INC_PATH "${__APPLIB_PATH__}/${APPLIB_VER}/inc")

# include directories
INCLUDE_DIRECTORIES("${APPLIB_INC_PATH}")

# applib.a
STRING(APPEND CMAKE_EXE_LINKER_FLAGS " ${APPLIB_LIB_PATH}/${PRODUCT_MODEL}_applib_${CMAKE_QR_BUILD_TYPE}.a ")

