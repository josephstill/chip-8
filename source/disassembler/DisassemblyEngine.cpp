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

    if (this->buffer.size() == 0)
    {
        this->disassembly << "ROM Parse Error: The file appears to be empty." << std::endl;
        return;
    }

	for (int x = 0; x < this->buffer.size(); ++x)
	{
		// Display the address
		this->disassembly << std::hex << std::setfill('0');
		this->disassembly << "0x" << std::setw(3) << std::hex << (x + CHIP_8_START);

		// Show a label if there is one
		std::map<unsigned int, std::string>::iterator linkIt = this->addressOutput.find(x + CHIP_8_START);
		if (linkIt != this->addressOutput.end())
		{
			this->disassembly << " " << linkIt->second << " ";
		}
		else
		{
			this->disassembly << "          "; // For looks
		}

		std::map<unsigned int, std::string>::iterator it = this->engineOutput.find(x + CHIP_8_START);
		if ( it != this->engineOutput.end())
		{
			this->disassembly << it->second << std::endl;
			++x; //There is a command here, we can skip the next nibble
		}
		else
		{
			this->disassembly << "DATA 0x" << std::setw(2) << std::hex << (int)this->buffer[x] << std::endl;
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

	unsigned char operation[2];
	operation[0] = this->buffer[address - CHIP_8_START];
	operation[1] = this->buffer[(address + 1) - CHIP_8_START];
	AssemblyUtils::DecodeResult result = AssemblyUtils::decode(operation);
	this->engineOutput[address] = result.command;
	if (result.nextAddress > 0x00)
	{
		if (result.nextAddressIsLink)
		{
			this->addressOutput[result.nextAddress] = result.linkName;
		}
		this->decode(result.nextAddress);
	}
	else if(result.offset > 0x00)
	{
		this->decode(address + result.offset);
	}
	return !result.commandIsTerminal;
}

} /* namespace disassembler */
