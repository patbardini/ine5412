#ifndef LRU_H
#define LRU_H

#include "PageReplacementAlgorithm.h"

class LRU : public PageReplacementAlgorithm {
private:
    std::vector<int> pagesVector;  // Vetor com as páginas atualmente presentes na memória
public:
    // Construtor e destrutor
    LRU(unsigned int n) : PageReplacementAlgorithm(n) {}
    ~LRU() {}
    
    std::vector<int> getPages();

    void calculatePageFaults(std::vector<int>& references) override;
    void printPageFaults() override;
};

#endif // LRU_H