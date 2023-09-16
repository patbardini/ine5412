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
        p->setRemainingTime(p->getBurstTime());
        p->setWaitingTime(0);
        p->setTurnaroundTime(0);
        // Reset other properties if necessary
    }
}

Scheduler::~Scheduler() {
    // Cleanup if necessary
}
