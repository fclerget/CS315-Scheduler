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
RoundRobinScheduler::RoundRobinScheduler() : currentThreadIndex(0) {  // Initialize currentThreadIndex here
    // Initialize threads with their respective lengths, queues, and IDs
    threads = {
        {Queue(), 1, 1, 4},   // Thread 1: size 1, length 4
        {Queue(), 1, 2, 4},   // Thread 2: size 1, length 4
        {Queue(), 1, 4, 4},   // Thread 3: size 1, length 4
        {Queue(), 1, 6, 4}    // Thread 4: size 1, length 4
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

        // Only service the current thread in round-robin order
        auto& currentThread = threads[currentThreadIndex];
        Task* currentTask = (!currentThread.taskQueue.isEmpty()) ? currentThread.taskQueue.top() : nullptr;

        // Display thread statuses
        for (size_t i = 0; i < threads.size(); ++i) {
            bool isRunning = (i == currentThreadIndex);
            bool isCreated = taskCreated[i];

            if (isRunning && isCreated) {
                // Turquoise if a task is both created and executed in this time unit
                setColor(COLOR_TURQUOISE);
                cout << "▓▒░";
            } else if (isRunning) {
                if (currentTask != nullptr) {
                    // Green if this thread is currently running a task
                    setColor(COLOR_GREEN);
                } else {
                    // Gray if this thread is currently selected but has no task
                    setColor(COLOR_GRAY);
                }
                cout << "▓▒░";
            } else if (isCreated && !isRunning) {
                // Yellow if a task is created but not running
                setColor(COLOR_YELLOW);
                cout << "▓▒░";
            } else if (!threads[i].taskQueue.isEmpty()) {
                // Red for other threads with tasks waiting but not running
                setColor(COLOR_RED);
                cout << "▓▒░";
            } else {
                // Gray if no tasks are in the queue or the thread isn't active
                setColor(COLOR_GRAY);
                cout << "▒▒▒";
            }
        }
        setColor(COLOR_WHITE);
        cout << " | " << (timeCounter % frameBoundary) + 1 << endl;

        // Increment the serviced time for the task in the current thread if it's running
        if (currentTask != nullptr) {
            incrementTopTask(currentThread.priority);

            if (currentTask->getServiced() == currentTask->getRequested()) {
                currentThread.taskQueue.pop();
                servicedCounter++;
            }
        }

        // Move to the next thread in round-robin order, even if the current thread had no task
        currentThreadIndex = (currentThreadIndex + 1) % threads.size();

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
