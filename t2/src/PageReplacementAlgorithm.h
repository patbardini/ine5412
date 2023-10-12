#ifndef PageReplacementAlgorithm_H
#define PageReplacementAlgorithm_H

class PageReplacementAlgorithm {
private:
    int numberOfFrames;
    int pageFaults;
public:
    PageReplacementAlgorithm(int n);
    virtual ~PageReplacementAlgorithm();

    int getNumberOfFrames();
    int getPageFaults();
    void setNumberOfFrames(int n);
    void setPageFaults(int pf);
};

#endif // PageReplacementAlgorithm_H