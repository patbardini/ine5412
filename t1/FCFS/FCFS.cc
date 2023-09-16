#include <iostream>
#include <queue>
#include <algorithm>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "FCFS.h"

FCFS::FCFS() {}

Process* FCFS::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    // The simulate already sorts the processes by arrival time
    return readyProcesses.front();
}


void FCFS::simulate() {
    std::cout << "-> Início algoritmo First Come First Served...\n\n";

    int currentTime = 0;
    Process* prevProcess = nullptr;
    std::vector<Process*> allProcesses = processes;  

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

        while (!currentProcess || currentProcess->getArrivalTime() > currentTime) {
            printProcessesState();
            currentTime++;
            updateReadyProcesses(currentTime);
            if (!currentProcess) {
                currentProcess = getNextProcess();
            }
        }

        // Troca de contexto se o processo atual for diferente do anterior
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);

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
        prevProcess = currentProcess;
    }
    }

    printResults(scheduler->getContextSwitches(), algorithmName);
    
}
