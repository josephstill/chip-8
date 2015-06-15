#include "ProcessorInspectionWindow.h"
#include "ui_ProcessorInspectionWindow.h"
#include <sstream>
#include <iostream>

ProcessorInspectionWindow::ProcessorInspectionWindow(QSharedPointer<emulator::Processor>& processor, QWidget *parent) : QWidget(parent),
                                                                                                                        ui(new Ui::ProcessorInspectionWindow),
                                                                                                                        processor(processor)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Processor View"));
    int registerNumber = 0;
    for(int x = 0; x < 4; ++x)
    {
        for(int y = 1; y < 8; y+=2)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(QString::number(this->processor->getMemory()->getRegisterVal(registerNumber), 16));
            ui->memoryMap->setItem(x, y, item);
            ++registerNumber;
        }
    }

    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(QString::number(this->processor->getMemory()->getPC(), 16));
        ui->memoryMap->setItem(4, 3, item);
    }

    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(QString::number(this->processor->getMemory()->getI(), 16));
        ui->memoryMap->setItem(4, 1, item);
    }

    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(QString::number(this->processor->getMemory()->getDT(), 16));
        ui->memoryMap->setItem(4, 5, item);
    }

    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(QString::number(this->processor->getMemory()->getST(), 16));
        ui->memoryMap->setItem(4, 7, item);
    }

    QTextDocument* dumpText = new QTextDocument();
    dumpText->setDefaultFont(QFont ("Courier", 9));
    this->ui->coreDump->setDocument(dumpText);

    connect(this->processor->getMemory().data(), SIGNAL(registerUpdated(unsigned int, unsigned char)),
            this,                                SLOT(registerUpdated(unsigned int, unsigned char)));
    connect(this->processor->getMemory().data(), SIGNAL(pcChange(unsigned int)),
            this,                                SLOT(pcUpdated(unsigned int)));
    connect(this->processor->getMemory().data(), SIGNAL(iChange(unsigned int)),
            this,                                SLOT(iUpdated(unsigned int)));
    connect(this->processor->getMemory().data(), SIGNAL(dtChanged(unsigned int)),
            this,                                SLOT(dtUpdated(unsigned int)));
    connect(this->processor->getMemory().data(), SIGNAL(stChanged(unsigned int)),
            this,                                SLOT(stUpdated(unsigned int)));
    connect(this->processor.data(),              SIGNAL(startingCommand(unsigned char*)),
            this,                                SLOT(commandUpdated(unsigned char*)));
    connect(this->ui->dumpButton,                SIGNAL(clicked()),
            this,                                SLOT(coreDump()));
    connect(this->ui->stepButton,                SIGNAL(clicked()),
            this->processor.data(),              SLOT(resumeExecution()));
    connect(this->ui->playButton,                SIGNAL(clicked()),
            this,                                SLOT(play()));
    connect(this->ui->pauseButton,               SIGNAL(clicked()),
            this,                                SLOT(stop()));
}

ProcessorInspectionWindow::~ProcessorInspectionWindow()
{
    delete ui;
}


void ProcessorInspectionWindow::registerUpdated(unsigned int reg, unsigned char val)
{
    int registerNumber = 0;
    for(int x = 0; x < 4; ++x)
    {
        for(int y = 1; y < 8; y+=2)
        {
            ui->memoryMap->item(x, y)->setText(QString::number(this->processor->getMemory()->getRegisterVal(registerNumber), 16));
            ++registerNumber;
        }
    }
}

void ProcessorInspectionWindow::pcUpdated(unsigned int val)
{
    this->ui->memoryMap->item(4, 3)->setText(QString::number(val, 16));
}

void ProcessorInspectionWindow::iUpdated(unsigned int val)
{
   this->ui->memoryMap->item(4, 1)->setText(QString::number(val, 16));
}

void ProcessorInspectionWindow::commandUpdated(unsigned char* command)
{
    unsigned int val = ((unsigned int) command[0])<<8 | (unsigned int) command[1];
    QString valToDisplay = QString::number(val, 16);
    this->ui->commandDisplay->setText(valToDisplay);
}

void ProcessorInspectionWindow::coreDump()
{
    QString dump = QString::fromStdString(this->processor->getMemory()->toString());
    this->ui->coreDump->document()->clear();
    this->ui->coreDump->document()->setPlainText(dump);
}

void ProcessorInspectionWindow::dtUpdated(unsigned int val)
{
   this->ui->memoryMap->item(4, 5)->setText(QString::number(val, 16));
}

void ProcessorInspectionWindow::stUpdated(unsigned int val)
{
    this->ui->memoryMap->item(4, 7)->setText(QString::number(val, 16));
}

void ProcessorInspectionWindow::play()
{
    this->processor->setStepMode(false);
}

void ProcessorInspectionWindow::stop()
{
    this->processor->setStepMode(true);
}
