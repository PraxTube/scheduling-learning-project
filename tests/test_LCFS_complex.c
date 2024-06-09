#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        LCFS

int main()
{
    printf("Checks if LCFS works for very complex process.");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   1,      3,      4,      'B'},
                                        {   2,      5,      4,      'C'},
                                        {   4,      2,      4,      'O'},
                                        {   6,      1,      4,      'G'},
                                        {   10,     1,      4,      'D'},
                                        {   12,     2,      4,      'S'},
                                        {   14,     3,      4,      'T'},
                                        {   16,     1,      4,      'F'},
                                        {   17,     3,      2,      'M'}};

    
    char* expected_result = "AAACCCCCGOODSSTTTMMMFBBB";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
