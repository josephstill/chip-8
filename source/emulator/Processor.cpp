#include "Processor.h"

namespace emulator
{

Processor::Processor(std::vector<unsigned char> data, QObject *parent) : QObject(parent),
                                                                         memory(new Memory(data)),
                                                                         continueRunning(false)
{

}

void Processor::execute()
{
    this->continueRunning = true;
    while(this->continueRunning && this->executeNextCommand());
}

void Processor::resumeExecution()
{

}

void Processor::setStepMode()
{

}

void Processor::clearStepMode()
{

}

bool Processor::executeNextCommand()
{
    unsigned char* command = this->memory->getFromMemory(this->memory->getPC(), 2);
}

void Processor::decode(unsigned char* operation)
{
    unsigned int opNibl3 = (unsigned int)(operation[0] >> 4);
    unsigned int opNibl2 = (unsigned int) (operation[0] & 0x0F);
    unsigned int opNibl1 = (unsigned int)(operation[1] >> 4);
    unsigned int opNibl0 = (unsigned int) (operation[1] & 0x0F);

    //TODO unless otherwise noted automatically , PC += 2

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
            //TODO jump NNN
        }
        break;
    case 0x2:
        {
            //TODO Call sub routine at NNN
        }
        break;
    case 0x3:
        {
            //TODO pc += 4 if VX == NN
        }
        break;
    case 0x4:
        {
            //TODO pc += 4 if *VX != NN
        }
        break;
    case 0x5:
        {
            if (opNibl0 == 0x0)
            {
                //TODO pc += 4 if *VX == *VY
            }
        }
        break;
    case 0x6:
        {
            //TODO *VX = NN
        }
        break;
    case 0x7:
        {
            //TODO *VX+=NN
        }
        break;
    case 0x8:
        {
            switch (opNibl0)
            {
            case 0x0:
                //TODO *Vx = *Vy
                break;
            case 0x1:
                //TODO *Vx = *Vx | *VyretVal = assembleVxVyN(SPRITE, opNibl2, opNibl1, opNibl0);
                break;
            case 0x2:
                //TODO *Vx = *Vx & *Vy
                break;
            case 0x3:
                //TODO *Vx = *Vx ^ *Vy
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
        break;
    case 0xA:
        //TODO I = nnn
        break;
    case 0xB:
        //TODO PC = nnn + *v0S
        break;
    case 0xC:
        //TODO Vx = random byte & nn
        break;
    case 0xD:
        //TODO Sprite
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
                //TODO I = *I + *Vx
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
