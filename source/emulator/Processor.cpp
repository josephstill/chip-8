#include "Processor.h"
#include <iostream> //TODO remove me
#include <iomanip> //TODO remove me

namespace emulator
{

Processor::Processor(std::vector<unsigned char> data, QObject *parent) : QObject(parent),
                                                                         memory(new Memory(data)),
                                                                         continueRunning(true),
                                                                         stepMode(true)
{

}

void Processor::execute()
{
    this->continueRunning = !this->stepMode;
    while(this->executeNextCommand());
}

void Processor::resumeExecution()
{
    this->continueRunning = true;
}

void Processor::setStepMode()
{
    this->setStepMode(true);
}

void Processor::clearStepMode()
{
    this->setStepMode(false);
}

bool Processor::executeNextCommand()
{
    this->continueRunning = false | !this->stepMode;
    unsigned char* command = this->memory->getFromMemory(this->memory->getPC(), 2);
    this->decode(command);
    return true;
}

void Processor::decode(unsigned char* operation)
{
    std::cout << "Processing a command ";
    unsigned int opNibl3 = (unsigned int)(operation[0] >> 4);
    unsigned int opNibl2 = (unsigned int) (operation[0] & 0x0F);
    unsigned int opNibl1 = (unsigned int)(operation[1] >> 4);
    unsigned int opNibl0 = (unsigned int) (operation[1] & 0x0F);
    std::cout << std::setw(1) << std::hex << opNibl3;
    std::cout << std::setw(1) << std::hex << opNibl2;
    std::cout << std::setw(1) << std::hex << opNibl1;
    std::cout << std::setw(1) << std::hex << opNibl0 << std::endl;

    while (!this->continueRunning);

    //TODO unless otherwise noted automatically , PC += 2const

    switch (opNibl3)
    {
    case 0x0:
        switch (operation[1])
        {
        case 0xe0:
            this->memory->clearScreen();
            break;
        case 0xee:
            //TODO return
            break;
        default:
            //TODO no opp code
            break;
        }
        break;
    case 0x1:
        {
            unsigned int newPcVal = opNibl2<<8 | (unsigned int) operation[1];
            this->memory->setPC(newPcVal);
        }
        break;
    case 0x2:
        {
            //TODO Call sub routine at NNN
        }
        break;
    case 0x3:
        {
            std::cout << std::hex << (unsigned int) this->memory->getRegisterVal(opNibl2) << " = ";
            std::cout << std::hex << (unsigned int) operation[1] << " ?";
            if (this->memory->getRegisterVal(opNibl2) == (unsigned int) operation[1])
            {
                std::cout << " yes" << std::endl;
                this->memory->setPC(this->memory->getPC() + 4);
            }
            else
            {
                std::cout << " no" << std::endl;
                this->memory->setPC(this->memory->getPC() + 2);
            }
        }
        break;
    case 0x4:
        {
            std::cout << std::hex << this->memory->getRegisterVal(opNibl2) << " != ";
            std::cout << std::hex << (unsigned int) operation[1] << " ?";
            if (this->memory->getRegisterVal(opNibl2) != (unsigned int) operation[1])
            {
                std::cout << " yes" << std::endl;
                this->memory->setPC(this->memory->getPC() + 4);
            }
            else
            {
                std::cout << " no" << std::endl;
                this->memory->setPC(this->memory->getPC() + 2);
            }
        }
        break;
    case 0x5:
        {
            if (opNibl0 == 0x0)
            {
                std::cout << std::hex << this->memory->getRegisterVal(opNibl2) << " == ";
                std::cout << std::hex << this->memory->getRegisterVal(opNibl1) << " ?";
                if (this->memory->getRegisterVal(opNibl2) == this->memory->getRegisterVal(opNibl1))
                {
                    std::cout << " yes" << std::endl;
                    this->memory->setPC(this->memory->getPC() + 4);
                }
                else
                {
                    std::cout << " no" << std::endl;
                    this->memory->setPC(this->memory->getPC() + 2);
                }
            }
        }
        break;
    case 0x6:
        {
            this->memory->setRegisterVal(opNibl2, (unsigned int) operation[1]);
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0x7:
        {
            unsigned int vx = this->memory->getRegisterVal(opNibl2);
            vx += (unsigned int) operation[1];
            this->memory->setRegisterVal(opNibl2, vx);
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0x8:
        {
            switch (opNibl0)
            {
            case 0x0:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x1:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl1) | this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x2:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl1) & this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x3:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl1) ^ this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x4:
                //TODO *Vx = *Vx + *Vy
                //TODO *VF = carry
                break;
            case 0x5:
                //TODO *Vx = *Vx - *Vy
                //TODO *VF = borrow
                break;
            case 0x6:
                //TODO *Vx = *vx >> 2 (SHR)
                //Vf = least sig bit
                break;
            case 0x7:
                //TODO *Vx = *Vy - *Vx
                //TODO *VF = Vy > Vx
                break;
            case 0xE:
                //TODO *Vx = Vx << 2 (SHL)
                //TODO *VF = most sig bit
                break;
            default:
                //TODO no op code
                break;
            }
        }
        break;
    case 0x9:
        //TODO skip if *Vx != *Vy
        std::cout << std::hex << this->memory->getRegisterVal(opNibl2) << " != ";
        std::cout << std::hex << this->memory->getRegisterVal(opNibl1) << " ?";
        if (this->memory->getRegisterVal(opNibl2) != this->memory->getRegisterVal(opNibl1))
        {
            std::cout << " yes" << std::endl;
            this->memory->setPC(this->memory->getPC() + 4);
        }
        else
        {
            std::cout << " no" << std::endl;
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0xA:
        {
            unsigned int newIVal = opNibl2<<8 | (unsigned int) operation[1];
            this->memory->setI(newIVal);
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0xB:
        //TODO PC = nnn + *v0S
        break;
    case 0xC:
        //TODO Vx = random byte & nn
        break;
    case 0xD:
        //TODO Sprite stuff
        this->memory->setPC(this->getMemory()->getPC() + 2);
        break;
    case 0xE:
        {
            switch (operation[1])
            {
            case 0x9E:
                //TODO PC += 4 if Key with val of Vx is pressed
                break;
            case 0xA1:
               //TODO PC += 4 if Key with val of Vx not is pressed
                break;
            default:
                //TODO bad op code
                break;
            }
        }
        break;
    case 0xF:
        {
            switch (operation[1])
            {
            case 0x07:
                //TODO Vx = *dt
                break;
            case 0x0A:
                //TODO Vk = key press
                break;
            case 0x15:
                //TODO DT = Vx
                break;
            case 0x18:
                //TODO ST = Vx
                break;
            case 0x1E:
                {
                    unsigned int i = this->memory->getI();
                    i += this->getMemory()->getRegisterVal(opNibl2);
                    this->memory->setI(i);
                    this->getMemory()->setPC(this->getMemory()->getPC() + 2);
                }
                break;
            case 0x29:
                //TODO I = *VX //Verify
                break;
            case 0x33:
                //TODO Store BCD representation of Vx in memory locations I, I+1, and I+2.
                break;
            case 0x55:
                //TODO Store registers V0 through Vx in memory starting at location I.
                break;
            case 0x65:
                //TODO Read registers V0 through Vx from memory starting at location I.
                break;
            default:
                //TODO bad opp code
                break;
            }
        }
        break;
    default:
        //TODO bad opp code
        break;
    }
}

}
