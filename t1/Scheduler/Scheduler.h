#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingAlgorithm.h"  // This will include Process.h implicitly

// Scheduler Header File
class Scheduler {
private:
    SchedulingAlgorithm* algorithm;  // Pointer to the chosen scheduling algorithm

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

    // Destructor
    ~Scheduler();
};

#endif // SCHEDULER_H
