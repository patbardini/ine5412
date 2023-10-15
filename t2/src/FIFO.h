#ifndef FIFO_H
#define FIFO_H

#include "PageReplacementAlgorithm.h"
#include <queue>

class FIFO : public PageReplacementAlgorithm {
private:
    std::queue<int> pages_queue;
public:
    FIFO(int n) : PageReplacementAlgorithm(n) {}
    ~FIFO() {}
    
    std::queue<int> getPages();
    void calculatePageFaults(std::list<int> references) override;
};

#endif // FIFO_H