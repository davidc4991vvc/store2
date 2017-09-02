// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
<<<<<<< HEAD
#pragma once

#ifndef __ISA_IDE_H__
#define __ISA_IDE_H__

#include "emu.h"
=======
#ifndef MAME_BUS_ISA_IDE_H
#define MAME_BUS_ISA_IDE_H

#pragma once

>>>>>>> upstream/master
#include "isa.h"
#include "machine/idectrl.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> isa16_ide_device

class isa16_ide_device : public device_t,
	public device_isa16_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	isa16_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	bool is_primary() { return m_is_primary; }
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);
=======
	isa16_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	bool is_primary() { return m_is_primary; }
>>>>>>> upstream/master
	DECLARE_ADDRESS_MAP(map, 16);
	DECLARE_ADDRESS_MAP(alt_map, 8);
	READ8_MEMBER(ide16_alt_r);
	WRITE8_MEMBER(ide16_alt_w);
<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

private:
=======

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

private:
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);

>>>>>>> upstream/master
	// internal state
	bool m_is_primary;
	required_device<ide_controller_device> m_ide;
};


// device type definition
<<<<<<< HEAD
extern const device_type ISA16_IDE;

#endif  /* __ISA_IDE_H__ */
=======
DECLARE_DEVICE_TYPE(ISA16_IDE, isa16_ide_device)

#endif // MAME_BUS_ISA_IDE_H
>>>>>>> upstream/master
