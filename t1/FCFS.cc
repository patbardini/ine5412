// Class FCFS: 
//       - This class will implement the First Come First Serve scheduling algorithm

class FCFS : public SchedulingAlgorithm 
{
private:
    // Queue of processes
    std::queue<Process*> queue;

public:
    // Method to add the process
    void addProcess(Process *process) override {
        queue.push(process);
    }

    // Method to get the next process
    Process* getNextProcess() override {
        if (queue.empty()) {
            return nullptr;
        }
        Process *process = queue.front();
        queue.pop();
        return process;
    }
};
