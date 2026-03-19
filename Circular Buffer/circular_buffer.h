#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include "config.h"

#define DEFAULT_BUFFER_SIZE 10
class CircularBuffer
{
    private:
    
    struct node
    {
        float data;
        struct node* next;
        struct node* prev;
    };

    int buffer_size;
    node* head;
    node* tail;
    node* current;
    
    
    public:
    
    CircularBuffer();
    ~CircularBuffer();
    
    void insert(float value);
    void show() const;
    void resize(int size);
    
    float latest() const;
    float sum() const;
    float average() const;
    float difference() const;
    
    int get_size() const;
    int copy(CircularBuffer* cb) const;

    void test();
    
    CircularBuffer(const CircularBuffer&) = delete;
    CircularBuffer& operator=(const CircularBuffer&) = delete;
};



#endif