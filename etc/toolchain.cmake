##########################################################################
# 上海盛本智能科技股份有限公司
# Shanghai Basewin Technology Co.,Ltd.
# All Rights Reserved 2017
##########################################################################
INCLUDE(CMakeForceCompiler)

# 指定目标系统类型及架构类型
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_C_COMPILER_WORKS 1)

# 指定交叉编译器，路径需要使用cygwin形式的路径，否则找不到
SET(TOOLCHAIN_ROOT_PATH "$ENV{TOOLCHAIN_ROOT_PATH}")
SET(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT_PATH}/bin/armcc.exe")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT_PATH}/bin/armcc.exe")
SET(CMAKE_AR "${TOOLCHAIN_ROOT_PATH}/bin/armar.exe" CACHE FILEPATH "Archiver")

#CMAKE_FORCE_C_COMPILER("C:/Program Files (x86)/DS-5/sw/gcc/bin/arm-linux-gnueabihf-gcc.exe" GNU)
#CMAKE_FORCE_CXX_COMPILER("C:/Program Files (x86)/DS-5/sw/gcc/bin/arm-linux-gnueabihf-g++.exe" GNU)

UNSET(CMAKE_C_FLAGS CACHE)
#SET(CMAKE_C_FLAGS "--cpu=ARM926EJ-S --fpu=softvfp" CACHE STRING "" FORCE)
UNSET(CMAKE_CXX_FLAGS CACHE)
#SET(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} CACHE STRING "" FORCE)
UNSET(CMAKE_EXE_LINKER_FLAGS CACHE)
#SET(CMAKE_EXE_LINKER_FLAGS "--cpu=ARM926EJ-S --fpu=softvfp" CACHE STRING "" FORCE)
UNSET(CMAKE_AR_FLAGS CACHE)
#SET(CMAKE_AR_FLAGS "-p -armcc,-Ospace" CACHE STRING "" FORCE)

SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> ${CMAKE_AR_FLAGS} -o <TARGET> <OBJECTS>" CACHE STRING "C Archive Create")
SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> ${CMAKE_AR_FLAGS} -o <TARGET> <OBJECTS>" CACHE STRING "CXX Archive Create")

include_directories("${TOOLCHAIN_ROOT_PATH}/include")

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_ROOT_PATH}")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
