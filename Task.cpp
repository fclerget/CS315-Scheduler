#include "Task.h"
#include <iostream>

Task:: Task(int req) { requested = req; }

int Task:: getRequested() {
	return requested;
}

int Task:: getServiced() {
	return serviced;
}

PriorityTask::PriorityTask(int req, int freq) : Task(req), frequency(freq) {}

int PriorityTask:: getFrequency() {
	return frequency;
}