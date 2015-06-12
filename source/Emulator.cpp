#include "Emulator.h"

#include "disassembler/RomParser.h"
#include <iostream>

Emulator::Emulator(QString filePath) : memory(disassembler::RomParser::loadBuffer(filePath.toStdString()))
{
    std::cout << this->memory << std::endl;
}

Emulator::~Emulator()
{

}
