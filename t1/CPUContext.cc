#include "CPUContext.h"
// Class CPUContext:
//       - This class will hold the information about the CPU context of a particular process
//          -> Program counter, stack pointer, etc.

// Initialize all context attributes to 0 
CPUContext::CPUContext() : SP(0), PC(0), ST(0) {
    for(int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
}

// Destructor (currently empty as we're not dynamically allocating anything)
CPUContext::~CPUContext() {
}
