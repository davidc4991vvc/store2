// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
<<<<<<< HEAD
#define NO_MEM_TRACKING
=======
#include "emu.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QFileDialog>
#include <QtGui/QCloseEvent>
>>>>>>> upstream/master

#include "mainwindow.h"

#include "debug/debugcon.h"
#include "debug/debugcpu.h"
#include "debug/dvdisasm.h"


MainWindow::MainWindow(running_machine* machine, QWidget* parent) :
<<<<<<< HEAD
	WindowQt(machine, NULL),
=======
	WindowQt(machine, nullptr),
>>>>>>> upstream/master
	m_historyIndex(0),
	m_inputHistory()
{
	setGeometry(300, 300, 1000, 600);

	//
	// The main frame and its input and log widgets
	//
	QFrame* mainWindowFrame = new QFrame(this);

	// The input line
	m_inputEdit = new QLineEdit(mainWindowFrame);
<<<<<<< HEAD
	connect(m_inputEdit, SIGNAL(returnPressed()), this, SLOT(executeCommand()));
=======
	connect(m_inputEdit, &QLineEdit::returnPressed, this, &MainWindow::executeCommandSlot);
>>>>>>> upstream/master
	m_inputEdit->installEventFilter(this);


	// The log view
	m_consoleView = new DebuggerView(DVT_CONSOLE,
										m_machine,
										mainWindowFrame);
	m_consoleView->setFocusPolicy(Qt::NoFocus);
	m_consoleView->setPreferBottom(true);

	QVBoxLayout* vLayout = new QVBoxLayout(mainWindowFrame);
	vLayout->addWidget(m_consoleView);
	vLayout->addWidget(m_inputEdit);
	vLayout->setSpacing(3);
	vLayout->setContentsMargins(4,0,4,2);

	setCentralWidget(mainWindowFrame);

	//
	// Options Menu
	//
	// Create three commands
	m_breakpointToggleAct = new QAction("Toggle Breakpoint at Cursor", this);
	m_breakpointEnableAct = new QAction("Disable Breakpoint at Cursor", this);
	m_runToCursorAct = new QAction("Run to Cursor", this);
	m_breakpointToggleAct->setShortcut(Qt::Key_F9);
	m_breakpointEnableAct->setShortcut(Qt::SHIFT + Qt::Key_F9);
	m_runToCursorAct->setShortcut(Qt::Key_F4);
<<<<<<< HEAD
	connect(m_breakpointToggleAct, SIGNAL(triggered(bool)), this, SLOT(toggleBreakpointAtCursor(bool)));
	connect(m_breakpointEnableAct, SIGNAL(triggered(bool)), this, SLOT(enableBreakpointAtCursor(bool)));
	connect(m_runToCursorAct, SIGNAL(triggered(bool)), this, SLOT(runToCursor(bool)));
=======
	connect(m_breakpointToggleAct, &QAction::triggered, this, &MainWindow::toggleBreakpointAtCursor);
	connect(m_breakpointEnableAct, &QAction::triggered, this, &MainWindow::enableBreakpointAtCursor);
	connect(m_runToCursorAct, &QAction::triggered, this, &MainWindow::runToCursor);
>>>>>>> upstream/master

	// Right bar options
	QActionGroup* rightBarGroup = new QActionGroup(this);
	rightBarGroup->setObjectName("rightbargroup");
	QAction* rightActRaw = new QAction("Raw Opcodes", this);
	QAction* rightActEncrypted = new QAction("Encrypted Opcodes", this);
	QAction* rightActComments = new QAction("Comments", this);
	rightActRaw->setCheckable(true);
	rightActEncrypted->setCheckable(true);
	rightActComments->setCheckable(true);
	rightActRaw->setActionGroup(rightBarGroup);
	rightActEncrypted->setActionGroup(rightBarGroup);
	rightActComments->setActionGroup(rightBarGroup);
	rightActRaw->setShortcut(QKeySequence("Ctrl+R"));
	rightActEncrypted->setShortcut(QKeySequence("Ctrl+E"));
<<<<<<< HEAD
	rightActComments->setShortcut(QKeySequence("Ctrl+C"));
	rightActRaw->setChecked(true);
	connect(rightBarGroup, SIGNAL(triggered(QAction*)), this, SLOT(rightBarChanged(QAction*)));
=======
	rightActComments->setShortcut(QKeySequence("Ctrl+N"));
	rightActRaw->setChecked(true);
	connect(rightBarGroup, &QActionGroup::triggered, this, &MainWindow::rightBarChanged);
>>>>>>> upstream/master

	// Assemble the options menu
	QMenu* optionsMenu = menuBar()->addMenu("&Options");
	optionsMenu->addAction(m_breakpointToggleAct);
	optionsMenu->addAction(m_breakpointEnableAct);
	optionsMenu->addAction(m_runToCursorAct);
	optionsMenu->addSeparator();
	optionsMenu->addActions(rightBarGroup->actions());

	//
	// Images menu
	//
	image_interface_iterator imageIterTest(m_machine->root_device());
<<<<<<< HEAD
	if (imageIterTest.first() != NULL)
=======
	if (imageIterTest.first() != nullptr)
>>>>>>> upstream/master
	{
		createImagesMenu();
	}

	//
	// Dock window menu
	//
	QMenu* dockMenu = menuBar()->addMenu("Doc&ks");

	setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

	// The processor dock
	QDockWidget* cpuDock = new QDockWidget("processor", this);
	cpuDock->setObjectName("cpudock");
	cpuDock->setAllowedAreas(Qt::LeftDockWidgetArea);
	m_procFrame = new ProcessorDockWidget(m_machine, cpuDock);
	cpuDock->setWidget(dynamic_cast<QWidget*>(m_procFrame));

	addDockWidget(Qt::LeftDockWidgetArea, cpuDock);
	dockMenu->addAction(cpuDock->toggleViewAction());

	// The disassembly dock
	QDockWidget* dasmDock = new QDockWidget("dasm", this);
	dasmDock->setObjectName("dasmdock");
	dasmDock->setAllowedAreas(Qt::TopDockWidgetArea);
	m_dasmFrame = new DasmDockWidget(m_machine, dasmDock);
	dasmDock->setWidget(m_dasmFrame);
<<<<<<< HEAD
	connect(m_dasmFrame->view(), SIGNAL(updated()), this, SLOT(dasmViewUpdated()));
=======
	connect(m_dasmFrame->view(), &DebuggerView::updated, this, &MainWindow::dasmViewUpdated);
>>>>>>> upstream/master

	addDockWidget(Qt::TopDockWidgetArea, dasmDock);
	dockMenu->addAction(dasmDock->toggleViewAction());
}


MainWindow::~MainWindow()
{
}


void MainWindow::setProcessor(device_t* processor)
{
	// Cpu swap
	m_procFrame->view()->view()->set_source(*m_procFrame->view()->view()->source_for_device(processor));
	m_dasmFrame->view()->view()->set_source(*m_dasmFrame->view()->view()->source_for_device(processor));

	// Scrollbar refresh - seems I should be able to do in the DebuggerView
	m_dasmFrame->view()->verticalScrollBar()->setValue(m_dasmFrame->view()->view()->visible_position().y);
	m_dasmFrame->view()->verticalScrollBar()->setValue(m_dasmFrame->view()->view()->visible_position().y);

	// Window title
<<<<<<< HEAD
	std::string title;
	strprintf(title,"Debug: %s - %s '%s'", m_machine->system().name, processor->name(), processor->tag());
	setWindowTitle(title.c_str());
=======
	string_format("Debug: %s - %s '%s'", m_machine->system().name, processor->name(), processor->tag());
	setWindowTitle(string_format("Debug: %s - %s '%s'", m_machine->system().name, processor->name(), processor->tag()).c_str());
>>>>>>> upstream/master
}


// Used to intercept the user clicking 'X' in the upper corner
void MainWindow::closeEvent(QCloseEvent* event)
{
	debugActQuit();

	// Insure the window doesn't disappear before we get a chance to save its parameters
	event->ignore();
}


// Used to intercept the user hitting the up arrow in the input widget
bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	// Only filter keypresses
<<<<<<< HEAD
	QKeyEvent* keyEvent = NULL;
=======
	QKeyEvent* keyEvent = nullptr;
>>>>>>> upstream/master
	if (event->type() == QEvent::KeyPress)
	{
		keyEvent = static_cast<QKeyEvent*>(event);
	}
	else
	{
		return QObject::eventFilter(obj, event);
	}

	// Catch up & down keys
	if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
	{
		if (keyEvent->key() == Qt::Key_Up)
		{
			if (m_historyIndex > 0)
				m_historyIndex--;
		}
		else if (keyEvent->key() == Qt::Key_Down)
		{
			if (m_historyIndex < m_inputHistory.size())
				m_historyIndex++;
		}

		// Populate the input edit or clear it if you're at the end
		if (m_historyIndex == m_inputHistory.size())
		{
			m_inputEdit->setText("");
		}
		else
		{
			m_inputEdit->setText(m_inputHistory[m_historyIndex]);
		}
	}
	else if (keyEvent->key() == Qt::Key_Enter)
	{
		executeCommand(false);
	}
	else
	{
		return QObject::eventFilter(obj, event);
	}

	return true;
}


void MainWindow::toggleBreakpointAtCursor(bool changedTo)
{
	debug_view_disasm *const dasmView = downcast<debug_view_disasm*>(m_dasmFrame->view()->view());
<<<<<<< HEAD
	if (dasmView->cursor_visible() && (debug_cpu_get_visible_cpu(*m_machine) == dasmView->source()->device()))
=======
	if (dasmView->cursor_visible() && (m_machine->debugger().cpu().get_visible_cpu() == dasmView->source()->device()))
>>>>>>> upstream/master
	{
		offs_t const address = downcast<debug_view_disasm *>(dasmView)->selected_address();
		device_debug *const cpuinfo = dasmView->source()->device()->debug();

		// Find an existing breakpoint at this address
<<<<<<< HEAD
		INT32 bpindex = -1;
		for (device_debug::breakpoint* bp = cpuinfo->breakpoint_first();
				bp != NULL;
=======
		int32_t bpindex = -1;
		for (device_debug::breakpoint* bp = cpuinfo->breakpoint_first();
				bp != nullptr;
>>>>>>> upstream/master
				bp = bp->next())
		{
			if (address == bp->address())
			{
				bpindex = bp->index();
				break;
			}
		}

		// If none exists, add a new one
		std::string command;
		if (bpindex == -1)
		{
<<<<<<< HEAD
			strprintf(command,"bpset 0x%X", address);
		}
		else
		{
			strprintf(command,"bpclear 0x%X", bpindex);
		}
		debug_console_execute_command(*m_machine, command.c_str(), 1);
=======
			command = string_format("bpset 0x%X", address);
		}
		else
		{
			command = string_format("bpclear 0x%X", bpindex);
		}
		m_machine->debugger().console().execute_command(command.c_str(), true);
>>>>>>> upstream/master
	}

	refreshAll();
}


void MainWindow::enableBreakpointAtCursor(bool changedTo)
{
	debug_view_disasm *const dasmView = downcast<debug_view_disasm*>(m_dasmFrame->view()->view());
<<<<<<< HEAD
	if (dasmView->cursor_visible() && (debug_cpu_get_visible_cpu(*m_machine) == dasmView->source()->device()))
=======
	if (dasmView->cursor_visible() && (m_machine->debugger().cpu().get_visible_cpu() == dasmView->source()->device()))
>>>>>>> upstream/master
	{
		offs_t const address = dasmView->selected_address();
		device_debug *const cpuinfo = dasmView->source()->device()->debug();

		// Find an existing breakpoint at this address
		device_debug::breakpoint* bp = cpuinfo->breakpoint_first();
<<<<<<< HEAD
		while ((bp != NULL) && (bp->address() != address))
			bp = bp->next();

		if (bp != NULL)
		{
			INT32 const bpindex = bp->index();
			std::string command;
			strprintf(command,bp->enabled() ? "bpdisable 0x%X" : "bpenable 0x%X", bpindex);
			debug_console_execute_command(*m_machine, command.c_str(), 1);
=======
		while ((bp != nullptr) && (bp->address() != address))
			bp = bp->next();

		if (bp != nullptr)
		{
			int32_t const bpindex = bp->index();
			std::string command = string_format(bp->enabled() ? "bpdisable 0x%X" : "bpenable 0x%X", bpindex);
			m_machine->debugger().console().execute_command(command.c_str(), true);
>>>>>>> upstream/master
		}
	}

	refreshAll();
}


void MainWindow::runToCursor(bool changedTo)
{
	debug_view_disasm* dasmView = downcast<debug_view_disasm*>(m_dasmFrame->view()->view());
<<<<<<< HEAD
	if (dasmView->cursor_visible() && (debug_cpu_get_visible_cpu(*m_machine) == dasmView->source()->device()))
	{
		offs_t address = downcast<debug_view_disasm*>(dasmView)->selected_address();
		std::string command;
		strprintf(command,"go 0x%X", address);
		debug_console_execute_command(*m_machine, command.c_str(), 1);
=======
	if (dasmView->cursor_visible() && (m_machine->debugger().cpu().get_visible_cpu() == dasmView->source()->device()))
	{
		offs_t address = downcast<debug_view_disasm*>(dasmView)->selected_address();
		std::string command = string_format("go 0x%X", address);
		m_machine->debugger().console().execute_command(command.c_str(), true);
>>>>>>> upstream/master
	}
}


void MainWindow::rightBarChanged(QAction* changedTo)
{
	debug_view_disasm* dasmView = downcast<debug_view_disasm*>(m_dasmFrame->view()->view());
	if (changedTo->text() == "Raw Opcodes")
	{
		dasmView->set_right_column(DASM_RIGHTCOL_RAW);
	}
	else if (changedTo->text() == "Encrypted Opcodes")
	{
		dasmView->set_right_column(DASM_RIGHTCOL_ENCRYPTED);
	}
	else if (changedTo->text() == "Comments")
	{
		dasmView->set_right_column(DASM_RIGHTCOL_COMMENTS);
	}
	m_dasmFrame->view()->viewport()->update();
}

<<<<<<< HEAD
=======
void MainWindow::executeCommandSlot()
{
	executeCommand(true);
}
>>>>>>> upstream/master

void MainWindow::executeCommand(bool withClear)
{
	QString command = m_inputEdit->text();

	// A blank command is a "silent step"
	if (command == "")
	{
<<<<<<< HEAD
		debug_cpu_get_visible_cpu(*m_machine)->debug()->single_step();
=======
		m_machine->debugger().cpu().get_visible_cpu()->debug()->single_step();
>>>>>>> upstream/master
		return;
	}

	// Send along the command
<<<<<<< HEAD
	debug_console_execute_command(*m_machine,
									command.toLocal8Bit().data(),
									true);
=======
	m_machine->debugger().console().execute_command(command.toLocal8Bit().data(), true);
>>>>>>> upstream/master

	// Add history & set the index to be the top of the stack
	addToHistory(command);

	// Clear out the text and reset the history pointer only if asked
	if (withClear)
	{
		m_inputEdit->clear();
		m_historyIndex = m_inputHistory.size();
	}

	// Refresh
	m_consoleView->viewport()->update();
	refreshAll();
}


void MainWindow::mountImage(bool changedTo)
{
	// The image interface index was assigned to the QAction's data memeber
	const int imageIndex = dynamic_cast<QAction*>(sender())->data().toInt();
	image_interface_iterator iter(m_machine->root_device());
	device_image_interface *img = iter.byindex(imageIndex);
<<<<<<< HEAD
	if (img == NULL)
	{
		debug_console_printf(*m_machine, "Something is wrong with the mount menu.\n");
=======
	if (img == nullptr)
	{
		m_machine->debugger().console().printf("Something is wrong with the mount menu.\n");
>>>>>>> upstream/master
		refreshAll();
		return;
	}

	// File dialog
	QString filename = QFileDialog::getOpenFileName(this,
													"Select an image file",
													QDir::currentPath(),
													tr("All files (*.*)"));

<<<<<<< HEAD
	if (img->load(filename.toUtf8().data()) != IMAGE_INIT_PASS)
	{
		debug_console_printf(*m_machine, "Image could not be mounted.\n");
=======
	if (img->load(filename.toUtf8().data()) != image_init_result::PASS)
	{
		m_machine->debugger().console().printf("Image could not be mounted.\n");
>>>>>>> upstream/master
		refreshAll();
		return;
	}

	// Activate the unmount menu option
	QAction* unmountAct = sender()->parent()->findChild<QAction*>("unmount");
	unmountAct->setEnabled(true);

	// Set the mount name
	QMenu* parentMenuItem = dynamic_cast<QMenu*>(sender()->parent());
	QString baseString = parentMenuItem->title();
	baseString.truncate(baseString.lastIndexOf(QString(" : ")));
	const QString newTitle = baseString + QString(" : ") + QString(img->filename());
	parentMenuItem->setTitle(newTitle);

<<<<<<< HEAD
	debug_console_printf(*m_machine, "Image %s mounted successfully.\n", filename.toUtf8().data());
=======
	m_machine->debugger().console().printf("Image %s mounted successfully.\n", filename.toUtf8().data());
>>>>>>> upstream/master
	refreshAll();
}


void MainWindow::unmountImage(bool changedTo)
{
	// The image interface index was assigned to the QAction's data memeber
	const int imageIndex = dynamic_cast<QAction*>(sender())->data().toInt();
	image_interface_iterator iter(m_machine->root_device());
	device_image_interface *img = iter.byindex(imageIndex);

	img->unload();

	// Deactivate the unmount menu option
	dynamic_cast<QAction*>(sender())->setEnabled(false);

	// Set the mount name
	QMenu* parentMenuItem = dynamic_cast<QMenu*>(sender()->parent());
	QString baseString = parentMenuItem->title();
	baseString.truncate(baseString.lastIndexOf(QString(" : ")));
	const QString newTitle = baseString + QString(" : ") + QString("[empty slot]");
	parentMenuItem->setTitle(newTitle);

<<<<<<< HEAD
	debug_console_printf(*m_machine, "Image successfully unmounted.\n");
=======
	m_machine->debugger().console().printf("Image successfully unmounted.\n");
>>>>>>> upstream/master
	refreshAll();
}


void MainWindow::dasmViewUpdated()
{
	debug_view_disasm *const dasmView = downcast<debug_view_disasm*>(m_dasmFrame->view()->view());
<<<<<<< HEAD
	bool const haveCursor = dasmView->cursor_visible() && (debug_cpu_get_visible_cpu(*m_machine) == dasmView->source()->device());
=======
	bool const haveCursor = dasmView->cursor_visible() && (m_machine->debugger().cpu().get_visible_cpu() == dasmView->source()->device());
>>>>>>> upstream/master
	bool haveBreakpoint = false;
	bool breakpointEnabled = false;
	if (haveCursor)
	{
		offs_t const address = dasmView->selected_address();
		device_t *const device = dasmView->source()->device();
		device_debug *const cpuinfo = device->debug();

		// Find an existing breakpoint at this address
		device_debug::breakpoint* bp = cpuinfo->breakpoint_first();
<<<<<<< HEAD
		while ((bp != NULL) && (bp->address() != address))
			bp = bp->next();

		if (bp != NULL)
=======
		while ((bp != nullptr) && (bp->address() != address))
			bp = bp->next();

		if (bp != nullptr)
>>>>>>> upstream/master
		{
			haveBreakpoint = true;
			breakpointEnabled = bp->enabled();
		}
	}

	m_breakpointToggleAct->setText(haveBreakpoint ? "Clear Breakpoint at Cursor" : haveCursor ? "Set Breakpoint at Cursor" : "Toggle Breakpoint at Cursor");
	m_breakpointEnableAct->setText((!haveBreakpoint || breakpointEnabled) ? "Disable Breakpoint at Cursor" : "Enable Breakpoint at Cursor");
	m_breakpointToggleAct->setEnabled(haveCursor);
	m_breakpointEnableAct->setEnabled(haveBreakpoint);
	m_runToCursorAct->setEnabled(haveCursor);
}


void MainWindow::debugActClose()
{
	m_machine->schedule_exit();
}


void MainWindow::addToHistory(const QString& command)
{
	if (command == "")
		return;

	// Always push back when there is no previous history
	if (m_inputHistory.size() == 0)
	{
		m_inputHistory.push_back(m_inputEdit->text());
		return;
	}

	// If there is previous history, make sure it's not what you just executed
	if (m_inputHistory.back() != m_inputEdit->text())
	{
		m_inputHistory.push_back(m_inputEdit->text());
	}
}


void MainWindow::createImagesMenu()
{
	QMenu* imagesMenu = menuBar()->addMenu("&Images");

	int interfaceIndex = 0;
<<<<<<< HEAD
	image_interface_iterator iter(m_machine->root_device());
	for (device_image_interface *img = iter.first(); img != NULL; img = iter.next())
	{
		std::string menuName;
		strprintf(menuName,"%s : %s", img->device().name(), img->exists() ? img->filename() : "[empty slot]");

		QMenu* interfaceMenu = imagesMenu->addMenu(menuName.c_str());
		interfaceMenu->setObjectName(img->device().name());
=======
	for (device_image_interface &img : image_interface_iterator(m_machine->root_device()))
	{
		std::string menuName = string_format("%s : %s", img.device().name(), img.exists() ? img.filename() : "[empty slot]");

		QMenu* interfaceMenu = imagesMenu->addMenu(menuName.c_str());
		interfaceMenu->setObjectName(img.device().name());
>>>>>>> upstream/master

		QAction* mountAct = new QAction("Mount...", interfaceMenu);
		QAction* unmountAct = new QAction("Unmount", interfaceMenu);
		mountAct->setObjectName("mount");
		mountAct->setData(QVariant(interfaceIndex));
		unmountAct->setObjectName("unmount");
		unmountAct->setData(QVariant(interfaceIndex));
<<<<<<< HEAD
		connect(mountAct, SIGNAL(triggered(bool)), this, SLOT(mountImage(bool)));
		connect(unmountAct, SIGNAL(triggered(bool)), this, SLOT(unmountImage(bool)));

		if (!img->exists())
=======
		connect(mountAct, &QAction::triggered, this, &MainWindow::mountImage);
		connect(unmountAct, &QAction::triggered, this, &MainWindow::unmountImage);

		if (!img.exists())
>>>>>>> upstream/master
			unmountAct->setEnabled(false);

		interfaceMenu->addAction(mountAct);
		interfaceMenu->addAction(unmountAct);

		// TODO: Cassette operations

		interfaceIndex++;
	}
}


//=========================================================================
//  MainWindowQtConfig
//=========================================================================
void MainWindowQtConfig::buildFromQWidget(QWidget* widget)
{
	WindowQtConfig::buildFromQWidget(widget);
	MainWindow* window = dynamic_cast<MainWindow*>(widget);
	m_windowState = window->saveState();

	QActionGroup* rightBarGroup = window->findChild<QActionGroup*>("rightbargroup");
	if (rightBarGroup->checkedAction()->text() == "Raw Opcodes")
		m_rightBar = 0;
	else if (rightBarGroup->checkedAction()->text() == "Encrypted Opcodes")
		m_rightBar = 1;
	else if (rightBarGroup->checkedAction()->text() == "Comments")
		m_rightBar = 2;
}


void MainWindowQtConfig::applyToQWidget(QWidget* widget)
{
	WindowQtConfig::applyToQWidget(widget);
	MainWindow* window = dynamic_cast<MainWindow*>(widget);
	window->restoreState(m_windowState);

	QActionGroup* rightBarGroup = window->findChild<QActionGroup*>("rightbargroup");
	rightBarGroup->actions()[m_rightBar]->trigger();
}


<<<<<<< HEAD
void MainWindowQtConfig::addToXmlDataNode(xml_data_node* node) const
{
	WindowQtConfig::addToXmlDataNode(node);
	xml_set_attribute_int(node, "rightbar", m_rightBar);
	xml_set_attribute(node, "qtwindowstate", m_windowState.toPercentEncoding().data());
}


void MainWindowQtConfig::recoverFromXmlNode(xml_data_node* node)
{
	WindowQtConfig::recoverFromXmlNode(node);
	const char* state = xml_get_attribute_string(node, "qtwindowstate", "");
	m_windowState = QByteArray::fromPercentEncoding(state);
	m_rightBar = xml_get_attribute_int(node, "rightbar", m_rightBar);
=======
void MainWindowQtConfig::addToXmlDataNode(util::xml::data_node &node) const
{
	WindowQtConfig::addToXmlDataNode(node);
	node.set_attribute_int("rightbar", m_rightBar);
	node.set_attribute("qtwindowstate", m_windowState.toPercentEncoding().data());
}


void MainWindowQtConfig::recoverFromXmlNode(util::xml::data_node const &node)
{
	WindowQtConfig::recoverFromXmlNode(node);
	const char* state = node.get_attribute_string("qtwindowstate", "");
	m_windowState = QByteArray::fromPercentEncoding(state);
	m_rightBar = node.get_attribute_int("rightbar", m_rightBar);
>>>>>>> upstream/master
}

DasmDockWidget::~DasmDockWidget()
{
}

ProcessorDockWidget::~ProcessorDockWidget()
{
}
