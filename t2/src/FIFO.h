#ifndef FIFO_H
#define FIFO_H

#include "PageReplacementAlgorithm.h"
#include <queue>

class FIFO : public PageReplacementAlgorithm {
private:
    std::queue<int> pagesQueue;  // Fila com as páginas atualmente presentes na memória
public:
    // Construtor e destrutor
    FIFO(unsigned int n) : PageReplacementAlgorithm(n) {}
    ~FIFO() {}
    
    std::queue<int> getPages();

    void calculatePageFaults(std::vector<int>& references) override;
    void printPageFaults() override;
};

#endif // FIFO_H