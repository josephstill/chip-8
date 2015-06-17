#include "disassembler/RomParser.h"
#include "Disassembler.h"
#include "MainWindow.h"
#include <QApplication>
#include <iostream>
#include <sstream>
#include <unistd.h> // command line parsing

void printUsage()
{
	std::cout << "Usage: " << std::endl;
    std::cout << "chip-8 -hxd -f <path to file>" << std::endl;
    std::cout << "-u    Launch the GUI" << std::endl;
	std::cout << "-f    Set the path to the ROM file" << std::endl;
	std::cout << "-h    Display help" << std::endl;
	std::cout << "Mode: (Choose one and only one)" << std::endl;
	std::cout << "-x    Show hex dump" << std::endl;
    std::cout << "-d    Disassemble the ROM" << std::endl;
    std::cout << "No arguments to show the GUI" << std::endl;
}

int main(int argc, char**argv)
{
	int condition;
	bool hexDump = false;
	bool emulate = false;
	bool disassemble = false;
	bool fileSet = false;
	bool launchUi = false;
	std::string file;

    while ((condition = getopt(argc, argv, "f:hxdu")) != -1)
	{
		switch (condition)
		{
		case 'f': // Set File
		{
			std::stringstream ss;
			ss << optarg;
			file = ss.str();
			fileSet = true;
			break;
		}
		case 'h': // Help
			printUsage();
			return 0;
			break;
		case 'd': // Disassemble Mode
			disassemble = true;
			break;
		case 'x': // Hex Dump Mode
			hexDump = true;
			break;
        case 'u':
            launchUi = true;
            break;
		default:
			printUsage();
			return 1;
		}
	}

    if (!fileSet || launchUi)
	{
		QApplication::setOrganizationName("Joseph Walker");
		QApplication::setApplicationName("Application Example");
		QApplication::setApplicationVersion("0.0.1");
		QApplication app(argc, argv);
	    MainWindow mainWin;
	    mainWin.show();
	    return app.exec();
	}

	// TODO: Validate File

	if (!launchUi)
	{
		if (hexDump && !(emulate || disassemble))
		{
			std::string hex = disassembler::RomParser::hexDump(file);
			std::cout << hex;
		}
        else if(disassemble && !(hexDump || emulate))
		{
			Disassembler d(file);
			std::cout << d.getText();
		}
		else
		{
			std::cout << "Please select one, and only one, mode." << std::endl;
			printUsage();
		}
	}

	return 0;
}
