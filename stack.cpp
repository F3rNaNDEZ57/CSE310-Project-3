#include "stack.h"
#include <iostream>

// Destructor to clean up the stack
Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Push a vertex index onto the stack
void Stack::push(int vertexIndex) {
    StackNode* newNode = new StackNode(vertexIndex, top);
    top = newNode;
}

// Pop the top vertex index off the stack
int Stack::pop() {
    if (isEmpty()) {
        std::cerr << "Stack is empty, cannot pop" << std::endl;
        return -1; // Error value, adjust as necessary
    }
    StackNode* temp = top;
    int vertexIndex = top->vertexIndex;
    top = top->next;
    delete temp;
    return vertexIndex;
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return top == nullptr;
}
