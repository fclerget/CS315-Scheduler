/**
 * @file Queue.cpp
 * @brief Basic queue for scheduler implementation.
 *
 * Example of a scheduler implemented using a queue.
 * Intended to show why a queue is a decent choice for a scheduler.
 *
 * @date 10/23/24
 * @authors Fiya Clerget and Marcello Novak
 */

#include "Queue.h"
#include <stdio.h>  // For printf
#include <stdlib.h> // For rand
#include <ctime>    // For time(NULL)

// Constructor and Destructor
Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

// Push method to add task at the end (tail) of the queue
void Queue::push(Task task) {
    QueueNode* newNode = new QueueNode{task, nullptr, tail};  // Create new node with task data

    // If the queue is not empty, link the new node as the nextTask of the tail
    if (tail != nullptr) {
        tail->nextTask = newNode;
    }
    tail = newNode;  // Move tail to the new node

    // If the queue was empty, set head to the new node as well
    if (head == nullptr) {
        head = newNode;
    }
}

// Pop method to remove task from the head (front) of the queue
void Queue::pop() {
    if (!isEmpty()) {
        QueueNode* temp = head;  // Save the current head
        head = head->nextTask;  // Move head to the next task

        if (head != nullptr) {
            head->prevTask = nullptr;  // Update new head's prevTask to null
        } else {
            tail = nullptr;  // If the queue is now empty, set tail to null
        }

        delete temp; // Delete the old head
    } else {
        printf("Queue is empty, cannot pop\n");
    }
}

// Top method to access front task without popping
Task* Queue::top() {
    if (!isEmpty()) {
        return &(head->taskData);  // Return pointer to front task
    } else {
        printf("Queue is empty, cannot view top\n");
        return nullptr;
    }
}

// Bool to check if the queue is empty
bool Queue::isEmpty() {
    return head == nullptr;
}

// Function to print the queue from front to end
void Queue::printQueue() {
    printf("| ");
    QueueNode* current = head;  // Start from the head (front of the queue)
    while (current != nullptr) {
        printf("[%d, %d] ", current->taskData.getRequested(), current->taskData.getServiced());
        current = current->nextTask;  // Move towards the end (tail) of the queue
    }
    printf("\n");
}

// Queue scheduler example function
void Queue::runExample() {
    srand(static_cast<unsigned int>(time(NULL)));  // Seed the random number generator

    // Counters for tasks created and serviced
    int taskCounter = 0;
    int servicedCounter = 0;

    int timeCounter = 0;  
    while (timeCounter <= 10000) {  // Example runs for 1000 "time units"

        // 20% chance of adding a new task each "time unit"
        if (rand() % 5 == 0) {
            Task newTask(rand() % 6 + 1);  // req between 1 and 5 "time units"
            push(newTask);
            taskCounter++;  // Increment task counter
        }

        // Print the current queue
        printQueue();
        
        // Iterate front task's serviced counter
        if (!isEmpty()) {
            Task* currentTask = top();  // Returns pointer to front task

            // If task completed, pop, else increment serviced counter
            if (currentTask->getRequested() == currentTask->getServiced()) {
                pop();
                servicedCounter++;  // Task completed
                taskCounter--;  // Task removed from queue
            } else {
                currentTask->setServiced(currentTask->getServiced() + 1);
            }
        }

        timeCounter++;  // Increment time counter
    }

    // Print tasks completed and tasks left in queue
    printf("Tasks completed: %d\n", servicedCounter);
    printf("Tasks left in queue: %d\n", taskCounter);
}