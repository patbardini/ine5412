#include <iostream>
#include <queue>
#include <algorithm>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "FCFS.h"

// Construtor padrão do algoritmo FCFS
FCFS::FCFS() {}

// Função que ordena os processos prontos para execução.
// Como o algoritmo é FCFS, ele simplesmente retorna o primeiro processo da lista.
Process* FCFS::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    // A simulação já ordena os processos pelo tempo de chegada
    return readyProcesses.front();
}

// Função que simula o algoritmo de escalonamento FCFS
void FCFS::simulate() {
    std::cout << "-> Início algoritmo First Come First Served...\n\n";

    int currentTime = 0; // Representa o tempo atual na simulação
    Process* prevProcess = nullptr; // Mantém o registro do processo anterior
    std::vector<Process*> allProcesses = processes;  // Todos os processos a serem escalonados

    // Imprime os cabeçalhos para o diagrama de tempo
    std::cout << "tempo ";
    for (size_t i = 1; i <= allProcesses.size(); i++) {
        std::cout << "P" << i << " ";
    }
    std::cout << "\n";

    // Função lambda para imprimir o estado atual dos processos
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

    // Enquanto houver processos a serem escalonados
    while (!processes.empty()) {
        updateReadyProcesses(currentTime); // Atualiza a lista de processos prontos
        Process* currentProcess = getNextProcess(); // Pega o próximo processo a ser escalonado

        // Se não houver processo atual ou se o tempo de chegada do processo for maior que o tempo atual
        while (!currentProcess || currentProcess->getArrivalTime() > currentTime) {
            printProcessesState();
            currentTime++;
            updateReadyProcesses(currentTime);
            if (!currentProcess) {
                currentProcess = getNextProcess();
            }
        }

        // Realiza a troca de contexto se o processo atual for diferente do anterior
        if (prevProcess != currentProcess && scheduler) {
            scheduler->contextSwitch(prevProcess, currentProcess);
        }

        currentProcess->setStartTime(currentTime);
        currentProcess->setState(Process::EXECUTING);

        // Executa o processo pelo tempo de burst
        for (int j = 0; j < currentProcess->getBurstTime(); ++j) {
            updateReadyProcesses(currentTime);
            printProcessesState();
            currentTime++;
            currentProcess->setRemainingTime(currentProcess->getRemainingTime()-1);
        }

        // Atualiza as informações do processo após a execução
        currentProcess->setEndTime(currentTime);
        currentProcess->setTurnaroundTime(currentProcess->getEndTime() - currentProcess->getArrivalTime());
        currentProcess->setState(Process::FINISHED);
        prevProcess = currentProcess;
    }

    // Imprime os resultados da simulação
    printResults(scheduler->getContextSwitches(), algorithmName);
}
