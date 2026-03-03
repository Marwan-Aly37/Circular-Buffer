#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include <stdint.h>

#define CIRCULAR_BUFFER_SIZE 10   // Define the size of the circular buffer

typedef struct Node
{
    uint16_t data;
    struct Node* next;
    struct Node* prev;
}node;


typedef struct CircularBuffer
{
    node buffer[CIRCULAR_BUFFER_SIZE];
    node* head;
    node* tail;
    node* current;

}circ_buff;

void initBuffer(circ_buff* cb);
void insert(circ_buff* cb, uint16_t value);
void show(circ_buff* cb);
void latest(circ_buff* cb);

uint32_t sum_buff(circ_buff* cb);
float avg_buff(circ_buff* cb);

#endif