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

    void addProcess(Process* process) override;
    Process* getNextProcess() override;
    void updateReadyProcesses(int currentTime) override;
    Process* getHighestPriorityProcess(Process* currentProcess);
    float calculateAverageTurnaroundTime();
    float calculateAverageWaitingTime();
    void printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage);
    void simulate() override;

private:
    std::vector<Process*> processes;
    std::map<int, Process*> processPid;  // to quickly access processes by their PID
};

#endif // PP_H
