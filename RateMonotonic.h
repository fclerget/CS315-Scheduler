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
#include "SchedulerCommon.h"
#include "Task.h"
#include <vector>
#include <iostream>
using namespace std;

class RateMonotonicScheduler {
    public:
        enum class ExampleType { STRUCTURED, STARVED };

        // Constructor and Destructor
        RateMonotonicScheduler(ExampleType exampleType);
        ~RateMonotonicScheduler();

        // Functions to run the examples
        void runExample();

    protected:
        vector<Thread> threads;       // Stores each thread with its queue, frequency, and ID
        vector<int> nextReleaseTimes; // Tracks the next release time for each thread

        void addTask(int priority);
        void incrementTopTask(int priority);
};