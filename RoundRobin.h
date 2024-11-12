#pragma once
/**
 * @file RoundRobin.h
 * @brief Contains the round robin class definitions
 * 
 * Contains the definition of the round robin class and the node struct.
 * Creates 4 threads using "Queues" to simulate a round robin scheduler.
 * 
 * @date 11/5/24
 * @author Fiya Clerget
 */

#include "Queue.h"
#include "Task.h"
#include <vector>
#include <iostream>
using namespace std;

struct Thread {
    Queue taskQueue;
    int priority;   // fixed priority for the thread
    int length;     // Length of the task created
    int frequency;  // fixed period of task execution for this thread
    // In Round Robin scheduling all threads have the same priority and frequency
};

class RoundRobinScheduler {
    public:
        // Constructor and Destructor
        RoundRobinScheduler();
        ~RoundRobinScheduler();

        // Functions to run the examples
        void runExampleStructured(); 
        void runExampleRandom();    
        
    protected:
        vector<Thread> threads;       // Stores each thread with its queue, frequency, and ID
        vector<int> nextReleaseTimes; // Tracks the next release time for each thread

        void addTask(int length);
        void incrementTopTask(int length);  // New method to increment top task for a given thread
    
};

