#ifndef DISASSEMBLYENGINE_H_
#define DISASSEMBLYENGINE_H_

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace disassembler
{

/**
 * This class provides the functionality to disassemble a ROM.
 */
class DisassemblyEngine
{

public:

	/**
	 * Constructs a disassembly engine for the given file name.
	 * @param fileName The name of the file to disassemble
	 */
	DisassemblyEngine(std::string fileName);

	/**
	 * Destructor
	 */
	~DisassemblyEngine();

	/**
	 * Begins the disassembly process
	 */
	void disassemble();

	/**
	 * Returns the disassembly in text format.
	 * @return A string containing the disassembly.
	 */
	std::string getDisassembly() const { return this->disassembly.str(); }

private:

	void decode(unsigned int address);
	bool decodeHelper(unsigned int address);

	std::map<unsigned int, std::string>  addressOutput;
	std::vector<unsigned char>           buffer;
	std::stringstream                    disassembly;
	std::map<unsigned int, std::string>  engineOutput;

};

} /* namespace disassembler */

#endif /* DISASSEMBLYENGINE_H_ */
