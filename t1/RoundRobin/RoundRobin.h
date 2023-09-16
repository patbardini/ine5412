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
    std::queue<Process*> queue;
    const int timeQuantum = 2;
    std::map<int, Process*> processPid; // mapeia o pid ao Process

public:
    RoundRobin();
    void addProcess(Process* process) override;
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime) override;
    float calculateAverageTurnaroundTime();
    float calculateAverageWaitingTime();
    void printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage);
    void simulate() override;
};

#endif // RoundRobin_H
