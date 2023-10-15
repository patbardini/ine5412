#include "Utils.h"

std::vector<int> Utils::read_file() {
    std::vector<int> references_list;
    int reference;

    std::cin >> reference;
    while (!std::cin.eof()) {
        references_list.push_back(reference);
        std::cin >> reference;
    }

    return references_list;
}
