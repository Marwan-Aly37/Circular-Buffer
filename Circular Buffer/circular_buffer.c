#include "circular_buffer.h"

void initBuffer(circ_buff* cb)
{
    for (int i = 0; i < CIRCULAR_BUFFER_SIZE; i++)
    {
        cb->buffer[i].data = 0;
        cb->buffer[i].next = &cb->buffer[(i + 1) % CIRCULAR_BUFFER_SIZE];
        cb->buffer[i].prev = &cb->buffer[(i - 1 + CIRCULAR_BUFFER_SIZE) % CIRCULAR_BUFFER_SIZE];
    }

    cb->head = &cb->buffer[0];
    cb->tail = &cb->buffer[CIRCULAR_BUFFER_SIZE - 1];
    cb->current = cb->head;
}

void insert(circ_buff* cb, uint16_t value)
{
    cb->current->data = value;
    cb->current = cb->current->next;
}

void show(circ_buff* cb)
{   
    node* temp = cb->current;

    while((temp -> next) != cb->current)
    {
        uint16_t value = temp->data;
        temp = temp->next;
        printf("%d ", value);
    }
    
    printf("%d ", temp->data);
    printf("\n");
}

void latest(circ_buff* cb)
{
    printf("%d \n", cb->current->prev->data);
    printf("%d \n", cb->current->prev->prev->data);
}

uint32_t sum_buff(circ_buff* cb)
{
    uint32_t sum = 0;
    node* temp = cb->head;

    while(temp != cb->tail)
    {
        sum += temp->data;
        temp = temp->next;
    }

    sum += temp->data;
    return sum;
}

float avg_buff(circ_buff* cb)
{
    uint32_t sum = sum_buff(cb);
    float average = (float)sum / CIRCULAR_BUFFER_SIZE;
    return average;
}


int main()
{
    circ_buff* cb;

    initBuffer(cb);
    
    insert(cb, 10);
    insert(cb, 20);
    insert(cb, 30);
    insert(cb, 40);
    insert(cb, 50);
    insert(cb, 60);
    insert(cb, 70);
    insert(cb, 80);
    insert(cb, 90);
    insert(cb, 100);
    insert(cb, 110);

    show(cb);
    latest(cb);

    int sum = sum_buff(cb);
    printf("Sum: %d\n", sum);

    float average = avg_buff(cb);
    printf("Average: %.2f\n", average);
    
    return 0;
}