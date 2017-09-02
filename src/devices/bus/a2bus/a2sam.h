// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2sam.h

    Implementation of the S.A.M. "Software Automated Mouth" card

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_SAM__
#define __A2BUS_SAM__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2SAM_H
#define MAME_BUS_A2BUS_A2SAM_H

#pragma once

>>>>>>> upstream/master
#include "a2bus.h"
#include "sound/dac.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_sam_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	a2bus_sam_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	a2bus_sam_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	required_device<dac_device> m_dac;

protected:
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual bool take_c800();
=======
	a2bus_sam_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// overrides of standard a2bus slot functions
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual bool take_c800() override;

	required_device<dac_byte_interface> m_dac;
>>>>>>> upstream/master
};

// device type definition
extern const device_type A2BUS_SAM;

<<<<<<< HEAD
#endif /* __A2BUS_SAM__ */
=======
#endif // MAME_BUS_A2BUS_A2SAM_H
>>>>>>> upstream/master
