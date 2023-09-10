#include "SchedulingAlgorithm.h"

// Class SchedulingAlgorithm: 
//       - This class will be an abstract class that will be inherited by the different scheduling algorithms

void SchedulingAlgorithm::addProcessesFromParams(std::vector<ProcessParams*>& processParams) {
    for(long unsigned int i = 0; i < processParams.size() ; i++) {
        ProcessParams *p = processParams[i];
        int creationTime = p->get_creation_time();
        int priority = p->get_priority();
        int duration = p->get_duration();
        
        Process* newProcess = new Process(i+1, creationTime, duration, priority);
        addProcess(newProcess);
    }
}
