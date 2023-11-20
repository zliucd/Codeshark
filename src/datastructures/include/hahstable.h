/*
 ============================================================================
 Name        : hashtable.h
 Description : hashtable header
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_HAHSTABLE_H
#define CODESHARK_HAHSTABLE_H

#include "datastructures/include/linklist.h"

#define MAX_HASH_SLOTS 597
#define HASH_NOT_FOUND "hash_not_found"

// hash table is a list of cshark_linklist_t
typedef struct _hashtable_t
{
    cshark_linklist_t *slots[MAX_HASH_SLOTS];
}hashtable_t;

// Hash table functions

hashtable_t *hashtable_init();
int hashtable_destroy(hashtable_t *ht);
string hashtable_find(hashtable_t *ht, int k);
int hashtable_add(hashtable_t *ht, int k, string val);
int hashtable_delete(int val);


#endif //CODESHARK_HAHSTABLE_H
