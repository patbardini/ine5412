
#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include "Process.h"


class Scheduler; // Declaração antecipada da classe Scheduler

// SchedulingAlgorithm Header File
class SchedulingAlgorithm 
{
public:
    // Construtor
    virtual ~SchedulingAlgorithm() {}

    // Simula o algoritmo de escalonamento
    virtual void simulate() = 0;

    // Adiciona um processo ao algoritmo de escalonamento
    virtual void addProcess(Process* process) {
        processes.push_back(process);
        processPid[process->getProcessID()] = process;
    }

    // Adiciona vários processos ao algoritmo de escalonamento
    virtual void addProcesses(const std::vector<Process*>& processes) {
        for(Process* process : processes) {
            addProcess(process);
        }
    }

    // Obtém o próximo processo do algoritmo de escalonamento
    virtual Process* getNextProcess() {
        // Se não houver processos, retorna nullptr
        if (processes.empty()) {
            return nullptr;
        }
        
        // Atualiza os processos prontos 
        std::vector<Process*> readyProcesses;
        for (Process* p : processes) {
            if (p->getState() == Process::READY) {
                readyProcesses.push_back(p);
            }
        }

        // Se não houver processos prontos, retorna nullptr
        if (readyProcesses.empty()) {
            return nullptr;
        }

        // Ordena os processos prontos com base na ordem em que o algoritmo de escalonamento deseja executá-los
        Process* selectedProcess = sortReadyProcesses(readyProcesses);

        // Remove o processo selecionado da lista de processos
        auto it = std::find(processes.begin(), processes.end(), selectedProcess);
        if (it != processes.end()) {
            processes.erase(it);
        }

        // Retorna o processo selecionado
        return selectedProcess;
    }

    // Atualiza os processos prontos para executar
    virtual void updateReadyProcesses(int currentTime) {
        for (auto &pair : processPid) {
            Process* p = pair.second;
            if (p->getArrivalTime() <= currentTime && p->getState() == Process::NEW) {
                p->setState(Process::READY);
            } 
        }
    }

    // Define o Scheduler associado ao algoritmo de escalonamento
    virtual void setScheduler(Scheduler* sched) {
        scheduler = sched;
    }

    // Calcula o tempo médio de turnaround
    virtual float calculateAverageTurnaroundTime() {
        float average = 0;
        for (auto &pair : processPid) {
            int turnaroundTime = pair.second->getTurnaroundTime();
            average += turnaroundTime;
        }
        average /= processPid.size();
        return average;
    }

    // Calcula o tempo médio de espera
    virtual float calculateAverageWaitingTime() {
        float average = 0;
        for (auto &pair : processPid) {
            int waitingTime = pair.second->getWaitingTime();
            average += waitingTime;
        }
        average /= processPid.size();
        return average;
    }

    // Imprime os resultados da simulação
    virtual void printResults(int contextSwitchCount, std::string algorithmName) {
        
        std::cout << "\n";
        std::cout << "----------------------------------------\n";
        
        std::cout << "Tempo de Turnaround para cada processo: "<< "\n";
        
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getTurnaroundTime)() << "\n";
        }
        
        std::cout << "Média = " << calculateAverageTurnaroundTime() << "\n";
        std::cout << "\n";
        
        std::cout << "Tempo de espera para cada processo: " << "\n";
        
        for (const auto& pair : processPid) {
            Process* p = pair.second;
            std::cout << "P" << pair.first << " = " << (p->getWaitingTime()) << "\n";
        
        }
        std::cout << "Média = " << calculateAverageWaitingTime() << "\n";
        
        std::cout << "\nTrocas de Contexto: " << contextSwitchCount << "\n";
        
        std::cout << "Algoritmo: " << algorithmName << " Fim.\n";
        std::cout << "========================================\n\n";
    }

protected:
    // Pointer to the scheduler
    Scheduler* scheduler = nullptr; // Ponteiro para o escalonador
    std::vector<Process*> processes; // Lista de processos
    std::map<int, Process*> processPid; // Mapa de processos com base no PID

    virtual Process* sortReadyProcesses(std::vector<Process*> readyProcesses) = 0; // Função virtual para ordenar os processos prontos de acordo com o algoritmo de escalonamento
};

#endif // SCHEDULINGALGORITHM_H