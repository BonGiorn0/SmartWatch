#include "CircularBuffer.h"

void circ_buffer_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
}

int circ_buffer_is_empty(CircularBuffer *cb) {
    return (cb->head == cb->tail);
}

int circ_buffer_is_full(CircularBuffer *cb) {
    return ((cb->head + 1) % CIRC_BUFFER_SIZE == cb->tail);
}

void circ_buffer_put(CircularBuffer *cb, uint8_t data) {
    if (!circ_buffer_is_full(cb)) {
        cb->buffer[cb->head] = data;
        cb->head = (cb->head + 1) % CIRC_BUFFER_SIZE;
    }
}

void circ_buffer_get(CircularBuffer *cb, uint8_t *dst) {
    if (!circ_buffer_is_empty(cb)) {
        *dst = cb->buffer[cb->tail];
        cb->tail = (cb->tail + 1) % CIRC_BUFFER_SIZE;
    }
}
