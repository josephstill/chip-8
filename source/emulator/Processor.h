#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QSharedPointer>
#include <vector>
#include "Memory.h"

namespace emulator
{

/**
 * This class provides a the functionality of a processor.
 */
class Processor : public QObject
{
    Q_OBJECT
public:

    /**
     * Creates a processor and loads the memory with data from the
     * give ROM file.
     * @param fileName The name of the file to load.
     * @param parent The parent of this object.
     */
    Processor(std::vector<unsigned char> data, QObject *parent = 0);

    /**
     * Begins execution of the ROM.
     */
    void execute();

    /**
     * Gets a copy of the memory.
     * @return a pointer to memory
     */
    QSharedPointer<Memory>& getMemory() { return this->memory; }

    /**
     * Enables or disables step mode.
     * @param stepMode True for step mode on.
     */
    void setStepMode(bool stepMode) { this->stepMode = stepMode; }

    /**
     *Stops execution of the ROM.
     */
    void stop() { this->continueRunning = false; }

public slots:

    /**
     * Resumes the execution of the ROM, if it is paused.
     */
    void resumeExecution();

    /**
     * Enables the execution of the rom one command at a time.
     */
    void setStepMode();

    /**
     * Enables the execution of the rom as normal.
     */
    void clearStepMode();

private:

    bool executeNextCommand();
    void decode(unsigned char* operation);

    bool                   continueRunning;
    bool                   stepMode;
    QSharedPointer<Memory> memory;
};

}
#endif // PROCESSOR_H
