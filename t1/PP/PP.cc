#include "PP.h"
#include <algorithm>
#include <iostream>

// Construtor da classe PP (Priority Preemptive)
PP::PP() {}

// Função para ordenar os processos prontos com base na prioridade (maior prioridade primeiro)
Process* PP::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });

    Process* highestPriorityProcess = readyProcesses.front();

    return highestPriorityProcess;
}

// Função para obter o processo de maior prioridade
Process* PP::getHighestPriorityProcess(Process* currentProcess) {
    Process* highestPriorityProcess = currentProcess;
    // Itera sobre todos os processos para encontrar o de maior prioridade
    for (Process* p : processes) {
        if (p->getState() == Process::READY && p->getPriority() > currentProcess->getPriority()) {
            highestPriorityProcess = p;
        }
    }
    // Se o processo de maior prioridade não for o processo atual, mude o estado do processo atual para READY
    if (highestPriorityProcess != currentProcess) {
        currentProcess->setState(Process::READY);
        processes.push_back(currentProcess);
    }
    return highestPriorityProcess;
}

// Função para simular o algoritmo Priority Preemptive
void PP::simulate() {
    std::cout << "-> Início algoritmo Priority Preemptive...\n\n";

    int currentTime = 0;
    std::vector<Process*> allProcesses = processes;  // Cria uma cópia de todos os processos para fins de saída
  
    Process* prevProcess = nullptr;

    std::cout << "tempo ";
    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    // Função auxiliar para imprimir o estado dos processos
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

    // Enquanto houver processos a serem executados
    while (!processes.empty()) {
        updateReadyProcesses(currentTime);
        Process* currentProcess = getNextProcess();

        // Se o processo anterior for diferente do atual, faça a troca de contexto
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        // Enquanto o processo atual não chegar ou seu tempo de chegada for maior que o tempo atual
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

        // Execute o processo atual até que seu tempo de burst termine
        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
            highestPriorityProcess = getHighestPriorityProcess(currentProcess);
            // Se um processo de maior prioridade estiver pronto ou o tempo restante do processo atual for 0, interrompa a execução
            if (highestPriorityProcess != currentProcess || currentProcess->getRemainingTime() <= 0) {
                break;
            }
            printProcessesState();
            currentTime++;
            currentProcess->setRemainingTime(currentProcess->getRemainingTime()-1);
        }

        // Se o processo atual não estiver em estado READY, finalize-o
        if (currentProcess->getState() != Process::READY) {
            currentProcess->setEndTime(currentTime);
            currentProcess->setTurnaroundTime(currentTime - currentProcess->getArrivalTime());
            currentProcess->setState(Process::FINISHED);
        } 
    }

    // Imprime os resultados finais
    printResults(scheduler->getContextSwitches(), algorithmName);
}
