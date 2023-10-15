#ifndef OPT_H
#define OPT_H

#include "PageReplacementAlgorithm.h"
#include <vector>

class OPT : public PageReplacementAlgorithm {
private:
    std::vector<int> pages_vector;
public:
    OPT(int n) : PageReplacementAlgorithm(n) {}
    ~OPT() {}
    
    std::vector<int> getPages();
    void calculatePageFaults(std::list<int> references) override;
};

#endif // OPT_H