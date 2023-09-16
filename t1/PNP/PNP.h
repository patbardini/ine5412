#ifndef PNP_H
#define PNP_H

// Inclusão das bibliotecas e arquivos de cabeçalho necessários
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <functional>
#include <string>
#include <map>

// Definição da classe PNP (Priority Non-Preemptive)
class PNP : public SchedulingAlgorithm { // A classe PNP herda de SchedulingAlgorithm
public:
    // Construtor da classe PNP
    PNP();

    // Função para simular o algoritmo, sobrescrevendo a função da classe base
    void simulate() override;

    // Função para ordenar os processos prontos com base na prioridade, sobrescrevendo a função da classe base
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;

private:
    // Nome do algoritmo, usado para fins de saída
    std::string algorithmName = "Priority Non-Preemptive";
};

#endif // PNP_H
