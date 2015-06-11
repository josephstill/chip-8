#include "DisassemblyEngine.h"
#include "RomParser.h"
#include "AssemblyUtils.h"
#include <iomanip>
#include <iostream>

#define CHIP_8_START 0x200

namespace disassembler
{

DisassemblyEngine::DisassemblyEngine(std::string fileName)
{
	this->buffer = RomParser::loadBuffer(fileName);
}

DisassemblyEngine::~DisassemblyEngine()
{

}

void DisassemblyEngine::disassemble()
{
	this->decode(CHIP_8_START);

	std::map<unsigned int, std::string>::iterator it;
	for (it = this->engineOutput.begin(); it != this->engineOutput.end(); ++it)
	{
		this->disassembly << "0x" << std::setw(3) << std::hex << it->first << " " << it->second << std::endl;
	}
}

void DisassemblyEngine::decode(unsigned int address)
{
	while (this->decodeHelper(address) && address < (this->buffer.size() - CHIP_8_START)) address +=2;
}

bool DisassemblyEngine::decodeHelper(unsigned int address)
{
	if (address + 1 >= (this->buffer.size() + CHIP_8_START) ||
		this->engineOutput.find(address) != this->engineOutput.end())
	{
		return false;
	}

	unsigned char operation[2];
	operation[0] = this->buffer[address - CHIP_8_START];
	operation[1] = this->buffer[(address + 1) - CHIP_8_START];
	this->engineOutput[address] = AssemblyUtils::decode(operation);
	return true;
}

} /* namespace disassembler */
