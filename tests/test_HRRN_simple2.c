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
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   2,      6,      4,      'B'},
                                        {   4,      4,      2,      'C'},
                                        {   6,      5,      3,      'D'},
                                        {   8,      2,      5,      'E'}};                           

    const char *expected_result = "AAABBBBBBCCCCEEDDDDD";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
