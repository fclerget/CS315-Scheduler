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

#include "RateMonotonic.h"

// Constructor initializes threads and next release times
RateMonotonicScheduler::RateMonotonicScheduler() {
    // Initialize threads with their respective frequencies, queues, and IDs
    threads = {
        {Queue(), 3, 1},   // Thread 1: frequency 3
        {Queue(), 6, 2},   // Thread 2: frequency 6
        {Queue(), 12, 3},  // Thread 3: frequency 12
        {Queue(), 24, 4}   // Thread 4: frequency 24
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
    // Frame boundary and counters for tasks created and serviced
    const int frameBoundary = 24;
    int taskCounter = 0;
    int servicedCounter = 0;

    int timeCounter = 0;
    while (timeCounter < 10000) {
        // Reset to the start of the frame boundary every 24 units
        if (timeCounter % frameBoundary == 0) {
            std::cout << "\n--- New Frame (24 units) ---\n";
        }

        // Add tasks to each thread's queue based on release times within the frame
        for (size_t i = 0; i < threads.size(); ++i) {
            if (timeCounter >= nextReleaseTimes[i]) {
                addTask(threads[i].threadID);
                nextReleaseTimes[i] += threads[i].frequency;  // Schedule the next release within frame
                taskCounter++;  // Increment task counter when a task is created
            }
        }

        // Get and service the highest-priority task
        Task* highestPriorityTask = nullptr;
        int highestPriorityThreadID = -1;

        // Find the highest-priority task across all threads
        for (auto& thread : threads) {
            if (!thread.taskQueue.isEmpty()) {
                Task* topTask = thread.taskQueue.top();
                if (highestPriorityTask == nullptr || thread.frequency < threads[highestPriorityThreadID - 1].frequency) {
                    highestPriorityTask = topTask;
                    highestPriorityThreadID = thread.threadID;
                }
            }
        }

        // Print the state of each thread (X for active, - for inactive)
        for (auto& thread : threads) {
            if (highestPriorityTask != nullptr && thread.threadID == highestPriorityThreadID) {
                std::cout << "X ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "| " << (timeCounter % frameBoundary) + 1 << std::endl;  // Print frame time step

        // If we have a task to service, increment or complete it
        if (highestPriorityTask != nullptr && highestPriorityThreadID != -1) {
            incrementTopTask(highestPriorityThreadID);  // Increment top task of the selected thread

            // Check if task has completed
            if (highestPriorityTask->getServiced() == highestPriorityTask->getRequested()) {
                threads[highestPriorityThreadID - 1].taskQueue.pop();
                servicedCounter++;  // Increment serviced counter when a task completes
            }
        }

        timeCounter++;
    }

    // Print the total counts after the scheduler run
    std::cout << "Total tasks created: " << taskCounter << std::endl;
    std::cout << "Total tasks serviced: " << servicedCounter << std::endl;
}

// Add a new task to the specified thread's queue
void RateMonotonicScheduler::addTask(int threadID) {
    int requestedTime;

    // Determine the requested time based on the thread frequency
    switch (threads[static_cast<size_t>(threadID - 1)].frequency) {
        case 3: requestedTime = 1; break;
        case 6: requestedTime = 2; break;
        case 12: requestedTime = 4; break;
        case 24: requestedTime = 8; break;
    }

    // Use the Queue's `push` method to add a new Task with only `requestedTime`
    threads[static_cast<size_t>(threadID - 1)].taskQueue.push(Task(requestedTime));
}

// Increment the `serviced` field of the top task in the specified thread
void RateMonotonicScheduler::incrementTopTask(int threadID) {
    if (!threads[static_cast<size_t>(threadID - 1)].taskQueue.isEmpty()) {
        Task* topTask = threads[static_cast<size_t>(threadID - 1)].taskQueue.top();
        topTask->setServiced(topTask->getServiced() + 1);
    }
}