#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

class Queue
{
    struct Node
    {
        uint16_t value;
        Node* next;
    };

    Node* head;
    Node* tail;
    uint16_t count;

public:
    Queue(): head(nullptr), tail(nullptr) {}

    void push(uint16_t value);
    uint16_t pop();
    uint16_t size();
};

#endif