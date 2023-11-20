/*
 ============================================================================
 Name        : tree_test.h
 Description : tree_test header
 Author      : Zhi Liu<zliucd66@gmail.com>

 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_TREE_TEST_H
#define CODESHARK_TREE_TEST_H

class TreeTest
{
public:
    TreeTest();
    ~TreeTest();
    void test_main();
};

void cpp_tree_test_main();

void test_tree_main();
static void test_tree_create();
static void test_tree_traverse();
static void test_tree_traverse_level();

#endif //CODESHARK_TREE_TEST_H
