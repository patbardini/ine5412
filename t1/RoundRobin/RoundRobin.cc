#include <iostream>
#include "RoundRobin.h"

RoundRobin::RoundRobin() {}

Process* RoundRobin::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    // The simulate already sorts the processes by arrival time
    return readyProcesses.front();
}

void RoundRobin::simulate() {
    std::cout << "-> Início algoritmo Round Robin...\n\n";

    int currentTime = 0;
    Process* prevProcess = nullptr;
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

        // Troca de contexto se o processo atual for diferente do anterior
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);


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
            // queue.push(currentProcess);  // Readiciona à fila se o processo ainda precisa de mais tempo
            processes.push_back(currentProcess);
            currentProcess->setState(Process::READY);
        } else {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
            currentProcess->setState(Process::FINISHED);
        }
        prevProcess = currentProcess;
    }
    }

    printResults(scheduler->getContextSwitches(), algorithmName);
}
