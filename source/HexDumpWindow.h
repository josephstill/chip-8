#ifndef HEXDUMPWINDOW_H_
#define HEXDUMPWINDOW_H_

#include <QWidget>
#include <QString>

/**
 *
 */
class HexDumpWindow: public QWidget
{
    Q_OBJECT

public:

	/**
     * Constructs a window to display the hex dump of a ROM.
     * @param romFilePath The path to the file to be dumped
     * @param parent The parent QObject
	 */
	HexDumpWindow(QString romFilePath, QWidget * parent = 0);

	/**
	 * Deconstructor
	 */
	virtual ~HexDumpWindow();

signals:
	/**
	 * Emitted when the window closes.
	 */
	void windowClosing();

protected:

	/**
	* Window closed
	*/
	void closeEvent (QCloseEvent * event);
};

#endif /* HEXDUMPWINDOW_H_ */
