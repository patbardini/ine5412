#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include <map>
#include "Process.h"           
#include "SchedulingAlgorithm.h" 
#include "Scheduler.h"

class FCFS : public SchedulingAlgorithm {
private:
    std::queue<Process*> queue;            // Queue to manage processes
    std::map<int, Process*> processPid;    // Maps ProcessID to the Process object

public:
    FCFS();

    // Overrides from the SchedulingAlgorithm class
    void addProcess(Process* process) override;
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime) override;
    void simulate() override;

};

#endif // FCFS_H
