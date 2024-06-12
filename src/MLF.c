#include "../lib/MLF.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    unsigned int elapsed;
    unsigned int level;
} process_info;

const unsigned int LEVELS = 4;
static queue_object **MLF_queues;
static queue_object *process_info_queue;

static queue_object *next_lower_level(process_info *proc_info) {
    if (proc_info->level >= LEVELS) {
        printf("Should never happen, level: %d\n", proc_info->level);
        return NULL;
    }

    if (proc_info->level < LEVELS - 1) {
        proc_info->level += 1;
    }
    return MLF_queues[proc_info->level];
}

// Put the process with the highest priority at the end of the queue. It
// doesn't actually sort the queue and has O(n) as a result.
static void semi_sort_queue(queue_object *queue) {
    queue_object *previous_ptr = queue;
    queue_object *current_ptr = queue->next;

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
    if (MLF_queues == NULL) {
        return NULL;
    }

    for (int i = 0; i < LEVELS; i++) {
        // Check if level queue is not empty
        if (MLF_queues[i]->next != NULL) {
            semi_sort_queue(MLF_queues[i]);
            return queue_poll(MLF_queues[i]);
        }
    }
    return NULL;
}

static process_info *get_process_info(process *proc) {
    if (process_info_queue == NULL) {
        return NULL;
    }

    queue_object *current_ptr = process_info_queue;
    while (current_ptr->next != NULL) {
        process_info *next = current_ptr->next->object;
        if (next->id == proc->id) {
            return next;
        }
        current_ptr = current_ptr->next;
    }
    return NULL;
}

void print_process(process *proc) {
    process_info *proc_info = get_process_info(proc);
    printf("\nid: %c, time_left: %d, elapsed: %d, level: %d\n", proc->id, proc->time_left, proc_info->elapsed, proc_info->level);
}

process *MLF_tick(process *running_process) {
    if (running_process == NULL || running_process->time_left == 0) {
        running_process = determine_next_process();
    }
    if (running_process != NULL) {
        // print_process(running_process);
        process_info *proc_info = get_process_info(running_process);
        // Process ran out of time, put in next lower level
        if (proc_info->elapsed >= (1 << proc_info->level)) {
            proc_info->elapsed = 0;
            queue_add(running_process, next_lower_level(proc_info));
            running_process = determine_next_process();
            if (running_process != NULL) {
                process_info *proc_info = get_process_info(running_process);
                running_process->time_left--;
                proc_info->elapsed++;
                // print_process(running_process);
            }
        } else {
            running_process->time_left--;
            proc_info->elapsed++;
            // print_process(running_process);
        }
    }
    return running_process;
}

int MLF_startup() {
    MLF_queues = (queue_object **)malloc(LEVELS * sizeof(queue_object *));
    process_info_queue = new_queue();

    if (MLF_queues == NULL) {
        return 1;
    }

    for (unsigned int i = 0; i < LEVELS; i++) {
        MLF_queues[i] = new_queue();
    }

    return 0;
}

process *MLF_new_arrival(process *arriving_process, process *running_process) {
    if (arriving_process != NULL) {
        process_info *new_process_info = (process_info *)malloc(sizeof(process_info));
        new_process_info->id = arriving_process->id;
        new_process_info->elapsed = 0;
        new_process_info->level = 0;
        queue_add(new_process_info, process_info_queue);

        if (running_process == NULL) {
            running_process = arriving_process;
        } else if (arriving_process->priority > running_process->priority) {
            // Replace running process
            process_info *proc_info = get_process_info(running_process);
            if (proc_info->elapsed >= (1 << proc_info->level)) {
                proc_info->elapsed = 0;
                queue_add(running_process, next_lower_level(proc_info));
            } else {
                queue_add(running_process, MLF_queues[proc_info->level]);
            }
            running_process = arriving_process;
        } else {
            // Add to first level queue
            queue_add(arriving_process, MLF_queues[0]);
        }
    }
    return running_process;
}

void MLF_finish() {
    for (unsigned int i = 0; i < LEVELS; i++) {
        free_queue(MLF_queues[i]);
    }
    free(MLF_queues);
}
