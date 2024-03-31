#ifndef STACK_H
#define STACK_H

#include "data_structures.h" // Assuming VERTEX might be used

class Stack {
public:
    Stack();
    ~Stack();
    void push(VERTEX* vertex);
    VERTEX* pop();
    VERTEX* top() const;
    bool isEmpty() const;

private:
    struct StackNode {
        VERTEX* data;
        StackNode* next;
    };
    StackNode* head;
};

#endif // STACK_H
