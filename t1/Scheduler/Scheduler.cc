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

Scheduler::~Scheduler() {
    // cleanup if necessary
}
