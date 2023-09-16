#ifndef PP_H
#define PP_H

#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <functional>
#include <string>
#include <map>

class PP : public SchedulingAlgorithm {
public:
    PP();

    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;
    void simulate() override;

private:
    std::string algorithmName = "Priority Preemptive";

    Process* getHighestPriorityProcess(Process* currentProcess);
};

#endif // PP_H
