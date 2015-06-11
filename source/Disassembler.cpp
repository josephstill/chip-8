#include "Disassembler.h"

Disassembler::Disassembler(std::string fileName): engine(fileName)
{
	this->engine.disassemble();
}

Disassembler::~Disassembler()
{

}

std::string Disassembler::getText() const
{
	return this->engine.getDisassembly();
}
