#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingAlgorithm.h"  // This will include Process.h implicitly
#include "CPU.h"

class Scheduler {
public:
    // Constructor to initialize with a specific scheduling algorithm
    Scheduler(SchedulingAlgorithm* alg);

    // Add a single process to the current scheduling algorithm
    void addProcess(Process* process);

    // Fetch the next process based on the current scheduling algorithm's logic
    Process* getNextProcess();

    // Run the simulation for the current scheduling algorithm
    void simulate();

    // Reset the processes to their initial state
    void resetProcesses(const std::vector<Process*>& processes);

    // The context switch function
    void contextSwitch(Process* fromProcess, Process* toProcess);

    // Destructor
    ~Scheduler();

    // Getters and setters

    void setAlgorithm(SchedulingAlgorithm* alg); // Change the current scheduling algorithm

    CPU& getCPU() { return cpu; } // Get a reference to the CPU

    int getContextSwitches() { return contextSwitches; } // Get the number of context switches

private:
    SchedulingAlgorithm* algorithm;  // Pointer to the chosen scheduling algorithm
    CPU cpu;                         // The CPU
    int contextSwitches;         // Number of context switches
};

#endif // SCHEDULER_H
