#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        SRTN

int main()
{
    printf("Checks if SRTN(P) works for simple process.");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   1,      3,      2,      'A'},
                                      {   2,      6,      4,      'B'},
                                      {   4,      4,      1,      'C'},
                                      {   6,      5,      5,      'D'},
                                      {   8,      2,      3,      'E'}};

    
    char* expected_result = " AAACCCCEEDDDDDBBBBBB";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
