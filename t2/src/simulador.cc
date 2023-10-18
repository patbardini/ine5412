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

    FIFO fifo = FIFO(numberOfFrames);
    fifo.calculatePageFaults(referencesVector);

    LRU lru = LRU(numberOfFrames);
    lru.calculatePageFaults(referencesVector);

    OPT opt = OPT(numberOfFrames);
    opt.calculatePageFaults(referencesVector);

    std::cout << numberOfFrames << " quadros" << std::endl;
    std::cout << referencesVector.size() << " refs" << std::endl;
    std::cout << "FIFO: " << fifo.getPageFaults() << " PFs" << std::endl;
    std::cout << "LRU: " << lru.getPageFaults() << " PFs" << std::endl;
    std::cout << "OPT: " << opt.getPageFaults() << " PFs" << std::endl;
}
