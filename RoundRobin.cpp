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
            {Queue(), 1, 1, 24},   // Thread 1: size 1, freq 24
            {Queue(), 2, 2, 24},   // Thread 2: size 2, freq 24
            {Queue(), 3, 4, 24},   // Thread 3: size 4, freq 24
            {Queue(), 4, 6, 24}    // Thread 4: size 6, freq 24
        };
    } else if (exampleType == ExampleType::STARVED) {
        // Starved example initialization
        threads = {
            {Queue(), 1, 1, 8},   // Thread 1: size 1, freq 8
            {Queue(), 2, 1, 8},   // Thread 2: size 1, freq 8
            {Queue(), 3, 4, 8},   // Thread 3: size 4, freq 8
            {Queue(), 4, 1, 8}    // Thread 4: size 1, freq 8
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
                addTask(i);  // Pass thread index instead of size
                nextReleaseTimes[i] += threads[i].frequency;
                taskCounter++;
                taskCreated[i] = true;  // Mark that a task was created for this thread
            }
        }

        // Only service the current thread in strict round-robin order
        auto& currentThread = threads[currentThreadIndex];
        bool taskExists = !currentThread.taskQueue.isEmpty();

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
        cout << " | " << (timeCounter % frameBoundary) + 1 << endl;

        // Increment the serviced time for the task in the current thread if it's running
        if (taskExists) {
            incrementCurrentTask(currentThreadIndex);

            // Check if the task is complete
            Task* currentTask = currentThread.taskQueue.top();
            if (currentTask->getServiced() == currentTask->getRequested()) {
                currentThread.taskQueue.pop();
                servicedCounter++;
            }
        }

        // Move to the next thread in round-robin order
        currentThreadIndex = (currentThreadIndex + 1) % threads.size();

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