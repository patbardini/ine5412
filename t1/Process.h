#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include "CPUContext.h"

// Process Header File
class Process 
{
    public:
    // Process ID
    int processID;
    // Arrival time
    int arrivalTime;
    // Burst time
    int burstTime;
    // Priority
    int priority;
    // Waiting time
    int waitingTime;
    // Turnaround time
    int turnaroundTime;
    // CPU context
    CPUContext cpuContext;
    // Constructor
    Process(int processID, int arrivalTime, int burstTime, int priority);
    // Destructor
    ~Process();
};

#endif /* PROCESS_H */