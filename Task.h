/**
 * @file Task.h
 * @brief Contains the definition of the Task and PriorityTask classes.
 *
 * Definitions for the Task and PriorityTask classes.
 * PriorityTask is a subclass of Task, adding a frequency attribute.
 * Also includes getter method definitions for both.
 *
 * @date 10/23/24
 * @author Fiya Clerget, Marcello Novak
 */

#pragma once

// Task class definition
class Task {
private:
	int requested;
	int serviced;
public:
	Task(int req);
	int getRequested();
	int getServiced();
	void setServiced(int serv);
};

// PriorityTask class definition, inherits from Task
class PriorityTask : protected Task{
private: 
	int frequency;  // aka priority
public:
	PriorityTask(int req, int freq);
	int getFrequency();
};