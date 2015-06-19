#include "Processor.h"
#include <QTime>
#include <QMutexLocker>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#define SLEEP_TIME 1000

namespace emulator
{

Processor::Processor(std::vector<unsigned char> data, QObject *parent) : QObject(parent),
                                                                         memory(new Memory(data)),
                                                                         continueRunning(true),
                                                                         stepMode(true),
                                                                         soundTimer(this),
                                                                         delayTimer(this),
                                                                         exit(false)
{
    connect(&soundTimer,     SIGNAL(timeout()),
            this,            SLOT(decrementSt()));
    connect(&delayTimer,     SIGNAL(timeout()),
            this,            SLOT(decrementDt()));

    soundTimer.setSingleShot(false);
    delayTimer.setSingleShot(false);

    soundTimer.start(1000/60);
    delayTimer.start(1000/60);
}


Processor::~Processor()
{
    this->exit = true;
    this->delayTimer.stop();
    this->soundTimer.stop();
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
    usleep(SLEEP_TIME);
    return !this->exit;
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
            this->memory->setPC(this->memory->getPC() + 2);
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
            if (this->memory->getRegisterVal(opNibl2) == operation[1])
            {
                this->memory->setPC(this->memory->getPC() + 2);
            }
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0x4:
        {
            if (this->memory->getRegisterVal(opNibl2) != operation[1])
            {
                this->memory->setPC(this->memory->getPC() + 2);
            }
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0x5:
        {
            if (opNibl0 == 0x0)
            {
                if (this->memory->getRegisterVal(opNibl2) == this->memory->getRegisterVal(opNibl1))
                {
                    this->memory->setPC(this->memory->getPC() + 2);
                }
                this->memory->setPC(this->memory->getPC() + 2);
            }
        }
        break;
    case 0x6:
        {
            this->memory->setRegisterVal(opNibl2, operation[1]);
            this->memory->setPC(this->memory->getPC() + 2);
        }
        break;
    case 0x7:
        {
            unsigned char vx = this->memory->getRegisterVal(opNibl2);
            vx += operation[1];
            this->memory->setRegisterVal(opNibl2, vx % 256);
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
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl2) | this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x2:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl2) & this->memory->getRegisterVal(opNibl1));
                this->memory->setPC(this->memory->getPC() + 2);
                break;
            case 0x3:
                this->memory->setRegisterVal(opNibl2, this->memory->getRegisterVal(opNibl2) ^ this->memory->getRegisterVal(opNibl1));
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
                    unsigned char value = this->memory->getRegisterVal(opNibl2);
                    if (value & 0x80)
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
        {
            if (opNibl0 > 0)
            {
                unsigned char fReg = 0x0;
                unsigned char* sprite = this->memory->getFromMemory(this->memory->getI(), opNibl0);
                unsigned int xVal   = (unsigned int) this->memory->getRegisterVal(opNibl2);
                unsigned int yVal   = (unsigned int) this->memory->getRegisterVal(opNibl1);
                int height = opNibl0;

                for (int row = 0; row < height; ++row)
                {
                    xVal = (unsigned int) this->memory->getRegisterVal(opNibl2);
                    for (int cols = 0; cols < 8; ++cols)
                    {
                        unsigned char bitMask = 0x1<<(7 - cols);
                        bool bitSet = sprite[row] & bitMask;
                        if (bitSet && this->memory->getPixel(xVal, yVal))
                        {
                            this->memory->setPixel(xVal, yVal, false);
                            fReg = 0x1;
                        }
                        else
                        {
                            bool setVal = this->memory->getPixel(xVal, yVal) || bitSet;
                            this->memory->setPixel(xVal, yVal, setVal);

                        }
                        xVal = (xVal + 1) % 64;

                    }
                    yVal = (yVal + 1) % 32;
                }
                delete sprite;
                this->memory->screenWriteComplete();
                this->memory->setRegisterVal(0xF, fReg);
            }
        }
        this->memory->setPC(this->getMemory()->getPC() + 2);
        break;
    case 0xE:
        {
            switch (operation[1])
            {
            case 0x9E:
                {
                    unsigned char keyVal = this->memory->getRegisterVal(opNibl2);
                    if (this->keyState.contains(keyVal) && this->keyState[keyVal])
                    {   
                        this->memory->setPC(this->getMemory()->getPC() + 4);
                    }
                    else
                    {
                        this->memory->setPC(this->getMemory()->getPC() + 2);
                    }
                }
                break;
            case 0xA1:
                {
                    unsigned char keyVal = this->memory->getRegisterVal(opNibl2);
                    if (this->keyState.contains(keyVal) && this->keyState[keyVal])
                    {
                        this->memory->setPC(this->getMemory()->getPC() + 2);
                    }
                    else
                    {
                        this->memory->setPC(this->getMemory()->getPC() + 4);
                    }
                }
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
                {
                    for (int x = 0; x < this->keyState.keys().size(); ++x)
                    {
                        if(this->keyState[this->keyState.keys()[x]])
                        {
                            this->memory->setRegisterVal(opNibl2, this->keyState.keys()[x]);
                            this->memory->setPC(this->memory->getPC() + 2);
                            break;
                        }
                    }
                }
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
                    unsigned char val = this->memory->getRegisterVal(opNibl2);
                    if (!this->memory->writeToMemory(this->memory->getI(), val / 100))
                    {
                        emit segmentationFault();
                    }

                    val %= 100;

                    if (!this->memory->writeToMemory(this->memory->getI() + 1, val / 10))
                    {
                        emit segmentationFault();
                    }

                    val %= 10;

                    if (!this->memory->writeToMemory(this->memory->getI() + 2, val))
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

void Processor::decrementDt()
{
    unsigned int dt = this->memory->getDT();
    if (dt > 0)
    {
        --dt;
        this->memory->setDT(dt);
    }
}

void Processor::decrementSt()
{
    unsigned int st = this->memory->getST();
    if (st > 0)
    {
        --st;
        this->memory->setST(st);
        std::cout << "Beep" <<std::endl;
    }
    std::cout << "No Beep" <<std::endl;
}

void Processor::keyPressed(unsigned char keyCode)
{
    QMutexLocker locker(&keyLock);
    this->keyState[keyCode] = true;
}

void Processor::keyReleased(unsigned char keyCode)
{
    QMutexLocker locker(&keyLock);
    this->keyState[keyCode] = false;
}

}
