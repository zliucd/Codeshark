#============================================================================
#Name        : CMakeLists.txt
#Description : CMakeLists.txt for common test
#Author      : Zhi Liu<zliucd66@gmail.com>
#Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
#              see LICENSE.txt.
#============================================================================

cmake_minimum_required(VERSION 3.18)
project(commontest)

set(TARGET_NAME common_test)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_executable(${TARGET_NAME} ${SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CODESHARK_BIN_DIR})

target_link_libraries(${TARGET_NAME}
                      ${ROOT_SRC_DIR}/lib/libcodeshark.so)

