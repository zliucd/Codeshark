/*
 ============================================================================
 Name        : linklist.cpp
 Description : linklist implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <cassert>

#include "common/include/node.h"
#include "common/include/err.h"
#include "datastructures/include/linklist.h"

/**
 * Initialize a link list with given number of nodes
 * @param n [in] number of nodes(not including head), max MAX_LINKLIST_NODES
 *               0 for empty link list with only the head
 * @return valid linklist pointer on success
 *         \NULL on n > MAX_LINKLIST_NODES
 */
cshark_linklist_t *cshark_linklist_init(size_t n)
{
    cshark_linklist_t *llt;
    cshark_node_t *nt;
    int i;

    if (n > MAX_LINKLIST_NODES)
    {
        return NULL;
    }

    llt = cshark_linkist_allocate();
    for (i = 0; i < n; i++)
    {
        nt = cshark_node_init();
        llt->last->next = nt;
        nt->prev = llt->last;
        nt->next = NULL;

        llt->last = nt;
        nt->val = (i + 1);
    }

    return llt;
}

/**
 * Initialize a new link list with only head node
 * @return link list pointer
 */
cshark_linklist_t *cshark_linkist_allocate()
{
    cshark_linklist_t *llt;

    llt = new cshark_linklist_t();

    llt->head = new cshark_node_t();
    llt->head->name = "head";
    llt->head->val = 0;

    llt->first = NULL;
    llt->last = llt->head;

    return llt;
}

/**
 * Make a deep copy of an existing linklist
 * @param llt [in] linklist to copy
 * @return new linklist
 */
cshark_linklist_t *cshark_linklist_copy(cshark_linklist_t *llt)
{
    cshark_linklist_t *new_llt;
    cshark_node_t *nt;
    cshark_node_t *new_nt;
    cshark_node_t *curr;
    cshark_node_t *pre;

    if (llt == NULL or llt->head == NULL)
    {
        return NULL;
    }

    new_llt = cshark_linkist_allocate();
    cshark_node_copy(llt->head, new_llt->head);

    nt = llt->head->next;  // copy from the first node after head
    curr = new_llt->head;
    pre = new_llt->head;
    while (nt != NULL)
    {
        new_nt = cshark_node_init();
        cshark_node_copy(nt, new_nt);

        curr->next = new_nt;
        new_nt->prev = curr;

        pre = curr;
        curr = new_nt;
        nt = nt->next;
    }

    curr->next = NULL;
    curr->prev = pre;

    return new_llt;
}

/**
 * Delete a link list of its all nodes including head
 * @param llt [in] linklist
 * @return \0 for success, or other error code
 */
int cshark_linklist_destroy(cshark_linklist_t *llt)
{
    cshark_node_t *p;
    cshark_node_t *q;

    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    p = llt->head;
    while(p != NULL)
    {
        q = p;
        p = p->next;

        delete(q);
    }

    delete(llt);

    // Caution: delete(llt) ***WILL NOT set llt to NULL***.
    // set 'llt = NULL' will not change llt value, as it's a pass-by-value parameter;
    // to change llt, use cshark_linklist_t **llt as parameter, and then '*llt = NULL'.
    return SUCCESS;
}

/**
 * Add a node to the tail of link list
 * @param llt [in,out] link list
 * @param v  [in] node value
 * @return \0 for success, or other error code
 */
int cshark_linklist_add(cshark_linklist_t *llt, int v)
{
    cshark_node_t *nt;
    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    if (cshark_linklist_getsize(llt) == MAX_NODES)
    {
        return ERROR_MAX_NODES;
    }

    nt = cshark_node_init();
    nt->val = v;
    assert (nt != NULL);

    llt->last->next = nt;
    nt->next = NULL;
    nt->prev = llt->last;
    llt->last = nt;

    return SUCCESS;
}


/**
 * Insert a node at the rear of the list
 * @param llt [in] linklist
 * @param node [in] node to insert
 * @return \0 for success, or other error code
 */
int cshark_linklist_insert(cshark_linklist_t *llt, cshark_node_t *node)
{
    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    if (cshark_linklist_getsize(llt) == MAX_NODES)
    {
        return ERROR_MAX_NODES;
    }

    llt->last->next = node;
    node->next = NULL;
    node->prev = llt->last;
    llt->last = node;

    return SUCCESS;
}

/**
 * Add a node in linklist
 * @param llt  [in] link list
 * @param v    [in] value to be added
 * @param name [in] optional value
 * @return \0 for success, or other error code
 */
int cshark_linklist_add_vals(cshark_linklist_t *llt, int v, string name)
{
    cshark_node_t *nt;
    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    if (cshark_linklist_getsize(llt) == MAX_NODES)
    {
        return ERROR_MAX_NODES;
    }

    nt = cshark_node_init();
    nt->val = v;
    nt->name = name;
    assert (nt != NULL);

    llt->last->next = nt;
    nt->next = NULL;
    nt->prev = llt->last;
    llt->last = nt;

    return SUCCESS;
}

/**
 * Get item size of a link list; head is not counted.
 * @param llt [in] linklist pointer
 * @return size of link list
 * @return positive integer for success, or other error code
 */
size_t cshark_linklist_getsize(cshark_linklist_t *llt)
{
    cshark_node_t *nt;
    int i;

    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    nt = llt->head;
    i = -1;
    while (nt != NULL)
    {
        nt = nt->next;
        i++;
    }

    return i;
}

/**
 * Find a node in a link list by value. If there are multiple nodes with same value,
 * return the first node.
 * @param llt [in] link list
 * @param v   [in] value to find
 * @return \NULL if not found, else valid node pointer
 */
cshark_node_t *cshark_linklist_find_val(cshark_linklist_t *llt, int v)
{
    cshark_node_t *nt;
    cshark_node_t *found;

    if (llt == NULL)
    {
        return NULL;
    }

    found = NULL;
    nt = llt->head;
    while (nt != NULL)
    {
        if (nt->val != v)
        {
            nt = nt->next;
        }
        else
        {
            found = nt;
            break;
        }
    }

    return found;
}

/**
 * Find a node in a link list by position(pos 1 means the first node following head)
 * @param llt [in] link list
 * @param pos [in] position
 * @return \NULL if not found, else valid node pointer
 */
cshark_node_t *cshark_linklist_find_pos(cshark_linklist_t *llt, size_t pos)
{
    cshark_node_t *nt;
    int i = 0;

    if (llt == NULL)
    {
        return NULL;
    }

    nt = llt->head;
    while (nt != NULL)
    {
        if (i == pos)
        {
            break;
        }

        nt = nt->next;
        i++;
    }

    return nt;
}


/**
 * Print a link list
 * @param llt [in] link list
 */
void cshark_linklist_print(cshark_linklist_t *llt)
{
    cshark_node_t *nt;

    if (llt == NULL)
    {
        return;
    }

    nt = llt->head;
    printf("==== Print link list ===\n");
    while (nt != NULL)
    {
        printf("%d  ", nt->val);
        nt = nt->next;
    }

    printf("\n");
}

/**
 * Delete a node from link list; if there are  nodes having the same value, delete the first one.
 * @param llt [in,out] link list pointer
 * @param val [in] value that the node is to be deleted
 * @return \0 for success, or other error code
 */
int cshark_linklist_delete_val(cshark_linklist_t *llt, int val)
{
    cshark_node_t *nt;
    cshark_node_t *nxt;
    cshark_node_t *pre;
    bool flag;
    int ret;

    if (llt == NULL or llt->head == NULL)
    {
        return -1;
    }

    nt = llt->head;
    flag = false;
    while (nt != NULL)
    {
        if (nt->val == val)
        {
            if (nt->next == NULL)   // last node
            {
                nt->prev->next = NULL;
                nt->prev = NULL;
                nt->next = NULL;

                delete(nt);
            }
            else
            {
                pre = nt->prev;
                nxt = nt->next;

                pre->next = nxt;
                nxt->prev = pre;

                delete(nt);
            }

            flag = true;
            break;
        }

        nt = nt->next;
    }

    if (flag == true)   // found node and deleted
    {
        ret = 0;
    }


    return ret;
}

/**
 * Delete a node in a link list by position, and update the last node
 * @param llt [in,out] linklist
 * @param pos [in] position
 * @param val [out] deleted node's value
 * @return \0 for success, or other error code
 */
int cshark_linklist_delete_pos(cshark_linklist_t *llt, size_t pos, int *val)
{
    cshark_node_t *nt;
    cshark_node_t *pre;
    cshark_node_t *nxt;
    size_t n;

    if (llt == NULL || pos == 0 or val == NULL)  // not allowed to delete head
    {
        return ERROR_PARAM;
    }

    nt = cshark_linklist_find_pos(llt, pos);

    if (nt == NULL)
    {
        return ERROR_NOT_FOUND;
    }

    nxt = nt->next;
    pre = nt->prev;

    if (nt->next == NULL)  // last node
    {
        pre->next = NULL;
    }
    else
    {
        pre->next = nxt;
        nxt->prev = pre;
    }

    *val = nt->val;
    delete(nt);

    // if linklist has only one node, last will be root (which should be NULL, the first non-root node)
    n = cshark_linklist_getsize(llt);
    llt->first = cshark_linklist_find_pos(llt, 1);
    llt->last = cshark_linklist_find_pos(llt, n);

    return SUCCESS;
}

/**
 * Reverse a linklist inplace
 * Time complexity: O(N)
 * @param llt [in,out] linklist
 * @return \0 for success, or other error code
 */
int cshark_linklist_reverse(cshark_linklist_t *llt)
{
    size_t n;
    int i;
    cshark_node_t *last;
    cshark_node_t *curr;
    cshark_node_t *tmp;

    if (llt == NULL or llt->head == NULL)
    {
        return ERROR_PARAM;
    }

    n = cshark_linklist_getsize(llt);

    if (n == 0)  // only head
    {
        return SUCCESS;
    }

    last = cshark_linklist_find_pos(llt, n);
    if (last == NULL)
    {
        return ERROR_NOT_FOUND;
    }

    curr = llt->head;
    for (i = 0; i < n; i++)
    {
        tmp = last->prev;

        curr->next = last;
        last->prev = curr;
        last->next = NULL;
        curr = last;
        last = tmp;
    }

    return SUCCESS;
}

/**
 * Get last node of link list
 * @return last node of linklist
 * @return NULL if the list has only root, or valid pointer
 */
cshark_node_t* cshark_linklist_get_last(cshark_linklist_t *llt)
{
    cshark_node_t *node;
    size_t n;

    n = cshark_linklist_getsize(llt);

    if (n == 0)
    {
        return NULL;
    }
    else
    {
        node = llt->last;
    }

    assert (node != NULL);
    return node;
}

/**
 * Get first node of link list; return NULL if the list has only root.
 * @return first node of linklist
 */
cshark_node_t* cshark_linklist_get_first(cshark_linklist_t *llt)
{
    cshark_node_t *node;
    size_t n;

    n = cshark_linklist_getsize(llt);
    if (n == 0)
    {
        return NULL;
    }
    else
    {
        node = llt->head->next;
    }

    assert (node != NULL);
    return node;
}


int cshark_linklist_delete_last(cshark_linklist_t *llt, int *val)
{
    cshark_node_t *node;
    size_t n;

    if (llt == NULL or val == NULL)
    {
        return ERROR_PARAM;
    }

    node = cshark_linklist_get_last(llt);
    if (node == NULL)
    {
        return ERROR_TARGET_EMPTY;
    }

    n = cshark_linklist_getsize(llt);
    cshark_linklist_delete_pos(llt, n, val);

    return SUCCESS;
}

int cshark_linklist_delete_first(cshark_linklist_t *llt, int *val)
{
    cshark_node_t *node;

    if (llt == NULL or val == NULL)
    {
        return ERROR_PARAM;
    }

    node = cshark_linklist_get_first(llt);
    if (node == NULL)
    {
        *val = ERROR_INVALID_VALUE;
        return ERROR_TARGET_EMPTY;
    }

    cshark_linklist_delete_pos(llt, 1, val);
    return SUCCESS;
}

/**
 * Pop the first node from linklist, and return a copy
 * \warning caller must manually free the return node
 * @param llt [in] linklist
 * @return valid node, or \NULL if the linklikst is empty
 */
cshark_node_t* cshark_linklist_pop_first(cshark_linklist_t *llt)
{
    cshark_node_t *node;
    cshark_node_t *first;
    int v;

    if (llt == NULL)
    {
        return NULL;
    }

    first = cshark_linklist_get_first(llt);
    if (first == NULL)
    {
        return NULL;
    }

    node = cshark_node_init();
    cshark_node_copy(first, node);
    cshark_linklist_delete_first(llt, &v);

    return node;
}

/**
 * Pop the last node from linklist, which is NOT a copy of last node
 * \warning caller must manually free the return node
 * @param llt [in] linklist
 * @return valid node, or \NULL if the linklikst is empty
 */
cshark_node_t* cshark_linklist_pop_last(cshark_linklist_t *llt)
{
    cshark_node_t *node;
    cshark_node_t *last;
    int v;

    if (llt == NULL)
    {
        return NULL;
    }

    last = cshark_linklist_get_last(llt);
    if (last == NULL)
    {
        return NULL;
    }

    llt->last = last->prev;
    last->prev->next = NULL;
    last->prev = NULL;
    return last;
}

/**
 * Initialize a linklist with values [0, 1, 2, ... n-1]
 * @param n [in] number of nodes
 */
LinkList::LinkList(size_t n)
{
    this->head = cshark_node_init();
    this->head->val = 0xbeef;

    cshark_node_t *nt;
    cshark_node_t *curr;
    int i;

    if (n > MAX_LINKLIST_NODES)
    {
        return;
    }

    curr = head;
    for (i = 0; i < n; i++)
    {
        nt = cshark_node_init();
        nt->val = i;
        curr->next = nt;
        nt->prev = curr;
        nt->next = NULL;
        curr = nt;
    }
}

/**
 * Linklist destructor, which delete all nodes in the list including head
 */
LinkList::~LinkList()
{
    cshark_node_t *curr;
    cshark_node_t *tmp;
    curr = this->head;

    while (curr != NULL)
    {
        tmp = curr;
        curr = curr->next;
        delete(tmp);
    }
}

/**
 * Print a linklist
 */
void LinkList::print()
{
    cshark_node_t *curr;

    curr = head->next;
    while (curr != NULL)
    {
        printf("%d,", curr->val);
        curr = curr->next;
    }

    printf("\n");
}

/**
 * Get the size of linklist
 * @return size of linklist
 */
size_t LinkList::get_size()
{
    size_t n;
    cshark_node_t *curr;

    curr = head->next;
    n = 0;
    while (curr != NULL)
    {
        curr = curr->next;
        n++;
    }

    return n;
}

/**
 * Get the first node of the linklist
 * @return  node
 */
cshark_node_t* LinkList::get_first()
{
    return this->head->next;
}

/**
 * Get the last node of the linklist
 * @return  NULL or valid pointer of the node
 */
cshark_node_t* LinkList::get_last()
{
    cshark_node_t *curr;
    curr = head->next;

    if (curr == NULL)
    {
        return NULL;
    }

    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    return curr;
}

/**
 * Find node by position, the first position is 0
 * @param pos [in] position
 * @return NULL or valid pointer of the node
 */
cshark_node_t* LinkList::find_by_pos(size_t pos)
{
    size_t i;
    cshark_node_t *curr;

    curr = head->next;
    i = 0;
    while (curr != NULL and i != pos)
    {
        curr = curr->next;
        i++;
    }

    return curr;
}

/**
 * Find the first node holding the value
 * @param val [in] value to search
 * @return NULL or valid pointer of the node
 */
cshark_node_t* LinkList::find_by_val(int val)
{
    size_t i;
    cshark_node_t *curr;

    curr = head->next;
    while (curr != NULL and curr->val != val)
    {
        curr = curr->next;
        i++;
    }

    return curr;
}

/**
 * Insert a new node at the tail of linklist
 * @param nt [in] node
 * @return \0 on success
 */
int LinkList::insert_node(cshark_node_t *nt)
{
    cshark_node_t *last;

    last = this->get_last();
    if (last == NULL)  // empty list with only head
    {
        head->next = nt;
        nt->prev = head;
        nt->next = NULL;
    }
    else
    {
        last->next = nt;
        nt->prev = last;
        nt->next = NULL;
    }

    return SUCCESS;
}

/**
 * Insert a value at the tail of linklist
 * @param val [in] value
 * @return \0 on success
 */
int LinkList::insert_val(int val)
{
    cshark_node_t *nt;
    nt = cshark_node_init();
    nt->val = val;

    this->insert_node(nt);

    return SUCCESS;
}

/**
 * Delete a node by position
 * @param pos [0] position
 * @return \0 on success or other error code
 */
int LinkList::delete_by_pos(size_t pos)
{
    size_t i;
    cshark_node_t *curr;
    cshark_node_t *pre;
    cshark_node_t *nxt;

    curr = head->next;
    if (curr == NULL or (pos > (this->get_size() - 1)))  // empty list or max position
    {
        return ERROR_PARAM;
    }

    i = 0;
    while (curr != NULL and i != pos)
    {
        curr = curr->next;
        i++;
    }

    nxt = curr->next;
    pre = curr->prev;

    pre->next = nxt;

    // nxt = NULL indicating curr is the last node
    if (nxt != NULL)
    {
        nxt->prev = pre;
    }
    delete(curr);

    return SUCCESS;
}

/**
 * Delete the first node of the linklist
 * \note: if the list is empty with only head, return ERR_PARAM
 * @return \0 on success or other error code
 */
int LinkList::delete_first()
{
    return this->delete_by_pos(0);
}

/**
 * Delete the last node of the linklist
 * \note: if the list is empty with only head, return ERR_PARAM
 * @return \0 on success or other error code
 */
int LinkList::delete_last()
{
    size_t n;
    n = this->get_size();

    return this->delete_by_pos(n - 1);
}

/**
 * Pop a node by position
 * \warning the caller must manually free the node
 * @param pos [in] position
 * @return NULL or valid pointer of the node
 */
cshark_node_t* LinkList::pop_by_pos(size_t pos)
{
    size_t i;
    cshark_node_t *curr;
    cshark_node_t *pre;
    cshark_node_t *nxt;

    curr = head->next;
    if (curr == NULL or (pos > (this->get_size() - 1)))  // empty list or max position
    {
        return NULL;
    }

    i = 0;
    while (curr != NULL and i != pos)
    {
        curr = curr->next;
        i++;
    }

    nxt = curr->next;
    pre = curr->prev;

    pre->next = nxt;

    // nxt = NULL indicating curr is the last node
    if (nxt != NULL)
    {
        nxt->prev = pre;
    }

    return curr;
}

/**
 * Pop the first node from linklist. If list is empty, return NULL
 * \warning the caller must manually free the node
 * @return NULL or valid pointer of the node
 */
cshark_node_t* LinkList::pop_first()
{
    return this->pop_by_pos(0);
}

/**
 * Pop the last node from linklist. If list is empty, return NULL
 * \warning the caller must manually free the node
 * @return \NULL or valid pointer of the node
 */
cshark_node_t* LinkList::pop_last()
{
    return this->pop_by_pos(this->get_size() - 1);
}

/**
 * Detach a linklist from head, e.g.,
 *      original: head->0->1->2->....
 *      now: head->(NULL)
 * \warning Use this function at caution, as detached nodes will be  out of control!
 * @return \0 on success
 */
int LinkList::detach_head()
{
    cshark_node_t *p;

    p = this->head->next;
    this->head->next = NULL;

    if (p != NULL)
    {
        p->prev = NULL;
    }

    return SUCCESS;
}

/**
 * Detach a linklist from given position
 * \warning detach() should be used at caution, as detached nodes are out of scope
 *          currently only support detaching head
 * @param pos [in] position
 *         -1: head
 * @return \0 on success
 */
int LinkList::detach(int pos)
{
    cshark_node_t *p;
    if (pos != -1)
    {
        return ERROR_PARAM;
    }

    p = this->head->next;
    this->head->next = NULL;
    if (p != NULL)
    {
        p->prev = NULL;
    }

    return SUCCESS;
}