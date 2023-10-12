# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -I./src

# Target executable name
TARGET = simulador

# Source directory
SRC_DIR = src

# .cc files 
SRC_FILES = $(SRC_DIR)/Utils.cc $(SRC_DIR)/PageReplacementAlgorithm.cc $(SRC_DIR)/FIFO.cc $(SRC_DIR)/LRU.cc $(SRC_DIR)/OPT.cc $(SRC_DIR)/simulador.cc

OBJ_FILES = $(SRC_FILES:.cc=.o)

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)
