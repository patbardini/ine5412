#include "OPT.h"
#include <algorithm>
#include <iostream>

std::vector<int> OPT::getPages() {
    return pagesVector;
}

void OPT::calculatePageFaults(std::vector<int>& references) {
    std::vector<int> nextReferences = references;  // Cópia do vetor de referências para armazenar somente as referências futuras

    for (int page : references) {
        nextReferences.erase(nextReferences.begin());  // Remove página atual do vetor de referências futuras
        if (std::find(pagesVector.begin(), pagesVector.end(), page) == pagesVector.end()) {  // Caso a página não estiver na memória
            if (pagesVector.size() >= getNumberOfFrames()) {  // Se o tamanho do vetor exceder a quantidade de quadros
                std::vector<int>::iterator toBeReplaced = predict(nextReferences);  // Seleciona página a ser substituída com base nas referências futuras
                pagesVector.erase(toBeReplaced);
            }
            pagesVector.push_back(page);  // Adiciona página ao final do vetor
            setPageFaults(getPageFaults()+1);  // Incrementa a quantidade de faltas de página
        }
    }
}

std::vector<int>::iterator OPT::predict(std::vector<int>& nextReferences) {
    int pageToBeReplaced = pagesVector.front();  // Página a ser substituída, a princípio a primeira do vetor 
    size_t currentIndex = 0;

    for (int page : pagesVector) {  // Para cada página presente na memória
        // Busca a sua próxima referência futura
        std::vector<int>::iterator iter = std::find(nextReferences.begin(), nextReferences.end(), page);
        // Obtém o seu índice no vetor de referências
        size_t newIndex = std::distance(nextReferences.begin(), iter);
        
        // Caso o índice obtido for maior do que o atual, passa a ser a nova página a ser substituída
        if (newIndex > currentIndex) {  
            currentIndex = newIndex;
            pageToBeReplaced = page;
        }
        
    }
    std::vector<int>::iterator pageToBeReplacedIter = std::find(pagesVector.begin(), pagesVector.end(), pageToBeReplaced);
    return pageToBeReplacedIter;
}

void OPT::printPageFaults() {
    std::cout << "OPT: " << getPageFaults() << " PFs" << std::endl;
}
