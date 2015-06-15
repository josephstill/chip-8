#include "Processor.h"
#include <QTime>
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
    qsrand(QTime::currentTime().msec());
    this->continueRunning = !this->stepMode;
    while(this->executeNextCommand());
}

void Processor::setStepMode(bool stepMode)
{
    this->stepMode = stepMode;
    this->continueRunning = !stepMode;
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
    emit startingCommand(command);
    while (!this->continueRunning); //If we are paused, wait to be unpaused
    this->decode(command);
    delete command;
    return true;
}

void Processor::decode(unsigned char* operation)
{
    unsigned int opNibl3 = (unsigned int)(operation[0] >> 4);
    unsigned int opNibl2 = (unsigned int) (operation[0] & 0x0F);
    unsigned int opNibl1 = (unsigned int)(operation[1] >> 4);
    unsigned int opNibl0 = (unsigned int) (operation[1] & 0x0F);

    switch (opNibl3)
    {
    case 0x0:
        switch (operation[1])
        {
        case 0xe0:
            this->memory->clearScreen();
            break;
        case 0xee:
            {
                this->getMemory()->setPC(this->memory->popStack()); //TODO stack issues
                this->memory->setPC(this->memory->getPC() + 2);

            }
            break;
        }
        break;
    case 0x1:
        {
            unsigned int newPcVal = opNibl2<<8 | (unsigned int) operation[1];
            if (newPcVal < 0x1000)
            {
                this->memory->setPC(newPcVal);
            }
            else
            {
                emit segmentationFault();
            }
        }
        break;
    case 0x2:
        {
            unsigned int callAddr = opNibl2<<8 | (unsigned int) operation[1];
            if (callAddr < 0x1000)
            {
                if (this->memory->pushStack(this->memory->getPC()))
                {
                    this->memory->setPC(callAddr);
                }
                else
                {
                   emit stackOverflow();
                }
            }
            else
            {
                emit segmentationFault();
            }
        }
        break;
    case 0x3:
        {
            if (this->memory->getRegisterVal(opNibl2) == (unsigned int) operation[1])
            {
                this->memory->setPC(this->memory->getPC() + 4);
            }
            else
            {
                this->memory->setPC(this->memory->getPC() + 2);
            }
        }
        break;
    case 0x4:
        {
            if (this->memory->getRegisterVal(opNibl2) != (unsigned int) operation[1])
            {
                this->memory->setPC(this->memory->getPC() + 4);
            }
            else
            {
                this->memory->setPC(this->memory->getPC() + 2);
            }
        }
        break;
    case 0x5:
        {
            if (opNibl0 == 0x0)
            {
                if (this->memory->getRegisterVal(opNibl2) == this->memory->getRegisterVal(opNibl1))
                {
                    this->memory->setPC(this->memory->getPC() + 4);
                }
                else
                {
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
                {
                    unsigned int value = this->memory->getRegisterVal(opNibl2) + this->memory->getRegisterVal(opNibl1);
                    this->memory->setRegisterVal(opNibl2, value % 256);
                    if (value > 255)
                    {
                        this->memory->setRegisterVal(0xf, 1);
                    }
                    else
                    {
                        this->memory->setRegisterVal(0xf, 0);
                    }
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                break;
            case 0x5:
                {
                    unsigned int firstVal = this->memory->getRegisterVal(opNibl2);
                    unsigned int secondVal = this->memory->getRegisterVal(opNibl1);
                    unsigned int value = firstVal - secondVal;
                    if (firstVal > secondVal)
                    {
                        this->memory->setRegisterVal(0xf, 1);
                    }
                    else
                    {
                        this->memory->setRegisterVal(0xf, 0);
                    }
                    this->memory->setRegisterVal(opNibl2, value % 256);
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                break;
            case 0x6:
                {
                    unsigned int value = this->memory->getRegisterVal(opNibl2);
                    if (value & 0x1)
                    {
                        this->memory->setRegisterVal(0xf, 1);
                    }
                    else
                    {
                        this->memory->setRegisterVal(0xf, 0);
                    }
                    this->memory->setRegisterVal(opNibl2, value>>1);
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                break;
            case 0x7:
                {
                    unsigned int firstVal = this->memory->getRegisterVal(opNibl1);
                    unsigned int secondVal = this->memory->getRegisterVal(opNibl2);
                    unsigned int value = firstVal - secondVal;
                    if (firstVal > secondVal)
                    {
                        this->memory->setRegisterVal(0xf, 1);
                    }
                    else
                    {
                        this->memory->setRegisterVal(0xf, 0);
                    }
                    this->memory->setRegisterVal(opNibl2, value % 256);
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                break;
            case 0xE:
                {
                    unsigned int value = this->memory->getRegisterVal(opNibl2);
                    if (value & 0x8)
                    {
                        this->memory->setRegisterVal(0xf, 1);
                    }
                    else
                    {
                        this->memory->setRegisterVal(0xf, 0);
                    }
                    this->memory->setRegisterVal(opNibl2, (value<<1) % 256);
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                break;
            }
        }
        break;
    case 0x9:
        if (this->memory->getRegisterVal(opNibl2) != this->memory->getRegisterVal(opNibl1))
        {
            this->memory->setPC(this->memory->getPC() + 4);
        }
        else
        {
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
        {
            unsigned int newPcVal = opNibl2<<8 | (unsigned int) operation[1];
            newPcVal += this->memory->getRegisterVal(0x0);
            this->memory->setPC(newPcVal);
        }
        break;
    case 0xC:
        {
            unsigned int rand = qrand() % 256;
            this->memory->setRegisterVal(opNibl2, rand & (unsigned int) operation[1]);
            this->memory->setPC(this->memory->getPC() + 2);
        }
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
            }
        }
        break;
    case 0xF:
        {
            switch (operation[1])
            {
            case 0x07:
                this->memory->setRegisterVal(opNibl2, this->memory->getDT());
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x0A:
                //TODO Vk = key press
                break;
            case 0x15:
                this->memory->setDT(this->memory->getRegisterVal(opNibl2));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x18:
                this->memory->setST(this->memory->getRegisterVal(opNibl2));
                this->memory->setPC(this->memory->getPC() + 2);
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
                {
                    this->memory->setI(this->memory->getRegisterVal(opNibl2) * 5);
                    this->getMemory()->setPC(this->getMemory()->getPC() + 2);
                }
                break;
            case 0x33:
                {
                    unsigned char val = (unsigned char) this->memory->getRegisterVal(opNibl2);
                    if (!this->memory->writeToMemory(this->memory->getI(), val / 100))
                    {
                        emit segmentationFault();
                    }

                    val %= 100;

                    if (!this->memory->writeToMemory(this->memory->getI(), val + 1 / 10))
                    {
                        emit segmentationFault();
                    }

                    val %= 10;

                    if (!this->memory->writeToMemory(this->memory->getI(), val + 2))
                    {
                        emit segmentationFault();
                    }
                    this->getMemory()->setPC(this->getMemory()->getPC() + 2);

                }
                break;
            case 0x55:
                {
                    for (unsigned int x = 0; x <= opNibl2; ++x)
                    {
                        if (!this->memory->writeToMemory(this->memory->getI() + x, this->memory->getRegisterVal(x)))
                        {
                            emit segmentationFault();
                            break;
                        }
                    }
                    this->getMemory()->setPC(this->getMemory()->getPC() + 2);
                }
                break;
            case 0x65:
                {
                    for (unsigned int x = 0; x <= opNibl2; ++x)
                    {
                        unsigned int addressInMem = this->memory->getI() + x;
                        unsigned char* val = this->memory->getFromMemory(addressInMem, 1);
                        this->memory->setRegisterVal(x, val[0]);
                        delete val;
                    }
                    this->getMemory()->setPC(this->getMemory()->getPC() + 2);
                }
                break;
            }
        }
        break;
    }
}

void Processor::catchSegmentationFault()
{
    emit segmentationFault();
}

void Processor::catchStackOverflow()
{
    emit stackOverflow();
}

}
