#include "../lib/SRTN.h"

static queue_object *SRTN_queue;

// Put the process with the smallest time left at the end of the queue. It
// doesn't actually sort the queue and has O(n) as a result.
static void semi_sort_queue() {
    queue_object *previous_ptr = SRTN_queue;
    queue_object *current_ptr = SRTN_queue->next;

    while (current_ptr->next != NULL) {
        process *proc = current_ptr->object;
        queue_object *next = current_ptr->next;

        if (proc->time_left < ((process *)next->object)->time_left ||
            (proc->time_left == ((process *)next->object)->time_left &&
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
    if (SRTN_queue->next == NULL) {
        return NULL;
    }
    // Exactly one element in queue
    if (SRTN_queue->next->next == NULL) {
        return queue_poll(SRTN_queue);
    }

    semi_sort_queue();
    return queue_poll(SRTN_queue);
}

process *SRTN_tick(process *running_process) {
    if (running_process == NULL || running_process->time_left == 0) {
        running_process = determine_next_process();
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }

    return running_process;
}

int SRTN_startup() {
    SRTN_queue = new_queue();
    if (SRTN_queue == NULL) {
        return 1;
    }
    return 0;
}

process *SRTN_new_arrival(process *arriving_process, process *running_process) {
    if (arriving_process != NULL) {
        if (running_process == NULL) {
            running_process = arriving_process;
        } else if (arriving_process->time_left < running_process->time_left) {
            queue_add(running_process, SRTN_queue);
            running_process = arriving_process;
        } else {
            queue_add(arriving_process, SRTN_queue);
        }
    }
    return running_process;
}

void SRTN_finish() { free_queue(SRTN_queue); }
