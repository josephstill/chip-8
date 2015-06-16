#include "Memory.h"
#include <iomanip>
#include <sstream>
#include <iostream>

#define PROGRAM_START 0x200
#define MEMORY_SIZE   0x1000
#define SCREEN_START  0x0f00

const static unsigned char CHARACTERS[16][5]=     {{0xF0,0x90,0x90,0x90,0xF0},
                                                   {0x20,0x60,0x20,0x20,0x70},
                                                   {0xF0,0x10,0xF0,0x80,0xF0},
                                                   {0xF0,0x10,0xF0,0x10,0xF0},
                                                   {0x90,0x90,0xF0,0x10,0x10},
                                                   {0xF0,0x80,0xF0,0x10,0xF0},
                                                   {0xF0,0x80,0xF0,0x90,0xF0},
                                                   {0xF0,0x10,0x20,0x40,0x40},
                                                   {0xF0,0x90,0xF0,0x90,0xF0},
                                                   {0xF0,0x90,0xF0,0x10,0xF0},
                                                   {0xF0,0x90,0xF0,0x90,0x90},
                                                   {0xE0,0x90,0xE0,0x90,0xE0},
                                                   {0xF0,0x80,0x80,0x80,0xF0},
                                                   {0xE0,0x90,0x90,0x90,0xE0},
                                                   {0xF0,0x80,0xF0,0x80,0xF0},
                                                   {0xF0,0x80,0xF0,0x80,0x80}};

namespace emulator
{

Memory::Memory(std::vector<unsigned char> program, QObject *parent) : QObject(parent),
                                                                      PC(PROGRAM_START),
                                                                      V(16, 0),
                                                                      I(0),
                                                                      delay(0),
                                                                      sound(0),
                                                                      memory(MEMORY_SIZE, 0)
{
    this->loadBuffer(program);
    this->loadCharacters();

    for (int x = 0; x < 64; x++)
    {
        QVector<bool> row(32, false);
        this->screen.push_back(row);
    }

    this->clearScreen();
}

Memory::~Memory()
{

}

void Memory::clearScreen()
{
    for (int x = 0; x < this->screen.size(); ++x)
    {
        for (int y = 0; y < this->screen[x].size(); ++y)
        {
            this->screen[x][y] = false;
        }
    }
    emit screenUpdated();
}

unsigned char* Memory::getFromMemory(unsigned int address, unsigned int size)
{
    unsigned char* data = new unsigned char[size];
    for (int x = 0; x < size && address + size < this->memory.size(); ++x)
    {
       data[x] = this->memory[address + x];
    }
    return data;
}

bool Memory::getPixel(unsigned int xPos, unsigned int yPos) const
{
   if (xPos < this->screen.size() && yPos < this->screen[xPos].size())
   {
        return this->screen[xPos][yPos];
   }
   else
   {
       std::cout << "X: " << xPos << " Y: " << yPos << std::endl;
   }
}


unsigned char Memory::getRegisterVal(unsigned int reg)
{
    unsigned char retVal = this->V[0xF];
    if (reg <= 0xF)
    {
        retVal = this->V[reg];
    }
    return retVal;
}

void Memory::loadBuffer(std::vector<unsigned char> program)
{
    for (int x = 0; x < program.size(); ++x)
    {
        this->memory[x + PROGRAM_START] = program[x];
    }
}

void Memory::loadCharacters()
{
    int storeAddress = 0;
    for (int letter = 0; letter < 16; ++letter)
    {
        for (int letterPart = 0; letterPart < 5; ++letterPart)
        {
            this->memory[storeAddress] = CHARACTERS[letter][letterPart];
            ++storeAddress;
        }
    }
}

void Memory::setDT(unsigned int value)
{
    this->delay = value;
    emit dtChanged(value);
}

void Memory::setI(unsigned int iVal)
{
    this->I = iVal;
    emit iChange(iVal);
}

void Memory::setPC(unsigned int val)
{
    this->PC = val;
    emit pcChange(this->PC);
}

void Memory::setRegisterVal(unsigned int reg, unsigned char data)
{
    if (reg < this->V.size())
    {
        this->V[reg] = data;
        emit registerUpdated(reg, data);
    }
}

void Memory::setPixel(unsigned int xPos, unsigned int yPos, bool value, bool writeCluster)
{
    if (xPos < this->screen.size() && yPos < this->screen[xPos].size())
    {
        this->screen[xPos][yPos] = value;

        if (!writeCluster)
        {
            emit screenUpdated();
        }
    }
}

void Memory::setST(unsigned int val)
{
    this->sound = val;
    emit stChanged(val);
}

bool Memory::pushStack(unsigned int address)
{
    if (this->stack.size() <= 16)
    {
        this->stack.push(address);
        return true;
    }
    return false;
}

bool Memory::writeToMemory(unsigned int address, unsigned char value)
{
    if (address < MEMORY_SIZE)
    {
        this->memory[address] = value;
        return true;
    }
    return false;
}


std::string Memory::toString() const
{
    std::stringstream output;
    output << std::hex << std::setfill('0');
    output << "Begin Core Dump: " << std::endl;
    output << std::endl;
    output << "Registers: " << std:: endl;
    for (int reg = 0; reg < 16; ++reg)
    {
        if (reg > 0 && reg % 4 == 0 ) output << std::endl;
        output << "V" << std::setw(1) << std::hex << reg << " " << std::setw(2) << std::hex << (int)this->V[reg] << " ";
    }
    output << std::endl << std::endl;
    output << "Program Counter:  " << std::setw(3) << std::hex << this->PC << std::endl;
    output << "Address Register: " << std::setw(3) << std::hex << this->I << std::endl;
    output << std::endl;
    output << "Memory Contents: " << std::endl;
    for (int address = 0; address < this->memory.size(); ++address)
    {
        if (address %2  == 0) output << ' ';
        if (address %16 == 0) output << std::endl << std::setw(4) << std::hex << address << " ";
        output << std::setw(2) << std::hex << (int) this->memory[address];
    }
    output << std::endl;
    return output.str();
}

 std::ostream& operator<<(std::ostream& output, const Memory& memory)
 {
     output << memory.toString();
     return output;
 }

}
