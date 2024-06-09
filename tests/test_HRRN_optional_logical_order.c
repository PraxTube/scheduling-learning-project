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
    printf("\n\nThis is optional, because it hasn't been officially said.\n"
            "I would recommend to code your algorithm to pass this test tho. \n"
            "This test checks the following case:\n"
            "If you have two processes with the same RR the OLDER one should be chosen.\n");
    printf("Comment: In this test B and C have the same RR at 3. \nBut "
            "B should get processed first, because if was older (waited longer).\n");
    printf("If doesn't pass:\n"
            "\t- When choosing from in queue you might need to add a '='. \n "
            "\t  Try it out and if it passes this test then your order is 'more logical'\n"
            "\t- If not: Ask whether you have to do it. If not just delete this test!\n\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      8,      'A'},
                                        {   1,      4,      9,      'B'},
                                        {   2,      2,      7,      'C'},
                                        {   11,     3,      6,      'D'},
                                        {   12,     1,      1,      'E'},
                                        {   13,     2,      3,      'F'}};

    char* expected_result = "AAABBBBCC  DDDEFF";
    
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
