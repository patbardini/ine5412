#include "PP.h"
#include <algorithm>
#include <iostream>

PP::PP() {}

Process* PP::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    // highest priority first
    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });

    Process* highestPriorityProcess = readyProcesses.front();

    return highestPriorityProcess;
}

Process* PP::getHighestPriorityProcess(Process* currentProcess) {
    Process* highestPriorityProcess = currentProcess;
    for (Process* p : processes) {
        if (p->getState() == Process::READY && p->getPriority() > currentProcess->getPriority()) {
            highestPriorityProcess = p;
        }
    }
    if (highestPriorityProcess != currentProcess) {
        currentProcess->setState(Process::READY);
        processes.push_back(currentProcess);
    }
    return highestPriorityProcess;
}


void PP::simulate() {
    std::cout << "-> Início algoritmo Priority Preemptive...\n\n";

    int currentTime = 0;
    // Create a copy of all processes for output purposes
    std::vector<Process*> allProcesses = processes;  
  
    Process* prevProcess = nullptr;

    std::cout << "tempo ";
    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    auto printProcessesState = [&]() {
        std::cout << " " << currentTime << "-" << (currentTime + 1) << "  ";
        for (Process* p : allProcesses) {
            switch (p->getState()) {
                case Process::EXECUTING:
                    std::cout << "## ";
                    break;
                case Process::READY:
                    std::cout << "-- ";
                    p->setWaitingTime(p->getWaitingTime()+1);
                    break;
                default:
                    std::cout << "   ";
                    break;
            }
        }
        std::cout << "\n";
    };

    while (!processes.empty()) {
        updateReadyProcesses(currentTime);
        Process* currentProcess = getNextProcess();

        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        while (!currentProcess || currentProcess->getArrivalTime() > currentTime) {
            printProcessesState();
            currentTime++;
            updateReadyProcesses(currentTime);
            if (!currentProcess) {
                currentProcess = getNextProcess();
            }
            
        }

        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTING);

        Process* highestPriorityProcess = currentProcess;

        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
            highestPriorityProcess = getHighestPriorityProcess(currentProcess);
            if (highestPriorityProcess != currentProcess || currentProcess->getRemainingTime() <= 0) {
                break;
            }
            printProcessesState();
            currentTime++;
            currentProcess->setRemainingTime(currentProcess->getRemainingTime()-1);
        }

        if (currentProcess->getState() != Process::READY) {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
            currentProcess->setState(Process::FINISHED);
        } 
    }

    printResults(scheduler->getContextSwitches(), algorithmName);
}
