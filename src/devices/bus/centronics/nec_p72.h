// license:BSD-3-Clause
// copyright-holders:Ramiro Polla

<<<<<<< HEAD
#pragma once

#ifndef __NEC_P72__
#define __NEC_P72__

#include "emu.h"
=======
#ifndef MAME_BUS_CENTRONICS_NEC_P72_H
#define MAME_BUS_CENTRONICS_NEC_P72_H

#pragma once

>>>>>>> upstream/master
#include "ctronics.h"
#include "cpu/nec/nec.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> nec_p72_t

class nec_p72_t : public device_t,
=======
// ======================> nec_p72_device

class nec_p72_device : public device_t,
>>>>>>> upstream/master
					public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	nec_p72_t(const machine_config &mconfig, const char *tag,
				device_t *owner, UINT32 clock);
	nec_p72_t(const machine_config &mconfig, device_type type,
				const char *name, const char *tag, device_t *owner,
				UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
=======
	nec_p72_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	nec_p72_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<cpu_device> m_maincpu;
};

// device type definition
<<<<<<< HEAD
extern const device_type NEC_P72;

#endif
=======
DECLARE_DEVICE_TYPE(NEC_P72, nec_p72_device)

#endif // MAME_BUS_CENTRONICS_NEC_P72_H
>>>>>>> upstream/master
