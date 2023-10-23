#ifndef Utils_H
#define Utils_H

#include <iostream>
#include <vector>

class Utils {
public:
    // Realiza a leitura do arquivo, armazenando seu conteúdo em um vetor
    static std::vector<int> readFile();
};

#endif // Utils_H