#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include "Process.h"
#include <vector>

// SchedulingAlgorithm Header File
class SchedulingAlgorithm 
{
public:
    // Virtual destructor for correct cleanup when using polymorphism
    virtual ~SchedulingAlgorithm() {}

    // Add a single process to the scheduler
    virtual void addProcess(Process* process) = 0;

    // Get the next process to run based on the algorithm's logic
    virtual Process* getNextProcess() = 0;

    // Adds multiple processes to the scheduler
    virtual void addProcesses(const std::vector<Process*>& processes) {
        for(Process* process : processes) {
            addProcess(process);
        }
    }
    
    // Simulate the scheduling algorithm
    virtual void simulate() = 0;

    // Other potential methods like removeProcess, updateProcess, etc., can be added here
};

#endif // SCHEDULINGALGORITHM_H

