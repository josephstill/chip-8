#ifndef PROCESSORINSPECTIONWINDOW_H
#define PROCESSORINSPECTIONWINDOW_H

#include <QWidget>
#include <QSharedPointer>
#include "emulator/Processor.h"

namespace Ui
{
    class ProcessorInspectionWindow;
}

class ProcessorInspectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessorInspectionWindow(QSharedPointer<emulator::Processor>& processor, QWidget *parent = 0);
    ~ProcessorInspectionWindow();

public slots:
    void registerUpdated(unsigned int reg, unsigned char val);
    void coreDump();
    void pcUpdated(unsigned int val);
    void iUpdated(unsigned int val);
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
