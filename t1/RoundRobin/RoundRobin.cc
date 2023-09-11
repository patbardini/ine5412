#include <iostream>
#include "RoundRobin.h"

RoundRobin::RoundRobin() {}

void RoundRobin::addProcess(Process* process) {
    queue.push(process);
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

void RoundRobin::simulate() {
    std::cout << "Starting Round Robin simulation...\n";

    int currentTime = 0;
    int totalProcesses = queue.size();
    std::vector<std::string> output;

    while (!queue.empty()) {
        Process* currentProcess = getNextProcess();

        if (currentProcess->getArrivalTime() > currentTime) {
            currentTime = currentProcess->getArrivalTime();
        }

        int burstTime = currentProcess->getBurstTime();

        for (int i = 0; i < std::min(timeQuantum, burstTime); ++i) {
            std::string timeOutput = " " + std::to_string(currentTime) + "-" + std::to_string(currentTime + 1) + " ";

            for (int j = 1; j <= totalProcesses; j++) {
                if (j == currentProcess->getProcessID()) {
                    timeOutput += "## ";
                } else {
                    timeOutput += "-- ";
                }
            }

            output.push_back(timeOutput);
            currentTime++;
        }

        currentProcess->setBurstTime(burstTime - timeQuantum);
        
        if (currentProcess->getBurstTime() > 0) {
            queue.push(currentProcess);  // Readiciona à fila se o processo ainda precisa de mais tempo
        } else {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
        }

        contextSwitches++;
    }

    std::cout << "tempo ";
    for (int i = 1; i <= totalProcesses; i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    for (const std::string& s : output) {
        std::cout << s << "\n";
    }

    std::cout << "Total Context Switches: " << contextSwitches << std::endl;
    std::cout << "Round Robin simulation finished.\n";
}
