#include "PageReplacementAlgorithm.h"

PageReplacementAlgorithm::PageReplacementAlgorithm(unsigned int n) {
    numberOfFrames = n;
    pageFaults = 0;
}

PageReplacementAlgorithm::~PageReplacementAlgorithm() {}

unsigned int PageReplacementAlgorithm::getNumberOfFrames() {
    return numberOfFrames;
}

int PageReplacementAlgorithm::getPageFaults() {
    return pageFaults;
}

void PageReplacementAlgorithm::setNumberOfFrames(unsigned int n) {
    numberOfFrames = n;
}

void PageReplacementAlgorithm::setPageFaults(int pf) {
    pageFaults = pf;
}

void PageReplacementAlgorithm::simulatePageFaults(std::vector<int>& references) {
    this->calculatePageFaults(references);
    this->printPageFaults();
}
