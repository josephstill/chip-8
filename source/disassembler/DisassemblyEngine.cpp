#include "DisassemblyEngine.h"
#include "RomParser.h"
#include "AssemblyUtils.h"

#include <iostream> //TODO Remove Me
#include <iomanip> //TODO Remove me

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
	this->decode(0); //TODO consider offset
}

void DisassemblyEngine::decode(unsigned int address)
{
	while (this->decodeHelper(address) && address < this->buffer.size()) ++address;
}

bool DisassemblyEngine::decodeHelper(unsigned int address)
{
	if (address + 1 >= this->buffer.size() ||
		this->engineOutput.find(address) != this->engineOutput.end())
	{
		return false;
	}

	unsigned char operation[2];
	operation[0] = this->buffer[address];
	operation[1] = this->buffer[address + 1];
	this->engineOutput[address] = AssemblyUtils::decode(operation);
	std::cout << this->engineOutput[address] << std::endl;
	address += 2;
	return true;
}

} /* namespace disassembler */
