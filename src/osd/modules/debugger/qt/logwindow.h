// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DEBUG_QT_LOG_WINDOW_H__
#define __DEBUG_QT_LOG_WINDOW_H__

<<<<<<< HEAD
#include <QtGui/QtGui>

=======
>>>>>>> upstream/master
#include "debuggerview.h"
#include "windowqt.h"


//============================================================
//  The Log Window.
//============================================================
class LogWindow : public WindowQt
{
	Q_OBJECT

public:
<<<<<<< HEAD
	LogWindow(running_machine* machine, QWidget* parent=NULL);
=======
	LogWindow(running_machine* machine, QWidget* parent=nullptr);
>>>>>>> upstream/master
	virtual ~LogWindow();


private:
	// Widgets
	DebuggerView* m_logView;
};


//=========================================================================
//  A way to store the configuration of a window long enough to read/write.
//=========================================================================
class LogWindowQtConfig : public WindowQtConfig
{
public:
	LogWindowQtConfig() :
		WindowQtConfig(WIN_TYPE_LOG)
	{
	}

	~LogWindowQtConfig() {}

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
