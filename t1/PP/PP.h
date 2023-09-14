#ifndef PP_H
#define PP_H

#include "SchedulingAlgorithm.h"
#include <vector>
#include <map>

class PP : public SchedulingAlgorithm {
public:
    PP();

    void addProcess(Process* process) override;

    Process* getNextProcess() override;

    void updateReadyProcesses(int currentTime) override;

    Process* checkForBiggerPriority(Process* currentProcess);

    void simulate() override;

private:
    std::vector<Process*> processes;
    std::map<int, Process*> processPid;  // to quickly access processes by their PID
};

#endif // PP_H
