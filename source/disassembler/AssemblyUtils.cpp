#include "AssemblyUtils.h"

namespace disassembler
{

const std::string   AssemblyUtils::JUMP_TO_MACHINE                 = "SYS";
const unsigned char AssemblyUtils::JUMP_TO_MACHINE_CODE[2]         = {0x00, 0x00};
const std::string   AssemblyUtils::CLS_NAME                		   = "CLS";
const unsigned char AssemblyUtils::CLS_CODE[2]                	   = {0x00, 0xE0};
const std::string   AssemblyUtils::RET_NAME                		   = "RET";
const unsigned char AssemblyUtils::RET_CODE[2]                	   = {0x00, 0xEE};
const std::string   AssemblyUtils::JUMP_TO_ADDR            		   = "JP";
const unsigned char AssemblyUtils::JUMP_TO_ADDR_CODE[2]       	   = {0x10, 0x00};
const std::string   AssemblyUtils::CALL_SUBROUTINE         		   = "CALL";
const unsigned char AssemblyUtils::CALL_SUBROUTINE_CODE[2]    	   = {0x20, 0x00};
const std::string   AssemblyUtils::SKIP_IF_EQUAL           		   = "SE Vx, ";
const unsigned char AssemblyUtils::SKIP_IF_EQUAL_CODE[2]      	   = {0x30, 0x00};
const std::string   AssemblyUtils::SKIP_IF_NOT_EQUAL       		   = "SNE Vx, ";
const unsigned char AssemblyUtils::SKIP_IF_NOT_EQUAL_CODE[2]  	   = {0x40, 0x00};
const std::string   AssemblyUtils::SKIP_REG_EQUAL          		   = "SE Vx, Vy";
const unsigned char AssemblyUtils::SKIP_REG_EQUAL_CODE[2]     	   = {0x50, 0x00};
const std::string   AssemblyUtils::LOAD_REG                		   = "LD Vx, ";
const unsigned char AssemblyUtils::LOAD_REG_CODE[2]           	   = {0x60, 0x00};
const std::string   AssemblyUtils::ADD_TO_REG              		   = "ADD Vx, ";
const unsigned char AssemblyUtils::ADD_TO_REG_CODE[2]         	   = {0x70, 0x00};
const std::string   AssemblyUtils::LOAD_FROM_REG           		   = "LD Vx, Vy";
const unsigned char AssemblyUtils::LOAD_FROM_REG_CODE[2]      	   = {0x80,0x00};
const std::string   AssemblyUtils::OR_BY_REG               		   = "OR Vx, Vy";
const unsigned char AssemblyUtils::OR__BY_REG_CODE[2]         	   = {0x80, 0x01};
const std::string   AssemblyUtils::AND_BY_REG              		   = "AND Vx, Vy";
const unsigned char AssemblyUtils::AND_BY_REG_CODE[2]         	   = {0x80, 0x02};
const std::string   AssemblyUtils::XOR_BY_REG              		   = "XOR Vx, Vy";
const unsigned char AssemblyUtils::XOR_BY_REG_CODE[2]         	   = {0x80, 0x03};
const std::string   AssemblyUtils::ADD_BY_REG              		   = "ADD Vx, Vy";
const unsigned char AssemblyUtils::ADD_BY_REG_CODE[2]         	   = {0x80, 0x04};
const std::string   AssemblyUtils::SUB_BY_REG              		   = "SUB Vx, Vy";
const unsigned char AssemblyUtils::SUB_BY_REG_CODE[2]         	   = {0x80, 0x05};
const std::string   AssemblyUtils::SHIFT_RIGHT             		   = "SHR Vx, "; //TODO use of Vy?
const unsigned char AssemblyUtils::SHIFT_RIGHT_CODE[2]        	   = {0x80, 0x06};
const std::string   AssemblyUtils::MINUS_EQUAL             		   = "SUBN Vx, Vy";
const unsigned char AssemblyUtils::MINUS_EQUAL_CODE[2]        	   = {0x80, 0x07};
const std::string   AssemblyUtils::SHIFT_LEFT              		   = "SHL Vx, "; //TODO use of Vy?
const unsigned char AssemblyUtils::SHIFT_LEFT_CODE[2]         	   = {0x80, 0x0E};
const std::string   AssemblyUtils::SKIP_REG_NOT_EQUAL      		   = "SNE Vx, Vy";
const unsigned char AssemblyUtils::SKIP_REG_NOT_EQUAL_CODE[2] 	   = {0x90, 0x00};
const std::string   AssemblyUtils::LOAD_I                  		   = "LD I, ";
const unsigned char AssemblyUtils::LOAD_I_CODE[2]             	   = {0xA0, 0x00};
const std::string   AssemblyUtils::JUMP_TO_ADDR_OFFSET     		   = "JP V0, ";
const unsigned char AssemblyUtils::JUMP_TO_ADDR_OFFSET_CODE[2]     = {0xB0, 0x00};
const std::string   AssemblyUtils::RANDOM                          = "RND Vx, ";
const unsigned char AssemblyUtils::RANDOM_CODE[2]                  = {0xC0, 0x00};
const std::string   AssemblyUtils::SPRITE                      	   = "DRW  Vx, Vy, ";
const unsigned char AssemblyUtils::SPRITE_CODE[2]                  = {0xD0, 0x00};
const std::string   AssemblyUtils::SKIP_KEYPRESS_EQUAL         	   = "SKP Vx, ";
const unsigned char AssemblyUtils::SKIP_KEYPRESS_EQUAL_CODE[2]     = {0xE0, 0x9E};
const std::string   AssemblyUtils::SKIP_KEYPRESS_NOT_EQUAL     	   = "SNKP Vx, ";
const unsigned char AssemblyUtils::SKIP_KEYPRESS_NOT_EQUAL_CODE[2] = {0xE0, 0xA1};
const std::string   AssemblyUtils::GET_DELAY_TIMER                 = "LD Vx, DT";
const unsigned char AssemblyUtils::GET_DELAY_TIMER_CODE[2]         = {0xF0, 0x07};
const std::string   AssemblyUtils::GET_KEY_PRESS                   = "LD Vx, K";
const unsigned char AssemblyUtils::GET_KEY_PRESS_CODE[2]           = {0xF0, 0x0A};
const std::string   AssemblyUtils::SET_DELAY_TIMER                 = "LD DT, Vx";
const unsigned char AssemblyUtils::SET_DELAY_TIMER_CODE[2]         = {0xF0, 0x15};
const std::string   AssemblyUtils::SET_SOUND_TIMER                 = "LD ST, Vx";
const unsigned char AssemblyUtils::SET_SOUND_TIMER_CODE[2]         = {0xF0, 0x18};
const std::string   AssemblyUtils::ADD_TO_I                        = "ADD I, Vx";
const unsigned char AssemblyUtils::ADD_TO_I_CODE[2]                = {0xF0, 0x1E};
const std::string   AssemblyUtils::LOAD_SPRITE                     = "LD F, Vx";
const unsigned char AssemblyUtils::LOAD_SPRITE_CODE[2]             = {0xF0, 0x29};
const std::string   AssemblyUtils::LOAD_BCD                        = "LD B, Vx";
const unsigned char AssemblyUtils::LOAD_BCD_CODE[2]                = {0xF0, 0x33};
const std::string   AssemblyUtils::STORE_REGS                      = "LD [I], Vx";
const unsigned char AssemblyUtils::STORE_REGS_CODE[2]              = {0xF0, 0x55};
const std::string   AssemblyUtils::READ_REGS                       = "LD Vx, [I]";
const unsigned char AssemblyUtils::READ_REGS_CODE[2]               = {0xF0, 0x65};

std::string AssemblyUtils::decode(unsigned char* operation)
{
	unsigned int opNib13 = (unsigned int)(operation[0] >> 4);
	unsigned int opNibl2 = (unsigned int) (operation[0] & 0x0F);
	unsigned int opNib11 = (unsigned int)(operation[1] >> 4);
	unsigned int opNibl0 = (unsigned int) (operation[1] & 0x0F);

    std::string retVal = "BAD OP CODE";

	switch (opNib13)
	{
	case 0x0:
		switch (operation[1])
		{
		case 0x00:
			retVal = JUMP_TO_MACHINE;
			break;
		case 0xe0:
			retVal = CLS_NAME;
			break;
		case 0xee:
			retVal = RET_NAME;
			break;
		}
		break;
	case 0x1:
		{
			retVal = JUMP_TO_ADDR;
		}
		break;
	case 0x2:
		{
			retVal = CALL_SUBROUTINE;
		}
		break;
	case 0x3:
		{
			retVal = SKIP_IF_EQUAL;
		}
		break;
	case 0x4:
		{
			retVal = SKIP_IF_NOT_EQUAL;
		}
		break;
	case 0x5:
		{
			retVal = SKIP_REG_EQUAL;
		}
		break;
	case 0x6:
		{
			retVal = LOAD_REG;
		}
		break;
	case 0x7:
		{
			retVal = ADD_TO_REG;
		}
		break;
	case 0x8:
		{
			switch (opNibl0)
			{
			case 0x0:
				retVal = LOAD_FROM_REG;
				break;
			case 0x1:
				retVal = OR_BY_REG;
				break;
			case 0x2:
				retVal = AND_BY_REG;
				break;
			case 0x3:
				retVal = XOR_BY_REG;
				break;
			case 0x4:
				retVal = ADD_BY_REG;
				break;
			case 0x5:
				retVal = SUB_BY_REG;
				break;
			case 0x6:
				retVal = SHIFT_RIGHT;
				break;
			case 0x7:
				retVal = MINUS_EQUAL;
				break;
			case 0xE:
				retVal = SHIFT_LEFT;
				break;
			}
		}
		break;
	case 0x9:
		retVal = SKIP_REG_NOT_EQUAL;
		break;
	case 0xA:
		retVal = LOAD_I;
		break;
	case 0xB:
		retVal = JUMP_TO_ADDR_OFFSET;
		break;
	case 0xC:
		retVal = RANDOM;
		break;
	case 0xD:
		retVal = SPRITE;
		break;
	case 0xE:
		break;
	case 0xF:
		break;
	}

	return retVal;
}

} /* namespace disassembler */
