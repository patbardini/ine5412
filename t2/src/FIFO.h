#ifndef FIFO_H
#define FIFO_H

#include "PageReplacementAlgorithm.h"
#include <queue>

class FIFO : public PageReplacementAlgorithm {
private:
    std::queue<int> pagesQueue;
public:
    FIFO(unsigned int n) : PageReplacementAlgorithm(n) {}
    ~FIFO() {}
    
    std::queue<int> getPages();
    void calculatePageFaults(std::vector<int>& references) override;
    void printPageFaults() override;
};

#endif // FIFO_H