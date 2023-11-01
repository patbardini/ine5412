#include "LRU.h"
#include <algorithm>
#include <iostream>

std::vector<int> LRU::getPages() {
    return pagesVector;
}

void LRU::calculatePageFaults(std::vector<int>& references) {
    for (int page : references) {
        // Busca pela página no vetor de páginas presentes na memória
        std::vector<int>::iterator iter = std::find(pagesVector.begin(), pagesVector.end(), page);

        if (iter == pagesVector.end()) { // Caso não encontre a página
            pagesVector.push_back(page);  // Adiciona ao final do vetor
            setPageFaults(getPageFaults()+1);  // Incrementa a quantidade de faltas de página
            if (pagesVector.size() > getNumberOfFrames()) {  // Se o tamanho do vetor exceder a quantidade de quadros
                pagesVector.erase(pagesVector.begin());  // Remove o primeiro elemento do vetor
            }
        } else {  // Caso encontre a página, esta é movida para o final do vetor
            pagesVector.erase(iter);
            pagesVector.push_back(page);
        }
    }
}

void LRU::printPageFaults() {
    std::cout << "LRU: " << getPageFaults() << " PFs" << std::endl;
}
