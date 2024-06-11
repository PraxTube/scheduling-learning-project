#include "../lib/RR.h"
#include <stdio.h>

static queue_object *RR_queue;
static unsigned int max_time;

// Get the next process that should be run.
static process *determine_next_process() {
    // Queue is empty
    if (RR_queue->next == NULL) {
        return NULL;
    }
    return queue_poll(RR_queue);
}

process *RR_tick(process *running_process) {
    if (running_process == NULL || running_process->time_left == 0) {
        running_process = determine_next_process();
    }
    if (running_process != NULL) {
        // Process ran out of time
        if (running_process->priority >= max_time) {
            running_process->priority = 0;
            queue_add(running_process, RR_queue);
            running_process = determine_next_process();
        }
        running_process->time_left--;
        running_process->priority++;
    }

    return running_process;
}

int RR_startup(int quantum) {
    RR_queue = new_queue();
    max_time = quantum;
    if (RR_queue == NULL) {
        return 1;
    }
    return 0;
}

process *RR_new_arrival(process *arriving_process, process *running_process) {
    if (arriving_process != NULL) {
        arriving_process->priority = 0;
        queue_add(arriving_process, RR_queue);
    }
    return running_process;
}

void RR_finish() {
 free_queue(RR_queue);
}
