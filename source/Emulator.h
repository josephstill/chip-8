#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include "emulator/Processor.h"

/**
 * This class defines the emulator.
 */
class Emulator: public QObject
{
    Q_OBJECT

public:

    /**
     * Constructs an emulator that is loaded with a ROM at the given file path.
     * @param filePath The path to the ROM to load.
     */
    Emulator(QString filePath, bool stepMode = true);

    /**
     * Destructor
     */
    ~Emulator();

    /**
     * Returns the processor object.
     * @return The processor.
     */
    QSharedPointer<emulator::Processor>& getProcessor() { return this->processor; }

public slots:

    /**
     * Begins emulator
     */
    void beginEmulation();

private:
    QSharedPointer<emulator::Processor> processor;
};

#endif // EMULATOR_H
