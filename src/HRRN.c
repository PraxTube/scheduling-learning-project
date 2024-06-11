#include "../lib/HRRN.h"

#include <stdio.h>

static queue_object *HRRN_queue;
static unsigned int elapsed;

// Calculate response ratio for a given process.
// This assumes that the duration (initial `time_left`)
// is stored inside proc->priority.
// This isn't super clean, but we don't use priority for anything else here.
static float priority(process *proc) {
    if (proc == NULL) {
        return 0;
    }
    if (proc->time_left == 0) {
        return 0;
    }
    unsigned int wait_time = elapsed - proc->start_time;
    float prio = (float)(wait_time + proc->priority) / (float)proc->priority;
    return prio;
}

// Put the process with the biggest response ratio at the end of the queue. It
// doesn't actually sort the queue and has O(n) as a result.
static void semi_sort_queue() {
    queue_object *previous_ptr = HRRN_queue;
    queue_object *current_ptr = HRRN_queue->next;

    while (current_ptr->next != NULL) {
        process *proc = current_ptr->object;
        queue_object *next = current_ptr->next;

        float prio = priority(proc);
        if (prio > priority(next->object) ||
            (prio == priority(next->object) &&
             ((process *)(current_ptr->object))->start_time <
                 ((process *)(next->object))->start_time)) {
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
    if (HRRN_queue->next == NULL) {
        return NULL;
    }
    // Exactly one element in queue
    if (HRRN_queue->next->next == NULL) {
        return queue_poll(HRRN_queue);
    }

    semi_sort_queue();
    return queue_poll(HRRN_queue);
}

process *HRRN_tick(process *running_process) {
    if (running_process == NULL || running_process->time_left == 0) {
        running_process = determine_next_process();
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }

    elapsed += 1;
    return running_process;
}

int HRRN_startup() {
    HRRN_queue = new_queue();
    elapsed = 0;
    if (HRRN_queue == NULL) {
        return 1;
    }
    return 0;
}

process *HRRN_new_arrival(process *arriving_process, process *running_process) {
    if (arriving_process != NULL) {
        arriving_process->priority = arriving_process->time_left;
        queue_add(arriving_process, HRRN_queue);
    }
    return running_process;
}

void HRRN_finish() { free_queue(HRRN_queue); }
