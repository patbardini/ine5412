#ifndef RoundRobin_H
#define RoundRobin_H

#include <queue>
#include <map>
#include <functional>
#include <string>
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"

// Classe RoundRobin que implementa o algoritmo de escalonamento Round Robin
class RoundRobin : public SchedulingAlgorithm {
private:
    // Quantum de tempo para cada processo no algoritmo Round Robin
    const int timeQuantum = 2;

    // Nome do algoritmo, usado para fins de impressão
    const char * algorithmName = "Round Robin";

public:
    // Construtor da classe RoundRobin
    RoundRobin();

    // Destrutor virtual da classe RoundRobin
    virtual ~RoundRobin() {}  

    // Função para simular o algoritmo Round Robin
    void simulate() override;

    // Função para ordenar os processos prontos com base na ordem de chegada
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;
};

#endif // RoundRobin_H
