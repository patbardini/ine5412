#ifndef PageReplacementAlgorithm_H
#define PageReplacementAlgorithm_H

#include <vector>

// Classe abstrata para os algoritmos de substituição de páginas
class PageReplacementAlgorithm {
private:
    unsigned int numberOfFrames;  // Quantidade de quadros
    int pageFaults;  // Quantidade de faltas de página
public:
    // Construtor e destrutor
    PageReplacementAlgorithm(unsigned int n);
    virtual ~PageReplacementAlgorithm();

    // Getters e setters
    unsigned int getNumberOfFrames();
    int getPageFaults();
    void setNumberOfFrames(unsigned int n);
    void setPageFaults(int pf);

    // Simulação de faltas de página
    void simulatePageFaults(std::vector<int>& references);
    // Realiza o cálculo da quantidade de faltas de página
    virtual void calculatePageFaults(std::vector<int>& references) = 0;
    // Apresenta na tela a quantidade de faltas de página
    virtual void printPageFaults() = 0;
};

#endif // PageReplacementAlgorithm_H