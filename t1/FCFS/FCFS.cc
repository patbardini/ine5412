#include <iostream>
#include <queue>
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
        if (p->getArrivalTime() <= currentTime && p->getState() == Process::NOVO) {
            p->setState(Process::PRONTO);
        }
    }
}

void FCFS::simulate() {
    std::cout << "Starting FCFS simulation...\n";

    int currentTime = 0;
    int totalProcesses = queue.size();  // get the total number of processes
    std::vector<std::string> output;    // to store the output for each time interval

    while (!queue.empty()) {
        Process* currentProcess = getNextProcess();

        if (currentProcess->getArrivalTime() > currentTime) {
            currentTime = currentProcess->getArrivalTime();
        }

        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTANDO);
        
        for (int i = 0; i < currentProcess->getBurstTime(); ++i) {
            updateReadyProcesses(currentTime);
            std::string timeOutput = " " + std::to_string(currentTime) + "-" + std::to_string(currentTime + 1) + " ";
            
            for (int j = 1; j <= totalProcesses; j++) {
                switch (processPid[j]->getState()) {
                    case Process::EXECUTANDO:
                        timeOutput += "## ";
                        break;
                    case Process::PRONTO:
                        timeOutput += "-- ";
                        break; 
                    default:
                        timeOutput += "   ";
                        break;
                }
            }

            output.push_back(timeOutput);
            currentTime++;
        }

        currentProcess->setEndTime(currentTime);
        currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        currentProcess->setState(Process::TERMINADO);
        contextSwitches++;
    }

    // Results
    std::cout << "tempo ";
    for (int i = 1; i <= totalProcesses; i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    for (const std::string& s : output) {
        std::cout << s << "\n";
    }

    std::cout << "Total Context Switches: " << contextSwitches << std::endl;
    std::cout << "FCFS simulation finished.\n";
}
