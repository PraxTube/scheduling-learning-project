#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   9
#define RR_QUANTUM      3
#define STRATEGY        RR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      4,       2,      'A'},
                                        {    6,      3,       8,      'B'},
                                        {    7,      5,       7,      'C'},
                                        {    8,      2,       1,      'D'},
                                        {   12,      3,       9,      'E'},
                                        {   13,      9,       6,      'F'},
                                        {   14,      1,       3,      'G'},
                                        {   15,      5,       5,      'H'},
                                        {   16,      4,      10,      'I'}};


    char* expected_result = "AAAA  BBBCCCDDEEECCFFFGHHHIIIFFFHHIFFF";

    print_schedule_info(PROCESS_COUNT, STRATEGY, RR_QUANTUM, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
