#include "Emulator.h"

#include "disassembler/RomParser.h"
#include <iostream>

Emulator::Emulator(QString filePath) : processor(new emulator::Processor(disassembler::RomParser::loadBuffer(filePath.toStdString())))
{

}

Emulator::~Emulator()
{

}

void Emulator::beginEmulation()
{
    this->processor->execute();
}
