#include "CPU.h"

namespace emulator
{

CPU::CPU(std::vector<unsigned char> program)
{
    //this->CPUState.PC = 0x200;
    this->loadCharacters();
    this->loadBuffer(program);
    this->loadScreen();
}

CPU::~CPU()
{

}

void CPU::loadBuffer(std::vector<unsigned char> program)
{

}

void CPU::loadCharacters()
{

}

void CPU::loadScreen()
{

}

}
