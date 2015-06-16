#include "EmulatorWindow.h"

#include <QPainter>

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32
#define PIXEL_SIZE    10

EmulatorWindow::EmulatorWindow(QString filePath, QWidget * parent): QWidget(parent),
                                                                    emulator(new Emulator(filePath, false)),
                                                                    widthInPixels(SCREEN_WIDTH),
                                                                    heightInPixels(SCREEN_HEIGHT),
                                                                    pixelWeight(PIXEL_SIZE)
{
    this->setWindowTitle(tr("Emulator"));
    this->setFixedSize(this->widthInPixels  * this->pixelWeight,
                       this->heightInPixels * this->pixelWeight);

    connect(this->emulator->getProcessor()->getMemory().data(), SIGNAL(screenUpdated()),
            this,                                               SLOT(refreshScreen()));
    connect(&gameThread,                                        SIGNAL(started()),
            this->emulator.data(),                              SLOT(beginEmulation()));

    this->update();
    this->emulator->moveToThread(&gameThread);
    gameThread.start();
}


EmulatorWindow::~EmulatorWindow()
{

}

void EmulatorWindow::launchProcessorInspection()
{

}

void EmulatorWindow::refreshScreen()
{
    this->update();
}

void EmulatorWindow::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
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

void EmulatorWindow::closeEvent (QCloseEvent * event)
{
    emit windowClosing();
}
