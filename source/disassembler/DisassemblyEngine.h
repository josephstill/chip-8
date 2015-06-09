#ifndef DISASSEMBLYENGINE_H_
#define DISASSEMBLYENGINE_H_

#include <string>
#include <vector>
#include <map>

namespace disassembler
{

/**
 *
 */
class DisassemblyEngine
{

public:

	/**
	 *
	 */
	DisassemblyEngine(std::string fileName);

	/**
	 *
	 */
	~DisassemblyEngine();

	/**
	 *
	 */
	void disassemble();

private:

	void decode(unsigned int address);
	bool decodeHelper(unsigned int address);


	std::vector<unsigned char>           buffer;
	std::map<unsigned int, std::string>  engineOutput;

};

} /* namespace disassembler */

#endif /* DISASSEMBLYENGINE_H_ */
