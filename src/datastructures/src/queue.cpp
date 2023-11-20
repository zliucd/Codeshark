/*
============================================================================
 Name        : queue.cpp
 Description : queue implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include "datastructures/include/linklist.h"
#include "datastructures/include/queue.h"
#include "common/include/err.h"

/**
 * Initialize a new and empty queue
 */
Queue::Queue()
{
    this->list = new LinkList(0);
}

/**
 * Delete the queue
 */
Queue::~Queue()
{
    delete(this->list);
}

/**
 * Push a node into queue
 * @param x [in] val
 * @return always SUCCESS
 */
int Queue::enqueue(int x)
{
    cshark_node_t *nt = cshark_node_init();
    nt->val = x;
    this->list->insert_node(nt);

    return SUCCESS;
}

/**
 * Pop the first node of the queue
 * \warning caller must manually free the node
 * @return the first node of the queue
 */
cshark_node_t *Queue::dequeue()
{
    cshark_node_t *ret;
    ret = this->list->pop_first();

    return ret;
}

/**
 * Check if queue is full
 * \note queue can increase dynamically, so always return 'no'
 * @return false
 */
bool Queue::is_full()
{
    return false;
}

/**
 * Check if queue is empty
 * @return 'yes' if empty otherwise 'no'
 */
bool Queue::is_empty()
{
    return this->list->get_size() == 0;
}

/**
 * Initiate an empty queue
 * @return head node the new queue
 */
cshark_queue *cshark_queue_init()
{
    return cshark_linklist_init(0);  /* only head */
}

/**
 * Destroy a queue
 * @param queue [in] queue to detory
 */
void cshark_queue_destroy(cshark_queue *queue)
{
    cshark_linklist_destroy(queue);
}

/**
 * Visit the first node (after root) of a queue
 * @param queue [in] queue
 * @return \NULL if queue is empty, else the first node
 */
cshark_node_t *cshark_queue_visit(cshark_queue *queue)
{
    return cshark_linklist_get_first(queue);
}

/**
 * Add a new node in queue
 * @param queue [in,out] queue
 * @param val   [in] value for the new node
 * @return 0 on success
 */
int cshark_queue_add(cshark_queue *queue, int val)
{
    if (queue == NULL)
    {
        return ERROR_PARAM;
    }

    cshark_linklist_add(queue, val);

    return SUCCESS;
}

/**
 * Insert a node insert queue
 * @param queue [in,out] queue
 * @param node [in] node
 * @return \0 on success or other error code
 */
int cshark_queue_insert(cshark_queue *queue, cshark_node_t *node)
{
    if (queue == NULL or node == NULL)
    {
        return ERROR_PARAM;
    }

    cshark_linklist_insert(queue, node);

    return SUCCESS;
}


/**
 * Get queue size
 * @param queue [in] queue
 * @return queue size
 */
size_t cshark_queue_getsize(cshark_queue *queue)
{
    return cshark_linklist_getsize(queue);
}

/**
 * Remove the first element of a queue, and make a copy of the element
 * \warning caller must manually free repli
 * @param queue [in] queue
 * @param repli [out] a copy of the first element
 * @return \0 on success
 */
int cshark_queue_remove_clone(cshark_queue *queue, cshark_node_t **repli)
{
    cshark_node_t *last;
    size_t queue_size;
    int v;

    queue_size = cshark_queue_getsize(queue);
    if (queue_size == 0)
    {
        *repli = NULL;
    }
    else
    {
        *repli = cshark_node_init();
    }

    last = cshark_linklist_get_first(queue);
    cshark_node_copy(last, *repli);

    cshark_linklist_delete_first(queue, &v);

    return SUCCESS;
}

/**
 * Remove the first element of a queue
 * @param queue [in] queue
 * @return \0 on success
 */
cshark_node_t* cshark_queue_remove(cshark_queue *queue)
{
    cshark_node_t *first;
    size_t queue_size;
    int v;

    queue_size = cshark_queue_getsize(queue);
    if (queue_size == 0)
    {
        first = NULL;
    }

    first = cshark_linklist_get_first(queue);
    cshark_linklist_delete_first(queue, &v);

    return SUCCESS;
}

/**
 * Pop the first element's value and do not delete the element
 * @param queue [in] queue
 * @param val [out] the first element's value
 * @return \0 on success
 */
int cshark_queue_pop(cshark_queue *queue, int *val)
{
    return cshark_linklist_delete_first(queue, val);
}
