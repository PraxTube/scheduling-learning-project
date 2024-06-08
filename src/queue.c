#include "../lib/queue.h"

#include <stdio.h>
#include <stdlib.h>

int queue_add(void *new_object, queue_object *queue) {
    queue_object *ptr = (queue_object *)malloc(sizeof(queue_object));

    if (ptr == NULL) {
        return 1;
    }

    if (queue->next != NULL) {
        queue_object *tmp_ptr = queue->next;
        ptr->next = tmp_ptr;
    }

    queue->object = ptr;
    ptr->object = new_object;

    return 0;
}

void *queue_poll(queue_object *queue) {
    queue_object *second_last = queue;
    queue_object *current_ptr = queue;
    while (1) {
        current_ptr = current_ptr->next;
        if (current_ptr->next == NULL) {
            break;
        }

        second_last = current_ptr;
    }

    if (second_last->next == NULL) {
        return NULL;
    }

    void *last_element = second_last->next->object;
    second_last->next = NULL;

    return last_element;
}

queue_object *new_queue() {
    // TODO
    return NULL;
}

void free_queue(queue_object *queue) {
    if (queue == NULL) {
        // ?
    }

    while (queue->next != NULL) {
        queue_object *previous_item = queue;
        queue = queue->next;
        free(previous_item);
    }
}

void *queue_peek(queue_object *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return queue->object;
}
