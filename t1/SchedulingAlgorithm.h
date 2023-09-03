#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H
#include <iostream>
#include <queue>
#include "Process.h"

// Class SchedulingAlgorithm:
//       - This class will be an abstract class that will be inherited by the different scheduling algorithms

class SchedulingAlgorithm 
{
public:
    virtual void addProcess(Process *process) = 0;
    virtual Process* getNextProcess() = 0;
    virtual ~SchedulingAlgorithm() { }
};

#endif /* SCHEDULINGALGORITHM_H */
