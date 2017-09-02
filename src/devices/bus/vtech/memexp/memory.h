// license:GPL-2.0+
// copyright-holders:Dirk Best
/***************************************************************************

    VTech Laser/VZ Memory Expansions

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VTECH_MEMEXP_MEMORY__
#define __VTECH_MEMEXP_MEMORY__

#include "emu.h"
=======
#ifndef MAME_BUS_VTECH_MEMEXP_MEMORY_H
#define MAME_BUS_VTECH_MEMEXP_MEMORY_H

#pragma once

>>>>>>> upstream/master
#include "memexp.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> laser110_16k_device

class laser110_16k_device : public device_t, public device_memexp_interface
{
public:
	// construction/destruction
	laser110_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();

private:
	std::vector<UINT8> m_ram;
};

// ======================> laser210_16k_device

class laser210_16k_device : public device_t, public device_memexp_interface
{
public:
	// construction/destruction
	laser210_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();

private:
	std::vector<UINT8> m_ram;
};

// ======================> laser310_16k_device

class laser310_16k_device : public device_t, public device_memexp_interface
{
public:
	// construction/destruction
	laser310_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();

private:
	std::vector<UINT8> m_ram;
};

// ======================> laser_64k_device

class laser_64k_device : public device_t, public device_memexp_interface
{
public:
	// construction/destruction
	laser_64k_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
// ======================> vtech_laser110_16k_device

class vtech_laser110_16k_device : public device_t, public device_vtech_memexp_interface
{
public:
	// construction/destruction
	vtech_laser110_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	std::vector<uint8_t> m_ram;
};

// ======================> vtech_laser210_16k_device

class vtech_laser210_16k_device : public device_t, public device_vtech_memexp_interface
{
public:
	// construction/destruction
	vtech_laser210_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	std::vector<uint8_t> m_ram;
};

// ======================> vtech_laser310_16k_device

class vtech_laser310_16k_device : public device_t, public device_vtech_memexp_interface
{
public:
	// construction/destruction
	vtech_laser310_16k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	std::vector<uint8_t> m_ram;
};

// ======================> vtech_laser_64k_device

class vtech_laser_64k_device : public device_t, public device_vtech_memexp_interface
{
public:
	// construction/destruction
	vtech_laser_64k_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( bankswitch_w );

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

private:
	std::vector<UINT8> m_ram;
};

// device type definition
extern const device_type LASER110_16K;
extern const device_type LASER210_16K;
extern const device_type LASER310_16K;
extern const device_type LASER_64K;

#endif // __VTECH_MEMEXP_MEMORY__
=======
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	std::vector<uint8_t> m_ram;
};

// device type definition
DECLARE_DEVICE_TYPE(VTECH_LASER110_16K, vtech_laser110_16k_device)
DECLARE_DEVICE_TYPE(VTECH_LASER210_16K, vtech_laser210_16k_device)
DECLARE_DEVICE_TYPE(VTECH_LASER310_16K, vtech_laser310_16k_device)
DECLARE_DEVICE_TYPE(VTECH_LASER_64K,    vtech_laser_64k_device)

#endif // MAME_BUS_VTECH_MEMEXP_MEMORY_H
>>>>>>> upstream/master
