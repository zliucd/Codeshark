/*
 ============================================================================
 Name         : perf.h
 Description  : perf header
 Author       : Zhi Liu<zliucd66@gmail.com>
 Copyright    : Codeshark is a free C/C++ code repository under Apache 2.0 license,
                see LICENSE.txt.
 ============================================================================
 */

#ifndef CODESHARK_PERF_H
#define CODESHARK_PERF_H

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

typedef struct _perf_t
{
    // high-precision clock
    high_resolution_clock::time_point curr_clock;
    float time_float;
    string time_str;
}perf_t;

void perf_get_time(perf_t *time_perf);
void perf_get_elapsed_time(perf_t *start, perf_t *end, perf_t *elapsed);


#endif //CODESHARK_PERF_H
