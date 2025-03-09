if(NOT DEFINED APP_NAME)
 set(APP_NAME "ModRTU_slave" CACHE STRING "ModRTU_slave")
 message(STATUS "Use default AppName : ${APP_NAME}")
else()
 message(STATUS "AppName be set: ${APP_NAME}")
endif()

#Debug Release RelWithDebInfo MinSizeRel
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
 add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
 add_definitions(-DRELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
 add_definitions(-MINSIZEREL)
else()
 message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}. Defaulting to Debug.")
 add_definitions(-DDEBUG)
endif()

#遞迴搜索.
#file(GLOB_RECURSE ALL_SRC "*.cpp")


# 漸進式嚴格-Wall -Wextra -pedantic -Werror.
add_compile_options(-Wall)

# cmake版本最低要求.
cmake_minimum_required(VERSION 3.10)
project(${APP_NAME} VERSION 1.0.0 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMODBUS REQUIRED libmodbus)

#STATIC靜態庫 SHARED動態庫.
add_library(SET_LIB SHARED settxt.cpp)

add_executable(${APP_NAME} main.cpp)
target_link_libraries(${APP_NAME} PRIVATE ${LIBMODBUS_LIBRARIES} SET_LIB)

include_directories(${LIBMODBUS_INCLUDE_DIRS})

#設定RPATH讓執行檔能在指定目錄下尋找動態庫($ORIGIN代表執行檔所在目錄).
set_target_properties(${APP_NAME} PROPERTIES BUILD_RPATH "$ORIGIN/lib")
set_target_properties(SET_LIB PROPERTIES BUILD_RPATH "$ORIGIN/lib")





