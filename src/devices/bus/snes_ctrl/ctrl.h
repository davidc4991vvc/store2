// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Super Famicom & SNES controller port emulation

**********************************************************************/

<<<<<<< HEAD

#pragma once

#ifndef __SNES_CONTROL_PORT__
#define __SNES_CONTROL_PORT__

#include "emu.h"
=======
#ifndef MAME_BUS_SNES_CTRL_CTRL_H
#define MAME_BUS_SNES_CTRL_CTRL_H

#pragma once

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class snes_control_port_device;

// ======================> device_snes_control_port_interface

class device_snes_control_port_interface : public device_slot_card_interface
{
public:
	// construction/destruction
	device_snes_control_port_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_snes_control_port_interface();

<<<<<<< HEAD
	virtual UINT8 read_pin4() { return 0; };
	virtual UINT8 read_pin5() { return 0; };
	virtual void write_pin6(UINT8 data) { };
	virtual void write_strobe(UINT8 data) { };
	virtual void port_poll() { };
=======
	virtual uint8_t read_pin4() { return 0; }
	virtual uint8_t read_pin5() { return 0; }
	virtual void write_pin6(uint8_t data) { }
	virtual void write_strobe(uint8_t data) { }
	virtual void port_poll() { }
>>>>>>> upstream/master

protected:
	snes_control_port_device *m_port;
};

<<<<<<< HEAD
typedef device_delegate<bool (INT16 x, INT16 y)> snesctrl_onscreen_delegate;
#define SNESCTRL_ONSCREEN_CB(name)  bool name(INT16 x, INT16 y)

typedef device_delegate<void (INT16 x, INT16 y)> snesctrl_gunlatch_delegate;
#define SNESCTRL_GUNLATCH_CB(name)  void name(INT16 x, INT16 y)

// ======================> snes_control_port_device

class snes_control_port_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
	snes_control_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
typedef device_delegate<bool (int16_t x, int16_t y)> snesctrl_onscreen_delegate;
#define SNESCTRL_ONSCREEN_CB(name)  bool name(int16_t x, int16_t y)

typedef device_delegate<void (int16_t x, int16_t y)> snesctrl_gunlatch_delegate;
#define SNESCTRL_GUNLATCH_CB(name)  void name(int16_t x, int16_t y)

// ======================> snes_control_port_device

class snes_control_port_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	snes_control_port_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	virtual ~snes_control_port_device();

	static void set_onscreen_callback(device_t &device, snesctrl_onscreen_delegate callback) { downcast<snes_control_port_device &>(device).m_onscreen_cb = callback; }
	static void set_gunlatch_callback(device_t &device, snesctrl_gunlatch_delegate callback) { downcast<snes_control_port_device &>(device).m_gunlatch_cb = callback; }

<<<<<<< HEAD
	UINT8 read_pin4();
	UINT8 read_pin5();
	void write_pin6(UINT8 data);
	void write_strobe(UINT8 data);
	void port_poll();

	snesctrl_onscreen_delegate m_onscreen_cb;
	snesctrl_gunlatch_delegate m_gunlatch_cb;

protected:
	// device-level overrides
	virtual void device_start();
=======
	uint8_t read_pin4();
	uint8_t read_pin5();
	void write_pin6(uint8_t data);
	void write_strobe(uint8_t data);
	void port_poll();

	bool onscreen_cb(int16_t x, int16_t y) { return m_onscreen_cb.isnull() ? true : m_onscreen_cb(x, y); }
	void gunlatch_cb(int16_t x, int16_t y) { if (!m_gunlatch_cb.isnull()) m_gunlatch_cb(x, y); }

protected:
	// device-level overrides
	virtual void device_start() override;

	snesctrl_onscreen_delegate m_onscreen_cb;
	snesctrl_gunlatch_delegate m_gunlatch_cb;
>>>>>>> upstream/master

	device_snes_control_port_interface *m_device;
};


// device type definition
<<<<<<< HEAD
extern const device_type SNES_CONTROL_PORT;
=======
DECLARE_DEVICE_TYPE(SNES_CONTROL_PORT, snes_control_port_device)
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SNES_CONTROL_PORT_ADD(_tag, _slot_intf, _def_slot) \
	MCFG_DEVICE_ADD(_tag, SNES_CONTROL_PORT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, false)

#define MCFG_SNESCTRL_ONSCREEN_CB(_class, _method) \
	snes_control_port_device::set_onscreen_callback(*device, snesctrl_onscreen_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));

#define MCFG_SNESCTRL_GUNLATCH_CB(_class, _method) \
	snes_control_port_device::set_gunlatch_callback(*device, snesctrl_gunlatch_delegate(&_class::_method, #_class "::" #_method, downcast<_class *>(owner)));


SLOT_INTERFACE_EXTERN( snes_control_port_devices );


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_SNES_CTRL_CTRL_H
>>>>>>> upstream/master
