#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        LCFS

int main()
{
    printf("Checks if LCFS works correctly if there is no process coming after one process\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,       6,      2,      'A'},
                                        {    8,      14,      1,      'B'},
                                        {   16,       9,      5,      'C'},
                                        {   21,      13,      4,      'D'},
                                        {   50,       8,      3,      'E'}};

    const char *expected_result = "AAAAAA  BBBBBBBBBBBBBBDDDDDDDDDDDDDCCCCCCCCC      EEEEEEEE";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
