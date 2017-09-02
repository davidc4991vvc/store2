// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    TIKI-100 8/16 8088/8087 expansion card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __TIKI100_8088__
#define __TIKI100_8088__

#include "emu.h"
=======
#ifndef MAME_BUS_TIKI100_8088_H
#define MAME_BUS_TIKI100_8088_H

#pragma once

>>>>>>> upstream/master
#include "bus/tiki100/exp.h"
#include "cpu/i86/i86.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> tiki100_8088_t

class tiki100_8088_t : public device_t,
=======
// ======================> tiki100_8088_device

class tiki100_8088_device : public device_t,
>>>>>>> upstream/master
						public device_tiki100bus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	tiki100_8088_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	tiki100_8088_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE8_MEMBER( write );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_tiki100bus_card_interface overrides
	virtual UINT8 iorq_r(address_space &space, offs_t offset, UINT8 data);
	virtual void iorq_w(address_space &space, offs_t offset, UINT8 data);
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_tiki100bus_card_interface overrides
	virtual uint8_t iorq_r(address_space &space, offs_t offset, uint8_t data) override;
	virtual void iorq_w(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

private:
	required_device<i8088_cpu_device> m_maincpu;

<<<<<<< HEAD
	UINT8 m_data;
=======
	uint8_t m_data;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type TIKI100_8088;


#endif
=======
DECLARE_DEVICE_TYPE(TIKI100_8088, tiki100_8088_device)

#endif // MAME_BUS_TIKI100_8088_H
>>>>>>> upstream/master
