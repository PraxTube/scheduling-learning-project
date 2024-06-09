#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   6
#define RR_QUANTUM      2
#define STRATEGY        HRRN

int main()
{
    printf("Checks behaviour with empty slots.\n");
    printf("If doesn't pass:\n"
            "\t- Did you forget to check for NULL somewhere? Refer to fcfs.c (pre-implemented...)\n"
            "\t- If not: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      8,      'A'},
                                        {   1,      4,      9,      'B'},
                                        {   2,      1,      7,      'C'},
                                        {   11,     3,      6,      'D'},
                                        {   12,     1,      1,      'E'},
                                        {   13,     2,      3,      'F'}};

    
    char* expected_result = "AAACBBBB   DDDEFF";


    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
