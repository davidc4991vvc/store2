// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Super Famicom & SNES Mouse

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SNES_MOUSE__
#define __SNES_MOUSE__


#include "emu.h"
=======
#ifndef MAME_BUS_SNES_CTRL_MOUSE_H
#define MAME_BUS_SNES_CTRL_MOUSE_H

#pragma once


>>>>>>> upstream/master
#include "ctrl.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> snes_mouse_device

class snes_mouse_device : public device_t,
							public device_snes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	snes_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_sms_control_port_interface overrides
	virtual UINT8 read_pin4();
	virtual void write_strobe(UINT8 data);
	virtual void port_poll();
=======
	snes_mouse_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_snes_control_port_interface overrides
	virtual uint8_t read_pin4() override;
	virtual void write_strobe(uint8_t data) override;
	virtual void port_poll() override;
>>>>>>> upstream/master

private:
	required_ioport m_buttons;
	required_ioport m_xaxis;
	required_ioport m_yaxis;
	int m_strobe;
	int m_idx;
<<<<<<< HEAD
	UINT32 m_latch;

	INT16 m_x, m_y, m_oldx, m_oldy;
	UINT8 m_deltax, m_deltay;
=======
	uint32_t m_latch;

	int16_t m_x, m_y, m_oldx, m_oldy;
	uint8_t m_deltax, m_deltay;
>>>>>>> upstream/master
	int m_speed;
	int m_dirx, m_diry;
};


// device type definition
<<<<<<< HEAD
extern const device_type SNES_MOUSE;


#endif
=======
DECLARE_DEVICE_TYPE(SNES_MOUSE, snes_mouse_device)

#endif // MAME_BUS_SNES_CTRL_MOUSE_H
>>>>>>> upstream/master
