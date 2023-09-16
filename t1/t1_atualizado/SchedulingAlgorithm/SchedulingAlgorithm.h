
#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include <iostream>
#include "Process.h"
#include <vector>
#include <string>

class Scheduler; // Forward declaration

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

    // Set the scheduler
    void setScheduler(Scheduler* sched) {
        scheduler = sched;
    }

    void printResults(int contextSwitchCount, const char * algorithmName) {
        std::cout << "\nTrocas de Contexto: " << contextSwitchCount << "\n";
        std::cout << "Algoritmo: " << algorithmName << " Fim.\n";
        std::cout << "========================================\n\n";

    }

protected:
    // Pointer to the scheduler
    Scheduler* scheduler = nullptr;

};

#endif // SCHEDULINGALGORITHM_H