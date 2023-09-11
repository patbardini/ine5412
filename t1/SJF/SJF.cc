#include "SJF.h"

SJF::SJF() {}

void SJF::addProcess(Process* process) {
    processes.push_back(process);
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
    
    // Sorting the processes based on burst time
    std::sort(processes.begin(), processes.end(), [](Process* a, Process* b) {
        return a->getBurstTime() < b->getBurstTime();
    });

    Process* shortestProcess = processes.front();
    processes.erase(processes.begin());
    return shortestProcess;
}

void SJF::simulate() {
    std::cout << "Starting SJF simulation...\n";

    int currentTime = 0;
    std::cout << "tempo ";

    std::vector<Process*> allProcesses = processes;  // Make a copy for printing purposes

    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    while (!processes.empty()) {
        Process* currentProcess = getNextProcess();
        
        if (currentProcess->getArrivalTime() > currentTime) {
            currentTime = currentProcess->getArrivalTime();
        }

        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            std::cout << currentTime << "-" << (currentTime + 1) << " ";
            
            for (Process* p : allProcesses) {  // Notice the change here
                if (p == currentProcess) {
                    std::cout << "## ";
                } else {
                    std::cout << "-- ";
                }
            }
            std::cout << "\n";
            currentTime++;
        }

        contextSwitches++;
    }
    std::cout << "Total Context Switches: " << contextSwitches << std::endl;
    std::cout << "SJF simulation finished.\n";
}
