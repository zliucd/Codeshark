/*
 ============================================================================
 Name        : tree.cpp
 Description : tree implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <assert.h>

#include "common/include/err.h"
#include "datastructures/include/tree.h"
#include "datastructures/include/stack.h"
#include "datastructures/include/queue.h"

/**
 * Binary tree constructor
 */
BTree::BTree()
{
    this->root = NULL;
    nodes = NULL;
}

/**
 * Delete all nodes of the tree. Make sure memory is freed cleanly.
 */
BTree::~BTree()
{
    LinkList *list;

    // delete all nodes including root
    // you may also use 'inorder' and 'postorder' to facilitate deallocation
    if (this->nodes == NULL)
    {
        assert (this->root == NULL);
        return;
    }

    this->traverse_preorder(&list);
    delete(list);

    // 'nodes' should be explicitly freed!
    // do not use 'delete nodes;', which could cause memory leak.
    delete [](this->nodes);
}

/**
 * Create a binary tree from scratch horizontally like this:
 *           1
 *        /     \
 *     2          3
 *    / \         / \
 *  4     5     6     7
 *
 * \warning: caller must manually free the binary tree, e.g.,
 * @param n [in] number of nodes including root
 */
int BTree::create_by_level(size_t n)
{
    cshark_node_t *p;
    size_t i, l, r;

    if (n == 0)
    {
        return ERROR_PARAM;
    }

    // Do not use malloc(), as the memory will be released by delete()
    // e.g., nodes = (cshark_node_t **)malloc(sizeof(cshark_node_t *) * n);
    nodes = new cshark_node_t*[n];
    for (i = 0; i < n; i++)
    {
        nodes[i] = cshark_node_init();
        p = nodes[i];
        p->val = i + 1;
        p->left = NULL;
        p->right = NULL;
        p->next = NULL;
        p->prev = NULL;
    }

    for (i = 0; i < n; i++)
    {
        p = nodes[i];
        l = 2 * (i + 1);
        r = 2 * (i + 1) + 1;

        if (l <= n)
        {
            p->left = nodes[l - 1];
        }
        if (r <= n)
        {
            p->right = nodes[r - 1];
        }
    }

    this->root = nodes[0];

    return SUCCESS;
}


/**
 * Traverse the tree in preorder, and save all nodes in a list
 * \warning The caller should explicitly delete the list; before deletion, detach the head from list.
 * @param list [out] linklist, which is allocated inside the function, and deallocated by caller
 */
void BTree::traverse_preorder(LinkList **list)
{
    LinkList *clist = new LinkList(0);  // make an empty list

    this->internal_trav_preorder(this->root, clist);
    *list = clist;
}

/**
 * Traverse the tree inorder, and put all traversed nodes orderly in a linklist
 * \note The list should be allocated with head before calling, deleting the list should only
 *       delete the head node.
 * @param p [in] curr node
 * @param list [in] linklist
 *
 */
void BTree::internal_trav_preorder(cshark_node_t *p, LinkList *list)
{
    if (p == NULL)
    {
        return;
    }

    list->insert_node(p);
    this->internal_trav_preorder(p->left, list);
    this->internal_trav_preorder(p->right, list);
}

/**
 * Traverse the tree in preorder, and save all nodes in a list
 * \warning The caller should explicitly delete the list; before deletion, detach the head from list.
 * @param list [out] linklist, which is allocated inside the function, and deallocated by caller
 */
void BTree::traverse_inorder(LinkList **list)
{
    LinkList *clist = new LinkList(0);  // make an empty list

    this->internal_trav_inorder(this->root, clist);
    *list = clist;
}

/**
 * Traverse the tree inorder, and put all traversed nodes orderly in a linklist
 * \note The list should be allocated with head before calling, deleting the list should only
 *       delete the head node.
 * @param p [in] curr node
 * @param list [in] linklist
 */
void BTree::internal_trav_inorder(cshark_node_t *p, LinkList *list)
{
    if (p == NULL)
    {
        return;
    }

    internal_trav_inorder(p->left, list);
    list->insert_node(p);
    internal_trav_inorder(p->right, list);
}


/**
 * Traverse the tree in preorder, and save all nodes in a list
 * \warning The caller should explicitly delete the list; before deletion, detach the head from list.
 * @param list [out] linklist, which is allocated inside the function, and deallocated by caller
 */
void BTree::traverse_postorder(LinkList **list)
{
    LinkList *clist = new LinkList(0);  // make an empty list

    this->internal_trav_postorder(this->root, clist);
    *list = clist;
}

/**
 * Traverse the tree inorder, and put all traversed nodes orderly in a linklist
 * \note The list should be allocated with head before calling, deleting the list should only
 *       delete the head node.
 * @param p [in] curr node
 * @param list [in] linklist
 *
 */
void BTree::internal_trav_postorder(cshark_node_t *p, LinkList *list)
{
    if (p == NULL)
    {
        return;
    }

    internal_trav_postorder(p->left, list);
    internal_trav_postorder(p->right, list);
    list->insert_node(p);
}


/**
 * Print a linklist in certain traverse order type, and save node's value in string
 * @param order [in] order type
 * @param s [in,out] printing results in form of "1,2,3,4,5,6,7"
 */
void BTree::print(ORDER_TYPE order, string &s)
{
    LinkList *list;
    cshark_node_t *p;

    list = new LinkList(0);  // only head

    if (order == PREORDER)
    {
        this->internal_trav_preorder(this->root, list);
    }
    else if (order == INORDER)
    {
        this->internal_trav_inorder(this->root, list);
    }
    else
    {
        this->internal_trav_postorder(this->root, list);
    }

    s = "";
    p = list->get_first();
    while (p != NULL)
    {
        if (s == "" )  // first node
        {
            s += to_string(p->val);
        }
        else if (p->next == NULL)  // last node
        {
            s += (","  + to_string(p->val));
        }
        else
        {
            s += ("," + to_string(p->val));
        }
        p = p->next;
    }

    list->detach_head();
    delete(list);
}

cshark_node_t* BTree::get_root()
{
    return this->root;
}


/**
 * Create a binary tree from scratch using n nodes like this:
 *           1
 *        /     \
 *     2          3
 *    / \         / \
 *  4     5     6     7
 *
 * \warning: caller must manually free the binary tree, e.g.,
 *
 * @param btree [out] root note to be created
 * @param n [in] number of nodes
 * @return \0 on success
 */
int cshark_btree_create(cshark_btree_t **bt, size_t n)
{
    int i, l, r;
    cshark_btree_t **nodes;
    cshark_btree_t *p;

    if (bt == NULL)
    {
        return ERROR_PARAM;
    }

    nodes = (cshark_btree_t **)malloc(sizeof(cshark_btree_t *) * n);
    for (i = 0; i < n; i++)
    {
        nodes[i] = cshark_node_init();
        p = nodes[i];
        p->val = i + 1;
        p->left = NULL;
        p->right = NULL;
    }

    for (i = 0; i < n; i++)
    {
        p = nodes[i];

        l = 2 * (i + 1);
        r = 2 * (i + 1) + 1;

        if (l <= n)
        {
            p->left = nodes[l - 1];
        }
        if (r <= n)
        {
            p->right = nodes[r - 1];
        }
    }

    *bt = nodes[0];
    return SUCCESS;
}


/**
 * Destroy a binary tree and its allocated memory footprints
 * @param bt [in] binary tree
 */
int cshark_btree_destroy(cshark_btree_t *bt)
{
    // TODO
    if (bt == NULL)
    {
        return ERROR_PARAM;
    }


    return SUCCESS;
}

/**
 * Traverse a tree in a horizontal(level-hierarchy) way
 * @param bt [in] root node of the binary tree
 * @param n [out] number of nodes in this tree
 * @param nodeslist [out] nodes linklist
 * \warning memory of nodes in nodeslist are allocated, which must be manually freed by the caller.
 *
 * @return 0 on success
 */
int _cshark_btree_traverse_level(cshark_btree_t *bt, size_t *n, cshark_linklist_t **nodes_list)
{
    cshark_queue *queue;
    cshark_node_t *curr;
    cshark_node_t *clone;
    cshark_btree_t *left;
    cshark_btree_t *right;
    cshark_linklist_t *nodeslist;
    int v, num;

    if (bt == NULL or n == NULL or nodeslist == NULL)
    {
        return ERROR_PARAM;
    }

    /* nodeslist must be manually freed by caller, even if it's empty with only root */
    nodeslist = cshark_linklist_init(0);
    num = 0;

    queue = cshark_queue_init();
    cshark_queue_insert(queue, bt);
    while (1)
    {
        curr = cshark_queue_visit(queue);
        if (curr != NULL)
        {
            // cshark_queue_remove_clone() will free "curr" node, so save left and right
            left = curr->left;
            right = curr->right;
            cshark_queue_remove_clone(queue, &clone);
            cshark_linklist_insert(nodeslist, clone);
            num++;

            if (left != NULL)
            {
                cshark_queue_insert(queue, left);
            }
            if (right != NULL)
            {
                cshark_queue_insert(queue, right);
            }
        }
        else
        {
            break;    /* no more nodes in queue */
        }
    }

    *nodes_list = &nodeslist[0];
    *n = num;

    return SUCCESS;
}


/**
 * Traverse a binary tree in preorder recursively, and also print each node's value
 * @param bt p[in] binary tree
 * @return number of nodes, < 0 indicating input is invalid
 */
void _cshark_btree_traverse_preorder_recur(cshark_btree_t *bt)
{
    if (bt == NULL)
    {
        return;
    }

    printf("%d ", bt->val);
    _cshark_btree_traverse_preorder_recur(bt->left);
    _cshark_btree_traverse_preorder_recur(bt->right);
}

/**
 * Traverse a binary tree non-recursively
 *  Time complexity: O(N)
 *  Space complexity: O(N), extra memory usage of stack and visited[]
 */
void BTree::internal_trav_preorder_nonrecur()
{
    // TODO
}


