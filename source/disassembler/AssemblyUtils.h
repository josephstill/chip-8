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
	const std::string   JUMP_TO_MACHINE                 = "SYS";
	const unsigned char JUMP_TO_MACHINE_CODE[2]         = {0x00, 0x00};
	const std::string   CLS_NAME                		= "CLS";
	const unsigned char CLS_CODE[2]                		= {0x00, 0xE0};
	const std::string   RET_NAME                		= "RET";
	const unsigned char RET_CODE[2]                		= {0x00, 0xEE};
	const std::string   JUMP_TO_ADDR            		= "JP";
	const unsigned char JUMP_TO_ADDR_CODE[2]       		= {0x10, 0x00};
	const std::string   CALL_SUBROUTINE         		= "CALL";
	const unsigned char CALL_SUBROUTINE_CODE[2]    		= {0x20, 0x00};
	const std::string   SKIP_IF_EQUAL           		= "SE Vx, ";
	const unsigned char SKIP_IF_EQUAL_CODE[2]      		= {0x30, 0x00};
	const std::string   SKIP_IF_NOT_EQUAL       		= "SNE Vx, ";
	const unsigned char SKIP_IF_NOT_EQUAL_CODE[2]  		= {0x40, 0x00};
	const std::string   SKIP_REG_EQUAL          		= "SE Vx, Vy";
	const unsigned char SKIP_REG_EQUAL_CODE[2]     		= {0x50, 0x00};
	const std::string   LOAD_REG                		= "LD Vx, ";
	const unsigned char LOAD_REG_CODE[2]           		= {0x60, 0x00};
	const std::string   ADD_TO_REG              		= "ADD Vx, ";
	const unsigned char ADD_TO_REG_CODE[2]         		= {0x70, 0x00};
	const std::string   LOAD_FROM_REG           		= "LD Vx, Vy";
	const unsigned char LOAD_FROM_REG_CODE[2]      		= {0x80,0x00};
	const std::string   OR_BY_REG               		= "OR Vx, Vy";
	const unsigned char OR__BY_REG_CODE[2]         		= {0x80, 0x01};
	const std::string   AND_BY_REG              		= "AND Vx, Vy";
	const unsigned char AND_BY_REG_CODE[2]         		= {0x80, 0x02};
	const std::string   XOR_BY_REG              		= "XOR Vx, Vy";
	const unsigned char XOR_BY_REG_CODE[2]         		= {0x80, 0x03};
	const std::string   ADD_BY_REG              		= "ADD Vx, Vy";
	const unsigned char ADD_BY_REG_CODE[2]         		= {0x80, 0x04};
	const std::string   SUB_BY_REG              		= "SUB Vx, Vy";
	const unsigned char SUB_BY_REG_CODE[2]         		= {0x80, 0x05};
	const std::string   SHIFT_RIGHT             		= "SHR Vx, "; //TODO use of Vy?
	const unsigned char SHIFT_RIGHT_CODE[2]        		= {0x80, 0x06};
	const std::string   MINUS_EQUAL             		= "SUBN Vx, Vy";
	const unsigned char MINUS_EQUAL_CODE[2]        		= {0x80, 0x07};
	const std::string   SHIFT_LEFT              		= "SHL Vx, "; //TODO use of Vy?
	const unsigned char SHIFT_LEFT_CODE[2]         		= {0x80, 0x0E};
	const std::string   SKIP_REG_NOT_EQUAL      		= "SNE Vx, Vy";
	const unsigned char SKIP_REG_NOT_EQUAL_CODE[2] 		= {0x90, 0x00};
	const std::string   LOAD_I                  		= "LD I, ";
	const unsigned char LOAD_I_CODE[2]             		= {0xA0, 0x00};
	const std::string   JUMP_TO_ADDR_OFFSET     		= "JP V0, ";
	const unsigned char JUMP_TO_ADDR_OFFSET_CODE[2]     = {0xB0, 0x00};
	const std::string   RANDOM                      	= "RND Vx, ";
	const unsigned char RANDOM_CODE[2]                 	= {0xC0, 0x00};
	const std::string   SPRITE                      	= "DRW  Vx, Vy, ";
	const unsigned char SPRITE_CODE[2]                 	= {0xD0, 0x00};
	const std::string   SKIP_KEYPRESS_EQUAL         	= "SKP Vx, ";
	const unsigned char SKIP_KEYPRESS_EQUAL_CODE[2]    	= {0xE0, 0x9E};
	const std::string   SKIP_KEYPRESS_NOT_EQUAL     	= "SNKP Vx, ";
	const unsigned char SKIP_KEYPRESS_NOT_EQUAL_CODE[2]	= {0xE0, 0xA1};
	const std::string   GET_DELAY_TIMER                 = "LD Vx, DT";
	const unsigned char GET_DELAY_TIMER_CODE[2]         = {0xF0, 0x07};
	const std::string   GET_KEY_PRESS                   = "LD Vx, K";
	const unsigned char GET_KEY_PRESS_CODE[2]           = {0xF0, 0x0A};
	const std::string   SET_DELAY_TIMER                 = "LD DT, Vx";
	const unsigned char SET_DELAY_TIMER_CODE[2]         = {0xF0, 0x15};
	const std::string   SET_SOUND_TIMER                 = "LD ST, Vx";
	const unsigned char SET_SOUND_TIMER_CODE[2]         = {0xF0, 0x18};
	const std::string   ADD_TO_I                        = "ADD I, Vx";
	const unsigned char ADD_TO_I_CODE[2]                = {0xF0, 0x1E};
	const std::string   LOAD_SPRITE                     = "LD F, Vx";
	const unsigned char LOAD_SPRITE_CODE[2]             = {0xF0, 0x29};
	const std::string   LOAD_BCD                        = "LD B, Vx";
	const unsigned char LOAD_BCD_CODE[2]                = {0xF0, 0x33};
	const std::string   STORE_REGS                      = "LD [I], Vx";
	const unsigned char STORE_REGS_CODE[2]              = {0xF0, 0x55};
	const std::string   READ_REGS                       = "LD Vx, [I]";
	const unsigned char READ_REGS_CODE[2]               = {0xF0, 0x65};
};

} /* namespace disassembler */

#endif /* ASSEMBLYUTILS_H_ */
