// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Nintendo Family Computer Konami Hyper Shot Controllers

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __NES_KONAMIHS__
#define __NES_KONAMIHS__


#include "emu.h"
#include "ctrl.h"

=======
#ifndef MAME_BUS_NES_CTRL_KONAMIHS_H
#define MAME_BUS_NES_CTRL_KONAMIHS_H

#pragma once

#include "ctrl.h"


>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> nes_konamihs_device

class nes_konamihs_device : public device_t,
							public device_nes_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_konamihs_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual ioport_constructor device_input_ports() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual UINT8 read_exp(offs_t offset);
	virtual void write(UINT8 data);

	required_ioport m_ipt_p1;
	required_ioport m_ipt_p2;
	UINT32 m_latch_p1, m_latch_p2;
};

// device type definition
extern const device_type NES_KONAMIHS;

#endif
=======
	nes_konamihs_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual ioport_constructor device_input_ports() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual uint8_t read_exp(offs_t offset) override;
	virtual void write(uint8_t data) override;

	required_ioport m_ipt_p1;
	required_ioport m_ipt_p2;
	uint32_t m_latch_p1, m_latch_p2;
};

// device type definition
DECLARE_DEVICE_TYPE(NES_KONAMIHS, nes_konamihs_device)

#endif // MAME_BUS_NES_CTRL_KONAMIHS_H
>>>>>>> upstream/master
