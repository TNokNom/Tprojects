
#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

class Instruction {
public:
    int id;
    std::string operation;

    Instruction(int id, const std::string &operation) : id(id), operation(operation) {}
};

class PipelineStage {
public:
    virtual void process(Instruction &instruction) = 0;
};

class FetchStage : public PipelineStage {
public:
    std::queue<Instruction> &instructionQueue;

    FetchStage(std::queue<Instruction> &instrQueue) : instructionQueue(instrQueue) {}

    void process(Instruction &instruction) override {
        if (!instructionQueue.empty()) {
            instruction = instructionQueue.front();
            instructionQueue.pop();
            std::cout << "Fetched Instruction: ID=" << instruction.id << ", Operation=" << instruction.operation << std::endl;
        } else {
            instruction = Instruction(-1, ""); // No instruction
        }
    }
};

class DecodeStage : public PipelineStage {
public:
    void process(Instruction &instruction) override {
        if (instruction.id != -1) {
            std::cout << "Decoded Instruction: ID=" << instruction.id << ", Operation=" << instruction.operation << std::endl;
        }
    }
};

class ExecuteStage : public PipelineStage {
public:
    void process(Instruction &instruction) override {
        if (instruction.id != -1) {
            std::cout << "Executing Instruction: ID=" << instruction.id << " -> Performing " << instruction.operation << std::endl;
            // Simulate execution delay
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
};

class WriteBackStage : public PipelineStage {
public:
    void process(Instruction &instruction) override {
        if (instruction.id != -1) {
            std::cout << "Writing back result of Instruction: ID=" << instruction.id << std::endl;
        }
    }
};

class Pipeline {
private:
    std::queue<Instruction> instructionQueue;
    FetchStage fetchStage;
    DecodeStage decodeStage;
    ExecuteStage executeStage;
    WriteBackStage writeBackStage;

public:
    Pipeline() 
        : fetchStage(instructionQueue), decodeStage(), executeStage(), writeBackStage() {}

    void addInstruction(const Instruction &instruction) {
        instructionQueue.push(instruction);
    }

    void run() {
        Instruction instruction(0, "");
        while (true) {
            fetchStage.process(instruction);
            decodeStage.process(instruction);
            executeStage.process(instruction);
            writeBackStage.process(instruction);

            // Simulate a small delay to represent the pipeline cycle
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            
            // Exit condition after all instructions are processed
            if (instruction.id == -1 && instructionQueue.empty()) {
                break;
            }

            // Prepare for the next loop iteration
            if (instruction.id != -1) {
                instruction.id++; // Increment instruction ID for the next cycle, if any
            }
        }
    }
};

int main() {
    Pipeline pipeline;

    // Add dummy instructions to the pipeline
    for (int i = 0; i < 5; ++i) {
        pipeline.addInstruction(Instruction(i, "Operation_" + std::to_string(i)));
    }

    // Run the pipeline
    pipeline.run();

    return 0;
}
