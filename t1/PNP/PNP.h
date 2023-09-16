#ifndef PNP_H
#define PNP_H

#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <functional>
#include <string>
#include <map>

class PNP : public SchedulingAlgorithm {
public:
    PNP();

    void simulate() override;
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;

private:
    std::string algorithmName = "Priority Non-Preemptive";

};

#endif // PNP_H
