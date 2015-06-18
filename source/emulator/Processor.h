#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include <QMap>
#include <QMutex>
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
    void setStepMode(bool stepMode);

    /**
     *Stops execution of the ROM.
     */
    void stop() { this->continueRunning = false; }

signals:

    /**
     * Alerts that the processor is starting a new command
     * @param command The command
     */
    void startingCommand(unsigned char* command);

    /**
     * Alerts of a segmentation fault
     */
    void segmentationFault();

    /**
     * Alerts of a stack overflow
     */
    void stackOverflow();

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

    /**
     * Lestens for segmentation faults
     */
    void catchSegmentationFault();

    /**
     * Alerts of stack overflows
     */
    void catchStackOverflow();

    /**
     * Decrements the delay timer
     */
    void decrementDt();

    /**
     * Decrements the sound timer.
     */
    void decrementSt();

    /**
     * Used to signal to the processor that a key was pressed
     * @param keyCode
     */
    void keyPressed(unsigned char keyCode);

    /**
     * Used to signal to the processor that a key was released
     * @param keyCode
     */
    void keyReleased(unsigned char keyCode);


private:

    bool executeNextCommand();
    void decode(unsigned char* operation);


    QMap<unsigned char, bool>       keyState;
    QMutex                          keyLock;

    bool                            continueRunning;
    bool                            stepMode;
    QSharedPointer<Memory>          memory;
    QTimer                          delayTimer;
    QTimer                          soundTimer;
};

}
#endif // PROCESSOR_H
