#include "Utils.h"

std::list<int> Utils::read_file() {
    std::list<int> references_list;
    int reference;

    std::cin >> reference;
    while (!std::cin.eof()) {
        references_list.push_back(reference);
        std::cin >> reference;
    }

    return references_list;
}
