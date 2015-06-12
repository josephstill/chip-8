#ifndef CPU_H_
#define CPU_H_

#include <QObject>
#include <QVector>
#include <QStack>
#include <iostream>
#include <vector> //Converting from STL, so this is necessary

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
     */
    Memory(std::vector<unsigned char> program);

    /**
     * Destructor
     */
    ~Memory();

    /**
      * Clears the screen
      */
     void clearScreen();

     /**
      * Returns data from memory. The data is from the given address and
      * the amount of bytes returned is equal to the size. If the address and
      * size reach over memory size bounds, an empty data set is returned
      * @param address The address to pull from.
      * @param size The number of bytes to return
      * @return data from memory
      */
     unsigned char* getFromMemory(unsigned int address, unsigned int size);

     /**
      * Gets the value from the register given.
      * @param reg The register to read.
      * @return The value from the register.
      */
     unsigned char getRegisterVal(unsigned int reg);

     /**
      * Gets the value of the program counter.
      * @return The value of the PC
      */
     unsigned int getPC() const { return this->PC; }

     /**
      * Updates the vale of the program counter and emits a signal.
      * @param val The new value of the program counter
      */
     void setPC(unsigned int val);

     /**
      * Sets the data in the given register to the given value.
      * A signal is emitted to inform of the data change.
      * @param reg The register to change
      * @param data The data to store
      */
     void setRegisterVal(unsigned int reg, unsigned char data);

signals:

    /**
     * Alerts that the screen has been cleared.
     */
    void screenCleared();

    /**
     * alerts that the program counter has changed.
     */
    void pcChange(unsigned int pcVal);

    /**
     * Alerts that a register has changed
     * @param reg The register that has changed
     * @param data The data that has changed
     */
    void registerUpdated(unsigned int reg, unsigned char data);

    //This is for core dumps
    friend std::ostream& operator<<(std::ostream& output, const Memory& memory);

private:
    void loadBuffer(std::vector<unsigned char> program);
    void loadCharacters();

    QVector<unsigned char>                 V;
    unsigned int                           I;
    QStack<unsigned int>                   stack;
    unsigned int                           PC;
    unsigned int                           delay;
    unsigned int                           sound; //TODO best option for this?
    QVector<unsigned char>                 memory;//TODO best option for this?
    QVector<unsigned char>                 screen;
};

}

#endif
