/*
 ============================================================================
 Name        : perf.cpp
 Description : perf implementation
 Author      : Zhi Liu<zliucd66@gmail.com>
 Copyright   : Codeshark is a free C/C++ code repository under Apache 2.0 license,
               see LICENSE.txt.
 ============================================================================
 */

#include <iostream>
#include <string>
#include <chrono>
#include <string.h>

#include "common/include/common.h"
#include "common/include/perf.h"

using namespace std;
using namespace chrono;

/**
 *  We use high_resolution_clock of C++ to measure performance.
 */


/**
 * Get current time clock and string, and set to arg(time_perf)
 * @param time_perf [in] time_perf pointer
 * @return nothing
 */
void perf_get_time(perf_t *time_perf)
{
    time_point<system_clock> curr_clock;
    time_t rawtime;
    tm *tm_now;
    char buff[MAX_STR_LEN];

    if (time_perf == NULL)
    {
        return;
    }

    time_perf->curr_clock = high_resolution_clock::now();

    curr_clock = system_clock::now();
    rawtime = system_clock::to_time_t(curr_clock);
    tm_now = localtime(&rawtime);

    memset(buff, 0, MAX_STR_LEN);
    strftime(buff, MAX_STR_LEN, "%Y-%m-%d %H:%M:%S", tm_now);
    time_perf->time_str = string(buff);
}

/**
 * Get current date and time in format "2022-01-01 12:00:00"
 * @return string
 */
string perf_get_current_datetime()
{
    time_t t;
    struct tm *timeinfo;
    char buffer[MAX_STR_LEN];

    memset(buffer, 0, MAX_STR_LEN);
    time(&t);
    timeinfo = localtime(&t);
    strftime(buffer, MAX_STR_LEN, "%Y-%m-%d %H:%M:%S", timeinfo);

    return string(buffer);
}

/**
 * Get elapsed time between two time points, and return elapsed time in seconds
 * @param start [in] run time pointer
 * @param end   [in] end time pointer
 * @param elapsed [out] elapsed time pointer
 * @return  time elapsed in seconds
 */
void perf_get_elapsed_time(perf_t *start, perf_t *end, perf_t *elapsed)
{
    duration<float, std::milli> elapsed_f;

    if (start == NULL or end == NULL or elapsed == NULL)
    {
        return;
    }

    elapsed_f = end->curr_clock - start->curr_clock;

    elapsed->time_float = elapsed_f.count() / 1000;
    elapsed->time_str = std::to_string(elapsed->time_float);
}




