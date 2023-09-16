#ifndef SJF_H
#define SJF_H

#include <vector>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <map>

class SJF : public SchedulingAlgorithm{
private:
    std::vector<Process*> processes;
    std::vector<Process*> readyQueue;
    std::map<int, Process*> processPid;
public:
    SJF();

    void addProcess(Process* process) override;
    Process* getNextProcess();
    void updateReadyProcesses(int currentTime) override;
    void simulate() override;
};

#endif // SJF_H
