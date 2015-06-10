#ifndef ASSEMBLYUTILS_H_
#define ASSEMBLYUTILS_H_

#include <string>

namespace disassembler
{

/**
 * This class provides a set of utilities that will be used in translating between
 * assembly and byte code.
 */
class AssemblyUtils
{

public:

	/**
	 * Decodes the given byte code into assembly.
	 * @param operation The byte code to decode.
	 * @return A string containing the assembly listing.
	 */
	static std::string decode(unsigned char* operation);

private:

	AssemblyUtils(); //No construction

	/*
	 * The following are assembly names and bases for operation codes that
	 * are implemented. X, Y, and N values are not included in these
	 * bases and will be added before sending them out.
	 */
	const static std::string   JUMP_TO_MACHINE;
	const static unsigned char JUMP_TO_MACHINE_CODE[2];
	const static std::string   CLS_NAME;
	const static unsigned char CLS_CODE[2];
	const static std::string   RET_NAME;
	const static unsigned char RET_CODE[2];
	const static std::string   JUMP_TO_ADDR;
	const static unsigned char JUMP_TO_ADDR_CODE[2];
	const static std::string   CALL_SUBROUTINE;
	const static unsigned char CALL_SUBROUTINE_CODE[2];
	const static std::string   SKIP_IF_EQUAL;
	const static unsigned char SKIP_IF_EQUAL_CODE[2];
	const static std::string   SKIP_IF_NOT_EQUAL;
	const static unsigned char SKIP_IF_NOT_EQUAL_CODE[2];
	const static std::string   SKIP_REG_EQUAL;
	const static unsigned char SKIP_REG_EQUAL_CODE[2];
	const static std::string   LOAD_REG;
	const static unsigned char LOAD_REG_CODE[2];
	const static std::string   ADD_TO_REG;
	const static unsigned char ADD_TO_REG_CODE[2];
	const static std::string   LOAD_FROM_REG;
	const static unsigned char LOAD_FROM_REG_CODE[2];
	const static std::string   OR_BY_REG;
	const static unsigned char OR__BY_REG_CODE[2];
	const static std::string   AND_BY_REG;
	const static unsigned char AND_BY_REG_CODE[2];
	const static std::string   XOR_BY_REG;
	const static unsigned char XOR_BY_REG_CODE[2];
	const static std::string   ADD_BY_REG;
	const static unsigned char ADD_BY_REG_CODE[2];
	const static std::string   SUB_BY_REG;
	const static unsigned char SUB_BY_REG_CODE[2];
	const static std::string   SHIFT_RIGHT;
	const static unsigned char SHIFT_RIGHT_CODE[2];
	const static std::string   MINUS_EQUAL;
	const static unsigned char MINUS_EQUAL_CODE[2];
	const static std::string   SHIFT_LEFT;
	const static unsigned char SHIFT_LEFT_CODE[2];
	const static std::string   SKIP_REG_NOT_EQUAL;
	const static unsigned char SKIP_REG_NOT_EQUAL_CODE[2];
	const static std::string   LOAD_I;
	const static unsigned char LOAD_I_CODE[2];
	const static std::string   JUMP_TO_ADDR_OFFSET;
	const static unsigned char JUMP_TO_ADDR_OFFSET_CODE[2];
	const static std::string   RANDOM;
	const static unsigned char RANDOM_CODE[2];
	const static std::string   SPRITE;
	const static unsigned char SPRITE_CODE[2];
	const static std::string   SKIP_KEYPRESS_EQUAL;
	const static unsigned char SKIP_KEYPRESS_EQUAL_CODE[2];
	const static std::string   SKIP_KEYPRESS_NOT_EQUAL;
	const static unsigned char SKIP_KEYPRESS_NOT_EQUAL_CODE[2];
	const static std::string   GET_DELAY_TIMER        ;
	const static unsigned char GET_DELAY_TIMER_CODE[2];
	const static std::string   GET_KEY_PRESS;
	const static unsigned char GET_KEY_PRESS_CODE[2];
	const static std::string   SET_DELAY_TIMER;
	const static unsigned char SET_DELAY_TIMER_CODE[2];
	const static std::string   SET_SOUND_TIMER;
	const static unsigned char SET_SOUND_TIMER_CODE[2];
	const static std::string   ADD_TO_I;
	const static unsigned char ADD_TO_I_CODE[2];
	const static std::string   LOAD_SPRITE;
	const static unsigned char LOAD_SPRITE_CODE[2];
	const static std::string   LOAD_BCD;
	const static unsigned char LOAD_BCD_CODE[2];
	const static std::string   STORE_REGS;
	const static unsigned char STORE_REGS_CODE[2];
	const static std::string   READ_REGS;
	const static unsigned char READ_REGS_CODE[2];
};

} /* namespace disassembler */

#endif /* ASSEMBLYUTILS_H_ */
