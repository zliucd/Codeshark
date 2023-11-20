/*
 ============================================================================
 Name        : linklist_test.h
 Description : linklist test header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_LINKLIST_TEST_H
#define CODESHARK_LINKLIST_TEST_H

#include "datastructures/include/linklist.h"

class TestLinkList
{
private:
    size_t n_small, n_big;

public:
    TestLinkList(size_t small, size_t big);
    ~TestLinkList();

    void test_main();
    void test_common();
    void test_find();

    void test_insert();
    void test_delete();
    void test_pop();
};


void cpp_test_linklist_main();
void test_linklist_main();

static void test_linklist_init();
static void test_linklist_destroy(cshark_linklist_t *llt);
static void test_linklist_allocate();
static void test_linklist_copy();
static void test_linklist_add();
static void test_linklist_insert();
static void test_linklist_find_val();
static void test_linklist_find_pos();
static void test_linklist_delete_val();
static void test_linklist_delete_pos();
static void test_linklist_reverse();

static void test_linklist_find_last();
static void test_linklist_find_first();
static void test_linklist_delete_last();
static void test_linklist_delete_first();
static void test_linklist_pop_first();
static void test_linklist_pop_last();


#endif //CODESHARK_LINKLIST_TEST_H
