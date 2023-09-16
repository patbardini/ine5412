#include "PNP.h"
#include <algorithm>
#include <iostream>

PNP::PNP() {}

void PNP::addProcess(Process* process) {
    processes.push_back(process);
    processPid[process->getProcessID()] = process;
}

Process* PNP::getNextProcess() {
    if (processes.empty()) {
        return nullptr;
    }

    // Filter the processes that have arrived and are in READY state
    std::vector<Process*> readyProcesses;
    for (Process* p : processes) {
        if (p->getState() == Process::READY) {
            readyProcesses.push_back(p);
        }
    }

    if (readyProcesses.empty()) {
        return nullptr;
    }

    // Sorting the ready processes based on priority (upper value is higher priority)
    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });

    Process* highestPriorityProcess = readyProcesses.front();

    // Remove the selected process from the main process list
    auto it = std::find(processes.begin(), processes.end(), highestPriorityProcess);
    if (it != processes.end()) {
        processes.erase(it);
    }

    return highestPriorityProcess;
}


void PNP::updateReadyProcesses(int currentTime) {
    for (auto &pair : processPid) {
        Process* p = pair.second;
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
            p->setState(Process::READY);
        }
    }
}

void PNP::simulate() {
    std::cout << "-> Início algoritmo Priority Non-Preemptive...\n\n";

    int currentTime = 0;
    Process* prevProcess = nullptr;
    std::cout << "tempo ";

    // Create a copy of all processes for output purposes
    std::vector<Process*> allProcesses = processes;  

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
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        }

        currentProcess->setState(Process::FINISHED);
    }

    const char * algorithmName = "Priority Non-Preemptive";
    printResults(scheduler->getContextSwitches(), algorithmName);
}
