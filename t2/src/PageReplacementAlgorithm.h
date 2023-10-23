#ifndef PageReplacementAlgorithm_H
#define PageReplacementAlgorithm_H

#include <vector>

class PageReplacementAlgorithm {
private:
    unsigned int numberOfFrames;
    int pageFaults;
public:
    PageReplacementAlgorithm(unsigned int n);
    virtual ~PageReplacementAlgorithm();

    unsigned int getNumberOfFrames();
    int getPageFaults();
    void setNumberOfFrames(unsigned int n);
    void setPageFaults(int pf);

    void simulatePageFaults(std::vector<int>& referencesVector);
    virtual void calculatePageFaults(std::vector<int>& references) = 0;
    virtual void printPageFaults() = 0;
};

#endif // PageReplacementAlgorithm_H