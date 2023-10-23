#include "LRU.h"
#include <algorithm>
#include <iostream>

std::vector<int> LRU::getPages() {
    return pagesVector;
}

void LRU::calculatePageFaults(std::vector<int>& references) {
    for (int page : references) {
        std::vector<int>::iterator iter = std::find(pagesVector.begin(), pagesVector.end(), page);

        if (iter == pagesVector.end()) {
            pagesVector.push_back(page);
            setPageFaults(getPageFaults()+1);
            if (pagesVector.size() > getNumberOfFrames()) {
                pagesVector.erase(pagesVector.begin());
            }
        } else {
            pagesVector.erase(iter);
            pagesVector.push_back(page);
        }
    }
}

void LRU::printPageFaults() {
    std::cout << "LRU: " << getPageFaults() << " PFs" << std::endl;
}
