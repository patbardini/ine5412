#include <iostream>
#include "CPU.h"
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
      remainingTime(burstTime),
      state(NEW),
      cpuContext() {}  // This calls the default constructor of CPUContext

Process::~Process() {}

void Process::saveContext(const CPU::Context& currentContext) {
    cpuContext = currentContext;
}

CPU::Context Process::getContext() const {
    return cpuContext;
}
