
#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include "Process.h"


class Scheduler; // Forward declaration

// SchedulingAlgorithm Header File
class SchedulingAlgorithm 
{
public:
    // Virtual destructor for correct cleanup when using polymorphism
    virtual ~SchedulingAlgorithm() {}

    // Simulate the scheduling algorithm
    virtual void simulate() = 0;

    // Add a single process to the scheduler
    virtual void addProcess(Process* process) {
        processes.push_back(process);
        processPid[process->getProcessID()] = process;
    }

    // Adds multiple processes to the scheduler
    virtual void addProcesses(const std::vector<Process*>& processes) {
        for(Process* process : processes) {
            addProcess(process);
        }
    }

    virtual Process* getNextProcess() {
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

        Process* selectedProcess = sortReadyProcesses(readyProcesses);

        auto it = std::find(processes.begin(), processes.end(), selectedProcess);
        if (it != processes.end()) {
            processes.erase(it);
        }

        return selectedProcess;
    }

    // Update the ready processes
    virtual void updateReadyProcesses(int currentTime) {
        for (auto &pair : processPid) {
            Process* p = pair.second;
            if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
                p->setState(Process::READY);
            } 
        }
    }

    // Set the scheduler
    virtual void setScheduler(Scheduler* sched) {
        scheduler = sched;
    }

    virtual float calculateAverageTurnaroundTime() {
        float average = 0;
        for (auto &pair : processPid) {
            int turnaroundTime = pair.second->getTurnaroundTime();
            average += turnaroundTime;
        }
        average /= processPid.size();
        return average;
    }

    virtual float calculateAverageWaitingTime() {
        float average = 0;
        for (auto &pair : processPid) {
            int waitingTime = pair.second->getWaitingTime();
            average += waitingTime;
        }
        average /= processPid.size();
        return average;
    }

    virtual void printAverageTime(const std::string& title, int (Process::*getter)() const, std::function<float()> calculateAverage) {
        
    }

    virtual void printResults(int contextSwitchCount, std::string algorithmName) {
        
        std::cout << "\n";
        std::cout << "----------------------------------------\n";
        
        std::cout << "Tempo de Turnaround para cada processo: "<< "\n";
        
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getTurnaroundTime)() << "\n";
        }
        
        std::cout << "Média = " << calculateAverageTurnaroundTime() << "\n";
        std::cout << "\n";
        
        std::cout << "Tempo de espera para cada processo: " << "\n";
        
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getWaitingTime()) << "\n";
        
        }
        std::cout << "Média = " << calculateAverageWaitingTime() << "\n";
        
        std::cout << "\nTrocas de Contexto: " << contextSwitchCount << "\n";
        
        std::cout << "Algoritmo: " << algorithmName << " Fim.\n";
        std::cout << "========================================\n\n";
    }

protected:
    // Pointer to the scheduler
    Scheduler* scheduler = nullptr;
    std::vector<Process*> processes;
    std::map<int, Process*> processPid;

    virtual Process* sortReadyProcesses(std::vector<Process*> readyProcesses) = 0;
};

#endif // SCHEDULINGALGORITHM_H