#include <iostream>
#include "RoundRobin.h"

RoundRobin::RoundRobin() {}

void RoundRobin::addProcess(Process* process) {
    queue.push(process);
    processPid[process->getProcessID()] = process;
}

void RoundRobin::addProcesses(const std::vector<Process*>& processes) {
    for (Process* p : processes) {
        addProcess(p);
    }
}

Process* RoundRobin::getNextProcess() {
    if (queue.empty()) {
        return nullptr;
    }
    Process* process = queue.front();
    queue.pop();
    return process;
}

void RoundRobin::updateReadyProcesses(int currentTime) {
    for (auto &pair : processPid) {
        Process* p = pair.second;
        // If the process has arrived and is not executing, set it to ready
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
            p->setState(Process::READY);
        } 
    }
}

float RoundRobin::calculateAverageTurnaroundTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int turnaroundTime = pair.second->getTurnaroundTime();
        average += turnaroundTime;
    }
    average /= processPid.size();
    return average;
}

float RoundRobin::calculateAverageWaitingTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int waitingTime = pair.second->getWaitingTime();
        average += waitingTime;
    }
    average /= processPid.size();
    return average;
}

void RoundRobin::printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage) {
    std::cout << title << "\n";
    for (const auto& pair : processPid) {
        Process* p = pair.second;
        std::cout << "P" << pair.first << " = " << (p->*getter)() << "\n";
    }
    std::cout << "Média = " << calculateAverage() << "\n";
    std::cout << "\n";
}

void RoundRobin::simulate() {
    std::cout << "-> Início algoritmo Round Robin...\n\n";

    int currentTime = 0;
    int totalProcesses = queue.size();

    std::cout << "tempo ";
    for (int i = 1; i <= totalProcesses; i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    auto printProcessesState = [&]() {
        std::cout << " " << currentTime << "-" << (currentTime + 1) << "  ";
        for (int j = 1; j <= totalProcesses; j++) {
            switch (processPid[j]->getState()) {
                case Process::EXECUTING:
                    std::cout << "## ";
                    break;
                case Process::READY:
                    std::cout << "-- ";
                    processPid[j]->setWaitingTime(processPid[j]->getWaitingTime()+1);
                    break;
                default:
                    std::cout << "   ";
                    break;
            }
        }
        std::cout << "\n";
    };

    while (!queue.empty()) {
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

        int remainingTime = currentProcess->getRemainingTime();

        for (int i = 0; i < std::min(timeQuantum, remainingTime); ++i) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
        }

        currentProcess->setRemainingTime(remainingTime - timeQuantum);
        
        if (currentProcess->getRemainingTime() > 0) {
            queue.push(currentProcess);  // Readiciona à fila se o processo ainda precisa de mais tempo
            currentProcess->setState(Process::READY);
        } else {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
            currentProcess->setState(Process::FINISHED);
        }

        contextSwitches++;
    }

    std::cout << "\n";
    std::cout << "----------------------------------------\n";

    printAverageTime("Tempo de Turnaround para cada processo:", &Process::getTurnaroundTime, [&]() { return calculateAverageTurnaroundTime(); });
    printAverageTime("Tempo de espera para cada processo:", &Process::getWaitingTime, [&]() { return calculateAverageWaitingTime(); });

    std::cout << "\nRound Robin fim.\n";
    std::cout << "========================================\n";
}
