#ifndef SJF_H
#define SJF_H

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Process.h"
#include "SchedulingAlgorithm.h"

// SJF Header File
class SJF : public SchedulingAlgorithm {
private:
    std::vector<Process*> processes;
    int contextSwitches = 0;

public:
    SJF();
    void addProcess(Process* process) override;
    void addProcesses(const std::vector<Process*>& processes) override;
    Process* getNextProcess() override;
    void simulate() override;
};

#endif // SJF_H