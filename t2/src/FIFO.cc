#include "FIFO.h"
#include <unordered_set>

std::queue<int> FIFO::getPages() {
    return pagesQueue;
}

void FIFO::calculatePageFaults(std::vector<int>& references) {
    // para acessar as páginas atuais com maior facilidade
    std::unordered_set<int> currentPagesSet;

    for (int page : references) {
        if (currentPagesSet.find(page) == currentPagesSet.end()) {
            pagesQueue.push(page);
            currentPagesSet.insert(page);
            setPageFaults(getPageFaults()+1);
            if (pagesQueue.size() > getNumberOfFrames()) {
                currentPagesSet.erase(pagesQueue.front());
                pagesQueue.pop();
            }
        }
    }
}
