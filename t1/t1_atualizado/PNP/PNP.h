#ifndef PNP_H
#define PNP_H

#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <map>

class PNP : public SchedulingAlgorithm {
public:
    PNP();

    void addProcess(Process* process) override;

    Process* getNextProcess() override;

    void updateReadyProcesses(int currentTime) override;

    void simulate() override;

private:
    std::vector<Process*> processes;
    std::map<int, Process*> processPid;  // to quickly access processes by their PID
};

#endif // PNP_H
