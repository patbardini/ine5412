// RoundRobin.h

#ifndef RoundRobin_H
#define RoundRobin_H

#include <queue>
#include <map>
#include <functional>
#include <string>
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"

// RoundRobin Header File
class RoundRobin : public SchedulingAlgorithm {
private:
    const int timeQuantum = 2;

    const char * algorithmName = "Round Robin";
    void simulate() override;
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;

public:
    RoundRobin();

    virtual ~RoundRobin() {}  // Virtual Destructor
};

#endif // RoundRobin_H
