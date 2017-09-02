// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer Pachinko Controller

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_PACHINKO__
#define __NES_PACHINKO__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_PACHINKO_H
#define MAME_BUS_NES_CTRL_PACHINKO_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_pachinko_device

class nes_pachinko_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_pachinko_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);

	required_ioport m_joypad;
	required_ioport m_trigger;
	UINT32 m_latch;
};

// device type definition
extern const device_type NES_PACHINKO;

#endif
=======
	nes_pachinko_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;

	required_ioport m_joypad;
	required_ioport m_trigger;
	uint32_t m_latch;
};

// device type definition
DECLARE_DEVICE_TYPE(NES_PACHINKO, nes_pachinko_device)

#endif // MAME_BUS_NES_CTRL_PACHINKO_H
>>>>>>> upstream/master
