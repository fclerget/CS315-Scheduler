/**
 * @file Queue.cpp
 * @brief Basic queue for scheduler implementation.
 *
 *
 * @author Marcello Novak and Fiya Clerget
 * @date 10/23/24
 */

#include "Task.h"
#include "Queue.h"
#include <stdio.h>  // For printf
#include <stdlib.h> // For rand
#include <ctime>    // For time(NULL)

 // Constructor and Destructor
Queue::Queue() : head(nullptr) {}  // Both head and tail are null

Queue::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

// Push and Pop methods from top of stack
void Queue::push(Task task) {
    Node* newNode = new Node{ task, nullptr };  // Create new node with task data

    if (head != nullptr) {
        head->prevTask = newNode;
    }
    head = newNode;

    // If the queue is empty
    if (head == nullptr) {
        head = newNode;
    }
    
}

void Queue::pop() {
    if (!isEmpty()) {
        Node* temp = head;  // Save the current head
        head = head->nextTask;  // Move head to the next task

        if (head != nullptr) {
            head->prevTask = nullptr;  // If stack isn't empty, update new head's prevTask
        }
        else {
            tail = nullptr;  // If the stack is now empty, set tail to null
        }

        delete temp; // Delete the old head

    }
    else {
        printf("Stack is empty, cannot pop\n");
    }
}

// Top method to access top task without popping
Task* Stack::top() {
    if (!isEmpty()) {
        return &(head->taskData);  // Return pointer to top task
    }
    else {
        printf("Stack is empty, cannot view top\n");
        return nullptr;
    }
}

// Bool to check if the stack is empty
bool Stack::isEmpty() {
    return head == nullptr;
}

// Function to print the stack (bottom to top for easier reading)
void Stack::printStack() {
    printf("| ");
    Node* current = tail;
    while (current != nullptr) {
        printf("[%d, %d] ", current->taskData.getRequested(), current->taskData.getServiced());
        current = current->prevTask;  // Move towards the top of the stack
    }
    printf("\n");
}