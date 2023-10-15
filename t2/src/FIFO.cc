#include "FIFO.h"
#include <unordered_set>

std::queue<int> FIFO::getPages() {
    return pages_queue;
}

void FIFO::calculatePageFaults(std::vector<int> references) {
    // para acessar as páginas atuais com maior facilidade
    std::unordered_set<int> current_pages_set;

    for (int page : references) {
        if (current_pages_set.find(page) == current_pages_set.end()) {
            pages_queue.push(page);
            current_pages_set.insert(page);
            setPageFaults(getPageFaults()+1);
            if (pages_queue.size() > getNumberOfFrames()) {
                current_pages_set.erase(pages_queue.front());
                pages_queue.pop();
            }
        }
    }
}
