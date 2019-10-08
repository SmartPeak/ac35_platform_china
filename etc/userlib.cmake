########################################
# userlib config
########################################

# path
SET(USER_LIB_PATH "${PROJECT_SOURCE_DIR}/${APP_PATH}/libs")
SET(USER_INC_PATH "${PROJECT_SOURCE_DIR}/${APP_PATH}/libs")

# include directories
INCLUDE_DIRECTORIES("${USER_INC_PATH}")

# userlib.a
STRING(APPEND CMAKE_EXE_LINKER_FLAGS " ${USER_LIB_PATH}/${USER_LIBS} ")

