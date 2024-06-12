#include "../lib/queue.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int queue_add(void *new_object, queue_object *queue) {
    if (queue == NULL) {
        return 1;
    }

    queue_object *ptr = (queue_object *)malloc(sizeof(queue_object));

    if (ptr == NULL) {
        return 1;
    }

    ptr->next = queue->next;
    queue->next = ptr;
    ptr->object = new_object;

    return 0;
}

void *queue_poll(queue_object *queue) {
    if (queue == NULL) {
        return NULL;
    }
    if (queue->next == NULL) {
        return NULL;
    }

    queue_object *second_last = queue;
    queue_object *current_ptr = queue;
    while (current_ptr->next != NULL) {
        second_last = current_ptr;
        current_ptr = current_ptr->next;
    }

    void *last_element = second_last->next->object;
    free(second_last->next);
    second_last->next = NULL;

    return last_element;
}

queue_object *new_queue() {
    queue_object *queue = (queue_object *)malloc(sizeof(queue_object));
    if (queue == NULL) {
        return NULL;
    }
    return queue;
}

void free_queue(queue_object *queue) {
    if (queue == NULL) {
        return;
    }

    queue_object *current_ptr = queue;

    while (current_ptr != NULL) {
        queue_object *previous_ptr = current_ptr;
        current_ptr = current_ptr->next;
        free(previous_ptr);
    }
}

void *queue_peek(queue_object *queue) {
    if (queue == NULL) {
        return NULL;
    }
    queue_object *current_ptr = queue;

    while (1) {
        if (current_ptr->next == NULL) {
            return current_ptr->object;
        }
        current_ptr = current_ptr->next;
    }
    return current_ptr;
}
