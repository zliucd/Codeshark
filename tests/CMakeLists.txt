#============================================================================
#Name        : CMakeLists.txt
#Description : CMakeLists file for tests
#Author      : Zhi Liu<zliucd66@gmail.com>
#Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
#              see LICENSE.txt.
#============================================================================

cmake_minimum_required(VERSION 3.18)
project(codeshark_test)

message("Building tests")

get_filename_component(ROOT_SRC_DIR  ${PROJECT_SOURCE_DIR} DIRECTORY)
set(CODESHARK_BIN_DIR ${ROOT_SRC_DIR}/bin)

include_directories(${ROOT_SRC_DIR}/src)
include_directories(${ROOT_SRC_DIR}/tests)

add_subdirectory(common_test)
add_subdirectory(datasturectures_test)

