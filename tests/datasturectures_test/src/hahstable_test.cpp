/*
============================================================================
Name        : hashtable_test.cpp
Description : hashtable test implementation
Author      : Zhi Liu<zliucd66@gmail.com>
Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
              see LICENSE.txt.
============================================================================
*/

#include <assert.h>

#include "common/include/node.h"
#include "common/include/err.h"
#include "common/include/perf.h"
#include "datastructures/include/linklist.h"
#include "datastructures/include/hahstable.h"
#include "datasturectures_test/include/hashtable_test.h"

/**
 * Main function for hash table tesing
 */
void test_hashtable_main()
{
    test_hashtable_init();
    test_hashtable_destroy();
    test_hashtble_add();
    test_hashtalbe_bulk_add();

}

/**
 * Test hash table initialization.
 */
static void test_hashtable_init()
{
    hashtable_t *ht;
    cshark_linklist_t *llt;
    int i;

    ht = hashtable_init();
    for (i = 0; i < MAX_HASH_SLOTS; i++)
    {
        llt = ht->slots[i];
        assert (llt->head != NULL and llt->head->next == NULL);
    }

    hashtable_destroy(ht);

    printf("[PASSED] hashtable_init()\n");

}

/**
 * Test hash table destroy, which is validated by ASAN.
 */
static void test_hashtable_destroy()
{
    //
}

/**
 * Test hash table simple add entries
 */
static void test_hashtble_add()
{
    hashtable_t *ht;
    cshark_linklist_t *llt;
    string val;
    int i, key;

    ht = hashtable_init();

    hashtable_add(ht, 5, "name5");
    llt = ht->slots[5];
    assert (cshark_linklist_find_val(llt, 5)->name == "name5");

    key = MAX_HASH_SLOTS + 5;
    val = "name" + to_string(MAX_HASH_SLOTS + 5);
    hashtable_add(ht, key, val);
    llt = ht->slots[5];
    assert (hashtable_find(ht, key) == val);

    hashtable_destroy(ht);

    printf("[PASSED] hashtable_add()\n");

}

/**
 * Test hash table add and find, and also test performance.
 */
static void test_hashtalbe_bulk_add()
{
    hashtable_t *ht;
    cshark_linklist_t *llt;
    string val;
    int i, key;
    perf_t start, end, elapsed;
    uint64_t max_hash_nodes;

    max_hash_nodes = 100000;  // 100,000 is very fast(0.73 sec on M1), 200,000 is not so fast(5.0 sec)

    perf_get_time(&start);
    ht = hashtable_init();
    for (i = 1; i <= max_hash_nodes; i++)
    {
        val = "name" + to_string(i);
        hashtable_add(ht, i, val);
    }

    for (i = 1; i <= max_hash_nodes; i++)
    {
        val = "name" + to_string(i);
        assert (hashtable_find(ht, i) == val);
    }

    hashtable_destroy(ht);

    perf_get_time(&end);
    perf_get_elapsed_time(&start, &end, &elapsed);
    printf("[PASSED] hashtable_bulk_add() and _find(), %llu nodes, elapsed:%s seconds\n", max_hash_nodes, elapsed.time_str.c_str());

}