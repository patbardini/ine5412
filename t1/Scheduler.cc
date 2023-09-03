#include "Scheduler.h"
// Scheduler Class: 
//       - Schedules the list of Process objects given and schedule them according to the selected algorithm.
//       - This class will also calculate the average waiting time and average turnaround time and the number of context switches

Scheduler::Scheduler(SchedulingAlgorithm* alg) : algorithm(alg) {} // Constructor implementation

void Scheduler::addProcess(Process* p) {
    algorithm->addProcess(p);
}

Process* Scheduler::getNextProcess() {
    return algorithm->getNextProcess();
}
