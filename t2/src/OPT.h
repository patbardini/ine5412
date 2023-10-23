#ifndef OPT_H
#define OPT_H

#include "PageReplacementAlgorithm.h"

class OPT : public PageReplacementAlgorithm {
private:
    std::vector<int> pagesVector;
public:
    OPT(unsigned int n) : PageReplacementAlgorithm(n) {}
    ~OPT() {}
    
    std::vector<int> getPages();
    void calculatePageFaults(std::vector<int>& references) override;
    std::vector<int>::iterator predict(std::vector<int>& nextReferences);
};

#endif // OPT_H