/*
 ============================================================================
 Name        : node.h
 Description : node header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_NODE_H
#define CODESHARK_NODE_H

#include <iostream>

using namespace std;

const size_t MAX_NODES = 100000;        // maximum nodes for performance reasons;
                                        // you may increase to reduce it to proper size.

#define MAX_LINKLIST_NODES   MAX_NODES
#define MAX_QUEUE_NODES      MAX_NODES
#define MAX_TREE_NODES       MAX_NODES

/**
 * @struct cshark_node_t
 * note_t is a common data structure used in link list and queue, tree, graph etc.
 * Operations of cshark_node_t is implemented in node.cpp
 */
typedef struct _cshark_node_t
{
    int val;
    string name;                   // reserved
    void *data;                    // reserved
    bool visited;                  // for tree and graph

    struct _cshark_node_t *prev;   // backward pointer for linklist
    struct _cshark_node_t *next;   // forward pointer for linklist
    struct _cshark_node_t *left;   // for tree
    struct _cshark_node_t *right;  // for tree

}cshark_node_t;

// Node functions

cshark_node_t *cshark_node_init();
int cshark_node_copy(cshark_node_t *src, cshark_node_t *dest);
void cshark_node_free(cshark_node_t *nt);

#endif //CODESHARK_NODE_H
