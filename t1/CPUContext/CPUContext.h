#ifndef CPU_CONTEXT_H
#define CPU_CONTEXT_H

#include <cstdint> // For uint64_t

class CPUContext {
public:
    uint64_t registers[6]; // 6 general-purpose registers
    uint64_t SP;           // Stack pointer
    uint64_t PC;           // Program counter
    uint64_t ST;           // Status

    // Constructor to initialize all context attributes
    CPUContext();

    // Destructor
    ~CPUContext();
};

#endif // CPU_CONTEXT_H
