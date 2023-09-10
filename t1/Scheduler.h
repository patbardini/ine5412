#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "SchedulingAlgorithm.h"

class Scheduler {
private:
    SchedulingAlgorithm* algorithm;
public:
    Scheduler(SchedulingAlgorithm* alg); // Constructor declaration
    void addProcess(Process* p);
    Process* getNextProcess();
};

#endif // SCHEDULER_H