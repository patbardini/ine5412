// FCFS.h

#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include "Process.h"           // Assuming you have this header
#include "SchedulingAlgorithm.h" // Assuming you have this header

// FCFS Header File
class FCFS : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;
    int contextSwitches = 0;

public:
    FCFS();

    void addProcess(Process* process) override;
    
    // Method to add multiple processes
    void addProcesses(const std::vector<Process*>& processes);

    Process* getNextProcess() override;
    void simulate() override;
};

#endif // FCFS_H
