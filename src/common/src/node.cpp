/*
 ============================================================================
 Name        : node.cpp
 Description : node source file
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include "common/include/node.h"
#include "common/include/err.h"


/**
 * Create and init a new node, which must be manually freed.
 * @return a new node
 */
cshark_node_t *cshark_node_init()
{
    // assume node can always be successfully allocated
    cshark_node_t *nt = new cshark_node_t();

    nt->val = 0xdeadbeef;
    nt->name = "unused";
    nt->visited = false;

    nt->prev = NULL;
    nt->next = NULL;
    nt->left = NULL;
    nt->right = NULL;

    return nt;
}

/**
 * Copy a node, and the dest node must also has been created.
 * @param src  [in] source node
 * @param dest [in,out] dest node
 * @return SUCCESS on success, or other error code
 */
int cshark_node_copy(cshark_node_t *src, cshark_node_t *dest)
{
    if (src == NULL or dest == NULL)
    {
        return ERROR_PARAM;
    }

    dest->name = src->name;
    dest->val = src->val;

    return SUCCESS;
}

/**
 * Free a node
 * @param nt [in] node pointer
 */
void cshark_node_free(cshark_node_t *nt)
{
    delete(nt);
}