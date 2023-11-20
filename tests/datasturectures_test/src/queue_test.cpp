/*
 ============================================================================
 Name        : queue_test.cpp
 Description : queue test implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <assert.h>

#include "datastructures/include/queue.h"
#include "datasturectures_test/include/queue_test.h"
#include "common/include/err.h"

QueueTest::QueueTest()
{
}

QueueTest::~QueueTest()
{

}

void QueueTest::test_main()
{
    cshark_node_t *nt;
    Queue *q1 = new Queue();

    assert (q1->is_empty() == true);
    assert (q1->is_full() == false);

    q1->enqueue(0);
    q1->enqueue(1);
    q1->enqueue(2);

    nt = q1->dequeue();
    assert (nt != NULL and nt->val == 0);
    delete(nt);

    nt = q1->dequeue();
    assert (nt != NULL and nt->val == 1);
    delete(nt);

    nt = q1->dequeue();
    assert (nt != NULL and nt->val == 2);
    delete(nt);

    assert (q1->is_empty() == true);
    assert (q1->is_full() == false);

    delete(q1);

    printf("[SUCCESS] Queue enqueue(), dequeu(), is_empty(), is_full()\n");
}

void cpp_test_queue_main()
{
    printf("\n=== Queue test ===\n");

    QueueTest *queue_test = new QueueTest();
    queue_test->test_main();
    delete(queue_test);
}