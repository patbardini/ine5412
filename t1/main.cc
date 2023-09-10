#include "Scheduler.h"
#include "FCFS.cc"

int main()
{
	File file;
	file.read_file();
	file.print_processes_params();

	FCFS fcfs;
    std::vector<ProcessParams *> processParams = file.get_processes_params();
    fcfs.addProcessesFromParams(processParams);
}