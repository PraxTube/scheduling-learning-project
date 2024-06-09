#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        PRIOP

int main()
{
    printf("Tests what happens when nothing gets run.");
    printf("If doesn't pass:\n"
            "\t- Did you forget to check for NULL?\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    1,      3,      3,      'A'},
                                        {    2,      2,      9,      'B'},
                                        {    10,     3,      4,      'C'},
                                        {    12,     2,      9,      'Z'}};
    
    char* expected_result = " ABBAA    CCZZC";


    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
