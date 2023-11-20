/*
 ============================================================================
 Name        : tree.h
 Description : tree header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_TREE_H
#define CODESHARK_TREE_H

#include "common/include/node.h"
#include "datastructures/include/linklist.h"

enum ORDER_TYPE {
    PREORDER = 1,
    INORDER = 2,
    POSTORDER = 4,
    LEVELORDER = 8
};

/**
 * BTree maintains binary tree structure
 */
class BTree
{
private:
    cshark_node_t *root;    // root node
    cshark_node_t **nodes;  // initiated in tree building, deleted in BTree()

public:
    BTree();
    ~BTree();
    int create_by_level(size_t n);

    void print(ORDER_TYPE, string &);
    void get_size();
    cshark_node_t *get_root();

    void traverse_preorder(LinkList **list);
    void traverse_inorder(LinkList **list);
    void traverse_postorder(LinkList **list);

    // Shall we put these functions outside of BTree class?
    void internal_trav_preorder(cshark_node_t *p, LinkList *list);
    void internal_trav_inorder(cshark_node_t *p, LinkList *list);
    void internal_trav_postorder(cshark_node_t *p, LinkList *list);

    void internal_trav_preorder_nonrecur();
};


typedef cshark_node_t cshark_btree_t;

// Tree functions

int cshark_btree_create(cshark_btree_t **bt, size_t n);
int cshark_btree_destroy(cshark_btree_t *bt);

void _cshark_btree_traverse_preorder_recur(cshark_btree_t *bt);
int _cshark_btree_traverse_level(cshark_btree_t *bt, size_t *n, cshark_linklist_t **nodes_list);

#endif //CODESHARK_TREE_H
