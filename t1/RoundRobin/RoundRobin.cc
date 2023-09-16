#include <iostream>
#include "RoundRobin.h"

// Construtor da classe RoundRobin
RoundRobin::RoundRobin() {}

// Função para ordenar os processos prontos com base na ordem de chegada
Process* RoundRobin::sortReadyProcesses(std::vector<Process*> readyProcesses) {
    // A simulação já ordena os processos pelo tempo de chegada
    return readyProcesses.front();
}

// Função para simular o algoritmo Round Robin
void RoundRobin::simulate() {
    std::cout << "-> Início algoritmo Round Robin...\n\n";

    int currentTime = 0;
    Process* prevProcess = nullptr;
    std::vector<Process*> allProcesses = processes;  

    // Imprime o cabeçalho da tabela de simulação
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

        // Espera até que um processo esteja pronto para ser executado
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

            // Executa o processo pelo tempo de quantum ou até que ele termine
            for (int i = 0; i < std::min(timeQuantum, remainingTime); ++i) {
                updateReadyProcesses(currentTime);
                printProcessesState();
                currentTime++;
            }

            currentProcess->setRemainingTime(remainingTime - timeQuantum);
            
            // Se o processo ainda precisa de mais tempo, ele é readicionado à fila
            if (currentProcess->getRemainingTime() > 0) {
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

    // Imprime os resultados da simulação
    printResults(scheduler->getContextSwitches(), algorithmName);
}
