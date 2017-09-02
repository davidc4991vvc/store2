// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DEBUG_QT_BREAK_POINTS_WINDOW_H__
#define __DEBUG_QT_BREAK_POINTS_WINDOW_H__

<<<<<<< HEAD
#include <QtGui/QtGui>

=======
>>>>>>> upstream/master
#include "debuggerview.h"
#include "windowqt.h"


//============================================================
//  The Breakpoints Window.
//============================================================
class BreakpointsWindow : public WindowQt
{
	Q_OBJECT

public:
<<<<<<< HEAD
	BreakpointsWindow(running_machine* machine, QWidget* parent=NULL);
=======
	BreakpointsWindow(running_machine* machine, QWidget* parent=nullptr);
>>>>>>> upstream/master
	virtual ~BreakpointsWindow();


private slots:
	void typeChanged(QAction* changedTo);


private:
	// Widgets
	DebuggerView* m_breakpointsView;
};


//=========================================================================
//  A way to store the configuration of a window long enough to read/write.
//=========================================================================
class BreakpointsWindowQtConfig : public WindowQtConfig
{
public:
	BreakpointsWindowQtConfig() :
		WindowQtConfig(WIN_TYPE_BREAK_POINTS),
		m_bwType(0)
	{
	}

	~BreakpointsWindowQtConfig() {}

	// Settings
	int m_bwType;

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
