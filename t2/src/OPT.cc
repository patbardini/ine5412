#include "OPT.h"
#include <algorithm>

std::vector<int> OPT::getPages() {
    return pagesVector;
}

void OPT::calculatePageFaults(std::vector<int>& references) {
    std::vector<int> nextReferences = references;

    for (int page : references) {
        nextReferences.erase(nextReferences.begin());
        if (std::find(pagesVector.begin(), pagesVector.end(), page) == pagesVector.end()) {
            if (pagesVector.size() >= getNumberOfFrames()) {
                std::vector<int>::iterator toBeReplaced = predict(nextReferences);
                pagesVector.erase(toBeReplaced);
            }
            pagesVector.push_back(page);
            setPageFaults(getPageFaults()+1);
        }
    }
}

std::vector<int>::iterator OPT::predict(std::vector<int>& nextReferences) {
    int pageToBeReplaced = pagesVector.front();
    size_t currentIndex = 0;

    for (int page : pagesVector) {
        std::vector<int>::iterator iter = std::find(nextReferences.begin(), nextReferences.end(), page);
        size_t newIndex = std::distance(nextReferences.begin(), iter);

        if (newIndex > currentIndex) {
            currentIndex = newIndex;
            pageToBeReplaced = page;
        }
        
    }
    std::vector<int>::iterator pageToBeReplacedIter = std::find(pagesVector.begin(), pagesVector.end(), pageToBeReplaced);
    return pageToBeReplacedIter;
}
