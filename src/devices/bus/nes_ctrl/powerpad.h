// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Entertainment System - Bandai Power Pad

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_POWERPAD__
#define __NES_POWERPAD__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_POWERPAD_H
#define MAME_BUS_NES_CTRL_POWERPAD_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_powerpad_device

class nes_powerpad_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_powerpad_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_bit34();
	virtual void write(UINT8 data);
=======
	nes_powerpad_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_bit34() override;
	virtual void write(uint8_t data) override;
>>>>>>> upstream/master

private:
	required_ioport m_ipt1;
	required_ioport m_ipt2;
<<<<<<< HEAD
	UINT32 m_latch[2];
=======
	uint32_t m_latch[2];
>>>>>>> upstream/master
};


// device type definition
extern const device_type NES_POWERPAD;


<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_NES_CTRL_POWERPAD_H
>>>>>>> upstream/master
