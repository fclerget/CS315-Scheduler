#pragma once
#include <iostream>

class Task {
private:
	int requested;
	int serviced;
public:
	Task(int req);
	int getRequested();
	int getServiced();
};

class PriorityTask : protected Task{
private: 
	//priority
	int frequency;
public:
	PriorityTask(int req, int freq);
	int getFrequency();
}

