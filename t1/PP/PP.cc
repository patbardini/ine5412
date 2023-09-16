#include "PP.h"
#include <algorithm>
#include <iostream>

PP::PP() {}

void PP::addProcess(Process* process) {
    processes.push_back(process);
    processPid[process->getProcessID()] = process;
}

Process* PP::getNextProcess() {
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

void PP::updateReadyProcesses(int currentTime) {
    for (auto &pair : processPid) {
        Process* p = pair.second;
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
            p->setState(Process::READY);
        }
    }
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

float PP::calculateAverageTurnaroundTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int turnaroundTime = pair.second->getTurnaroundTime();
        average += turnaroundTime;
    }
    average /= processPid.size();
    return average;
}

float PP::calculateAverageWaitingTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int waitingTime = pair.second->getWaitingTime();
        average += waitingTime;
    }
    average /= processPid.size();
    return average;
}

void PP::printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage) {
    std::cout << title << "\n";
    for (const auto& pair : processPid) {
        Process* p = pair.second;
        std::cout << "P" << pair.first << " = " << (p->*getter)() << "\n";
    }
    std::cout << "Média = " << calculateAverage() << "\n";
    std::cout << "\n";
}

void PP::simulate() {
    std::cout << "-> Início algoritmo Priority Preemptive...\n\n";

    int currentTime = 0;
    // Create a copy of all processes for output purposes
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

    std::cout << "\n";
    std::cout << "----------------------------------------\n";

    printAverageTime("Tempo de Turnaround para cada processo:", &Process::getTurnaroundTime, [&]() { return calculateAverageTurnaroundTime(); });
    printAverageTime("Tempo de espera para cada processo:", &Process::getWaitingTime, [&]() { return calculateAverageWaitingTime(); });

    std::cout << "\nPriority Preemptive fim.\n";
    std::cout << "========================================\n";
}
