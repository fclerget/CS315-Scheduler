/**
 * @file RateMonotonic.h
 * @brief Contains the rate monotonic class definitions
 * 
 * Contains the definition of the rate monotonic class and the node struct.
 * Uses 4 threads using "Queues" to simulate a rate monotonic scheduler.
 * 
 * @date 10/31/24
 * @author Marcello Novak
 */

#pragma once
#include "Queue.h"
#include "Task.h"
#include <vector>
#include <iostream>
using namespace std;

struct Thread {
    Queue taskQueue;
    int priority;   // Priority rank for the thread
    int length;     // Length of the task created
    int frequency;  // Period of task execution for this thread
};

class RateMonotonicScheduler {
    public:
        // Constructor and Destructor
        RateMonotonicScheduler();
        ~RateMonotonicScheduler();

        // Functions to run the examples
        void runExampleStructured(); 
        void runExampleRandom();    
        
    protected:
        vector<Thread> threads;       // Stores each thread with its queue, frequency, and ID
        vector<int> nextReleaseTimes; // Tracks the next release time for each thread

        void addTask(int threadID);
        void incrementTopTask(int threadID);  // New method to increment top task for a given thread
    
};
