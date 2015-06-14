#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include "emulator/Processor.h"

class Emulator: public QObject
{
    Q_OBJECT

public:

    /**
     * Constructs an emulator that is loaded with a ROM at the given file path.
     * @param filePath The path to the ROM to load.
     */
    Emulator(QString filePath);

    /**
     * Destructor
     */
    ~Emulator();

    QSharedPointer<emulator::Processor>& getProcessor() { return this->processor; }

private:
    QSharedPointer<emulator::Processor> processor;
};

#endif // EMULATOR_H
