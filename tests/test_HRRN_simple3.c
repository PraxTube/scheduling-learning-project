#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        HRRN

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{  0,      7,      8,      'A'},
                                        {    1,      1,      9,      'B'},
                                        {    2,      3,      7,      'C'},
                                        {    3,      5,      1,      'G'},
                                        {    4,      7,      1,      'E'}};

    char* expected_result = "AAAAAAABCCCGGGGGEEEEEEE";

    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
