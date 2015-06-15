#include "Emulator.h"

#include "disassembler/RomParser.h"
#include <iostream>

Emulator::Emulator(QString filePath, bool stepMode) : processor(new emulator::Processor(disassembler::RomParser::loadBuffer(filePath.toStdString())))
{
    this->processor->setStepMode(stepMode);
}

Emulator::~Emulator()
{

}

void Emulator::beginEmulation()
{
    this->processor->execute();
}
