/*
 ============================================================================
 Name        : tree_test.h
 Description : tree test implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <stdio.h>
#include <assert.h>

#include "datastructures/include/tree.h"
#include "datasturectures_test/include/tree_test.h"

TreeTest::TreeTest()
{

}

TreeTest::~TreeTest()
{

}

void TreeTest::test_main()
{
    BTree *btree;
    LinkList *list;
    string s;
    int ret;

    // empty tree
    btree = new BTree();
    ret = btree->create_by_level(0);
    assert (ret > 0);
    delete(btree);

    //  test preorder traversal
    //  tree with one node
    btree = new BTree();
    ret = btree->create_by_level(1);
    assert (ret == 0);
    btree->print(PREORDER, s);
    assert (s == "1");
    delete(btree);

    // tree with many nodes
    btree = new BTree();
    ret = btree->create_by_level(7);
    assert (ret == 0);
    btree->print(PREORDER, s);
    assert (s == "1,2,4,5,3,6,7");
    delete(btree);

    printf("[SUCCESS] Btree preorder recursive traversal\n");

    ////////////////////////////////////////
    //  test inorder traversal
    //  tree with one node
    btree = new BTree();
    ret = btree->create_by_level(7);
    assert (ret == 0);
    btree->print(INORDER, s);
    assert (s == "4,2,5,1,6,3,7");
    delete(btree);

    printf("[SUCCESS] Btree inorder recursive traversal\n");

    //  test post traversal
    btree = new BTree();
    ret = btree->create_by_level(7);
    assert (ret == 0);
    btree->print(POSTORDER, s);
    assert (s == "4,5,2,6,7,3,1");
    delete(btree);

    printf("[SUCCESS] Btree postorder recursive traversal\n");
}

void cpp_tree_test_main()
{
    printf("\n=== Binary tree test ===\n");

    TreeTest *tree_test = new TreeTest();
    tree_test->test_main();
    delete(tree_test);
}

void test_tree_main()
{
    test_tree_create();
    test_tree_traverse_level();
}

static void test_tree_create()
{
    cshark_btree_t *root;

    cshark_btree_create(&root, 9);
    _cshark_btree_traverse_preorder_recur(root);
    cshark_btree_destroy(root);

    printf("[PASSED] btree_create()\n");
}

static void test_tree_traverse_level()
{
    cshark_btree_t *root;
    cshark_linklist_t *nodes_list;
    size_t n;

    nodes_list = NULL;
    cshark_btree_create(&root, 10);
    _cshark_btree_traverse_level(root, &n, &nodes_list);

    cshark_linklist_print(nodes_list);

    cshark_btree_destroy(root);
    cshark_linklist_destroy(nodes_list);
}
