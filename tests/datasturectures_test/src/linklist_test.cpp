/*
 ============================================================================
 Name        : linklist_test.cpp
 Description : linklist test implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <cassert>

#include "common/include/node.h"
#include "common/include/err.h"
#include "datastructures/include/linklist.h"
#include "datasturectures_test/include/linklist_test.h"

TestLinkList::TestLinkList(size_t small, size_t big)
{
    this->n_small = small;
    this->n_big = big;

}

TestLinkList::~TestLinkList()
{

}

void TestLinkList::test_main()
{
    this->test_common();
    this->test_find();
    this->test_insert();
    this->test_delete();
    this->test_pop();
}

void TestLinkList::test_common()
{
    cshark_node_t *nt;
    LinkList *empty_list;
    LinkList *small_list;

    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    // empty list
    assert (empty_list->get_first() == NULL and empty_list->get_last() == NULL);
    assert (empty_list->get_size() == 0);

    // small list
    nt = small_list->get_first();
    assert (nt != NULL and nt->val == 0);

    nt = small_list->get_last();
    assert (nt != NULL and nt->val == (this->n_small - 1));
    assert (small_list->get_size() == this->n_small);

    delete(empty_list);
    delete(small_list);

    printf("[SUCCESS] Linklist common[getsize(), get_first(), get_last()]\n");
}

void TestLinkList::test_find()
{
    cshark_node_t *nt;
    LinkList *empty_list;
    LinkList *small_list;

    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    // test find_by_pos
    nt = small_list->find_by_pos(0);
    assert (nt != NULL and nt->val == 0);

    nt = small_list->find_by_pos(5);    // max position: size - 1
    assert (nt != NULL and nt->val == 5);

    nt = small_list->find_by_pos(9);
    assert (nt != NULL and nt->val == 9);

    nt = small_list->find_by_pos(10);
    assert (nt == NULL);

    // test find_by_val
    nt = small_list->find_by_val(0);  // value starting from 1
    assert (nt != NULL and nt->val == 0);

    nt = small_list->find_by_val(5);
    assert (nt != NULL and nt->val == 5);

    nt = small_list->find_by_val(9);
    assert (nt != NULL and nt->val == 9);

    nt = small_list->find_by_val(10);
    assert (nt == NULL);

    nt = small_list->find_by_val(11);
    assert (nt == NULL);

    delete(empty_list);
    delete(small_list);

    printf("[SUCCESS] Linklist find[find_by_pos(), find_by_val()]\n");
}

void TestLinkList::test_insert()
{
    cshark_node_t *nt;
    cshark_node_t *nt2;
    cshark_node_t *last;
    size_t m;
    LinkList *empty_list;
    LinkList *small_list;

    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    nt = cshark_node_init();
    nt->val = 0x20ce;

    nt2 = cshark_node_init();
    nt2->val = 0xbc90;

    m = small_list->get_size();

    small_list->insert_node(nt);
    last = small_list->get_last();
    assert (small_list->get_size() == (m + 1));
    assert (last != NULL and last->val == 0x20ce);

    small_list->insert_val(0xbdfe);
    last = small_list->get_last();
    assert (small_list->get_size() == (m + 2));
    assert (last != NULL and last->val == 0xbdfe);

    // empty list
    m = empty_list->get_size();
    assert (m == 0);

    empty_list->insert_node(nt2);
    last = empty_list->get_last();
    assert (empty_list->get_size() == (m + 1));
    assert (last != NULL and last->val == 0xbc90);

    empty_list->insert_val(0x690f);
    last = empty_list->get_last();
    assert (empty_list->get_size() == (m + 2));
    assert (last != NULL and last->val == 0x690f);

    delete(empty_list);
    delete(small_list);
    printf("[SUCCESS] Linklist insert[insert_node(), insert_val()]\n");
}

void TestLinkList::test_delete()
{
    cshark_node_t *nt0;
    cshark_node_t *nt1;
    cshark_node_t *nt2;
    int val0, status;
    size_t n, tmp;
    LinkList *empty_list;
    LinkList *small_list;

    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    nt0 = small_list->find_by_pos(0);
    nt1 = small_list->find_by_pos(1);
    n = small_list->get_size();
    val0 = nt0->val;

    status = small_list->delete_by_pos(0);
    assert (status == SUCCESS);
    assert (small_list->get_size() == (n - 1));
    assert (small_list->get_first()->val == nt1->val);
    assert (small_list->find_by_val(val0) == NULL);

    nt2 = small_list->find_by_pos(small_list->get_size() - 2);
    nt1 = small_list->find_by_pos(small_list->get_size() - 1);
    val0 = nt1->val;

    status = small_list->delete_by_pos(small_list->get_size() - 1);  // delete last
    assert (status == SUCCESS);
    assert (small_list->get_size() == (n - 2));
    assert (small_list->get_last()->val == nt2->val);
    assert (small_list->find_by_val(val0) == NULL);

    n = small_list->get_size();
    status = small_list->delete_by_pos(n);
    assert (status = ERROR_PARAM);

    // empty list
    status = empty_list->delete_by_pos(0);
    assert (status == ERROR_PARAM);

    delete(empty_list);
    delete(small_list);

    // test delete first and last for small list
    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    status = small_list->delete_first();
    assert (status == SUCCESS);
    assert (small_list->get_size() == this->n_small - 1);
    assert (small_list->get_first()->val == 1);

    status = small_list->delete_last();
    assert (status == SUCCESS);
    assert (small_list->get_size() == this->n_small - 2);
    assert (small_list->get_last()->val == 8);

    // test delete first and last for empty list
    status = empty_list->delete_first();
    assert (status == ERROR_PARAM);
    status = empty_list->delete_last();
    assert (status == ERROR_PARAM);

    delete(empty_list);
    delete(small_list);

    printf("[SUCCESS] Linklist delete[delete_pos(), delete_first(), delete_last()]\n");
}

void TestLinkList::test_pop()
{
    cshark_node_t *nt0;
    cshark_node_t *nt1;
    cshark_node_t *nt2;

    LinkList *empty_list;
    LinkList *small_list;

    empty_list = new LinkList(0);
    small_list = new LinkList(this->n_small);

    nt0 = small_list->pop_first();
    assert (nt0 != NULL and nt0->val == 0);
    nt1 = small_list->pop_last();
    assert (nt1 != NULL and nt1->val == 9);

    assert(small_list->get_size() == 8 and small_list->get_first()->val == 1 and small_list->get_last()->val == 8);

    nt2 = small_list->pop_by_pos(10);
    assert (nt2 == NULL);

    delete(nt0);
    delete(nt1);

    // empty list
    nt0 = empty_list->pop_first();
    assert (nt0 == NULL );
    nt1 = empty_list->pop_last();
    assert (nt1 == NULL);

    delete(empty_list);
    delete(small_list);

    printf("[SUCCESS] Linklist pop[pop_first(), pop_last()]\n");
}

/**
 * Linklist test entrance function
 */
void cpp_test_linklist_main()
{
    printf("=== Linklist test ===\n");

    TestLinkList *test_list = new TestLinkList(10, 1000);
    test_list->test_main();
    delete(test_list);
}

/**
 * Stub of linklist test functions
 */
void test_linklist_main()
{
    test_linklist_init();
    test_linklist_add();
    test_linklist_allocate();
    test_linklist_copy();
    test_linklist_add();
    test_linklist_insert();
    test_linklist_reverse();

    test_linklist_find_val();
    test_linklist_find_pos();
    test_linklist_find_first();
    test_linklist_find_last();

    test_linklist_delete_first();
    test_linklist_delete_last();
    test_linklist_delete_val();
    test_linklist_delete_pos();
    test_linklist_pop_first();
    test_linklist_pop_last();
}

/**
 * Test linklist initialization function
 */
static void test_linklist_init()
{
    cshark_linklist_t *llt;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    assert (llt != NULL and llt->head->name == "head" and llt->first == NULL and llt->last == llt->head);
    assert (cshark_linklist_getsize(llt) == 0);

    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 10
    llt = cshark_linklist_init(10);
    assert (llt != NULL and llt->first->val == 1 and llt->last->val == 10);
    assert (cshark_linklist_getsize(llt) == 10);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: MAX_NODES
    llt = cshark_linklist_init(MAX_NODES);
    assert (llt != NULL and cshark_linklist_getsize(llt) == MAX_NODES);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: MAX+NODES + 1, which should return NULL
    llt = cshark_linklist_init(MAX_NODES + 1);
    assert (llt == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 2 *MAX_NODES, which should return NULL
    llt = cshark_linklist_init(MAX_NODES * 2);
    assert (llt == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_init() and cshark_linklist_destroy()\n");
}

/**
 * Test linklist allocating function
 */
static void test_linklist_allocate()
{
    cshark_linklist_t *llt;
    llt = cshark_linkist_allocate();

    assert(cshark_linklist_getsize(llt) == 0);
    assert(llt->head->name == "head");
    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_allocate()\n");
}

/**
 * Test linklist copy function
 */
static void test_linklist_copy()
{
    cshark_linklist_t *llt;
    cshark_linklist_t *new_llt;
    cshark_node_t *nt;
    cshark_node_t *new_nt;
    int i;
    size_t n;

    n = 10;
    llt = cshark_linklist_init(n);
    new_llt = cshark_linklist_copy(llt);

    nt = llt->head->next;
    new_nt = llt->head->next;
    for (i = 0; i < n; i++)
    {
        assert (nt->val == new_nt->val);
    }

    n = cshark_linklist_getsize(new_llt);
    assert (new_llt != NULL and n == n);

//    nt = cshark_linklist_find_pos(new_llt, n);
//    assert (nt != NULL and nt->val == n);

    cshark_linklist_destroy(llt);
    llt = NULL;
    cshark_linklist_destroy(new_llt);
    new_llt = NULL;

    // test invalid copy
    llt = NULL;
    new_llt = cshark_linklist_copy(llt);
    assert (new_llt == NULL);

    printf("[PASSED] cshark_linklist_copy()\n");
}

/**
 * Test linklist destroy function
 * @param llt [in] link list to destroy
 */
static void test_linklist_destroy(cshark_linklist_t *llt)
{
    // this function is tested with ASAN for memory leak and other memory issues
}

/**
 * Test linklist adding node function
 */
static void test_linklist_add()
{
    cshark_linklist_t *llt;
    int status;

    llt = cshark_linklist_init(0);
    status = cshark_linklist_add(llt, 5);
    assert (status == SUCCESS and llt->first->val == 5 and llt->last->val == 5);
    cshark_linklist_destroy(llt);

    llt = cshark_linklist_init(10);
    status = cshark_linklist_add(llt, 20);
    assert (status == SUCCESS and llt->first->val == 1 and llt->last->val == 20);
    cshark_linklist_destroy(llt);

    // test MAX_NODES + 1
    llt = cshark_linklist_init(MAX_NODES);
    status = cshark_linklist_add(llt, 0xff);
    assert (status == ERROR_MAX_NODES and cshark_linklist_getsize(llt) == MAX_NODES);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_add()\n");
}

/**
 * Test linklist inserting node function
 */
static void test_linklist_insert()
{
    cshark_linklist_t *llt;
    int status;
    cshark_node_t *new_node;

    new_node = cshark_node_init();
    new_node->val = 50;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    status = cshark_linklist_insert(llt, new_node);
    assert (status == SUCCESS and llt->first->val == 50 and llt->last->val == 50);
    cshark_linklist_destroy(llt);

    // new_node has been freed in cshark_linklist_destroy(llt), so allocate again
    new_node = cshark_node_init();
    new_node->val = 50;

    // #nodes: 10
    llt = cshark_linklist_init(10);
    status = cshark_linklist_insert(llt, new_node);
    assert (status == SUCCESS and llt->first->val == 1 and llt->last->val == 50);
    cshark_linklist_destroy(llt);

    // #nodes: MAX_NODES
    llt = cshark_linklist_init(MAX_NODES);
    status = cshark_linklist_insert(llt, new_node);
    assert (status == ERROR_MAX_NODES and cshark_linklist_getsize(llt) == MAX_NODES);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_insert()\n");
}

/**
 * Test linklist finding value function
 */
static void test_linklist_find_val()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;
    int  v;

    llt = cshark_linklist_init(MAX_NODES);

    // test finding valid value
    v = 3000;
    nt = cshark_linklist_find_val(llt, v);
    assert (nt != NULL and nt->val == v);

    // test finding invalid value
    v = MAX_NODES + 5;
    nt = cshark_linklist_find_val(llt, v);

    assert (nt == NULL);
    cshark_linklist_destroy(llt);

    // empty linklist
    llt = cshark_linklist_init(0);
    nt = cshark_linklist_find_val(llt, 0);
    assert (nt == NULL);

    // single-node list
    nt = cshark_linklist_find_val(llt, 1);
    assert (nt == NULL);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_find_val()\n");
}

/**
 * Test linklist finding node by position function
 */
static void test_linklist_find_pos()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    nt = cshark_linklist_find_pos(llt, 0);
    assert (nt == NULL);

    // #nodes: 1
    nt = cshark_linklist_find_pos(llt, 1);
    assert (nt == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 1
    llt = cshark_linklist_init(1);
    nt = cshark_linklist_find_pos(llt, 1);
    assert (nt != NULL and nt->val == 1);
    cshark_linklist_destroy(llt);

    // #nodes: 100
    llt = cshark_linklist_init(100);
    nt = cshark_linklist_find_pos(llt, 25);
    assert (nt != NULL and nt->val == 25);

    nt = cshark_linklist_find_pos(llt, 101);
    assert (nt == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: MAX_NODES
    llt = cshark_linklist_init(MAX_NODES);
    nt = cshark_linklist_find_pos(llt, MAX_NODES);
    assert (nt != NULL and nt->val == MAX_NODES);

    nt = cshark_linklist_find_pos(llt, MAX_NODES + 1);
    assert (nt == NULL);

    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_find_pos()\n");
}

/**
 * Test linklist deleting node by value function
 */
static void test_linklist_delete_val()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;
    int status;

    // #nodes: 1
    llt = cshark_linklist_init(1);
    status = cshark_linklist_delete_val(llt, 1);
    assert (status == SUCCESS and cshark_linklist_getsize(llt) == 0 and llt->first == NULL and llt->last == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 100
    llt = cshark_linklist_init(100);
    status = cshark_linklist_delete_val(llt, 1);
    assert (status == SUCCESS and cshark_linklist_getsize(llt) == 99 and llt->first->val == 2 and llt->last->val == 100);
    status = cshark_linklist_delete_val(llt, 1);

    assert (status == ERROR_NOT_FOUND and cshark_linklist_getsize(llt) == 99 and llt->first->val == 2 and llt->last->val == 100);
    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_delete_val()\n");
}

/**
 * Test linklist deleting node by position function
 */
static void test_linklist_delete_pos()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;
    int status, val;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    status = cshark_linklist_delete_pos(llt, 0, &val);
    assert (status == ERROR_PARAM);
    cshark_linklist_destroy(llt);

    // #nodes: 1
    llt = cshark_linklist_init(1);
    status = cshark_linklist_delete_pos(llt, 1, &val);
    assert (status == SUCCESS and val == 1 and cshark_linklist_getsize(llt) == 0
            and llt->first == NULL and llt->last == NULL);
    cshark_linklist_destroy(llt);

    // #nodes: 100
    llt = cshark_linklist_init(10);
    status = cshark_linklist_delete_pos(llt, 5, &val);
    assert (status == SUCCESS and val == 5 and cshark_linklist_getsize(llt) == 9
            and llt->first->val == 1 and llt->last->val == 10);
    nt = cshark_linklist_find_val(llt, 5);
    assert (nt == NULL);

    status = cshark_linklist_delete_pos(llt, 9, &val);
    assert (status == SUCCESS and val == 10 and cshark_linklist_getsize(llt) == 8
            and llt->first->val == 1 and llt->last->val == 9);

    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_delete_pos()\n");
}

/**
 * Test linklist reverse function
 */
static void test_linklist_reverse()
{
    cshark_linklist_t *llt;
    int status, i;
    cshark_node_t *nt;
    size_t n;

    n = 10;
    llt = cshark_linklist_init(n);
    status = cshark_linklist_reverse(llt);
    assert (status == SUCCESS);

    nt = llt->head->next;
    i = 10;
    while (nt != NULL)
    {
        assert (nt->val == (i--));
        nt = nt->next;
    }

    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_reverse()\n");
}

/**
 * Test linklist finding first function
 */
static void test_linklist_find_first()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    nt = cshark_linklist_get_first(llt);
    assert (nt == NULL);
    cshark_linklist_destroy(llt);

    // #nodes: 1
    llt = cshark_linklist_init(1);
    nt = cshark_linklist_get_first(llt);
    assert (nt != NULL and nt->val == 1);
    cshark_linklist_destroy(llt);

    // #nodes: 10
    llt = cshark_linklist_init(100);
    nt = cshark_linklist_get_first(llt);
    assert (nt != NULL and nt->val == 1);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_find_first()\n");
}

/**
 * Test linklist finding last function
 */
static void test_linklist_find_last()
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    nt = cshark_linklist_get_first(llt);
    assert (nt == NULL);
    cshark_linklist_destroy(llt);

    // #nodes: 1
    llt = cshark_linklist_init(1);
    nt = cshark_linklist_get_last(llt);
    assert (nt != NULL and nt->val == 1);
    cshark_linklist_destroy(llt);

    // #nodes: 100
    llt = cshark_linklist_init(100);
    nt = cshark_linklist_get_last(llt);
    assert (nt != NULL and nt->val == 100);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_find_last()\n");
}

/**
 * Test linklist delete first node function
 */
static void test_linklist_delete_first()
{
    cshark_linklist_t *llt;
    int status, val;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    status = cshark_linklist_delete_first(llt, &val);
    assert (status == ERROR_TARGET_EMPTY);
    assert (cshark_linklist_getsize(llt) == 0 and llt->first == NULL and llt->last == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 1
    llt = cshark_linklist_init(1);
    status = cshark_linklist_delete_first(llt, &val);
    assert (status == SUCCESS);
    assert (val == 1 and cshark_linklist_getsize(llt) == 0 and llt->first == NULL and llt->last == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;

    // #nodes: 100
    llt = cshark_linklist_init(100);
    status = cshark_linklist_delete_first(llt, &val);
    assert (status == SUCCESS);
    assert (val == 1 and cshark_linklist_getsize(llt) == 99 and llt->first->val == 2 and llt->last->val == 100);
    cshark_linklist_destroy(llt);
    llt = NULL;

    printf("[PASSED] cshark_linklist_delete_first()\n");
}

/**
 * Test linklist delete last node function
 */
static void test_linklist_delete_last()
{
    cshark_linklist_t *llt;
    int status, val;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    status = cshark_linklist_delete_last(llt, &val);
    assert (status != SUCCESS);
    assert (cshark_linklist_getsize(llt) == 0);
    cshark_linklist_destroy(llt);

    // #nodes: 1
    llt = cshark_linklist_init(1);
    status = cshark_linklist_delete_last(llt, &val);
    assert (status == SUCCESS);
    assert (val == 1 and cshark_linklist_getsize(llt) == 0);
    cshark_linklist_destroy(llt);

    // #nodes: 100
    llt = cshark_linklist_init(100);
    status = cshark_linklist_delete_last(llt, &val);
    assert (status == SUCCESS);
    assert (val == 100 and cshark_linklist_getsize(llt) == 99 and llt->last->val == 99);
    cshark_linklist_destroy(llt);

    printf("[PASSED] cshark_linklist_delete_last()\n");
}

/**
 * Test linklist pop first function
 */
static void test_linklist_pop_first()
{
    cshark_linklist_t *llt;
    cshark_node_t *node;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    node = cshark_linklist_pop_first(llt);
    assert (node == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);      // delete anyway

    // #nodes: 1
    llt = cshark_linklist_init(1);
    node = cshark_linklist_pop_first(llt);
    assert (node != NULL and node->val == 1 and cshark_linklist_getsize(llt) == 0
            and llt->first == NULL and llt->last == NULL);

    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);

    // #nodes: 10
    llt = cshark_linklist_init(10);
    node = cshark_linklist_pop_first(llt);
    assert (node != NULL and node->val == 1 and cshark_linklist_getsize(llt) == 9
            and cshark_linklist_get_first(llt)->val == 2 and cshark_linklist_get_last(llt)->val == 10);
    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);

    printf("[PASSED] cshark_linklist_pop_first()\n");
}

/**
 * Test linklist pop last node function
 */
static void test_linklist_pop_last()
{
    cshark_linklist_t *llt;
    cshark_node_t *node;

    // #nodes: 0
    llt = cshark_linklist_init(0);
    node = cshark_linklist_pop_last(llt);
    assert (node == NULL);
    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);

    // #nodes: 1
    llt = cshark_linklist_init(1);
    node = cshark_linklist_pop_last(llt);
    assert (node != NULL and node->val == 1 and cshark_linklist_getsize(llt) == 0);
    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);

    // #nodes: 10
    llt = cshark_linklist_init(10);
    node = cshark_linklist_pop_last(llt);
    assert (node != NULL and node->val == 10 and cshark_linklist_getsize(llt) == 9
            and llt->first->val == 1 and llt->last->val == 9);
    cshark_linklist_destroy(llt);
    llt = NULL;
    delete(node);

    printf("[PASSED] cshark_linklist_pop_last()\n");
}
