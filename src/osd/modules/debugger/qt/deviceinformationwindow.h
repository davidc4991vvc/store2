// license:BSD-3-Clause
// copyright-holders:Andrew Gardner
#ifndef __DEBUG_QT_DEVICE_INFORMATION_WINDOW_H__
#define __DEBUG_QT_DEVICE_INFORMATION_WINDOW_H__

<<<<<<< HEAD
#include <QtGui/QtGui>

=======
>>>>>>> upstream/master
#include "windowqt.h"

//============================================================
//  The Device Information Window.
//============================================================
class DeviceInformationWindow : public WindowQt
{
	Q_OBJECT

public:
<<<<<<< HEAD
	DeviceInformationWindow(running_machine* machine, device_t* device = NULL, QWidget* parent=NULL);
=======
	DeviceInformationWindow(running_machine* machine, device_t* device = nullptr, QWidget* parent=nullptr);
>>>>>>> upstream/master
	virtual ~DeviceInformationWindow();

	void set_device(const char *tag);
	const char *device_tag() const;

private:
	device_t *m_device;

	void fill_device_information();
};




//=========================================================================
//  A way to store the configuration of a window long enough to read/write.
//=========================================================================
class DeviceInformationWindowQtConfig : public WindowQtConfig
{
public:
	std::string m_device_tag;

	DeviceInformationWindowQtConfig() :
		WindowQtConfig(WIN_TYPE_DEVICE_INFORMATION)
	{
	}

	~DeviceInformationWindowQtConfig() {}

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
