#include "circular_buffer.h"

CircularBuffer::CircularBuffer()
{
    buffer_size = DEFAULT_BUFFER_SIZE;
    this->head = new node;
    this->head->data = 0;
    this->current = this->head;

    for (int i = 0; i < buffer_size - 1; i++)
    {
        node* new_node = new node;
        new_node->data = 0;
        new_node->prev = this->current;
        this->current->next = new_node;
        this->current = this->current->next; 
    }
    this->tail = this->current;
    this->tail->next = this->head;
    this->head->prev = this->tail;
    this->current = this->head;
}

void CircularBuffer::insert(float value)
{
    this->current->data = value;
    this->current = this->current->next;
}

void CircularBuffer::show() const
{   
    node* temp = this->current;
    LOG_DEBUG("%s", "Buffer: ");
    while((temp -> next) != this->current)
    {
        float value = temp->data;
        temp = temp->next;
        LOG_DEBUG("%.2f ", value);
    }
    
    LOG_DEBUG("%.2f\n", temp->data);
}

float CircularBuffer::latest() const
{
    return this->current->prev->data;
}

void CircularBuffer::resize(int size)
{
    if(size < buffer_size) 
    { 
        int diff = buffer_size - size; 
        node* delete_node = this->current->next; 
        for(int i = 0; i < diff; i++) 
        { 
            node* next_node = delete_node->next; 
            next_node->prev = this->current; 
            this->current->next = next_node; 
            
            if(this->tail == delete_node)
            {
                this->tail = delete_node->prev;
            }

            if(this->head == delete_node)
            {
                this->head = next_node;
            }
            
            delete delete_node; 
            delete_node = next_node; 
        } 
    }

    else if(size > buffer_size)
    {
        int diff = size - buffer_size;
        for(int i = 0; i<diff; i++)
        {
            node* new_node = new node;
            new_node->data = 0;
            new_node->prev = this->tail;
            new_node->next = this->head;
            this->tail->next = new_node;
            this->head->prev = new_node;
            tail = new_node;
        }
    }

    this->buffer_size = size;
}

float CircularBuffer::sum() const
{
    float sum = 0.0;
    node* temp = this->head;

    while(temp != this->tail)
    {
        sum += temp->data;
        temp = temp->next;
    }

    sum += temp->data;
    return sum;
}

float CircularBuffer::average() const
{
    float sum = this->sum();
    float average = (float)sum / buffer_size;
    return average;
}

float CircularBuffer::difference() const
{
    float diff = this->current->prev->data - this->current->prev->prev->data;   
    return diff;
}

float CircularBuffer::find(int index) const
{
    if(index > buffer_size - 1 || index < 0)
    {
        LOG_WARN("Index is out of range!");
        return -1.0;
    }

    node* finder;
    
    if(index > buffer_size/2)
    {
        int steps = buffer_size -1 -index;
        finder = this->tail;
        for(int i = 0; i < steps;i++)
        {
            finder = finder->prev;
        }
    }

    else
    {
        finder = this->head;
        for(int i = 0; i < index;i++)
        {
            finder = finder->next;
        }
    }

    return finder->data;
}

int CircularBuffer::copy(CircularBuffer* cb) const
{
    if(cb == nullptr)
    {
        return -1;
    }
    int size = cb->get_size();
    int size_2 = this->get_size();
    node* ptr_1 = cb->head;
    node* ptr_2 = this->head;

    if(size != size_2)
    {
        LOG_WARN("Buffers are not the same size!");
    }

    for(int i = 0; i<size; i++)
    {
        ptr_2->data = ptr_1->data;
        ptr_1 = ptr_1->next;
        ptr_2 = ptr_2->next;
    }
    
    if(size <= size_2)
    {
        
        int diff = size_2 - size;

        for(int i = 0; i<diff;i++)
        {
            ptr_2->data = 0;
            ptr_2 = ptr_2->next;
        }      
    }
    
    return 1;    
}

int CircularBuffer::get_size() const
{
    return buffer_size;
}

CircularBuffer::~CircularBuffer()
{
    node* temp = this->head;
    for(int i = 0; i <buffer_size; i++)
    {
        node* node_next = temp->next;
        delete temp;
        temp = node_next;
    }

}

void CircularBuffer::test()
{    
    CircularBuffer cb_test;
    cb_test.insert(10);
    cb_test.insert(20);
    cb_test.insert(30);
    cb_test.insert(40);
    cb_test.insert(50);
    cb_test.insert(60);
    cb_test.insert(70);
    cb_test.insert(80);
    cb_test.insert(90);
    cb_test.insert(100);

    
    cb_test.show();
    float x = cb_test.latest();
    LOG_INFO("Latest: %.2f",x);

    int sum = cb_test.sum();
    LOG_INFO("Sum: %d", sum);
    
    float average = cb_test.average();
    LOG_INFO("Average: %.2f", average);
    
    cb_test.resize(20);
    cb_test.insert(110);
    cb_test.insert(120);
    cb_test.insert(130);
    cb_test.insert(140);
    cb_test.insert(150);
    cb_test.insert(160);
    cb_test.insert(170);
    cb_test.insert(180);
    cb_test.insert(190);
    cb_test.insert(200);
    cb_test.insert(210);
    cb_test.insert(220);
    cb_test.insert(230);
    cb_test.insert(240);
    cb_test.insert(250);
    cb_test.insert(260);
    cb_test.insert(270);
    cb_test.insert(280);
    cb_test.insert(290);
    cb_test.insert(300);
    cb_test.show();

    float diff =cb_test.difference();
    LOG_INFO("Difference: %.2f",diff);

    CircularBuffer cb_test_2;
    cb_test_2.resize(15);
    cb_test_2.copy(&cb_test);
    cb_test_2.show();

    float y = cb_test.find(15);
    LOG_DEBUG("Found: %.2f\n", y);
}

int main()
{
    CircularBuffer cb;
    cb.test();
    
    return 0;
}