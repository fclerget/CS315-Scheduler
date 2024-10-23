/**
 * @file Stack.cpp
 * @brief Basic stack scheduler implementation.
 *
 * Example of a scheduler implemented using a stack.
 * Intended to show why a stack is not a good choice for a scheduler.
 *
 * @author Marcello Novak
 * @date 10/23/24
 */

#include "Task.h"
#include "Stack.h"
#include <stdio.h>  // For printf
#include <stdlib.h> // For rand
#include <ctime>    // For time(NULL)

// Constructor and Destructor
Stack::Stack() : head(nullptr), tail(nullptr) {}  // Both head and tail are null

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Push and Pop methods from top of stack
void Stack::push(Task task) {
    Node* newNode = new Node{task, head, nullptr};  // Create new node with task data

    // If stack isn't empty, update previous head's prevTask
    if (head != nullptr) {
        head->prevTask = newNode;
    }
    head = newNode; // Move head to the new node
    
    // If the stack was empty, set tail to the new node
    if (tail == nullptr) {
        tail = newNode;
    }
}

void Stack::pop() {
    if (!isEmpty()) {
        Node* temp = head;  // Save the current head
        head = head->nextTask;  // Move head to the next task

        if (head != nullptr) { 
            head->prevTask = nullptr;  // If stack isn't empty, update new head's prevTask
        } else {  
            tail = nullptr;  // If the stack is now empty, set tail to null
        }

        delete temp; // Delete the old head

    } else {
        printf("Stack is empty, cannot pop\n");
    }
}

// Top method to access top task without popping
Task* Stack::top() {
    if (!isEmpty()) {
        return &(head->taskData);  // Return pointer to top task
    } else {
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

// Stack scheduler example function
void Stack::runExample() {
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
        };
        
        // Iterate top task's serviced counter
        if (!isEmpty()) {
            Task* currentTask = Stack::top();  // Returns pointer to top task

            // If task completed, pop, else increment serviced counter
            if (currentTask->getRequested() == currentTask->getServiced()) {
                pop();
                servicedCounter++;  // Task completed
                taskCounter--;  // Task removed from stack
            } else {
                currentTask->setServiced(currentTask->getServiced() + 1);
            }
        }

        // Print the current stack
        printStack();

        timeCounter++;  // Increment time counter
    }

    // Print tasks completed and tasks left in stack
    printf("Tasks completed: %d\n", servicedCounter);
    printf("Tasks left in stack: %d\n", taskCounter);
}
