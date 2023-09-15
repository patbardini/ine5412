#ifndef PROCESS_H
#define PROCESS_H

#include "CPUContext.h"

// Process Header File
class Process {
private:
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int startTime;
    int endTime;
    int remainingTime;
    int state;
    CPUContext cpuContext;

public:
    enum State {
        NEW, 
        READY, 
        EXECUTING, 
        FINISHED 
    };

    // Constructor
    Process(int processID, int arrivalTime, int burstTime, int priority);

    // Destructor
    ~Process();

    // Add getter and setter methods for private members if necessary
    int getProcessID() const { return processID; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getPriority() const { return priority; }
    int getWaitingTime() const { return waitingTime; }
    int getTurnaroundTime() const { return turnaroundTime; }
    int getStartTime() const { return startTime; }
    int getEndTime() const { return endTime; }
    int getRemainingTime() const { return remainingTime; }
    int getState() const { return state; }
    
    void setWaitingTime(int wt) { waitingTime = wt; }
    void setTurnaroundTime(int tt) { turnaroundTime = tt; }
    void setBurstTime(int bt) { burstTime = bt; }
    void setPriority(int p) { priority = p; }
    void setArrivalTime(int at) { arrivalTime = at; }
    void setProcessID(int pid) { processID = pid; }
    void setStartTime(int st) { startTime = st; }
    void setEndTime(int et) { endTime = et; }
    void setRemainingTime(int rt) { remainingTime = rt; }
    void setState(int s) { state = s; }

    void saveContext(const CPUContext& currentContext);
    CPUContext getContext() const;

};

#endif /* PROCESS_H */
