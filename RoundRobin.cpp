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
#include "ASCII.h"
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

// Main scheduler loop with scrolling thread status display
void RoundRobinScheduler::runExampleStructured() {
    const int frameBoundary = 24;
    int taskCounter = 0;
    int servicedCounter = 0;

    int timeCounter = 0;
    while (timeCounter < 10008) {
        if (timeCounter % frameBoundary == 0) {
            setColor(COLOR_WHITE);
            cout << "▓▒░▓▒░▓▒░▓▒░ | New Frame\n";
        }

        // Track which threads have new tasks created in this time unit
        vector<bool> taskCreated(threads.size(), false);

        // Add tasks based on release times
        for (size_t i = 0; i < threads.size(); ++i) {
            if (timeCounter >= nextReleaseTimes[i]) {
                addTask(threads[i].priority);
                nextReleaseTimes[i] += threads[i].frequency;
                taskCounter++;
                taskCreated[i] = true;  // Mark that a task was created for this thread
            }
        }

        // Get and service the highest-priority task
        Task* highestPriorityTask = nullptr;
        int highestPriorityThreadIndex = -1;

        // Find the highest-priority task
        for (size_t i = 0; i < threads.size(); ++i) {
            auto& thread = threads[i];
            if (!thread.taskQueue.isEmpty()) {
                Task* topTask = thread.taskQueue.top();
                if (highestPriorityTask == nullptr || thread.priority < threads[static_cast<size_t>(highestPriorityThreadIndex)].priority) {
                    highestPriorityTask = topTask;
                    highestPriorityThreadIndex = static_cast<int>(i);
                }
            }
        }

        // Display thread statuses
        for (size_t i = 0; i < threads.size(); ++i) {
            bool isRunning = (i == static_cast<size_t>(highestPriorityThreadIndex));
            bool isCreated = taskCreated[i];

            if (isRunning && isCreated) {
                // Turquoise if a task is both created and executed in this time unit
                setColor(COLOR_TURQUOISE);
                cout << "▓▒░";
            } else if (isRunning) {
                // Green if this is the highest-priority task running
                setColor(COLOR_GREEN);
                cout << "▓▒░";
            } else if (isCreated && !isRunning) {
                // Purple if a task is created but preempted by a higher-priority task
                setColor(COLOR_YELLOW);
                cout << "▓▒░";
            } else if (!threads[i].taskQueue.isEmpty() && i > static_cast<size_t>(highestPriorityThreadIndex)) {
                // Red only if a lower-priority task is preempted (higher threads are never preempted by lower threads)
                setColor(COLOR_RED);
                cout << "▓▒░";
            } else {
                // Gray if no tasks are in the queue or the thread isn't preempted
                setColor(COLOR_GRAY);
                cout << "▒▒▒";
            }
        }
        setColor(COLOR_WHITE);
        cout << " | " << (timeCounter % frameBoundary) + 1 << endl;

        if (highestPriorityTask != nullptr && highestPriorityThreadIndex != -1) {
            incrementTopTask(threads[static_cast<size_t>(highestPriorityThreadIndex)].priority);

            if (highestPriorityTask->getServiced() == highestPriorityTask->getRequested()) {
                threads[static_cast<size_t>(highestPriorityThreadIndex)].taskQueue.pop();
                servicedCounter++;
            }
        }

        timeCounter++;
    }

    cout << "Total tasks created: " << taskCounter << endl;
    cout << "Total tasks serviced: " << servicedCounter << endl;
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