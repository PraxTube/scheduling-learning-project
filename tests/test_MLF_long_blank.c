#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   7
#define RR_QUANTUM      2
#define STRATEGY        MLF

int main()
{
    printf("Tests more complex example");
    printf("If doesn't pass:\n"
            "\t- Is the last level PRIONP?\n"
            "\t- To you poll from the correct queue every time?\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,       30,     6,      'A'},
                                        {   7,       42,     4,      'B'},
                                        {   20,      5,      1,      'C'},
                                        {   32,      70,     9,      'D'},
                                        {   40,      13,     4,      'E'},
                                        {   52,      1,      3,      'F'},
                                        {   60,      4,      2,      'G'}};

    char* expected_result = "AAAAAAABBBBBBBAAAAAAAAAAAAAAAAAAAAAAADCDDEEECCDDDDEEEEFCCDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBEEEEEE";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
