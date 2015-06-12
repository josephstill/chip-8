#include "HexDumpWindow.h"
#include "disassembler/RomParser.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QTextCharFormat>

HexDumpWindow::HexDumpWindow(QString romFilePath, QWidget * parent) : QWidget(parent, Qt::Window)
{
	this->setWindowTitle(tr("Hex Dump"));

	QString dump = QString::fromStdString(disassembler::RomParser::hexDump(romFilePath.toStdString()));
	QPlainTextEdit* editor = new QPlainTextEdit(dump);
	editor->setFont(QFont ("Courier", 11));
	editor->setReadOnly(true);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(editor);

	this->setLayout(layout);
	this->setFixedSize(600, 600);
}

HexDumpWindow::~HexDumpWindow()
{

}

void HexDumpWindow::closeEvent (QCloseEvent * event)
{
	emit windowClosing();
}

