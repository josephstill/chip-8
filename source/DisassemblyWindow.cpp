#include "DisassemblyWindow.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QTextCharFormat>

DisassemblyWindow::DisassemblyWindow(QString romFilePath, QWidget * parent) : QWidget(parent, Qt::Window),
                                                                              disassembler(romFilePath.toStdString())
{
	this->setWindowTitle(tr("Disassembler"));

	QString disassembly = QString::fromStdString(this->disassembler.getText());
	QPlainTextEdit* editor = new QPlainTextEdit(disassembly);
	editor->setFont(QFont ("Courier", 11));
	editor->setReadOnly(true);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(editor);

	this->setLayout(layout);
	this->setFixedSize(400, 600);
}

DisassemblyWindow::~DisassemblyWindow()
{

}

void DisassemblyWindow::closeEvent (QCloseEvent * event)
{
	emit windowClosing();
}
