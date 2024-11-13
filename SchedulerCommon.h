#pragma once

#include "Queue.h"

struct Thread {
    Queue taskQueue;
    int priority;   // Fixed priority for the thread
    int size;       // Length of the task created
    int frequency;  // Fixed period of task execution for this thread
 
};
