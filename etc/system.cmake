##################################################################
# system ui CONFIG
##################################################################

AUX_SOURCE_DIRECTORY(./app SYSTEM_UI_SRC_LIST)
ADD_EXECUTABLE(${APP_NAME} ${SYSTEM_UI_SRC_LIST})

#----INC
INCLUDE_DIRECTORIES("app")
