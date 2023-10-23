#include "Utils.h"
#include "FIFO.h"
#include "OPT.h"
#include "LRU.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: ./simulador <numero_de_frames> < <nome_do_arquivo>" << std::endl;
        return 1;
    }

    int numberOfFrames = std::stoi(argv[1]);
    std::vector<int> referencesVector = Utils::readFile();

    // Imprime os resultados referentes à quantidade de quadros e ao número de referências
    std::cout << numberOfFrames << " quadros" << std::endl;
    std::cout << referencesVector.size() << " refs" << std::endl;

    // Calcula e imprime os resultados para cada um dos algoritmos solicitados
    FIFO fifo = FIFO(numberOfFrames);
    fifo.simulatePageFaults(referencesVector);

    LRU lru = LRU(numberOfFrames);
    lru.simulatePageFaults(referencesVector);

    OPT opt = OPT(numberOfFrames);
    opt.simulatePageFaults(referencesVector);
}
