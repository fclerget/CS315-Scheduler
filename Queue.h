/**
 * @file Queue.h
 * @brief Contains the queue class definitions
 *
 * Contains the definition of the queue class and the node struct.
 * The queue class is used to store tasks in a FIFO order.
 *
 * @date 10/31/24
 * @author Fiya Clerget, Marcello Novak
 */


#pragma once
#include "Task.h"

struct QueueNode {
    Task taskData;
    QueueNode* nextTask; 
    QueueNode* prevTask;
};

class Queue {
private:
    QueueNode* head;  // Front of the queue
    QueueNode* tail;  // End of the queue
public:

    // Constructor and Destructor
    Queue();
    ~Queue();

    // Push and Pop methods
    void push(Task task);
    void pop();

    Task* top();     // Pointer for front task, so it can be accessed without popping
    bool isEmpty();  // Bool to check if the queue is empty

    void printQueue();  // Function to print the queue
    void runExample();  // Function to run the example
};
