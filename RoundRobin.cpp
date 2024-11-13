/**
 * @file RoundRobin.cpp
 * @brief Round Robin scheduler implementation.
 * 
 * Example of a scheduler implemented using round robin scheduling.
 * Creates 4 threads using "Queues" to simulate a round robin scheduler.
 * 
 * @date 11/5/24
 * @author Fiya Clerget, Marcello Novak
 */

#include "RoundRobin.h"
#include "ASCII.h"
using namespace std;

// Constructor initializes threads and next release times based on example type
RoundRobinScheduler::RoundRobinScheduler(ExampleType exampleType) : currentThreadIndex(0) {
    if (exampleType == ExampleType::STRUCTURED) {
        // Structured example initialization
        threads = {
            {Queue(), 1, 2, 24},   // Thread 1: size 1, freq 24
            {Queue(), 2, 4, 24},   // Thread 2: size 2, freq 24
            {Queue(), 3, 6, 24},   // Thread 3: size 4, freq 24
            {Queue(), 4, 8, 24}    // Thread 4: size 6, freq 24
        };
    } else if (exampleType == ExampleType::STARVED) {
        // Starved example initialization
        threads = {
            {Queue(), 1, 1, 8},   // Thread 1: size 1, freq 8
            {Queue(), 2, 3, 8},   // Thread 2: size 1, freq 8
            {Queue(), 3, 2, 8},   // Thread 3: size 4, freq 8
            {Queue(), 4, 8, 8}    // Thread 4: size 1, freq 8
        };
    }

    // Set initial next release times based on the threads' frequencies
    for (const auto& thread : threads) {
        nextReleaseTimes.push_back(thread.frequency);
    }
}

// Main scheduler loop with scrolling thread status display
void RoundRobinScheduler::runExample() {
    const int frameBoundary = 24;   
    const int timeQuantum = 4;
    int currentQuantum = 0;

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
            if (timeCounter % threads[i].frequency == 0) {
                addTask(i);  // Pass thread index
                taskCounter++;
                taskCreated[i] = true;  // Mark that a task was created for this thread
            }
        }

        size_t checkedThreads = 0;
        bool taskExists = false;

        // Find the next thread with a task
        while (checkedThreads < threads.size()) {
            auto& currentThread = threads[currentThreadIndex];
            taskExists = !currentThread.taskQueue.isEmpty();

            if (taskExists) {
                break;  // Found a thread with tasks
            } else {
                // Color it orange in display logic
                // Move to next thread
                currentThreadIndex = (currentThreadIndex + 1) % threads.size();
                checkedThreads++;
            }
        }

        // If no threads have tasks, we can idle or continue
        if (checkedThreads == threads.size() && !taskExists) {
            // All threads are empty; you may choose to idle here
            // For now, we'll proceed to display and increment timeCounter
        }

        // Display thread statuses
        for (size_t i = 0; i < threads.size(); ++i) {
            bool isRunning = (i == currentThreadIndex);
            bool isCreated = taskCreated[i];
            bool hasTask = !threads[i].taskQueue.isEmpty();

            if (isRunning && isCreated && hasTask) {
                // Turquoise if a task is both created and executed in this time unit
                setColor(COLOR_TURQUOISE);
                cout << "▓▒░";
            } else if (isRunning && hasTask) {
                // Green if this thread is currently running a task
                setColor(COLOR_GREEN);
                cout << "▓▒░";
            } else if (isRunning && !hasTask) {
                // Orange if this thread is selected but has no task (idle)
                setColor(COLOR_ORANGE);
                cout << "▓▒░";
            } else if (isCreated && !isRunning) {
                // Yellow if a task is created but not running
                setColor(COLOR_YELLOW);
                cout << "▓▒░";
            } else if (hasTask) {
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
        cout << " | " << timeCounter + 1 << endl;

        // If there is a task to execute
        if (taskExists) {
            // Execute the task
            incrementCurrentTask(currentThreadIndex);
            currentQuantum++;  // Increment quantum time

            // Check if the task is complete
            auto& currentThread = threads[currentThreadIndex];
            Task* currentTask = currentThread.taskQueue.top();
            if (currentTask->getServiced() == currentTask->getRequested()) {
                currentThread.taskQueue.pop();
                servicedCounter++;
                // Move to next thread and reset quantum
                currentThreadIndex = (currentThreadIndex + 1) % threads.size();
                currentQuantum = 0;
            } else if (currentQuantum >= timeQuantum) {
                // Time quantum expired, preempt and move to next thread
                currentThreadIndex = (currentThreadIndex + 1) % threads.size();
                currentQuantum = 0;
            }
        } else {
            // No task exists in the current thread, move to next thread
            currentThreadIndex = (currentThreadIndex + 1) % threads.size();
            // No need to reset currentQuantum here
        }

        timeCounter++;
    }

    cout << "Total tasks created: " << taskCounter << endl;
    cout << "Total tasks serviced: " << servicedCounter << endl;
}

// Add a new task to the specified thread's queue
void RoundRobinScheduler::addTask(size_t threadIndex) {
    // Get the thread by index and push a task to its queue
    Thread& thread = threads[threadIndex];
    int requestedTime = thread.size;  // Use the thread's size as the requested time for the task
    thread.taskQueue.push(Task(requestedTime));
}

// Increment the `serviced` field of the task in the specified thread
void RoundRobinScheduler::incrementCurrentTask(size_t index) {
    // Get the thread by index and increment its top task if it has one
    if (!threads[index].taskQueue.isEmpty()) {
        Task* topTask = threads[index].taskQueue.top();
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