/**
 * @file RoundRobin.cpp
 * @brief Round Robin scheduler implementation.
 * 
 * Example of a scheduler implemented using round robin scheduling.
 * Creates 4 threads using "Queues" to simulate a round robin scheduler.
 * 
 * @date 11/5/24
 * @author Fiya Clerget
 */

#include <algorithm>  // For find_if
#include "RoundRobin.h"
using namespace std;

// Constructor initializes threads and next release times
RoundRobinScheduler::RoundRobinScheduler() {
    // Initialize threads with their respective frequencies, queues, and IDs
    threads = {
        {Queue(), 1, 1, 4},   // Thread 1: size 1, frequency 3
        {Queue(), 1, 2, 4},   // Thread 2: size 1, frequency 6
        {Queue(), 1, 4, 4},  // Thread 3: size 2, frequency 12
        {Queue(), 1, 6, 4}   // Thread 4: size 4, frequency 24
    };

    // Set initial next release times based on the threads' lengths
    for (const auto& thread : threads) {
        nextReleaseTimes.push_back(thread.length);
    }
}



// Add a new task to the specified thread's queue
void RoundRobinScheduler::addTask(int length) {
    // Find the thread by priority and get its length as requested time
    auto it = find_if(threads.begin(), threads.end(), [length](const Thread& t) {
        return t.length == length;
    });

    if (it != threads.end()) {
        int requestedTime = it->length;  // Use the thread's length as the requested time for the task
        it->taskQueue.push(Task(requestedTime));
    }
}

// Increment the `serviced` field of the top task in the specified thread
void RoundRobinScheduler::incrementTopTask(int length) {
    // Find the thread by priority
    auto it = find_if(threads.begin(), threads.end(), [length](const Thread& t) {
        return t.length == length;
    });

    if (it != threads.end() && !it->taskQueue.isEmpty()) {
        Task* topTask = it->taskQueue.top();
        topTask->setServiced(topTask->getServiced() + 1);
    }
}

// Destructor to clear the queues in each thread
RoundRobinScheduler::~RoundRobinScheduler() {
    for (auto& thread : threads) {
        while (!thread.taskQueue.isEmpty()) {
            thread.taskQueue.pop();
        }
    }
}