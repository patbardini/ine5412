#include "SJF.h"
#include <algorithm>
#include <iostream>

SJF::SJF() {}

void SJF::addProcess(Process* process) {
    processes.push_back(process);
    processPid[process->getProcessID()] = process;
}

void SJF::addProcesses(const std::vector<Process*>& processList) {
    for (Process* p : processList) {
        addProcess(p);
    }
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

float SJF::calculateAverageTurnaroundTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int turnaroundTime = pair.second->getTurnaroundTime();
        average += turnaroundTime;
    }
    average /= processPid.size();
    return average;
}

float SJF::calculateAverageWaitingTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int waitingTime = pair.second->getWaitingTime();
        average += waitingTime;
    }
    average /= processPid.size();
    return average;
}

void SJF::printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage) {
    std::cout << title << "\n";
    for (const auto& pair : processPid) {
        Process* p = pair.second;
        std::cout << "P" << pair.first << " = " << (p->*getter)() << "\n";
    }
    std::cout << "Média = " << calculateAverage() << "\n";
    std::cout << "\n";
}

void SJF::simulate() {
    std::cout << "-> Início algoritmo Shortest Job First...\n\n";

    int currentTime = 0;
    std::cout << "tempo ";
    std::vector<Process*> allProcesses = processes;  

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

    std::cout << "\n";
    std::cout << "----------------------------------------\n";

    printAverageTime("Tempo de Turnaround para cada processo:", &Process::getTurnaroundTime, [&]() { return calculateAverageTurnaroundTime(); });
    printAverageTime("Tempo de espera para cada processo:", &Process::getWaitingTime, [&]() { return calculateAverageWaitingTime(); });

    std::cout << "\nShortest Job First fim.\n";
    std::cout << "========================================\n";
}
