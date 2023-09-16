#ifndef SJF_H
#define SJF_H

#include <vector>
#include <functional>
#include <string>
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <map>

// Classe SJF (Shortest Job First) que herda de SchedulingAlgorithm.
// Esta classe implementa o algoritmo de escalonamento Shortest Job First.
class SJF : public SchedulingAlgorithm {
private:
    // Nome do algoritmo, usado para fins de impressão.
    const char * algorithmName = "Shortest Job First";

public:
    // Construtor padrão da classe SJF.
    SJF();

    // Função para ordenar os processos prontos com base no tempo de burst.
    // Retorna o processo com o menor tempo de burst.
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;

    // Função para simular o algoritmo Shortest Job First.
    void simulate() override;
};

#endif // SJF_H
