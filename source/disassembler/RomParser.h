#ifndef ROMPARSER_H_
#define ROMPARSER_H_

#include <string>
#include <vector>

namespace disassembler
{

/**
 * Parses ROM files and provides a list of instructions.
 */
class RomParser
{

public:

	struct command
	{
		unsigned char val[2];
	};

	static std::vector<RomParser::command> parseRom(std::string romFileName);
	static std::string hexDump(std::string romFileName);

private:
	// No construction
	RomParser();
};

} /* namespace disassembler */

#endif /* ROMPARSER_H_ */
