#ifndef SJF_H
#define SJF_H

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Process.h"
#include "SchedulingAlgorithm.h"

// SJF Header File
class SJF : public SchedulingAlgorithm {
private:
    std::vector<Process*> processes;
    std::map<int, Process*> processPid; // mapeia o pid ao Process
    int contextSwitches = 0;

public:
    SJF();
    void addProcess(Process* process) override;
    void addProcesses(const std::vector<Process*>& processes) override;
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime);
    void simulate() override;
};

#endif // SJF_H