/*
============================================================================
 Name        : stack.h
 Description : stack header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_STACK_H
#define CODESHARK_STACK_H

#include "common/include/node.h"
#include "datastructures/include/linklist.h"

/**
 * @class Stack maintains stack structure, which is a linklist internally
 */
class Stack
{
private:
    LinkList *list;
public:
    Stack();
    ~Stack();

    bool is_empty();
    bool is_full();
    string print();

    int push(int n);
    int push(cshark_node_t *);
    cshark_node_t* pop();
    cshark_node_t* get_top();
};

#endif //CODESHARK_STACK_H
