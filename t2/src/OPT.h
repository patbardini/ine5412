#ifndef OPT_H
#define OPT_H

#include "PageReplacementAlgorithm.h"

class OPT : public PageReplacementAlgorithm {
private:
    std::vector<int> pagesVector;  // Vetor com as páginas atualmente presentes na memória
public:
    // Construtor e destrutor
    OPT(unsigned int n) : PageReplacementAlgorithm(n) {}
    ~OPT() {}
    
    std::vector<int> getPages();

    void calculatePageFaults(std::vector<int>& references) override;
    // Prevê qual página deve ser substituída com base num vetor com as próximas referências
    std::vector<int>::iterator predict(std::vector<int>& nextReferences);
    void printPageFaults() override;
};

#endif // OPT_H