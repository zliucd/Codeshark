/*
============================================================================
 Name        : linklist.h
 Description : linklist header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_LINKLIST_H
#define CODESHARK_LINKLIST_H

#include "common/include/node.h"

/**
 * @class Linklist maintains double-linked list structure
 *        using forward and backward pointers.
 */
class LinkList
{
private:
    cshark_node_t *head;

public:
    LinkList(size_t n);
    ~LinkList();

    void print();
    size_t get_size();
    cshark_node_t *get_head();
    cshark_node_t *get_first();
    cshark_node_t *get_last();
    cshark_node_t *find_by_pos(size_t pos);
    cshark_node_t *find_by_val(int val);

    int insert_node(cshark_node_t *nt);
    int insert_val(int val);

    int delete_by_pos(size_t pos);
    int delete_first();
    int delete_last();

    cshark_node_t* pop_by_pos(size_t pos);
    cshark_node_t* pop_first();
    cshark_node_t* pop_last();
    int detach(int pos);
    int detach_head();
};


/**
 * @struct linklist structure
 * valid list: head(0) -> (1) -> (2) -> .... -> (n) -> NULL
 * empty list: head(0) -> NULL
 */
typedef struct _cshark_link_t
{
    cshark_node_t *head;      // head node always exists for a linklist, even if it's empty
    cshark_node_t *first;     // NULL if the list is empty (with only root)
    cshark_node_t *last;      // NULL if the list is empty (with only root)
}cshark_linklist_t;

// Functions

// linklist common functions
cshark_linklist_t *cshark_linklist_init(size_t n);
cshark_linklist_t *cshark_linkist_allocate();
int cshark_linklist_destroy(cshark_linklist_t *llt);
void cshark_linklist_print(cshark_linklist_t *llt);
cshark_linklist_t *cshark_linklist_copy(cshark_linklist_t *llt);
int cshark_linklist_reverse(cshark_linklist_t *llt);

// linklist find-like functions
size_t cshark_linklist_getsize(cshark_linklist_t *llt);
cshark_node_t* cshark_linklist_get_first(cshark_linklist_t *llt);
cshark_node_t* cshark_linklist_get_last(cshark_linklist_t *llt);
cshark_node_t* cshark_linklist_find_val(cshark_linklist_t *llt, int v);
cshark_node_t* cshark_linklist_find_pos(cshark_linklist_t *llt, size_t pos);

/// linklist add-like functions
int cshark_linklist_add(cshark_linklist_t *llt, int v);
int cshark_linklist_insert(cshark_linklist_t *llt, cshark_node_t *node);

// linklist remove-like functions
int cshark_linklist_delete_val(cshark_linklist_t *llt, int val);
int cshark_linklist_delete_pos(cshark_linklist_t *llt, size_t pos, int *val);
int cshark_linklist_delete_last(cshark_linklist_t *llt, int *val);
int cshark_linklist_delete_first(cshark_linklist_t *llt, int *val);
cshark_node_t* cshark_linklist_pop_first(cshark_linklist_t *llt);
cshark_node_t* cshark_linklist_pop_last(cshark_linklist_t *llt);

#endif //CODESHARK_LINKLIST_H
