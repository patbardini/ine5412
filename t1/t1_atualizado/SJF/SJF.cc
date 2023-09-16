#include "SJF.h"
#include <algorithm>
#include <iostream>

SJF::SJF() {}

void SJF::addProcess(Process* process) {
    processes.push_back(process);
    processPid[process->getProcessID()] = process;
}


Process* SJF::getNextProcess() {
    if (processes.empty()) {
        return nullptr;
    }

    std::vector<Process*> readyProcesses;
    for (Process* p : processes) {
        if (p->getState() == Process::READY) {
            readyProcesses.push_back(p);
        }
    }

    if (readyProcesses.empty()) {
        return nullptr;
    }

    // Sorting the processes based on burst time
    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getBurstTime() < b->getBurstTime();
    });

    Process* shortestProcess = readyProcesses.front();

    auto it = std::find(processes.begin(), processes.end(), shortestProcess);
    if (it != processes.end()) {
        processes.erase(it);
    }

    return shortestProcess;
}

void SJF::updateReadyProcesses(int currentTime) {
    for (auto &pair : processPid) {
        Process* p = pair.second;
        // If the process has arrived and is set to NEW, set it to READY
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
            p->setState(Process::READY);
        }
    }
}

void SJF::simulate() {
    std::cout << "-> Início algoritmo Shortest Job First...\n\n";

    int currentTime = 0;
    Process* prevProcess = nullptr;
    std::cout << "tempo ";
    std::vector<Process*> allProcesses = processes;  

    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    while (!processes.empty()) {
        updateReadyProcesses(currentTime);
        Process* currentProcess = getNextProcess();
        
        if (currentProcess == nullptr) {
            currentTime++;
            continue;  // Skip to the next iteration
        }

        // Muda de contexto caso o processo atual seja diferente do anterior
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }
        
        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTING);

        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
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
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
            currentTime++;
        }

        currentProcess->setState(Process::FINISHED);
        prevProcess = currentProcess;
    }

    const char * algorithmName = "Shortest Job First";
    printResults(scheduler->getContextSwitches(), algorithmName);

}