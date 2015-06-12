#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QString>

#include "emulator/Memory.h"

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

private:
    emulator::Memory memory;
};

#endif // EMULATOR_H
