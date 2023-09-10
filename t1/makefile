# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Target executable name
TARGET = main

# .cc files
CC_FILES = CPUContext.cc Process.cc Scheduler.cc SchedulingAlgorithm.cc main.cc

# .o files
OBJ_FILES = $(CC_FILES:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)
