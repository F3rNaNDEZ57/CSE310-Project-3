#include "stack.h"

Stack::Stack() : head(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(VERTEX* vertex) {
    StackNode* newNode = new StackNode{vertex, head};
    head = newNode;
}

VERTEX* Stack::pop() {
    if (isEmpty()) {
        return nullptr;
    }
    StackNode* temp = head;
    VERTEX* popped = head->data;
    head = head->next;
    delete temp;
    return popped;
}

VERTEX* Stack::top() const {
    if (isEmpty()) {
        return nullptr;
    }
    return head->data;
}

bool Stack::isEmpty() const {
    return head == nullptr;
}
