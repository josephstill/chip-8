#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "DisassemblyWindow.h"
#include "HexDumpWindow.h"
#include "ProcessorInspectionWindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QFileDialog>
#include <QThread>
#include "Emulator.h"
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

private:

    QThread*           gameThread;

    QLineEdit*         filePathEditor;
    QPushButton*       browseButton;
    QPushButton*       emulateButton;
    QPushButton*       disassembleButton;
    QPushButton*       hexDumpButton;

    Emulator*                  e;
    DisassemblyWindow*         disassemblyWindow; //TODO this should be a shared pointer
    HexDumpWindow*             hexDumpWindow;
    ProcessorInspectionWindow* ProcessorInspection;
};


#endif /* MAINWINDOW_H_ */
