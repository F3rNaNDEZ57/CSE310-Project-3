#ifndef STACK_H
#define STACK_H

#include "data_structures.h"

// Define a stack node for storing vertices
typedef struct StackNode {
    int vertexIndex; // You can store pVERTEX if you prefer pointers
    StackNode* next;

    StackNode(int idx, StackNode* nxt = nullptr) : vertexIndex(idx), next(nxt) {}
} StackNode;

// Define the stack itself
class Stack {
public:
    Stack() : top(nullptr) {}
    ~Stack();

    void push(int vertexIndex);
    int pop();
    bool isEmpty() const;

private:
    StackNode* top; // Top of the stack
};

#endif // STACK_H
