#include <QWidget>
#include <QSharedPointer>
#include <QThread>

#include "ProcessorInspectionWindow.h"
#include "Emulator.h"

/**
 * This class defines the emulation window.
 */
class EmulatorWindow : public QWidget
{
    Q_OBJECT

public:

    /**
     * Builds an emulator window.
     * @param filePath The path to the file to be ran in emulation.
     * @param parent The parent of this window.
     */
    EmulatorWindow(QString filePath, QWidget * parent = 0);

    /**
     * Deconstructor
     */
    ~EmulatorWindow();

public slots:

    /**
     * Launches a processor inspection window
     */
    void launchProcessorInspection();

    /**
     * Refreshes the screen
     */
    void refreshScreen();

signals:

    /**
     * Emitted when the window closes.
     */
    void windowClosing();

protected:

    /**
     *
     * @param event
     */
    void paintEvent( QPaintEvent* event);

    /**
    * Window closed
    */
    void closeEvent (QCloseEvent * event);

private:

    QThread                                     gameThread;
    QSharedPointer<Emulator>                    emulator;
    QSharedPointer<ProcessorInspectionWindow>   processorInspectionWindow;
    int                                         widthInPixels;
    int                                         heightInPixels;
    int                                         pixelWeight;
};
