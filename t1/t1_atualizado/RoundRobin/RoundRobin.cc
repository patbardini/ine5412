#include <iostream>
#include "RoundRobin.h"

RoundRobin::RoundRobin() {}

void RoundRobin::addProcess(Process* process) {
    queue.push(process);
    processPid[process->getProcessID()] = process;
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

void RoundRobin::simulate() {
    std::cout << "-> Início algoritmo Round Robin...\n\n";

    int currentTime = 0;
    int totalProcesses = queue.size();
    Process* prevProcess = nullptr;
    std::vector<std::string> output;

    while (!queue.empty()) {
        Process* currentProcess = getNextProcess();

        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTING);

        int remainingTime = currentProcess->getRemainingTime();

        for (int i = 0; i < std::min(timeQuantum, remainingTime); ++i) {
            updateReadyProcesses(currentTime);
            std::string timeOutput = " " + std::to_string(currentTime) + "-" + std::to_string(currentTime + 1) + " ";

            for (int j = 1; j <= totalProcesses; j++) {
                switch (processPid[j]->getState()) {
                    case Process::EXECUTING:
                        timeOutput += "## ";
                        break;
                    case Process::READY:
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

        currentProcess->setRemainingTime(remainingTime - timeQuantum);
        
        if (currentProcess->getRemainingTime() > 0) {
            queue.push(currentProcess);  // Readiciona à fila se o processo ainda precisa de mais tempo
            currentProcess->setState(Process::READY);
        } else {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
            currentProcess->setState(Process::FINISHED);
        }
        prevProcess = currentProcess;
    }

    std::cout << "tempo ";
    for (int i = 1; i <= totalProcesses; i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    for (const std::string& s : output) {
        std::cout << s << "\n";
    }


    const char * algorithmName = "Round Robin";
    printResults(scheduler->getContextSwitches(), algorithmName);
}
