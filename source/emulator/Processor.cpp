#include "Processor.h"

namespace emulator
{

Processor::Processor(std::vector<unsigned char> data, QObject *parent) : QObject(parent),
                                                                         memory(new Memory(data)),
                                                                         continueRunning(false)
{

}

void Processor::execute()
{
    this->continueRunning = true;
    while(this->continueRunning && this->executeNextCommand());
}

void Processor::resumeExecution()
{

}

void Processor::setStepMode()
{

}

void Processor::clearStepMode()
{

}

bool Processor::executeNextCommand()
{

}

}
