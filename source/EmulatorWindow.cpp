#include "EmulatorWindow.h"

#include <QPainter>
#include <iostream>


#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32
#define PIXEL_SIZE    10

EmulatorWindow::EmulatorWindow(QString filePath, QWidget * parent): QWidget(parent),
                                                                    emulator(new Emulator(filePath)),
                                                                    processorInspectionWindow(new ProcessorInspectionWindow(this->emulator->getProcessor())),
                                                                    widthInPixels(SCREEN_WIDTH),
                                                                    heightInPixels(SCREEN_HEIGHT),
                                                                    pixelWeight(PIXEL_SIZE)
{
    this->setWindowTitle(tr("Emulator"));
    this->setFixedSize(this->widthInPixels  * this->pixelWeight,
                       this->heightInPixels * this->pixelWeight);

    this->loadKeyMap();

    connect(this->emulator->getProcessor()->getMemory().data(), SIGNAL(screenUpdated()),
            this,                                               SLOT(refreshScreen()));
    connect(&gameThread,                                        SIGNAL(started()),
            this->emulator.data(),                              SLOT(beginEmulation()));
    connect(this,                                               SIGNAL(keyPressed(unsigned char)),
            this->emulator->getProcessor().data(),              SLOT(keyPressed(unsigned char)));
    connect(this,                                               SIGNAL(keyReleased(unsigned char)),
            this->emulator->getProcessor().data(),              SLOT(keyReleased(unsigned char)));

    this->update();
    this->emulator->moveToThread(&gameThread);
    gameThread.start();

    this->launchProcessorInspection();
}


EmulatorWindow::~EmulatorWindow()
{

}

void EmulatorWindow::launchProcessorInspection()
{
    this->processorInspectionWindow->show();
}

void EmulatorWindow::refreshScreen()
{
    this->update();
}

void EmulatorWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRectF fill(0,
                0,
                (this->widthInPixels  * this->pixelWeight) - 1,
                (this->heightInPixels * this->pixelWeight) - 1);
    painter.fillRect(fill, Qt::black);
    for (int x = 0; x < this->widthInPixels; ++x)
    {
        for (int y = 0; y < this->heightInPixels; ++y)
        {
            if (this->emulator->getProcessor()->getMemory()->getPixel(x, y))
            {
                QRectF pix(x * PIXEL_SIZE,
                           y * PIXEL_SIZE,
                           PIXEL_SIZE,
                           PIXEL_SIZE);
                painter.fillRect(pix, Qt::white);
            }
        }
    }
}

void EmulatorWindow::loadKeyMap()
{
    this->keyMap[Qt::Key_1] = 0x1;
    this->keyMap[Qt::Key_2] = 0x2;
    this->keyMap[Qt::Key_3] = 0x3;
    this->keyMap[Qt::Key_4] = 0xc;
    this->keyMap[Qt::Key_Q] = 0x4;
    this->keyMap[Qt::Key_W] = 0x5;
    this->keyMap[Qt::Key_E] = 0x6;
    this->keyMap[Qt::Key_R] = 0xd;
    this->keyMap[Qt::Key_A] = 0x7;
    this->keyMap[Qt::Key_S] = 0x8;
    this->keyMap[Qt::Key_D] = 0x9;
    this->keyMap[Qt::Key_F] = 0xe;
    this->keyMap[Qt::Key_Z] = 0xa;
    this->keyMap[Qt::Key_X] = 0x0;
    this->keyMap[Qt::Key_C] = 0xb;
    this->keyMap[Qt::Key_V] = 0xf;
}

void EmulatorWindow::closeEvent (QCloseEvent * event)
{
    disconnect(this->emulator->getProcessor()->getMemory().data(), SIGNAL(screenUpdated()),
               this,                                               SLOT(refreshScreen()));
    disconnect(&gameThread,                                        SIGNAL(started()),
               this->emulator.data(),                              SLOT(beginEmulation()));
    disconnect(this,                                               SIGNAL(keyPressed(unsigned char)),
               this->emulator->getProcessor().data(),              SLOT(keyPressed(unsigned char)));
    disconnect(this,                                               SIGNAL(keyReleased(unsigned char)),
               this->emulator->getProcessor().data(),              SLOT(keyReleased(unsigned char)));
    this->processorInspectionWindow->close();
    this->emulator->getProcessor()->setStepMode();
    emit windowClosing();
}


void EmulatorWindow::keyPressEvent(QKeyEvent* event)
{
    if (this->keyMap.contains((Qt::Key)event->key()))
    {
        emit keyPressed(this->keyMap[(Qt::Key)event->key()]);
    }
}


void EmulatorWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (this->keyMap.contains((Qt::Key)event->key()))
    {
        emit keyReleased(this->keyMap[(Qt::Key)event->key()]);
    }
}
