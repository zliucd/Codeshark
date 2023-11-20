/*
 ============================================================================
 Name        : stack_test.cpp
 Description : stack test implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <assert.h>
#include "datasturectures_test/include/stack_test.h"

StackTest::StackTest()
{
}

StackTest::~StackTest()
{

}

void StackTest::test_main()
{
    cshark_node_t *nt;
    Stack *s1 = new Stack();

    assert (s1->is_empty() == true);
    assert (s1->is_full() == false);

    s1->push(0);
    s1->push(1);
    s1->push(2);

    nt = s1->pop();
    assert (nt != NULL and nt->val == 2);
    delete(nt);

    nt = s1->pop();
    assert (nt != NULL and nt->val == 1);
    delete(nt);

    nt = s1->pop();
    assert (nt != NULL and nt->val == 0);
    delete(nt);

    assert (s1->is_empty() == true);
    assert (s1->is_full() == false);

    delete(s1);

    printf("[SUCCESS] Stack push(), pop(), is_empty(), is_full()\n");
}

void cpp_test_stack_main()
{
    printf("\n=== Stack test ===\n");

    StackTest *stack_test = new StackTest();
    stack_test->test_main();
    delete(stack_test);
}
