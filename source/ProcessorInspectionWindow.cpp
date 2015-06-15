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

    QTextDocument* dumpText = new QTextDocument();
    dumpText->setDefaultFont(QFont ("Courier", 9));
    this->ui->coreDump->setDocument(dumpText);

    connect(this->processor->getMemory().data(), SIGNAL(registerUpdated(unsigned int, unsigned char)),
            this,                                SLOT(registerUpdated(unsigned int, unsigned char)));
    connect(this->ui->dumpButton,                SIGNAL(clicked()),
            this,                                SLOT(coreDump()));

}

ProcessorInspectionWindow::~ProcessorInspectionWindow()
{
    delete ui;
}


void ProcessorInspectionWindow::registerUpdated(unsigned int reg, unsigned char val)
{
    int regX = (reg % 4);
    int regY = (reg / 4) + 1;
    this->ui->memoryMap->item(regX, regY)->setText(QString::number(val, 16));
}

void ProcessorInspectionWindow::coreDump()
{
    QString dump = QString::fromStdString(this->processor->getMemory()->toString());
    this->ui->coreDump->document()->clear();
    this->ui->coreDump->document()->setPlainText(dump);
}
