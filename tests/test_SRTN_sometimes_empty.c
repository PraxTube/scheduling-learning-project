#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   9
#define RR_QUANTUM      2
#define STRATEGY        SRTN

int main()
{
    printf("Tests for period where nothing is run.\n");
    printf("If doesn't pass:\n"
            "\t- Did you look for NULL values?\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    1,      4,      9,      'A'},
                                        {    3,      3,      8,      'B'},
                                        {    10,     3,      7,      'C'},
                                        {    14,     4,      6,      'Z'}};
    
    char* expected_result = " AAAABBB  CCC ZZZZ";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
