#include "Process.h"

// Class Process: 
//       - This class will hold the information about a particular process
//          -> Process ID, arrival time, burst time, priority, etc.
//       - Each object created from this class will be stored into a list and will be scheduled by the Scheduler class

// Constructor
Process::Process(int processID, int arrivalTime, int burstTime, int priority) {
    this->processID = processID;
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    this->priority = priority;
    this->waitingTime = 0;
    this->turnaroundTime = 0;
    this->cpuContext = new CPUContext();
}
// Destructor
Process::~Process() { }
