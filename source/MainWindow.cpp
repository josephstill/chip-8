#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFile>

#include <iostream>

MainWindow::MainWindow()
{
	this->filePathEditor    = new QLineEdit();
	this->browseButton      = new QPushButton("Browse");
	this->emulateButton     = new QPushButton("Emulate");
	this->disassembleButton = new QPushButton("Disassemble");
	this->hexDumpButton     = new QPushButton("Hex Dump");

	connect(this->browseButton,      SIGNAL(clicked()), this, SLOT(launchBrowser()));
	connect(this->emulateButton,     SIGNAL(clicked()), this, SLOT(launchEmulator()));
	connect(this->disassembleButton, SIGNAL(clicked()), this, SLOT(launchDisassembler()));
	connect(this->hexDumpButton,     SIGNAL(clicked()), this, SLOT(launchHexDump()));

	QFrame* content = new QFrame;
	QHBoxLayout* fileFrameLayout = new QHBoxLayout;
	QLabel* lable = new QLabel("File Name");
	fileFrameLayout->addWidget(lable);
	fileFrameLayout->addWidget(filePathEditor);
	fileFrameLayout->addWidget(browseButton);
	content->setLayout(fileFrameLayout);
	QGroupBox *groupBox = new QGroupBox(tr("Launch View"));
	QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(this->emulateButton);
    vbox->addWidget(this->disassembleButton);
    vbox->addWidget(this->hexDumpButton);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

	QVBoxLayout* mainWindowLayout = new QVBoxLayout;
	mainWindowLayout->addWidget(content);
	mainWindowLayout->addWidget(groupBox);
	this->setLayout(mainWindowLayout);

	this->setFixedSize(600, 200);
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::launchEmulator()
{

}

void MainWindow::launchDisassembler()
{
	QFile rom(this->filePathEditor->text());

	if (rom.exists())
	{
		this->disassemblyWindow = new DisassemblyWindow(this->filePathEditor->text());
		this->disassemblyWindow->show();
		this->disassembleButton->setEnabled(false);

		connect(this->disassemblyWindow, SIGNAL(windowClosing()),
				this, SLOT(disassemblerClosed()));
	}
	else
	{
		//TODO add warning window
	}
}

void MainWindow::launchHexDump()
{
	QFile rom(this->filePathEditor->text());

	if (rom.exists())
	{
		this->hexDumpWindow = new HexDumpWindow(this->filePathEditor->text());
		this->hexDumpWindow->show();
		this->hexDumpButton->setEnabled(false);

		connect(this->hexDumpWindow, SIGNAL(windowClosing()),
				this, SLOT(hexWindowClosed()));
	}
	else
	{
		//TODO add warning window
	}
}

void MainWindow::launchBrowser()
{
	QString path = this->filePathEditor->text().isEmpty() ? "~" : this->filePathEditor->text();
	QString fileName = QFileDialog::getOpenFileName(this,
	                                                tr("Open ROM File"),
	                                                path,
	                                                tr("Chip-8 Files (*.ch8)"));
	if (!fileName.isEmpty())
	{
		this->filePathEditor->setText(fileName);
	}
}


void MainWindow::disassemblerClosed()
{
	this->disassembleButton->setEnabled(true);
	disconnect(this->disassemblyWindow, SIGNAL(windowClosing()),
			   this, SLOT(disassemblerClosed()));
}


void MainWindow::hexWindowClosed()
{
	this->hexDumpButton->setEnabled(true);
	disconnect(this->hexDumpWindow, SIGNAL(windowClosing()),
			   this, SLOT(hexWindowClosed()));
}
