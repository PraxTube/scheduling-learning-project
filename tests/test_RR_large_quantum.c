#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      5
#define STRATEGY        RR

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   1,      3,      2,      'A'},
                                        {   2,      6,      4,      'B'},
                                        {   4,      4,      1,      'C'},
                                        {   6,      5,      5,      'D'},
                                        {   8,      2,      3,      'E'}};
    const char *expected_result = " AAABBBBBCCCCDDDDDEEB";
    print_schedule_info(PROCESS_COUNT, STRATEGY, RR_QUANTUM, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
