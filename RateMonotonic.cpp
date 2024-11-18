/**
 * @file RateMonotonic.cpp
 * @brief Rate monotonic scheduler implementation.
 * 
 * Example of a scheduler implemented using rate monotonic scheduling.
 * Uses 4 threads using "Queues" to simulate a rate monotonic scheduler.
 * 
 * @date 10/31/24
 * @authors Fiya Clerget, Marcello Novak
 */

#include "RateMonotonic.h"
#include "ASCII.h"    // For coloring
#include <algorithm>  // For find_if


using namespace std;

// Constructor initializes threads and next release times based on example type
RateMonotonicScheduler::RateMonotonicScheduler(ExampleType exampleType) {
    if (exampleType == ExampleType::STRUCTURED) {
        // Structured example initialization
        threads = {
            {Queue(), 1, 1, 3},   // Thread 1: priority 1, size 1, frequency 3
            {Queue(), 2, 2, 6},   // Thread 2: priority 2, size 2, frequency 6
            {Queue(), 3, 2, 12},  // Thread 3: priority 3, size 2, frequency 12
            {Queue(), 4, 4, 24}   // Thread 4: priority 4, size 4, frequency 24
        };
    } else if (exampleType == ExampleType::STARVED) {
        // Starved example initialization
        threads = {
            {Queue(), 1, 1, 3},   // Thread 1: priority 1, size 1, frequency 3
            {Queue(), 2, 2, 6},   // Thread 2: priority 2, size 2, frequency 6
            {Queue(), 3, 4, 12},  // Thread 3: priority 3, size 4, frequency 12
            {Queue(), 4, 4, 24}   // Thread 4: priority 4, size 4, frequency 24
        };
    }

    // Set initial next release times based on the threads' frequencies
    for (const Thread& thread : threads) {
        nextReleaseTimes.push_back(thread.frequency);
    }
}
// Destructor to clear the queues in each thread
RateMonotonicScheduler::~RateMonotonicScheduler() {
    for (Thread& thread : threads) {
        while (!thread.taskQueue.isEmpty()) {
            thread.taskQueue.pop();
        }
    }
}

// Main scheduler loop with scrolling thread status display
void RateMonotonicScheduler::runExample() {
    const int frameBoundary = 24;
    int taskCounter = 0;
    int servicedCounter = 0;

    int timeCounter = 0;
    while (timeCounter < 10008) {
        if (timeCounter % frameBoundary == 0) {
            setColor(COLOR_WHITE);
            cout << "█▓▒░█▓▒░█▓▒░█▓▒░ | New Frame\n";
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
            Thread& thread = threads[i];
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
                cout << "█▓▒░";
            } else if (isRunning) {
                // Green if this is the highest-priority task running
                setColor(COLOR_GREEN);
                cout << "█▓▒░";
            } else if (isCreated && !isRunning) {
                // Purple if a task is created but preempted by a higher-priority task
                setColor(COLOR_YELLOW);
                cout << "█▓▒░";
            } else if (!threads[i].taskQueue.isEmpty() && i > static_cast<size_t>(highestPriorityThreadIndex)) {
                // Red only if a lower-priority task is preempted (higher threads are never preempted by lower threads)
                setColor(COLOR_RED);
                cout << "█▓▒░";
            } else {
                // Gray if no tasks are in the queue or the thread isn't preempted
                setColor(COLOR_GRAY);
                cout << "░░░░";
            }
        }
        setColor(COLOR_WHITE);
        cout << " | " << (timeCounter + 1) << endl;

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

void RateMonotonicScheduler::addTask(int priority) {
    auto it = find_if(threads.begin(), threads.end(), [priority](const Thread& t) {
        return t.priority == priority;
    });

    if (it != threads.end()) {
        int requestedTime = it->size;
        it->taskQueue.push(Task(requestedTime));
    }
}

void RateMonotonicScheduler::incrementTopTask(int priority) {
    auto it = find_if(threads.begin(), threads.end(), [priority](const Thread& t) {
        return t.priority == priority;
    });

    if (it != threads.end() && !it->taskQueue.isEmpty()) {
        Task* topTask = it->taskQueue.top();
        topTask->setServiced(topTask->getServiced() + 1);
    }
}
