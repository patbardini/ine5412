#include "PNP.h"
#include <algorithm>
#include <iostream>

PNP::PNP() {}

// Sorting the ready processes based on priority (upper value is higher priority)
Process* PNP::sortReadyProcesses(std::vector<Process*> readyProcesses) {

    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });

    Process* highestPriorityProcess = readyProcesses.front();

    return highestPriorityProcess;
}

void PNP::simulate() {
    std::cout << "-> Início algoritmo Priority Non-Preemptive...\n\n";

    int currentTime = 0;

    Process* prevProcess = nullptr;
    
    // Create a copy of all processes for output purposes
    std::vector<Process*> allProcesses = processes;  

    std::cout << "tempo ";
    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    // Helper function to print processes' states
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

        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
            currentProcess->setRemainingTime(currentProcess->getRemainingTime()-1);
        }

        currentProcess->setEndTime(currentTime);
        currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        currentProcess->setState(Process::FINISHED);
    }

    printResults(scheduler->getContextSwitches(), algorithmName);
}