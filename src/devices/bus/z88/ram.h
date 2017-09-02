// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __Z88_RAM_H__
#define __Z88_RAM_H__

#include "emu.h"
=======
#ifndef MAME_BUS_Z88_RAM_H
#define MAME_BUS_Z88_RAM_H

#pragma once

>>>>>>> upstream/master
#include "z88.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> z88_32k_ram_device

class z88_32k_ram_device : public device_t,
							public device_z88cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	z88_32k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	z88_32k_ram_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();

	// z88cart_interface overrides
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);
	virtual UINT8* get_cart_base();
	virtual UINT32 get_cart_size() { return 0x8000; }

protected:
	// internal state
	UINT8 *     m_ram;
=======
	z88_32k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	z88_32k_ram_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	// z88cart_interface overrides
	virtual DECLARE_READ8_MEMBER(read) override;
	virtual DECLARE_WRITE8_MEMBER(write) override;
	virtual uint8_t* get_cart_base() override;
	virtual uint32_t get_cart_size() override { return 0x8000; }

protected:
	// internal state
	uint8_t *     m_ram;
>>>>>>> upstream/master
};

// ======================> z88_128k_ram_device

class z88_128k_ram_device : public z88_32k_ram_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	z88_128k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// z88cart_interface overrides
	virtual UINT32 get_cart_size() { return 0x20000; }
=======
	z88_128k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// z88cart_interface overrides
	virtual uint32_t get_cart_size() override { return 0x20000; }
>>>>>>> upstream/master
};

// ======================> z88_512k_ram_device

class z88_512k_ram_device : public z88_32k_ram_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	z88_512k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// z88cart_interface overrides
	virtual UINT32 get_cart_size() { return 0x80000; }
=======
	z88_512k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// z88cart_interface overrides
	virtual uint32_t get_cart_size() override { return 0x80000; }
>>>>>>> upstream/master
};

// ======================> z88_1024k_ram_device

class z88_1024k_ram_device : public z88_32k_ram_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	z88_1024k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// z88cart_interface overrides
	virtual UINT32 get_cart_size() { return 0x100000; }
};

// device type definition
extern const device_type Z88_32K_RAM;
extern const device_type Z88_128K_RAM;
extern const device_type Z88_512K_RAM;
extern const device_type Z88_1024K_RAM;

#endif  /* __Z88_RAM_H__ */
=======
	z88_1024k_ram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// z88cart_interface overrides
	virtual uint32_t get_cart_size() override { return 0x100000; }
};

// device type definition
DECLARE_DEVICE_TYPE(Z88_32K_RAM,   z88_32k_ram_device)
DECLARE_DEVICE_TYPE(Z88_128K_RAM,  z88_128k_ram_device)
DECLARE_DEVICE_TYPE(Z88_512K_RAM,  z88_512k_ram_device)
DECLARE_DEVICE_TYPE(Z88_1024K_RAM, z88_1024k_ram_device)

#endif // MAME_BUS_Z88_RAM_H
>>>>>>> upstream/master
