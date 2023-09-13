// FCFS.h

#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include <map>
#include "Process.h"           // Assuming you have this header
#include "SchedulingAlgorithm.h" // Assuming you have this header

// FCFS Header File
class FCFS : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;
    std::map<int, Process*> processPid; // mapeia o pid ao Process
    int contextSwitches = 0;

public:
    FCFS();

    void addProcess(Process* process) override;
    
    // Method to add multiple processes
    void addProcesses(const std::vector<Process*>& processes);

    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime);
    void simulate() override;
};

#endif // FCFS_H
