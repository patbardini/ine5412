#include "Utils.h"

std::vector<int> Utils::readFile() {
    std::vector<int> referencesVector;
    int reference;

    std::cin >> reference;
    while (!std::cin.eof()) {
        referencesVector.push_back(reference);
        std::cin >> reference;
    }

    return referencesVector;
}
