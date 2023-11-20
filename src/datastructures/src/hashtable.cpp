/*
 ============================================================================
 Name        : hashtable.cpp
 Description : hashtable implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include "common/include/err.h"
#include "datastructures/include/hahstable.h"
#include "datastructures/include/linklist.h"

/**
 * Initialize a new hash table
 * @return hashtable
 */
hashtable_t *hashtable_init()
{
    hashtable_t *ht;
    int i;

    ht = new hashtable_t();

    for (i = 0; i < MAX_HASH_SLOTS; i++)
    {
        ht->slots[i] = cshark_linklist_init(0);
    }

    return ht;
}


/**
 * Destroy a hash table
 * @param ht [in] hashtable
 * @return \0 on success, or other error code
 */
int hashtable_destroy(hashtable_t *ht)
{
    int i;

    if (ht == NULL)
    {
        return ERROR_PARAM;
    }

    for (i = 0; i < MAX_HASH_SLOTS; i++)
    {
        cshark_linklist_destroy(ht->slots[i]);
    }

    delete(ht);
    return SUCCESS;
}

/**
 * Find a value in hash table
 * @param ht [in] hash table
 * @param v [in] value to find
 * @return string
 */
string hashtable_find(hashtable_t *ht, int key)
{
    cshark_linklist_t *llt;
    size_t slot_pos;
    cshark_node_t *nt;
    string s;

    s = HASH_NOT_FOUND;

    slot_pos = key % MAX_HASH_SLOTS;
    llt = ht->slots[slot_pos];
    if (cshark_linklist_getsize(llt) == 0)
    {
        return NULL;
    }
    else
    {
        nt = llt->head;
        while (nt != NULL)
        {
           if (nt->val == key)
           {
               s = nt->name;
               return s;
           }
           else
           {
               nt = nt->next;
               continue;
           }
        }
    }

    return s;
}

/**
 * Add an entry in hash table, if exists, update hash slot
 * @param val [in] value
 * @param name [in] name
 * @return SUCCESS
 */
int hashtable_add(hashtable_t *ht, int key, string value)
{
    cshark_linklist_t *llt;
    size_t slot_pos;
    cshark_node_t *nt;

    slot_pos = key % MAX_HASH_SLOTS;
    llt = ht->slots[slot_pos];

    return SUCCESS;
}
