// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
<<<<<<< HEAD
#define NO_MEM_TRACKING
=======
#include "emu.h"
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
>>>>>>> upstream/master

#include "breakpointswindow.h"

#include "debug/debugcon.h"
#include "debug/debugcpu.h"
#include "debug/dvbpoints.h"
#include "debug/dvwpoints.h"


BreakpointsWindow::BreakpointsWindow(running_machine* machine, QWidget* parent) :
<<<<<<< HEAD
	WindowQt(machine, NULL)
{
	setWindowTitle("Debug: All Breakpoints");

	if (parent != NULL)
=======
	WindowQt(machine, nullptr)
{
	setWindowTitle("Debug: All Breakpoints");

	if (parent != nullptr)
>>>>>>> upstream/master
	{
		QPoint parentPos = parent->pos();
		setGeometry(parentPos.x()+100, parentPos.y()+100, 800, 400);
	}

	//
	// The main frame and its input and breakpoints widgets
	//
	QFrame* mainWindowFrame = new QFrame(this);

	// The main breakpoints view
	m_breakpointsView = new DebuggerView(DVT_BREAK_POINTS, m_machine, this);

	// Layout
	QVBoxLayout* vLayout = new QVBoxLayout(mainWindowFrame);
	vLayout->setObjectName("vlayout");
	vLayout->setSpacing(3);
	vLayout->setContentsMargins(2,2,2,2);
	vLayout->addWidget(m_breakpointsView);

	setCentralWidget(mainWindowFrame);

	//
	// Menu bars
	//
	QActionGroup* typeGroup = new QActionGroup(this);
	typeGroup->setObjectName("typegroup");
	QAction* typeBreak = new QAction("Breakpoints", this);
	typeBreak->setObjectName("typebreak");
	QAction* typeWatch = new QAction("Watchpoints", this);
	typeWatch->setObjectName("typewatch");
	typeBreak->setCheckable(true);
	typeWatch->setCheckable(true);
	typeBreak->setActionGroup(typeGroup);
	typeWatch->setActionGroup(typeGroup);
	typeBreak->setShortcut(QKeySequence("Ctrl+1"));
	typeWatch->setShortcut(QKeySequence("Ctrl+2"));
	typeBreak->setChecked(true);
<<<<<<< HEAD
	connect(typeGroup, SIGNAL(triggered(QAction*)), this, SLOT(typeChanged(QAction*)));
=======
	connect(typeGroup, &QActionGroup::triggered, this, &BreakpointsWindow::typeChanged);
>>>>>>> upstream/master

	// Assemble the options menu
	QMenu* optionsMenu = menuBar()->addMenu("&Options");
	optionsMenu->addActions(typeGroup->actions());
}


BreakpointsWindow::~BreakpointsWindow()
{
}


void BreakpointsWindow::typeChanged(QAction* changedTo)
{
	// Clean
	delete m_breakpointsView;
<<<<<<< HEAD
	m_breakpointsView = NULL;
=======
	m_breakpointsView = nullptr;
>>>>>>> upstream/master

	// Create
	if (changedTo->text() == "Breakpoints")
	{
		m_breakpointsView = new DebuggerView(DVT_BREAK_POINTS, m_machine, this);
		setWindowTitle("Debug: All Breakpoints");
	}
	else if (changedTo->text() == "Watchpoints")
	{
		m_breakpointsView = new DebuggerView(DVT_WATCH_POINTS, m_machine, this);
		setWindowTitle("Debug: All Watchpoints");
	}

	// Re-register
	QVBoxLayout* layout = findChild<QVBoxLayout*>("vlayout");
	layout->addWidget(m_breakpointsView);
}



//=========================================================================
//  BreakpointsWindowQtConfig
//=========================================================================
void BreakpointsWindowQtConfig::buildFromQWidget(QWidget* widget)
{
	WindowQtConfig::buildFromQWidget(widget);
	BreakpointsWindow* window = dynamic_cast<BreakpointsWindow*>(widget);

	QActionGroup* typeGroup = window->findChild<QActionGroup*>("typegroup");
	if (typeGroup->checkedAction()->text() == "Breakpoints")
		m_bwType = 0;
	else if (typeGroup->checkedAction()->text() == "Watchpoints")
		m_bwType = 1;
}


void BreakpointsWindowQtConfig::applyToQWidget(QWidget* widget)
{
	WindowQtConfig::applyToQWidget(widget);
	BreakpointsWindow* window = dynamic_cast<BreakpointsWindow*>(widget);

	QActionGroup* typeGroup = window->findChild<QActionGroup*>("typegroup");
	typeGroup->actions()[m_bwType]->trigger();
}


<<<<<<< HEAD
void BreakpointsWindowQtConfig::addToXmlDataNode(xml_data_node* node) const
{
	WindowQtConfig::addToXmlDataNode(node);
	xml_set_attribute_int(node, "bwtype", m_bwType);
}


void BreakpointsWindowQtConfig::recoverFromXmlNode(xml_data_node* node)
{
	WindowQtConfig::recoverFromXmlNode(node);
	m_bwType = xml_get_attribute_int(node, "bwtype", m_bwType);
=======
void BreakpointsWindowQtConfig::addToXmlDataNode(util::xml::data_node &node) const
{
	WindowQtConfig::addToXmlDataNode(node);
	node.set_attribute_int("bwtype", m_bwType);
}


void BreakpointsWindowQtConfig::recoverFromXmlNode(util::xml::data_node const &node)
{
	WindowQtConfig::recoverFromXmlNode(node);
	m_bwType = node.get_attribute_int("bwtype", m_bwType);
>>>>>>> upstream/master
}
