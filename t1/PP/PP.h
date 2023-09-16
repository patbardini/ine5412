#ifndef PP_H
#define PP_H

// Inclusões necessárias para a classe PP
#include "SchedulingAlgorithm.h"
#include "Scheduler.h"
#include <vector>
#include <functional>
#include <string>
#include <map>

// Definição da classe PP que herda de SchedulingAlgorithm
class PP : public SchedulingAlgorithm {
public:
    // Construtor da classe
    PP();

    // Função virtual para ordenar os processos prontos com base na prioridade
    // Esta função é sobrescrita da classe base
    Process* sortReadyProcesses(std::vector<Process*> readyProcesses) override;

    // Função virtual para simular o algoritmo Priority Preemptive
    // Esta função é sobrescrita da classe base
    void simulate() override;

private:
    // Nome do algoritmo, usado principalmente para fins de impressão
    std::string algorithmName = "Priority Preemptive";

    // Função privada para obter o processo de maior prioridade
    // Esta função é usada internamente durante a simulação
    Process* getHighestPriorityProcess(Process* currentProcess);
};

#endif // PP_H
