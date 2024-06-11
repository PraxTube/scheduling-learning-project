#include "../lib/PRIOP.h"

#include <stdio.h>

static queue_object *PRIOP_queue;

// Put the process with the highest priority at the end of the queue. It
// doesn't actually sort the queue and has O(n) as a result.
static void semi_sort_queue() {
    queue_object *previous_ptr = PRIOP_queue;
    queue_object *current_ptr = PRIOP_queue->next;

    while (current_ptr->next != NULL) {
        process *proc = current_ptr->object;
        queue_object *next = current_ptr->next;

        if (proc->priority > ((process *)next->object)->priority ||
            (proc->priority == ((process *)next->object)->priority &&
             proc->start_time < ((process *)(next->object))->start_time)) {
            previous_ptr->next = current_ptr->next;
            current_ptr->next = next->next;
            next->next = current_ptr;
            previous_ptr = next;
        } else {
            previous_ptr = current_ptr;
            current_ptr = current_ptr->next;
        }
    }
}

// Get the next process that should be run.
static process *determine_next_process() {
    // Queue is empty
    if (PRIOP_queue->next == NULL) {
        return NULL;
    }

    semi_sort_queue();
    return queue_poll(PRIOP_queue);
}

process *PRIOP_tick(process *running_process) {
    if (running_process == NULL || running_process->time_left == 0) {
        running_process = determine_next_process();
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }

    return running_process;
}

int PRIOP_startup() {
    PRIOP_queue = new_queue();
    if (PRIOP_queue == NULL) {
        return 1;
    }
    return 0;
}

process *PRIOP_new_arrival(process *arriving_process,
                           process *running_process) {
    if (arriving_process != NULL) {
        if (running_process == NULL) {
            running_process = arriving_process;
        } else if (arriving_process->priority > running_process->priority) {
            queue_add(running_process, PRIOP_queue);
            running_process = arriving_process;
        } else {
            queue_add(arriving_process, PRIOP_queue);
        }
    }
    return running_process;
}

void PRIOP_finish() { free_queue(PRIOP_queue); }
