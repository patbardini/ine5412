#include "ReadFile.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "Process.h"
#include <vector>
#include <iostream>
#include <fstream>


int main() {
    // Read processes from the file
    File fileReader;
    fileReader.read_file();
    std::vector<ProcessParams*> params = fileReader.get_processes_params();

    // Convert process params to actual processes
    std::vector<Process*> processes;

    int processID = 1;

    for(auto& param : params) {
		// Process* p = new Process(param->get_creation_time(), param->get_duration(), param->get_priority());
        Process* p = new Process(processID, param->get_creation_time(), param->get_duration(), param->get_priority());
        processes.push_back(p);
        processID++;
    }

    // Setup scheduler with FCFS algorithm
    FCFS fcfsAlgorithm;
    Scheduler scheduler(&fcfsAlgorithm); // Assuming scheduler takes a SchedulingAlgorithm pointer in its constructor

    // Add processes to scheduler
    scheduler.addProcesses(processes);

    // Run the scheduling simulation
    scheduler.simulate();

    // Cleanup if necessary (e.g., delete processes and process params)
    //...

    return 0;
}
