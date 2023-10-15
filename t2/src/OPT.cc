#include "OPT.h"
#include <algorithm>

std::vector<int> OPT::getPages() {
    return pages_vector;
}

void OPT::calculatePageFaults(std::vector<int> references) {
    std::vector<int> nextReferences = references;

    for (int page : references) {
        nextReferences.erase(nextReferences.begin());

        if (std::find(pages_vector.begin(), pages_vector.end(), page) == pages_vector.end()) {
            if (pages_vector.size() >= getNumberOfFrames()) {
                std::vector<int>::iterator toBeReplaced = predict(nextReferences);
                pages_vector.erase(toBeReplaced);
            }
            pages_vector.push_back(page);
            setPageFaults(getPageFaults()+1);
        }
    }
}

std::vector<int>::iterator OPT::predict(std::vector<int> nextReferences) {
    int pageToBeReplaced = pages_vector.front();
    size_t currentIndex = 0;

    for (int page : pages_vector) {
        std::vector<int>::iterator iter = std::find(nextReferences.begin(), nextReferences.end(), page);
        size_t newIndex = std::distance(nextReferences.begin(), iter);

        if (newIndex > currentIndex) {
            currentIndex = newIndex;
            pageToBeReplaced = page;
        }
        
    }
    std::vector<int>::iterator pageToBeReplacedIt = std::find(pages_vector.begin(), pages_vector.end(), pageToBeReplaced);
    return pageToBeReplacedIt;
}
