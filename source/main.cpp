#include "disassembler/RomParser.h"
#include <iostream>
#include <sstream>
#include <unistd.h> // command line parsing

void printUsage()
{
	std::cout << "Usage: " << std::endl;
	std::cout << "chip-8 -hxde -f <path to file>" << std::endl;
	std::cout << "-f    Set the path to the ROM file" << std::endl;
	std::cout << "-h    Display help" << std::endl;
	std::cout << "Mode: (Choose one and only one)" << std::endl;
	std::cout << "-x    Show hex dump" << std::endl;
	std::cout << "-d    Disassemble the ROM" << std::endl;
	std::cout << "-e    Run the ROM on emulator" << std::endl;
}

int main(int argc, char**argv)
{
	int condition;
	bool hexDump = false;
	bool emulate = false;
	bool disassemble = false;
	bool fileSet = false;
	std::string file;

	while ((condition = getopt(argc, argv, "f:hxde")) != -1)
	{
		switch (condition)
		{
		case 'f':
		{
			std::stringstream ss;
			ss << optarg;
			file = ss.str();
			fileSet = true;
			break;
		}
		case 'h':
			printUsage();
			return 0;
			break;
		case 'd':
			disassemble = true;
			break;
		case 'e':
			emulate = true;
			break;
		case 'x':
			hexDump = true;
			break;
		default:
			printUsage();
			return 1;
		}
	}

	if (!fileSet)
	{
		std::cout << "You must set a file to load" << std::endl;
		printUsage();
		return 1;
	}



	if (hexDump && !(emulate || disassemble))
	{
		std::string hex = disassembler::RomParser::hexDump(file);
		std::cout << hex;
	}
	else if(emulate && !(hexDump || disassemble))
	{
		std::cout << "Coming Soon" << std::endl;
	}
	else if(disassemble && !(hexDump || emulate))
	{
		std::cout << "Coming Soon" << std::endl;
	}
	else
	{
		std::cout << "Please select one, and only one, mode." << std::endl;
		printUsage();
	}

	return 0;
}
