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

    // Update the ready processes
    virtual void updateReadyProcesses(int currentTime) = 0;

    // The context switch function
    virtual void contextSwitch(Process* fromProcess, Process* toProcess) {
        CPUContext currentCPUContext;

        if (fromProcess) {
            // Save the current context of the CPU to the fromProcess.
            fromProcess->saveContext(currentCPUContext);
        }

        if (toProcess) {
            // Restore the saved context from toProcess to the CPU.
            currentCPUContext = toProcess->getContext();
        }
    }

};

#endif // SCHEDULINGALGORITHM_H
