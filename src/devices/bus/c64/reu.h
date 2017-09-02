// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 1700/1750/1764 RAM Expansion Unit emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __REU__
#define __REU__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_REU_H
#define MAME_BUS_C64_REU_H

#pragma once


>>>>>>> upstream/master
#include "bus/generic/slot.h"
#include "bus/generic/carts.h"
#include "exp.h"
#include "machine/mos8726.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_reu_cartridge_device

class c64_reu_cartridge_device : public device_t,
									public device_c64_expansion_card_interface
{
<<<<<<< HEAD
public:
	// construction/destruction
	c64_reu_cartridge_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, int jp1, size_t ram_size, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

=======
>>>>>>> upstream/master
protected:
	enum
	{
		TYPE_1700,
		TYPE_1750,
		TYPE_1764
	};

<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2);

	required_device<mos8726_device> m_dmac;
	required_device<generic_slot_device> m_eprom;
	optional_shared_ptr<UINT8> m_ram;
=======
	// construction/destruction
	c64_reu_cartridge_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant, int jp1, size_t ram_size);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_c64_expansion_card_interface overrides
	virtual uint8_t c64_cd_r(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, uint8_t data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

	required_device<mos8726_device> m_dmac;
	required_device<generic_slot_device> m_eprom;
	optional_shared_ptr<uint8_t> m_ram;
>>>>>>> upstream/master

	int m_variant;
	int m_jp1;
	size_t m_ram_size;
};


// ======================> c64_reu1700_cartridge_device

class c64_reu1700_cartridge_device :  public c64_reu_cartridge_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_reu1700_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c64_reu1700_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> c64_reu1750_cartridge_device

class c64_reu1750_cartridge_device :  public c64_reu_cartridge_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_reu1750_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c64_reu1750_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

// ======================> c64_reu1700_cartridge_device

class c64_reu1764_cartridge_device :  public c64_reu_cartridge_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_reu1764_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	c64_reu1764_cartridge_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type C64_REU1700;
extern const device_type C64_REU1750;
extern const device_type C64_REU1764;



#endif
=======
DECLARE_DEVICE_TYPE(C64_REU1700, c64_reu1700_cartridge_device)
DECLARE_DEVICE_TYPE(C64_REU1750, c64_reu1750_cartridge_device)
DECLARE_DEVICE_TYPE(C64_REU1764, c64_reu1764_cartridge_device)


#endif // MAME_BUS_C64_REU_H
>>>>>>> upstream/master
