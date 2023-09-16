#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <map>
#include <functional>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"

class FCFS : public SchedulingAlgorithm {
private:
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;
    void simulate() override;
    const char * algorithmName = "First Come First Served";

public:
    FCFS();
    virtual ~FCFS() {}  // Virtual Destructor
};

#endif // FCFS_H
