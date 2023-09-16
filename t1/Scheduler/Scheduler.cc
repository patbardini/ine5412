// Scheduler.cc

#include "Scheduler.h"

Scheduler::Scheduler(SchedulingAlgorithm* alg) : algorithm(alg) {
    algorithm->setScheduler(this);
    contextSwitches = 0;
}

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
    algorithm->setScheduler(this);
    contextSwitches = 0;
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

// Corrected the contextSwitch function definition
void Scheduler::contextSwitch(Process* fromProcess, Process* toProcess) {
    if (fromProcess) {
        // Save the current context of the CPU to the fromProcess
        fromProcess->saveContext(cpu.getCurrentContext());
    }

    if (toProcess) {
        // Restore the saved context from toProcess to the CPU.
        cpu.setCurrentContext(toProcess->getContext());
    }
    contextSwitches++;
}

Scheduler::~Scheduler() {
    // Cleanup if necessary
}
