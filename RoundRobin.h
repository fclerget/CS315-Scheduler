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
#include "SchedulerCommon.h"
#include "RateMonotonic.h"
#include "Task.h"
#include <vector>
#include <iostream>
using namespace std;

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

        int currentThreadIndex = 0;  // Index of the current thread being serviced
};

