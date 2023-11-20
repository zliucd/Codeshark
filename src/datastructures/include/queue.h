/*
============================================================================
 Name        : queue.h
 Description : queue header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_QUEUE_H
#define CODESHARK_QUEUE_H

#include "datastructures/include/linklist.h"

/**
 * @class Queue maintains queue structure, which is a linklist internally.
 */
class Queue
{
private:
    LinkList *list;
public:
    Queue();
    ~Queue();

    bool is_empty();
    bool is_full();
    int enqueue(int n);
    cshark_node_t * dequeue();
};

typedef cshark_linklist_t cshark_queue;

// Queue functions

cshark_queue *cshark_queue_init();
void cshark_queue_destroy(cshark_queue *queue);
int cshark_queue_add(cshark_queue *queue, int val);
int cshark_queue_insert(cshark_queue *queue, cshark_node_t *node);
int cshark_queue_remove_clone(cshark_queue *queue, cshark_node_t **repli);
cshark_node_t* cshark_queue_remove(cshark_queue *queue);
size_t  cshark_queue_getsize(cshark_queue *queue);
cshark_node_t *cshark_queue_visit(cshark_queue *queue);
int cshark_queue_pop(cshark_queue *queue, int *val);

#endif //CODESHARK_QUEUE_H
