#include <QWidget>
#include <QSharedPointer>
#include <QThread>
#include <QMap>
#include <QKeyEvent>
#include <QMutex>

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

    /**
     * Signals that a key was pressed
     */
    void keyPressed(unsigned char);

    /**
     * Signals that a key was released
     */
    void keyReleased(unsigned char);

protected:

    /**
     *
     * @param event
     */
    void paintEvent( QPaintEvent* event);

    /**
    * Window closed
    */
    void closeEvent (QCloseEvent* event);

    /**
     *
     * @param event
     */
    virtual void keyPressEvent(QKeyEvent* event);

    /**
     *
     * @param event
     */
    virtual void keyReleaseEvent(QKeyEvent* event);

private:

    void loadKeyMap();

    QThread                                     gameThread;
    QSharedPointer<Emulator>                    emulator;
    QSharedPointer<ProcessorInspectionWindow>   processorInspectionWindow;
    QMap<Qt::Key, unsigned char>                keyMap;

    int                                         widthInPixels;
    int                                         heightInPixels;
    int                                         pixelWeight;
};
