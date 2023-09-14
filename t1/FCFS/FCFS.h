// FCFS.h

#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include <map>
#include "Process.h"           
#include "SchedulingAlgorithm.h" 

// FCFS Header File
class FCFS : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;
    std::map<int, Process*> processPid; // mapeia o pid ao Process

public:
    FCFS();

    void addProcess(Process* process) override;
    void addProcesses(const std::vector<Process*>& processes) override;
    void contextSwitch(Process* fromProcess, Process* toProcess) override;
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime) override;
    void simulate() override;
    
};

#endif // FCFS_H
