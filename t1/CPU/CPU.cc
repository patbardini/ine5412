#include "CPU.h"
// CPU INE5412

// Initializer for the Context nested class
CPU::Context::Context() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
    SP = 0;
    PC = 0;
    ST = 0;
}

CPU::Context::Context(const Context& other) {
    for (int i = 0; i < 6; ++i) {
        registers[i] = other.registers[i];
    }
    SP = other.SP;
    PC = other.PC;
    ST = other.ST;
}

CPU::Context::~Context() {
    // Destructor body can be kept empty unless we allocate resources dynamically
}

// Initializer for the CPU class
CPU::CPU() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
    SP = 0;
    PC = 0;
    ST = 0;
}

CPU::~CPU() {
    // Destructor body can be kept empty unless we allocate resources dynamically
}

void CPU::setCurrentContext(const Context& context) {
    for (int i = 0; i < 6; ++i) {
        registers[i] = context.registers[i];
    }
    SP = context.SP;
    PC = context.PC;
    ST = context.ST;
}

CPU::Context CPU::getCurrentContext() const {
    Context context;
    for (int i = 0; i < 6; ++i) {
        context.registers[i] = registers[i];
    }
    context.SP = SP;
    context.PC = PC;
    context.ST = ST;
    return context;
}
