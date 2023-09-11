# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11 -IReadFile -IScheduler -IProcess -ISchedulingAlgorithm -ICPUContext -IFCFS -ISJF

# Target executable name
TARGET = read_file

# .cc files 
SRC_FILES = Scheduler/Scheduler.cc Process/Process.cc CPUContext/CPUContext.cc FCFS/FCFS.cc SJF/SJF.cc read_file.cc
OBJ_FILES = $(SRC_FILES:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)
