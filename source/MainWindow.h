#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "DisassemblyWindow.h"
#include "HexDumpWindow.h"
#include "EmulatorWindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QFileDialog>

/**
 * Constructs the main window for the emmulator.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:

    /**
     * Constructs the main window
     */
    MainWindow();

protected:

    void closeEvent(QCloseEvent *event);

private slots:
	void launchEmulator();
	void launchDisassembler();
    void launchHexDump();
	void launchBrowser();
	void disassemblerClosed();
	void hexWindowClosed();
    void emulatorWindowClosed();

private:

    void displayInvalidRomWarning();

    QLineEdit*         filePathEditor;
    QPushButton*       browseButton;
    QPushButton*       emulateButton;
    QPushButton*       disassembleButton;
    QPushButton*       hexDumpButton;

    EmulatorWindow*            emulatorWindow;
    DisassemblyWindow*         disassemblyWindow;
    HexDumpWindow*             hexDumpWindow;
    ProcessorInspectionWindow* ProcessorInspection;
};


#endif /* MAINWINDOW_H_ */
