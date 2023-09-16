// Scheduler.cc

#include "Scheduler.h"

Scheduler::Scheduler(SchedulingAlgorithm* alg) : algorithm(alg) {}

void Scheduler::addProcess(Process* process) {
    algorithm->addProcess(process);
}

Process* Scheduler::getNextProcess() {
    return algorithm->getNextProcess();
}

void Scheduler::simulate() {
    algorithm->simulate();
}

void Scheduler::setAlgorithm(SchedulingAlgorithm* alg) {
    algorithm = alg;
}

void Scheduler::resetProcesses(const std::vector<Process*>& processes) {
    for (Process* p : processes) {
        p->setState(Process::NEW);
        p->setWaitingTime(0);
        p->setTurnaroundTime(0);
        p->setStartTime(0);
        p->setEndTime(0);
        p->setRemainingTime(p->getBurstTime());
        // Reset other properties if necessary
    }
}

Scheduler::~Scheduler() {
    // Cleanup if necessary
}
