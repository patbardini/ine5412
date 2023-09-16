#include <iostream>
#include <queue>
#include <algorithm>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "FCFS.h"

FCFS::FCFS() {}

void FCFS::addProcess(Process* process) {
    queue.push(process);
    processPid[process->getProcessID()] = process;
}

void FCFS::addProcesses(const std::vector<Process*>& processes) {
    for (Process* p : processes) {
        addProcess(p);
    }
}

void FCFS::contextSwitch(Process* fromProcess, Process* toProcess) {
    SchedulingAlgorithm::contextSwitch(fromProcess, toProcess);
}


Process* FCFS::getNextProcess() {
    if (queue.empty()) {
        return nullptr;
    }
    Process* process = queue.front();
    queue.pop();
    return process;
}

void FCFS::updateReadyProcesses(int currentTime) {
    for (auto &pair : processPid) {
        Process* p = pair.second;
        // If the process has arrived and is not executing, set it to ready
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
            p->setState(Process::READY);
        } 
    }

}

float FCFS::calculateAverageTurnaroundTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int turnaroundTime = pair.second->getTurnaroundTime();
        average += turnaroundTime;
    }
    average /= processPid.size();
    return average;
}

float FCFS::calculateAverageWaitingTime() {
    float average = 0;
    for (auto &pair : processPid) {
        int waitingTime = pair.second->getWaitingTime();
        average += waitingTime;
    }
    average /= processPid.size();
    return average;
}

void FCFS::printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage) {
    std::cout << title << "\n";
    for (const auto& pair : processPid) {
        Process* p = pair.second;
        std::cout << "P" << pair.first << " = " << (p->*getter)() << "\n";
    }
    std::cout << "Média = " << calculateAverage() << "\n";
    std::cout << "\n";
}

void FCFS::simulate() {
    std::cout << "-> Início algoritmo First Come First Served...\n\n";

    int currentTime = 0;
    int totalProcesses = queue.size();  // get the total number of processes
    std::vector<std::string> output;    // to store the output for each time interval
    Process* prevProcess = nullptr;

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
        Process* currentProcess = getNextProcess();

        while (!currentProcess || currentProcess->getArrivalTime() > currentTime) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
            if (!currentProcess) {
                currentProcess = getNextProcess();
            }
        }

        if (prevProcess != nullptr) {
            contextSwitch(prevProcess, currentProcess);
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

        contextSwitch(currentProcess, nullptr);
        prevProcess = currentProcess;
    }

    std::cout << "\n";
    std::cout << "----------------------------------------\n";

    printAverageTime("Tempo de Turnaround para cada processo:", &Process::getTurnaroundTime, [&]() { return calculateAverageTurnaroundTime(); });
    printAverageTime("Tempo de espera para cada processo:", &Process::getWaitingTime, [&]() { return calculateAverageWaitingTime(); });

    std::cout << "\nFirst Come First Served fim.\n";
    std::cout << "========================================\n";
}
