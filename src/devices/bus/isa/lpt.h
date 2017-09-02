// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    IBM-PC printer interface

***************************************************************************/

<<<<<<< HEAD
#ifndef __ISA_LPT_H__
#define __ISA_LPT_H__
=======
#ifndef MAME_BUS_ISA_LPT_H
#define MAME_BUS_ISA_LPT_H

#pragma once
>>>>>>> upstream/master

#include "isa.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa8_lpt_device

class isa8_lpt_device : public device_t,
	public device_isa8_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	isa8_lpt_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	bool is_primary() { return m_is_primary; }

	WRITE_LINE_MEMBER(pc_cpu_line);

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
=======
	isa8_lpt_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	bool is_primary() { return m_is_primary; }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

private:
	WRITE_LINE_MEMBER(pc_cpu_line);
>>>>>>> upstream/master

	// internal state
	bool m_is_primary;
};

// device type definition
<<<<<<< HEAD
extern const device_type ISA8_LPT;

#endif /* __ISA_LPT_H__ */
=======
DECLARE_DEVICE_TYPE(ISA8_LPT, isa8_lpt_device)

#endif // MAME_BUS_ISA_LPT_H
>>>>>>> upstream/master
