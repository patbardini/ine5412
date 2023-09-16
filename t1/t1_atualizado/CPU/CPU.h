#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
public:
    class Context {
    public:
        uint64_t registers[6]; // 6 general-purpose registers
        uint64_t SP;           // Stack pointer
        uint64_t PC;           // Program counter
        uint64_t ST;           // Status

        Context();
        Context(const Context& other);
        ~Context();
    };

    CPU();
    ~CPU();

    void setCurrentContext(const Context& context); // Restore the CPU context with the given values
    Context getCurrentContext() const; // Fetch the current context of the CPU

private:
    uint64_t registers[6]; // Actual 6 general-purpose registers of the CPU
    uint64_t SP;           // Actual Stack pointer of the CPU
    uint64_t PC;           // Actual Program counter of the CPU
    uint64_t ST;           // Actual Status of the CPU
};

#endif // CPU_H
