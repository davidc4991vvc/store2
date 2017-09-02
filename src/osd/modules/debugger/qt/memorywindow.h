// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DEBUG_QT_MEMORY_WINDOW_H__
#define __DEBUG_QT_MEMORY_WINDOW_H__

<<<<<<< HEAD
#include <QtGui/QtGui>
=======
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
>>>>>>> upstream/master

#include "debuggerview.h"
#include "windowqt.h"

class DebuggerMemView;


//============================================================
//  The Memory Window.
//============================================================
class MemoryWindow : public WindowQt
{
	Q_OBJECT

public:
<<<<<<< HEAD
	MemoryWindow(running_machine* machine, QWidget* parent=NULL);
=======
	MemoryWindow(running_machine* machine, QWidget* parent=nullptr);
>>>>>>> upstream/master
	virtual ~MemoryWindow();


private slots:
	void memoryRegionChanged(int index);
	void expressionSubmitted();
<<<<<<< HEAD
	void chunkChanged(QAction* changedTo);
=======
	void formatChanged(QAction* changedTo);
>>>>>>> upstream/master
	void addressChanged(QAction* changedTo);
	void reverseChanged(bool changedTo);
	void increaseBytesPerLine(bool changedTo);
	void decreaseBytesPerLine(bool checked=false);


private:
	void populateComboBox();
	void setToCurrentCpu();
<<<<<<< HEAD
	QAction* chunkSizeMenuItem(const QString& itemName);
=======
	QAction* dataFormatMenuItem(const QString& itemName);
>>>>>>> upstream/master


private:
	// Widgets
	QLineEdit* m_inputEdit;
	QComboBox* m_memoryComboBox;
	DebuggerMemView* m_memTable;
};


//=========================================================================
//  The mem window gets its own debugger view to handle right click pop-ups
//=========================================================================
class DebuggerMemView : public DebuggerView
{
public:
	DebuggerMemView(const debug_view_type& type,
					running_machine* machine,
<<<<<<< HEAD
					QWidget* parent=NULL)
=======
					QWidget* parent=nullptr)
>>>>>>> upstream/master
		: DebuggerView(type, machine, parent)
	{}
	virtual ~DebuggerMemView() {}

protected:
	void mousePressEvent(QMouseEvent* event);
};


//=========================================================================
//  A way to store the configuration of a window long enough to read/write.
//=========================================================================
class MemoryWindowQtConfig : public WindowQtConfig
{
public:
	MemoryWindowQtConfig() :
		WindowQtConfig(WIN_TYPE_MEMORY),
		m_reverse(0),
		m_addressMode(0),
<<<<<<< HEAD
		m_chunkSize(0),
=======
		m_dataFormat(0),
>>>>>>> upstream/master
		m_memoryRegion(0)
	{
	}

	~MemoryWindowQtConfig() {}

	// Settings
	int m_reverse;
	int m_addressMode;
<<<<<<< HEAD
	int m_chunkSize;
=======
	int m_dataFormat;
>>>>>>> upstream/master
	int m_memoryRegion;

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
