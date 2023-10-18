#ifndef LRU_H
#define LRU_H

#include "PageReplacementAlgorithm.h"

class LRU : public PageReplacementAlgorithm {
private:
    std::vector<int> pagesVector;
public:
    LRU(int n) : PageReplacementAlgorithm(n) {}
    ~LRU() {}
    
    std::vector<int> getPages();
    void calculatePageFaults(std::vector<int> references) override;
};

#endif // LRU_H