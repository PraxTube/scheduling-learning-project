#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   6
#define RR_QUANTUM      2
#define STRATEGY        MLF

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,       6,      2,      'A'},
                                        {    8,      60,      1,      'B'},
                                        {   16,       9,      5,      'C'},
                                        {   21,      13,      4,      'D'},
                                        {   37,       8,      3,      'E'},
                                        {   70,       3,      6,      'F'}};


    char* expected_result = "AAAAAA  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCDFEFFCCDDEECCCCDDDDEEEECCDDDDDDE";

    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
