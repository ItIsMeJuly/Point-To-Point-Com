#include "Queue.h"
#include <stdlib.h>

void Queue::push(uint16_t value)
{
    if(count == 0)
    {
        head = new Node();
        head->value = value;
        tail = head;
    }
    else
    {
        Node* node = new Node();
        node->value = value;
        node->next = head;
        head = node;
    }

    count += 1;
}

uint16_t Queue::pop()
{
    if(count == 0)
    {
        return 0;
    }

    uint16_t holder = tail->value;
    
    count -= 1;

    if(count == 1)
    {
        delete head;

        head->next = nullptr;
        tail->next = nullptr;

        head = nullptr;
        tail = nullptr;

        return holder;
    }

    Node* traverse = head;
    while(traverse->next->next != nullptr)
    {
        traverse = traverse->next;
    }

    delete tail;
    traverse->next = nullptr;
    tail = traverse;

    return holder;
}

uint16_t Queue::size()
{
    return count;
}