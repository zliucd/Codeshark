#============================================================================
#Name        : CMakeLists.txt
#Description : CMakeLists file for module data structures
#Author      : Zhi Liu<zliucd66@gmail.com>
#Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
#              see LICENSE.txt.
#============================================================================

cmake_minimum_required(VERSION 3.18)
project(datastructures)

set(TARGET_NAME datastructures)
set(CMAKE_CXX_STANDARD ${CODESHARK_CXX_STANDARD})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp include/*.h)

get_filename_component(UPPER_SRC_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
get_filename_component(ROOT_SRC_DIR ${UPPER_SRC_DIR} DIRECTORY)

message("Building module:data structures")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)      # current project include
include_directories(${UPPER_SRC_DIR})                      # /flowfeat/src
include_directories(${ROOT_SRC_DIR}/external)         # /flowfeat/external

add_library(${TARGET_NAME} OBJECT  ${SOURCES})