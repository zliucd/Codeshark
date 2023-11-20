#============================================================================
#Name        : CMakeLists.txt
#Description : Top-level CMakeLists file
#Author      : Zhi Liu<zliucd66@gmail.com>
#Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
#              see LICENSE.txt.
#============================================================================

cmake_minimum_required(VERSION 3.18)
project(CodeShark)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(CODESHARK_CXX_STANDARD ${CMAKE_CXX_STANDARD})
set(CODESHARK_BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(CODESHARK_ENABLE_ASAN 1)

message("Building environment:")
message("=== Compiler: ${CMAKE_CXX_COMPILER}")
message("=== Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
message("=== CXX standard: ${CMAKE_CXX_STANDARD}")

message("=== Type: ${CMAKE_BUILD_TYPE}")

if (${CODESHARK_BUILD_TYPE} STREQUAL "Debug" AND ${CODESHARK_ENABLE_ASAN} EQUAL 1)
    message("=== Address Sanitizer: enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
else()
    message("=== Address Sanitizer: disabled")
endif()

message("Building codeshark")

add_subdirectory(src)
add_subdirectory(tests)

add_dependencies(common_test libcodeshark)
add_dependencies(datastructures_test libcodeshark)

