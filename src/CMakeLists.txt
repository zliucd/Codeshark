#============================================================================
#Name        : CMakeLists.txt
#Description : CMakeLists file for module src
#Author      : Zhi Liu<zliucd66@gmail.com>
#Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
#              see LICENSE.txt.
#============================================================================

cmake_minimum_required(VERSION 3.18)
project(libcodeshark)

message("Building libcodeshark.so")

set(TARGET_NAME libcodeshark)

get_filename_component(ROOT_SRC_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_SRC_DIR}/lib)

add_subdirectory(common)
add_subdirectory(datastructures)

add_library(${TARGET_NAME} SHARED
            $<TARGET_OBJECTS:common>
            $<TARGET_OBJECTS:datastructures>)

# use ".so" as the extension of shared objects
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "" SUFFIX ".so")

include_directories(${ROOT_SRC_DIR}/src)