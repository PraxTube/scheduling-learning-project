#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   9
#define RR_QUANTUM      2
#define STRATEGY        RR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      4,       2,      'A'},
                                        {    6,      3,       8,      'B'},
                                        {    10,      10,       7,      'C'},
                                        {    17,      10,       1,      'D'},
                                        {   22,      7,       9,      'E'},
                                        {   40,      9,       6,      'F'},
                                        {   43,      1,       3,      'G'},
                                        {   46,      5,       5,      'H'},
                                        {   55,      4,      10,      'I'}};


    char* expected_result = "AAAA  BBB CCCCCCCCDDCCDDEEDDEEDDEEDDE   FFFFGFFHHFFHHFHIIII";
    print_schedule_info(PROCESS_COUNT, STRATEGY, RR_QUANTUM, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
