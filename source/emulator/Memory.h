#ifndef CPU_H_
#define CPU_H_

#include <QObject>
#include <QVector>
#include <QStack>
#include <iostream>
#include <vector> //Converting from STL, so this is necessary
#include <string>

namespace emulator
{

/**
 * This class provides a model of the CPU.
 */
class Memory :public QObject
{
    Q_OBJECT

public:

    /**
     * Constructs the CPU object. The CPU will be loaded with the
     * provided and initialized so that it can run.
     * @param program The program to load into the CPU
     * @param parent The parent of this object
     */
    Memory(std::vector<unsigned char> program, QObject *parent = 0);

    /**
     * Destructor
     */
    ~Memory();

    /**
      * Clears the screen
      */
     void clearScreen();

     /**
      * Rturns the value of the delay timer.
      * @return The contents of the delay timer.
      */
     unsigned int getDT() { return this->delay; }

     /**
      * Returns data from memory. The data is from the given address and
      * the amount of bytes returned is equal to the size. If the address and
      * size reach over memory size bounds, an empty data set is returned
      * @param address The address to pull from.
      * @param size The number of bytes to return
      * @return data from memory
      */
     unsigned char* getFromMemory(unsigned int addmemoryress, unsigned int size);

     /**
      * Returns the value of the address register
      * @return the value of I
      */
     unsigned int getI() { return this->I; }

     /**
      * Gets the value from the register given.
      * @param reg The register to read.
      * @return The value from the register.
      */
     unsigned char getRegisterVal(unsigned int reg);

     /**
      * Returns the vale of the sound timer
      * @return The value of the sound timer.
      */
     unsigned int getST() { return this->sound; }

     /**
      * Gets the value of the program counter.
      * @return The value of the PC
      */
     unsigned int getPC() const { return this->PC; }

     /**
      * Gets the state of a pixel out of memory
      * @param xVal The x position
      * @param yVal the y position
      * @return True if the pixel is lit
      */
     bool getPixel(unsigned int xPos, unsigned int yPos) const;

     /**
      * Sets the delay timer to the given value
      * @param value The value to set the delay timer to.
      */
     void setDT(unsigned int value);

     /**
      * Sets the address stored in I.
      * @param iVal
      */
     void setI(unsigned int iVal);

     /**
      * Updates the vale of the program counter and emits a signal.
      * @param val The new value of the program counter
      */
     void setPC(unsigned int val);

     /**
      * Sets the given pixel to a provided value
      * @param xPos X position of the pixel
      * @param yPos Y position of the pixel
      * @param value The value to set to.
      */
     void setPixel(unsigned int xPos, unsigned int yPos, bool value, bool writeCluster = false);

     /**
      * Sets the sound time to the given value.
      * @param val The value to set the sound timer to.
      */
     void setST(unsigned int val);

     /**
      * Sets the data in the given register to the given value.
      * A signal is emitted to inform of the data change.
      * @param reg The register to change
      * @param data The data to store
      */
     void setRegisterVal(unsigned int reg, unsigned char data);

     /**
      *Creates a string representation of this object;
      * @return a string represenataion of this object.
      */
     std::string toString() const;

     /**
      * Pops an address off of the stack
      * @return An address from the stack.
      */
     unsigned int popStack() { return this->stack.pop(); }

     /**
      * Pushes an address onto the stack. Returns false if the stack is too large
      * @param address The address to push
      * @return False if the stack is too large
      */
     bool pushStack(unsigned int address);

     /**
      * Writes the given value to memory in the given place.
      * @param address The address to write.
      * @param value The value to write.
      * @return True if the write was successful;
      */
     bool writeToMemory(unsigned int address, unsigned char value);

     //This is for core dumps
     friend std::ostream& operator<<(std::ostream& output, const Memory& memory);

signals:

    /**
     * Alerts that the screen has been updated.
     */
    void screenUpdated();

    /**
     * Alerts that the delay timer has changed
     * @param value The new value
     */
    void dtChanged(unsigned int value);

    /**
     * alerts that the program counter has changed.
     */
    void pcChange(unsigned int pcVal);

    /**
     * alerts that the program counter has changed.
     */
    void iChange(unsigned int iVal);

    /**
     * Alerts that a register has changed
     * @param reg The register that has changed
     * @param data The data that has changed
     */
    void registerUpdated(unsigned int reg, unsigned char data);

    /**
     * Alerts that the sound timer has changed
     * @param value The new value
     */
    void stChanged(unsigned int value);

private:
    void loadBuffer(std::vector<unsigned char> program);
    void loadCharacters();

    QVector<unsigned char>                 V;
    unsigned int                           I;
    QStack<unsigned int>                   stack;
    unsigned int                           PC;
    unsigned int                           delay;
    unsigned int                           sound;
    QVector<unsigned char>                 memory;
    QVector< QVector<bool> >               screen;
};

}

#endif
