#include <iostream>
#include "CPUContext.h"
#include "Process.h"

Process::Process(int processID, int arrivalTime, int burstTime, int priority) 
    : processID(processID),
      arrivalTime(arrivalTime),
      burstTime(burstTime),
      priority(priority),
      waitingTime(0),
      turnaroundTime(0),
      startTime(0),
      endTime(0),
      state(NEW),
      cpuContext() {}  // This calls the default constructor of CPUContext

Process::~Process() {}

void Process::saveContext(const CPUContext& currentContext) {
    cpuContext = currentContext;
}

CPUContext Process::getContext() const {
    return cpuContext;
}
