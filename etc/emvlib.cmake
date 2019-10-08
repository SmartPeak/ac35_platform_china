########################################
# emv lib config
########################################
# EMV path
SET(__EMV_PATH__ "${_PATH_}/emv")
SET(EMV_LIB_PATH "${__EMV_PATH__}/${EMV_VER}")
SET(EMV_INC_PATH "${__EMV_PATH__}/${EMV_VER}/include")

# include directories
INCLUDE_DIRECTORIES("${EMV_INC_PATH}")

# emvlib.a
STRING(APPEND CMAKE_EXE_LINKER_FLAGS " ${EMV_LIB_PATH}/EmvCTKernel_${CMAKE_QR_BUILD_TYPE}.a")
STRING(APPEND CMAKE_EXE_LINKER_FLAGS " ${EMV_LIB_PATH}/quics_${CMAKE_QR_BUILD_TYPE}.a")
