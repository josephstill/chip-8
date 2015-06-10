#ifndef ROMPARSER_H_
#define ROMPARSER_H_

#include <string>
#include <vector>

namespace disassembler
{

/**
 * This class provides a set of static utilities relating to reading a ROM file.
 */
class RomParser
{

public:

	/**
	 * A container that holds a single command
	 */
	struct command
	{
		unsigned char val[2];
	};

	/**
	 * Creates a hex dump of the provided ROM file.
	 * @param romFileName The path to the file to parse.
	 * @return a string containing the hex dump.
	 */
	static std::string hexDump(std::string romFileName);

	/**
	 *
	 */
	static std::vector<unsigned char> loadBuffer(std::string romFileName);

	/**
	 * Parses the ROM file into individual commands and provides the commands in a vector.
	 * @param romFileName The path to the file to parse
	 * @return a vector of commands
	 */
	static std::vector<RomParser::command> parseRom(std::string romFileName);

private:
	// No construction
	RomParser();
};

} /* namespace disassembler */

#endif /* ROMPARSER_H_ */
