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
    printf("Checks if LCFS works correctly if there is an empty slot. (in Front)\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   1,      3,      1,      'A'},
                                        {   3,      6,      4,      'B'},
                                        {   5,      8,      2,      'C'},
                                        {   7,      4,      3,      'D'},
                                        {   8,      5,      5,      'E'}};                           
    
    const char *expected_result = " AAABBBBBBDDDDEEEEECCCCCCCC";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
