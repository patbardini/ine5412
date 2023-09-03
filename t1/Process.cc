#include <iostream>
#include "CPUContext.h"

// Class Process: 
//       - This class will hold the information about a particular process
//          -> Process ID, arrival time, burst time, priority, etc.
//       - Each object created from this class will be stored into a list and will be scheduled by the Scheduler class

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
    Process(int processID, int arrivalTime, int burstTime, int priority, CPUContext cpuContext) {
        this->processID = processID;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->waitingTime = 0;
        this->turnaroundTime = 0;
        this->cpuContext = cpuContext;
    }
    // Destructor
    ~Process() { }
};


