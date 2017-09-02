// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __PCE_ROM_H
#define __PCE_ROM_H
=======
#ifndef MAME_BUS_PCE_PCE_ROM_H
#define MAME_BUS_PCE_PCE_ROM_H

#pragma once
>>>>>>> upstream/master

#include "pce_slot.h"


// ======================> pce_rom_device

class pce_rom_device : public device_t,
						public device_pce_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	pce_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	pce_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() {}
	virtual void device_reset() {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
=======
	pce_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;

protected:
	pce_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override { }
	virtual void device_reset() override { }
>>>>>>> upstream/master
};

// ======================> pce_cdsys3_device

class pce_cdsys3_device : public pce_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	pce_cdsys3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	pce_cdsys3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
>>>>>>> upstream/master
};


// ======================> pce_populous_device

class pce_populous_device : public pce_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	pce_populous_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
	pce_populous_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;
>>>>>>> upstream/master
};


// ======================> pce_sf2_device

class pce_sf2_device : public pce_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	pce_sf2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

private:
	UINT8 m_bank_base;
};



// device type definition
extern const device_type PCE_ROM_STD;
extern const device_type PCE_ROM_CDSYS3;
extern const device_type PCE_ROM_POPULOUS;
extern const device_type PCE_ROM_SF2;



#endif
=======
	pce_sf2_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank_base;
};


// device type definition
DECLARE_DEVICE_TYPE(PCE_ROM_STD,      pce_rom_device)
DECLARE_DEVICE_TYPE(PCE_ROM_CDSYS3,   pce_cdsys3_device)
DECLARE_DEVICE_TYPE(PCE_ROM_POPULOUS, pce_populous_device)
DECLARE_DEVICE_TYPE(PCE_ROM_SF2,      pce_sf2_device)

#endif // MAME_BUS_PCE_PCE_ROM_H
>>>>>>> upstream/master
