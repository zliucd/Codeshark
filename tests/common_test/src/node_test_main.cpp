/*
 ============================================================================
 Name        : node_test_main.cpp
 Description : node test main program
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <iostream>

#include "common_test/include/node_test.h"

using namespace std;

int main(int argc, char *argv[])
{
    printf("=== common test ===\n");

    // test functions implemented in other cpp files within same directory
    // Do not write test code in this file
    test_node_init();

    printf("[SUCCESS] common test\n");

}