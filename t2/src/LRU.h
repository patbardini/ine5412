#ifndef LRU_H
#define LRU_H

#include "PageReplacementAlgorithm.h"
#include <vector>

class LRU : public PageReplacementAlgorithm {
private:
    std::vector<int> pages_vector;
public:
    LRU(int n) : PageReplacementAlgorithm(n) {}
    ~LRU() {}
    
    std::vector<int> getPages();
};

#endif // LRU_H