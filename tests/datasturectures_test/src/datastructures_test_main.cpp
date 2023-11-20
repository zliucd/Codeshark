/*
 ============================================================================
 Name        : datastructures_test_main.cpp
 Description : data structures test main program
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include "common/include/common.h"
#include "datasturectures_test/include/linklist_test.h"
#include "datasturectures_test/include/stack_test.h"
#include "datasturectures_test/include/queue_test.h"
#include "datasturectures_test/include/hashtable_test.h"
#include "datasturectures_test/include/tree_test.h"

int main(int argc, char *argv[])
{
    codeshark_prologue();

    cpp_test_linklist_main();
    cpp_test_stack_main();
    cpp_test_queue_main();
    cpp_tree_test_main();

    codeshark_epilogue();

    return 0;
}
