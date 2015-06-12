#ifndef DISASSEMBLYWINDOW_H_
#define DISASSEMBLYWINDOW_H_

#include "Disassembler.h"
#include <QWidget>

/**
 *
 */
class DisassemblyWindow: public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructs a window to display the disassembled ROM.
     * @param romFilePath The path to the file to be disassembled
     * @param parent The parent QObject
     */
	DisassemblyWindow(QString romFilePath, QWidget * parent = 0);

	/**
	 * Destructor
	 */
	virtual ~DisassemblyWindow();

signals:

	/**
	 * Emitted when the window is closing.
	 */
	void windowClosing();

protected:

	/**
	 * Window closed
	 */
	void closeEvent (QCloseEvent * event);

private:

	Disassembler disassembler;
};

#endif /* DISASSEMBLYWINDOW_H_ */
