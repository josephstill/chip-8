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

	for (int x = 0; x < this->buffer.size(); ++x)
	{
		std::map<unsigned int, std::string>::iterator it = this->engineOutput.find(x + CHIP_8_START);
		if ( it != this->engineOutput.end())
		{
			this->disassembly << "0x" << std::setw(3) << std::hex << it->first << " " << it->second << std::endl;
			++x; //There is a command here, we can skip the next nibble
		}
		else
		{
			this->disassembly << std::hex << std::setfill('0');
			this->disassembly << "0x" << std::setw(3) << std::hex << (x + CHIP_8_START) << " DATA ";
			this->disassembly << "0x" << std::setw(2) << std::hex << (int)this->buffer[x] << std::endl;
		}
	}
}

void DisassemblyEngine::decode(unsigned int address)
{
	unsigned int currentAddress = address;
	while(decodeHelper(currentAddress))
	{
		currentAddress+=2;
	}
}

bool DisassemblyEngine::decodeHelper(unsigned int address)
{
	if ((address - CHIP_8_START) + 1 >= this->buffer.size() ||
		 this->engineOutput.find(address) != this->engineOutput.end())
	{
		return false;
	}

	//TODO we may have decoded address + 1

	unsigned char operation[2];
	operation[0] = this->buffer[address - CHIP_8_START];
	operation[1] = this->buffer[(address + 1) - CHIP_8_START];
	AssemblyUtils::DecodeResult result = AssemblyUtils::decode(operation);
	this->engineOutput[address] = result.command;
	if (result.nextAddress > 0x00)
	{
		//TODO process link
		this->decode(result.nextAddress);
	}
	else if(result.offset > 0x00)
	{
		this->decode(address + result.offset);
	}
	return !result.commandIsTerminal;
}

} /* namespace disassembler */
