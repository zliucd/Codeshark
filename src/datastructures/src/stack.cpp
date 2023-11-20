/*
============================================================================
 Name        : stack.cpp
 Description : stack implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include "common/include/node.h"
#include "common/include/err.h"
#include "datastructures/include/linklist.h"
#include "datastructures/include/stack.h"

/**
 * Initialize a new and empty stack, which could shrink when pop()
 */
Stack::Stack()
{
    this->list = new LinkList(0);
}

/**
 * Delete the stack
 */
Stack::~Stack()
{
    delete(this->list);
}

/**
 * Push a node into stack
 * @param x [in] val of the new node
 * @return \0 on  success
 */
int Stack::push(int x)
{
    cshark_node_t *nt = cshark_node_init();
    nt->val = x;

    this->list->insert_node(nt);
    return SUCCESS;
}

/**
 * Push a node into stack
 * @param nt [in] node
 * @return \0 on success
 */
int Stack::push(cshark_node_t *nt)
{
    this->list->insert_node(nt);
    return SUCCESS;
}

/**
 * Pop an element from stack
 * \warning caller must manually free the node
 * @return \NULL if the stack is empty
 *          valid pointer of the node
 */
cshark_node_t *Stack::pop()
{
    cshark_node_t *ret;
    ret = this->list->pop_last();

    return ret;
}

/**
 * Get the top element from stack
 * @return \NULL if the stack is empty
 *          valid pointer of the node
 */
cshark_node_t *Stack::get_top()
{
    return this->list->get_last();
}

/**
 * Check if stack is full
 * \note stack can increase dynamically, so always return 'false'
 * @return false
 */
bool Stack::is_full()
{
    return false;
}

/**
 * Check if stack is empty
 * @return \true if empty otherwise \false
 */
bool Stack::is_empty()
{
    return this->list->get_size() == 0;
}

/**
 * Print a stack
 * @return printable string
 */
string Stack::print()
{
    cshark_node_t *p;
    string s;

    printf("-----------\n    top  \n-----------");
    for (p = this->list->get_first(); p != NULL; p = p->next)
    {
        s = s + "," + to_string(p->val);
    }

    printf("%s\n", s.c_str());
    return s;
}