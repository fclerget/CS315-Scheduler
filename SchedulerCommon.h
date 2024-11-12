#pragma once

#include "Queue.h"

struct Thread {
    Queue taskQueue;
    int priority;   // fixed priority for the thread
    int length;     // Length of the task created
    int frequency;  // fixed period of task execution for this thread
    // In Round Robin scheduling all threads have the same priority and frequency
};