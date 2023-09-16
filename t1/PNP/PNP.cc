#include "PNP.h"
#include <algorithm>
#include <iostream>

// Construtor padrão da classe PNP
PNP::PNP() {}

// Função para ordenar os processos prontos com base na prioridade (valor mais alto tem prioridade mais alta)
Process* PNP::sortReadyProcesses(std::vector<Process*> readyProcesses) {

    // Ordena o vetor de processos prontos em ordem decrescente de prioridade
    std::sort(readyProcesses.begin(), readyProcesses.end(), [](Process* a, Process* b) {
        return a->getPriority() > b->getPriority();
    });

    // Pega o processo de maior prioridade
    Process* highestPriorityProcess = readyProcesses.front();

    return highestPriorityProcess;
}

// Função para simular o algoritmo Priority Non-Preemptive
void PNP::simulate() {
    std::cout << "-> Início algoritmo Priority Non-Preemptive...\n\n";

    int currentTime = 0; // Tempo atual da simulação

    Process* prevProcess = nullptr; // Processo anterior que estava em execução
    
    // Cria uma cópia de todos os processos para fins de saída
    std::vector<Process*> allProcesses = processes;  

    // Imprime o cabeçalho da saída
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

    // Enquanto houver processos para serem executados
    while (!processes.empty()) {
        updateReadyProcesses(currentTime);
        Process* currentProcess = getNextProcess();

        // Se o processo atual for diferente do anterior e o escalonador estiver definido, realiza a troca de contexto
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        // Enquanto o processo atual não estiver definido ou seu tempo de chegada for maior que o tempo atual
        while (!currentProcess || currentProcess->getArrivalTime() > currentTime) {
            printProcessesState();
            currentTime++;
            updateReadyProcesses(currentTime);
            if (!currentProcess) {
                currentProcess = getNextProcess();
            }
        }

        // Define o tempo de início do processo atual e o coloca em execução
        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTING);

        // Executa o processo pelo tempo de burst
        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
            currentProcess->setRemainingTime(currentProcess->getRemainingTime()-1);
        }

        // Define o tempo de término do processo e calcula o turnaround time
        currentProcess->setEndTime(currentTime);
        currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        currentProcess->setState(Process::FINISHED);
    }

    // Imprime os resultados da simulação
    printResults(scheduler->getContextSwitches(), algorithmName);
}
