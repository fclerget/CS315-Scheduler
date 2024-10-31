/**
 * @file Queue.h
 * @brief Contains the queue class definitions
 *
 * Contains the definition of the squeue class and the node struct.
 * The queue class is used to store tasks in a FIFO order.
 *
 * @date 10/29/24
 * @author Fiya Clerget
 */


#pragma once
#include "Task.h"

struct Node {
    Task taskData;
    Node* prevTask;
};


class Queue {
public:

    // Constructor and Destructor
    Queue();
    ~Queue();

    // Push and Pop methods
    void push(Task task);
    void pop();

    bool isEmpty();  // Bool to check if the queue is empty

    void printQueue();  // Function to print the queue
    void runExample();  // Function to run the example
private:
    Node* head;  // Top of the queue
};
