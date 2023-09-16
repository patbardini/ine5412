#ifndef SJF_H
#define SJF_H

#include <vector>
#include <functional>
#include <string>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <map>

class SJF : public SchedulingAlgorithm{
private:

    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;
    void simulate() override;

public:
    SJF();
    const char * algorithmName = "Shortest Job First";
};

#endif // SJF_H
