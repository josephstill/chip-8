#include "RomParser.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h> //fopen

namespace disassembler
{

std::string RomParser::hexDump(std::string romFileName)
{
	std::stringstream ss;
	std::vector<RomParser::command> rom = parseRom(romFileName);
	unsigned long address = 0;
	ss << std::hex << std::setfill('0');
	for (int x = 0; x < rom.size(); x++)
	{
		if (x % 8 == 0)
		{
			if (address > 0)
			{
				ss << "\n";
			}
			ss << std::setw(8) << std::hex << address << ' ';
			address += 16;
		}
		ss << std::setw(2) << std::hex << (int)rom[x].val[0];
		ss << std::setw(2) << std::hex << (int)rom[x].val[1];
		ss << ' ';
	}
	ss << "\n";
	return ss.str();
}

std::vector<unsigned char> RomParser::loadBuffer(std::string romFileName)
{
	std::vector<unsigned char> retVal;
	char buffer[16];
	std::ifstream reader(romFileName.c_str(), std::ios::in);
	while (reader.good())
	{
		int readIndex;
		for (readIndex = 0; readIndex < 16 && reader.get(buffer[readIndex]); ++readIndex);

		if (readIndex != 0)
		{
			for (int i = 0; i < 16; ++i)
			{
				if (i < readIndex)
				{
					retVal.push_back(buffer[i]);
				}
			}
		}
	}

	if (reader.is_open())
	{
		reader.close();
	}
	return retVal;
}

std::vector<RomParser::command> RomParser::parseRom(std::string romFileName)
{
	std::vector<RomParser::command> retVal;
	char buffer[16];
	std::ifstream reader(romFileName.c_str(), std::ios::in);
	while (reader.good())
	{
		int readIndex;
		for (readIndex = 0; readIndex < 16 && reader.get(buffer[readIndex]); ++readIndex);

		if (readIndex != 0)
		{
			for (int i = 0; i < 16; ++i)
			{
				if (i % 2 == 0)
				{
					retVal.push_back(RomParser::command());
				}
				if (i < readIndex)
				{
					retVal.back().val[i % 2] = buffer[i];
				}
				else
				{

				}
			}
		}
	}

	if (reader.is_open())
	{
		reader.close();
	}
	return retVal;
}

} /* namespace disassembler */
