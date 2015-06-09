#ifndef DISASSEMBLER_H_
#define DISASSEMBLER_H_

#include "disassembler/DisassemblyEngine.h"

#include <string>

/**
 * This class manages the disassembly of chip-8 ROMS.
 */
class Disassembler
{

public:

	/**
	 * Initializes the disassembler with the file of the given name.
	 * @param fileName The name of the file to disassemble.
	 */
	Disassembler(std::string fileName);

	/**
	 * Destructor
	 */
	~Disassembler();

	/**
	 * Returns the string contents of the disassembled file.
	 * @return A string containing the disassembled file
	 */
	std::string getText() const;

private:
	disassembler::DisassemblyEngine engine;

};

#endif /* DISASSEMBLER_H_ */
