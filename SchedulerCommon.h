/**
 * @file SchedulerCommon.h
 * @brief Contains the Thread definition
 *
 * Contains the definition of the Thread struct
 * The struct is used by both algorithms
 *
 * @date 11/5/24
 * @author Fiya Clerget, Marcello Novak
 */
#pragma once

#include "Queue.h"

struct Thread {
    Queue taskQueue;
    int priority;   // Fixed priority for the thread
    int size;       // Length of the task created
    int frequency;  // Fixed period of task execution for this thread
 
};
