// RoundRobin.h

#ifndef RoundRobin_H
#define RoundRobin_H

#include <queue>
#include "SchedulingAlgorithm.h"

// RoundRobin Header File
class RoundRobin : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;
    int contextSwitches = 0;
    const int timeQuantum = 2;

public:
    RoundRobin();
    void addProcess(Process* process) override;
    void addProcesses(const std::vector<Process*>& processes);
    Process* getNextProcess() override;
    void simulate() override;
};

#endif // RoundRobin_H
