// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SNS_SUFAMI_H
#define __SNS_SUFAMI_H
=======
#ifndef MAME_BUS_SNES_SUFAMI_H
#define MAME_BUS_SNES_SUFAMI_H

#pragma once
>>>>>>> upstream/master

#include "snes_slot.h"
#include "rom.h"


// ======================> sns_rom_sufami_device

class sns_rom_sufami_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_sufami_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);
=======
	sns_rom_sufami_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<sns_sufami_cart_slot_device> m_slot1;
	required_device<sns_sufami_cart_slot_device> m_slot2;
};

// ======================> sns_rom_strom_device

class sns_rom_strom_device : public sns_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_rom_strom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
=======
	sns_rom_strom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// additional reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type SNS_LOROM_SUFAMI;
extern const device_type SNS_STROM;

#endif
=======
DECLARE_DEVICE_TYPE(SNS_LOROM_SUFAMI, sns_rom_sufami_device)
DECLARE_DEVICE_TYPE(SNS_STROM,        sns_rom_strom_device)

#endif // MAME_BUS_SNES_SUFAMI_H
>>>>>>> upstream/master
