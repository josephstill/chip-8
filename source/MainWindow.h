#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QFileDialog>

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

private:

    QLineEdit*    filePathEditor;
    QPushButton*  browseButton;
    QPushButton*  emulateButton;
    QPushButton*  disassembleButton;
    QPushButton*  hexDumpButton;
};


#endif /* MAINWINDOW_H_ */
