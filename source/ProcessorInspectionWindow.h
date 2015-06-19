#ifndef PROCESSORINSPECTIONWINDOW_H
#define PROCESSORINSPECTIONWINDOW_H

#include <QWidget>
#include <QSharedPointer>
#include "emulator/Processor.h"

namespace Ui
{
    class ProcessorInspectionWindow;
}

/**
 * Creates a window that inspects processor elements.
 */
class ProcessorInspectionWindow : public QWidget
{
    Q_OBJECT

public:

    /**
     * Constructs the window.
     * @param processor The processor to inspect.
     * @param parent The parent of this window.
     */
    explicit ProcessorInspectionWindow(QSharedPointer<emulator::Processor>& processor, QWidget *parent = 0);
    ~ProcessorInspectionWindow();

public slots:

    /**
     * Updates UI elements when a register is updated
     * @param reg The register that is updated
     * @param val The value that it is updated to.
     */
    void registerUpdated(unsigned int reg, unsigned char val);

    /**
     * Displays a core dump in the core dump window.
     */
    void coreDump();

    /**
     * Updates the display of the program counter.
     * @param val The new value of the program counter.
     */
    void pcUpdated(unsigned int val);

    /**
     * Updates the value of I when I is updated.
     * @param val
     */
    void iUpdated(unsigned int val);

    /**
     * Updates the display of the command when it is updated.
     * @param command The new command.
     */
    void commandUpdated(unsigned char* command);
    void dtUpdated(unsigned int val);
    void stUpdated(unsigned int val);
    void play();
    void stop();

private:
    Ui::ProcessorInspectionWindow          *ui;
    QSharedPointer<emulator::Processor>&   processor;
};

#endif // PROCESSORINSPECTIONWINDOW_H
