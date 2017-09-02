// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DEBUG_QT_MAIN_WINDOW_H__
#define __DEBUG_QT_MAIN_WINDOW_H__

<<<<<<< HEAD
#include <QtGui/QtGui>
#include <vector>

=======
#include <vector>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>

>>>>>>> upstream/master
#include "debug/dvdisasm.h"

#include "debuggerview.h"
#include "windowqt.h"

class DasmDockWidget;
class ProcessorDockWidget;


//============================================================
//  The Main Window.  Contains processor and dasm docks.
//============================================================
class MainWindow : public WindowQt
{
	Q_OBJECT

public:
<<<<<<< HEAD
	MainWindow(running_machine* machine, QWidget* parent=NULL);
=======
	MainWindow(running_machine* machine, QWidget* parent=nullptr);
>>>>>>> upstream/master
	virtual ~MainWindow();

	void setProcessor(device_t* processor);


protected:
	// Used to intercept the user clicking 'X' in the upper corner
	void closeEvent(QCloseEvent* event);

	// Used to intercept the user hitting the up arrow in the input widget
	bool eventFilter(QObject* obj, QEvent* event);


private slots:
	void toggleBreakpointAtCursor(bool changedTo);
	void enableBreakpointAtCursor(bool changedTo);
	void runToCursor(bool changedTo);
	void rightBarChanged(QAction* changedTo);

<<<<<<< HEAD
	void executeCommand(bool withClear=true);
=======
	void executeCommandSlot();
>>>>>>> upstream/master

	void mountImage(bool changedTo);
	void unmountImage(bool changedTo);

	void dasmViewUpdated();

	// Closing the main window actually exits the program
	void debugActClose();


private:
	void createImagesMenu();

	// Widgets and docks
	QLineEdit* m_inputEdit;
	DebuggerView* m_consoleView;
	ProcessorDockWidget* m_procFrame;
	DasmDockWidget* m_dasmFrame;

	// Menu items
	QAction* m_breakpointToggleAct;
	QAction* m_breakpointEnableAct;
	QAction* m_runToCursorAct;

	// Terminal history
	int m_historyIndex;
	std::vector<QString> m_inputHistory;
	void addToHistory(const QString& command);
<<<<<<< HEAD
=======
	void executeCommand(bool withClear);
>>>>>>> upstream/master
};


//============================================================
//  Docks with the Main Window.  Disassembly.
//============================================================
class DasmDockWidget : public QWidget
{
	Q_OBJECT

public:
<<<<<<< HEAD
	DasmDockWidget(running_machine* machine, QWidget* parent=NULL) :
=======
	DasmDockWidget(running_machine* machine, QWidget* parent=nullptr) :
>>>>>>> upstream/master
		QWidget(parent),
		m_machine(machine)
	{
		m_dasmView = new DebuggerView(DVT_DISASSEMBLY,
										m_machine,
										this);

		// Force a recompute of the disassembly region
		downcast<debug_view_disasm*>(m_dasmView->view())->set_expression("curpc");

		QVBoxLayout* dvLayout = new QVBoxLayout(this);
		dvLayout->addWidget(m_dasmView);
		dvLayout->setContentsMargins(4,0,4,0);
	}


	virtual ~DasmDockWidget();


	DebuggerView* view() { return m_dasmView; }


	QSize minimumSizeHint() const
	{
		return QSize(150,150);
	}


	QSize sizeHint() const
	{
		return QSize(150,200);
	}


private:
	DebuggerView* m_dasmView;

	running_machine* m_machine;
};


//============================================================
//  Docks with the Main Window.  Processor information.
//============================================================
class ProcessorDockWidget : public QWidget
{
	Q_OBJECT

public:
	ProcessorDockWidget(running_machine* machine,
<<<<<<< HEAD
						QWidget* parent=NULL) :
		QWidget(parent),
		m_processorView(NULL),
=======
						QWidget* parent=nullptr) :
		QWidget(parent),
		m_processorView(nullptr),
>>>>>>> upstream/master
		m_machine(machine)
	{
		m_processorView = new DebuggerView(DVT_STATE,
											m_machine,
											this);
		m_processorView->setFocusPolicy(Qt::NoFocus);

		QVBoxLayout* cvLayout = new QVBoxLayout(this);
		cvLayout->addWidget(m_processorView);
		cvLayout->setContentsMargins(4,0,4,2);
	}


	virtual ~ProcessorDockWidget();


	DebuggerView* view() { return m_processorView; }


	QSize minimumSizeHint() const
	{
		return QSize(150,300);
	}


	QSize sizeHint() const
	{
		return QSize(200,300);
	}


private:
	DebuggerView* m_processorView;

	running_machine* m_machine;
};


//=========================================================================
//  A way to store the configuration of a window long enough to read/write.
//=========================================================================
class MainWindowQtConfig : public WindowQtConfig
{
public:
	MainWindowQtConfig() :
		WindowQtConfig(WIN_TYPE_MAIN),
		m_rightBar(0),
		m_windowState()
	{}

	~MainWindowQtConfig() {}

	// Settings
	int m_rightBar;
	QByteArray m_windowState;

	void buildFromQWidget(QWidget* widget);
	void applyToQWidget(QWidget* widget);
<<<<<<< HEAD
	void addToXmlDataNode(xml_data_node* node) const;
	void recoverFromXmlNode(xml_data_node* node);
=======
	void addToXmlDataNode(util::xml::data_node &node) const;
	void recoverFromXmlNode(util::xml::data_node const &node);
>>>>>>> upstream/master
};



#endif
