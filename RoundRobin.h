#pragma once
/**
 * @file RoundRobin.h
 * @brief Contains the round robin class definitions
 * 
 * Contains the definition of the round robin class and the node struct.
 * Creates 4 threads using "Queues" to simulate a round robin scheduler.
 * 
 * @date 11/5/24
 * @author Fiya Clerget, Marcello Novak
 */

#include "Queue.h"
#include "SchedulerCommon.h"
#include "RateMonotonic.h"
#include "Task.h"
#include <vector>
#include <iostream>
using namespace std;

class RoundRobinScheduler {
    protected:
        vector<Thread> threads;       // Stores each thread with its queue, frequency, and ID
        vector<int> nextReleaseTimes; // Tracks the next release time for each thread

        void addTask(unsigned long long threadIndex);
        void incrementCurrentTask(unsigned long long index);

        unsigned long long currentThreadIndex = 0;  // Index of the current thread being serviced
    public:
        enum class ExampleType { STRUCTURED, STARVED };

        // Constructor and Destructor
        RoundRobinScheduler(ExampleType exampleType);
        ~RoundRobinScheduler();

        // Function to run the example
        void runExample();

};
