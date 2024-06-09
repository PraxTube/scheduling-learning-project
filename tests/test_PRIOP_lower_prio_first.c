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
    printf("Tests the pre-emption.");
    printf("If doesn't pass:\n"
            "\t- Take a look at how you choose the processes when they arrive.\n"
            "\t- Take a look at how you choose the processes when one process finished.\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      3,      1,      'U'},
                                        {    1,      4,      2,      'W'},
                                        {    2,      5,      3,      'E'},
                                        {    3,      2,      4,      'N'}};
    
    char* expected_result = "UWENNEEEEWWWUU";

    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
