// Scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingAlgorithm.h"  // This will include Process.h implicitly

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

    // Change the current scheduling algorithm
    void setAlgorithm(SchedulingAlgorithm* alg);

    // Reset the processes to their initial state
    void resetProcesses(const std::vector<Process*>& processes);

    // Destructor
    ~Scheduler();

private:
    SchedulingAlgorithm* algorithm;  // Pointer to the chosen scheduling algorithm
};

#endif // SCHEDULER_H
