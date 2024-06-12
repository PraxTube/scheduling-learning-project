#include "../lib/process.h"
#include "../lib/scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROCESS_COUNT 9
#define RR_QUANTUM 2
#define STRATEGY HRRN

int main() {
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {
      {0, 4, 2, 'A'},  {6, 3, 8, 'B'},  {7, 5, 7, 'C'},
      {8, 2, 1, 'D'},  {12, 3, 9, 'E'}, {13, 9, 6, 'F'},
      {14, 1, 3, 'G'}, {15, 5, 5, 'H'}, {16, 4, 10, 'I'}};

  char *expected_result = "AAAA  BBBDDCCCCCGEEEHHHHHIIIIFFFFFFFFF";

  char *resulting_schedule =
      scheduler(processes, PROCESS_COUNT, STRATEGY, RR_QUANTUM);

  if (strcmp(expected_result, resulting_schedule)) {
    fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n", expected_result,
            resulting_schedule);
    free(resulting_schedule);
    exit(1);
  }
  printf("Passed.\n");

  free(resulting_schedule);
  exit(0);
}
