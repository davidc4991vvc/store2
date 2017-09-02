// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Super Famicom - Sunsoft Pachinko Controller

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __SNES_PACHINKO__
#define __SNES_PACHINKO__


#include "emu.h"
=======
#ifndef MAME_BUS_SNES_CTRL_PACHINKO_H
#define MAME_BUS_SNES_CTRL_PACHINKO_H

#pragma once


>>>>>>> upstream/master
#include "ctrl.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> snes_pachinko_device

class snes_pachinko_device : public device_t,
							public device_snes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	snes_pachinko_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

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
	snes_pachinko_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

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
	required_ioport m_dial;
	required_ioport m_button;
	int m_strobe;
<<<<<<< HEAD
	UINT32 m_latch;
=======
	uint32_t m_latch;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SNES_PACHINKO;


#endif
=======
DECLARE_DEVICE_TYPE(SNES_PACHINKO, snes_pachinko_device)

#endif // MAME_BUS_SNES_CTRL_PACHINKO_H
>>>>>>> upstream/master
