/**
 * @file Stack.h
 * @brief Contains the stack class definitions
 * 
 * Contains the definition of the stack class and the node struct.
 * The stack class is used to store tasks in a LIFO order.
 * Includes a top method to access the top task without popping.
 *
 * @date 10/31/24
 * @author Marcello Novak
 */


#pragma once
#include "Task.h"

struct StackNode {
    Task taskData;
    StackNode* nextTask;
    StackNode* prevTask;  // It's doubly linked so I can print it easier
};

class Stack {
private:
    StackNode* head;  // Top of the stack
    StackNode* tail;  // Bottom of the stack (new)
public:

    // Constructor and Destructor
    Stack();
    ~Stack();
    
    // Push and Pop methods
    void push(Task task);
    void pop();

    Task* top();     // Pointer for top task, so it can be accessed without popping
    bool isEmpty();  // Bool to check if the stack is empty

    void printStack();  // Function to print the stack
    void runExample();  // Function to run the example

};