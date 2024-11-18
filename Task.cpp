/**
 * @file Task.cpp
 * @brief Task class implementation.
 *
 * Implementation of the Task and PriorityTask classes.
 * Includes constructors and getter methods for both classes.
 *
 * @date 10/23/24
 * @authors Fiya Clerget, Marcello Novak
 */

#include "Task.h"

// Task constructor
Task::Task(int req) : requested(req), serviced(0) {}

// Getter and setter methods for Task class
int Task:: getRequested() {
	return requested;
}

int Task:: getServiced() {
	return serviced;
}

void Task:: setServiced(int serv) {
	serviced = serv;
}
