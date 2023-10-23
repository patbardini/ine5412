#include "FIFO.h"
#include <unordered_set>
#include <iostream>

std::queue<int> FIFO::getPages() {
    return pagesQueue;
}

void FIFO::calculatePageFaults(std::vector<int>& references) {
    std::unordered_set<int> currentPagesSet;  // Para acessar as páginas atuais com maior facilidade

    for (int page : references) {
        if (currentPagesSet.find(page) == currentPagesSet.end()) {  // Se a página não estiver na memória
            pagesQueue.push(page);  // Adiciona ao final da fila
            currentPagesSet.insert(page);  // Adiciona ao set
            setPageFaults(getPageFaults()+1);  // Incrementa a quantidade de faltas de página
            if (pagesQueue.size() > getNumberOfFrames()) {  // Se o tamanho da fila exceder a quantidade de quadros
                currentPagesSet.erase(pagesQueue.front());  // Remove do set o primeiro elemento da fila
                pagesQueue.pop();  // Remove o primeiro elemento da fila
            }
        }
    }
}

void FIFO::printPageFaults() {
    std::cout << "FIFO: " << getPageFaults() << " PFs" << std::endl;
}
