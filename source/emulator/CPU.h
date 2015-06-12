#ifndef CPU_H_
#define CPU_H_

#include <vector>
#include <deque>

namespace emulator
{

/**
 * This class provides a model of the CPU.
 */
class CPU
{
    Q_OBJECT

public:

    /**
     * v:      Registers (1 - 16)
     * I:      Address Register
     * stack:  CPU Stack
     * PC:     Program Counter
     * delay:  Delay timer
     * sound:  Sound timer
     * memory: Memory contents
     * screen: Screen state
     */
	struct CPUState
	{
        std::vector<unsigned char>           v;
        unsigned int                         I;
        std::deque<unsigned int>             stack;
        unsigned int                         PC;
        unsigned int                         delay;
        unsigned int                         sound;
        std::map<unsigned char, std::string> memory;
        std::map<unsigned char, std::string> screen;
	};

    /**
     * Constructs the CPU object. The CPU will be loaded with the
     * provided and initialized so that it can run.
     * @param program The program to load into the CPU
     */
    CPU(std::vector<unsigned char> program);

    /**
     * Destructor
     */
    ~CPU();

    /**
     * Returns the CPU state
     * @return A container holding the state of the CPU.
     */
    CPUState& getCPUState() { return this->state; }

private:
    void loadBuffer(std::vector<unsigned char> program);
    void loadCharacters();
    void loadScreen();

    CPUState state;
};

}

#endif
