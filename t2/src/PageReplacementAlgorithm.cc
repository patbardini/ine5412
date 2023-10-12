#include "PageReplacementAlgorithm.h"

PageReplacementAlgorithm::PageReplacementAlgorithm(int n) {
    numberOfFrames = n;
    pageFaults = 0;
}

PageReplacementAlgorithm::~PageReplacementAlgorithm() {}

int PageReplacementAlgorithm::getNumberOfFrames() {
    return numberOfFrames;
}

int PageReplacementAlgorithm::getPageFaults() {
    return pageFaults;
}

void PageReplacementAlgorithm::setNumberOfFrames(int n) {
    numberOfFrames = n;
}

void PageReplacementAlgorithm::setPageFaults(int pf) {
    pageFaults = pf;
}
