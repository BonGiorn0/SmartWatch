#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "main.h"

#define CIRC_BUFFER_SIZE 300

typedef struct {
    uint8_t buffer[CIRC_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
} CircularBuffer;

void circ_buffer_init(CircularBuffer *cb);
int circ_buffer_is_empty(CircularBuffer *cb);
int circ_buffer_is_full(CircularBuffer *cb);
void circ_buffer_put(CircularBuffer *cb, uint8_t data);
void circ_buffer_get(CircularBuffer *cb, uint8_t *dst);

#endif
