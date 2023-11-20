/*
 ============================================================================
 Name        : node_test.cpp
 Description : node_test implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <cassert>

#include "common/include/node.h"
#include "common_test/include/node_test.h"

/**
 * Test node initialization. This is a mini test for demonstration.
 */
void test_node_init()
{
    cshark_node_t *nt;

    nt = new cshark_node_t();
    assert (nt->prev == NULL and nt->next == NULL);
    cshark_node_free(nt);
}



