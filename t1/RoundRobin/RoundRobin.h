// RoundRobin.h

#ifndef RoundRobin_H
#define RoundRobin_H

#include <queue>
#include <map>
#include "SchedulingAlgorithm.h"

// RoundRobin Header File
class RoundRobin : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;
    int contextSwitches = 0;
    const int timeQuantum = 2;
    std::map<int, Process*> processPid; // mapeia o pid ao Process

public:
    RoundRobin();
    void addProcess(Process* process) override;
    void addProcesses(const std::vector<Process*>& processes);
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime) override;
    void simulate() override;
};

#endif // RoundRobin_H
