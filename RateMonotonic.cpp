/**
 * @file RateMonotonic.cpp
 * @brief Rate monotonic scheduler implementation.
 * 
 * Example of a scheduler implemented using rate monotonic scheduling.
 * Uses 4 threads using "Queues" to simulate a rate monotonic scheduler.
 * 
 * @date 10/31/24
 * @author Marcello Novak
 */

#include <algorithm>  // For find_if
#include "RateMonotonic.h"
using namespace std;

// Constructor initializes threads and next release times
RateMonotonicScheduler::RateMonotonicScheduler() {
    // Initialize threads with their respective frequencies, queues, and IDs
    threads = {
        {Queue(), 1, 1, 3},   // Thread 1: size 1, frequency 3
        {Queue(), 2, 2, 6},   // Thread 2: size 1, frequency 6
        {Queue(), 3, 2, 12},  // Thread 3: size 2, frequency 12
        {Queue(), 4, 4, 24}   // Thread 4: size 4, frequency 24
    };

    // Set initial next release times based on the threads' frequencies
    for (const auto& thread : threads) {
        nextReleaseTimes.push_back(thread.frequency);
    }
}

// Destructor to clear the queues in each thread
RateMonotonicScheduler::~RateMonotonicScheduler() {
    for (auto& thread : threads) {
        while (!thread.taskQueue.isEmpty()) {
            thread.taskQueue.pop();
        }
    }
}

// Main scheduler loop with scrolling thread status display
void RateMonotonicScheduler::runExampleStructured() {
    const int frameBoundary = 24;  // Global frame boundary for the scheduler
    int taskCounter = 0;     // Counter for tasks created and serviced
    int servicedCounter = 0;  

    int timeCounter = 0;
    while (timeCounter < 10008) {
        // Reset to the start of the frame boundary every 24 units
        if (timeCounter % frameBoundary == 0) {
            cout << "| | | | | New\n";
        }

        // Add tasks to each thread's queue based on release times within the frame
        for (size_t i = 0; i < threads.size(); ++i) {
            if (timeCounter >= nextReleaseTimes[i]) {
                addTask(threads[i].priority);
                nextReleaseTimes[i] += threads[i].frequency;  // Schedule the next release within frame
                taskCounter++;  // Increment task counter when a task is created
            }
        }

        // Get and service the highest-priority task
        Task* highestPriorityTask = nullptr;
        int highestPriorityThreadIndex = -1;

        // Find the highest-priority task across all threads based on priority
        for (size_t i = 0; i < threads.size(); ++i) {
            auto& thread = threads[i];
            if (!thread.taskQueue.isEmpty()) {
                Task* topTask = thread.taskQueue.top();
                if (highestPriorityTask == nullptr || thread.priority < threads[highestPriorityThreadIndex].priority) {
                    highestPriorityTask = topTask;
                    highestPriorityThreadIndex = i;
                }
            }
        }

        // Print the state of each thread (X for active, - for inactive)
        for (const auto& thread : threads) {
            if (highestPriorityTask != nullptr && thread.priority == threads[highestPriorityThreadIndex].priority) {
                cout << "X ";
            } else {
                cout << "- ";
            }
        }
        cout << "| " << (timeCounter % frameBoundary) + 1 << endl;  // Print frame time step

        // If we have a task to service, increment or complete it
        if (highestPriorityTask != nullptr && highestPriorityThreadIndex != -1) {
            incrementTopTask(threads[highestPriorityThreadIndex].priority);  // Increment top task of the selected thread

            // Check if task has completed
            if (highestPriorityTask->getServiced() == highestPriorityTask->getRequested()) {
                threads[highestPriorityThreadIndex].taskQueue.pop();
                servicedCounter++;  // Increment serviced counter when a task completes
            }
        }

        timeCounter++;
    }

    // Print the total counts after the scheduler run
    cout << "Total tasks created: " << taskCounter << endl;
    cout << "Total tasks serviced: " << servicedCounter << endl;
}

// Add a new task to the specified thread's queue
void RateMonotonicScheduler::addTask(int priority) {
    // Find the thread by priority and get its length as requested time
    auto it = find_if(threads.begin(), threads.end(), [priority](const Thread& t) {
        return t.priority == priority;
    });

    if (it != threads.end()) {
        int requestedTime = it->length;  // Use the thread's length as the requested time for the task
        it->taskQueue.push(Task(requestedTime));
    }
}

// Increment the `serviced` field of the top task in the specified thread
void RateMonotonicScheduler::incrementTopTask(int priority) {
    // Find the thread by priority
    auto it = find_if(threads.begin(), threads.end(), [priority](const Thread& t) {
        return t.priority == priority;
    });

    if (it != threads.end() && !it->taskQueue.isEmpty()) {
        Task* topTask = it->taskQueue.top();
        topTask->setServiced(topTask->getServiced() + 1);
    }
}