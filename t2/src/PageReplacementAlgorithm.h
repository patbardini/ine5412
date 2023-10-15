#ifndef PageReplacementAlgorithm_H
#define PageReplacementAlgorithm_H

#include <list>

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

    virtual void calculatePageFaults(std::list<int> references) = 0;
};

#endif // PageReplacementAlgorithm_H