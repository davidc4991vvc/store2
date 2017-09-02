// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __DMV_RAM_H__
#define __DMV_RAM_H__

#include "emu.h"
=======
#ifndef MAME_BUS_DMV_RAM_H
#define MAME_BUS_DMV_RAM_H

#pragma once

>>>>>>> upstream/master
#include "dmvbus.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================>

<<<<<<< HEAD
class dmv_ram_device :
		public device_t,
		public device_dmvslot_interface
{
public:
	// construction/destruction
	dmv_ram_device(const machine_config &mconfig, device_type type, UINT32 size, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

protected:
	// device-level overrides
	virtual void device_start();

	// dmvcart_interface overrides
	virtual void ram_read(UINT8 cas, offs_t offset, UINT8 &data);
	virtual void ram_write(UINT8 cas, offs_t offset, UINT8 data);

private:
	UINT8 *     m_ram;
	UINT8       m_size;
};


class dmv_k200_device :
		public dmv_ram_device
{
public:
	// construction/destruction
	dmv_k200_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


class dmv_k202_device :
		public dmv_ram_device
{
public:
	// construction/destruction
	dmv_k202_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


class dmv_k208_device :
		public dmv_ram_device
{
public:
	// construction/destruction
	dmv_k208_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class dmv_ram_device_base :
		public device_t,
		public device_dmvslot_interface
{
protected:
	// construction/destruction
	dmv_ram_device_base(const machine_config &mconfig, device_type type, uint32_t size, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	// dmvcart_interface overrides
	virtual void ram_read(uint8_t cas, offs_t offset, uint8_t &data) override;
	virtual void ram_write(uint8_t cas, offs_t offset, uint8_t data) override;

private:
	uint8_t *     m_ram;
	uint8_t       m_size;
};


class dmv_k200_device : public dmv_ram_device_base
{
public:
	// construction/destruction
	dmv_k200_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


class dmv_k202_device : public dmv_ram_device_base
{
public:
	// construction/destruction
	dmv_k202_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


class dmv_k208_device : public dmv_ram_device_base
{
public:
	// construction/destruction
	dmv_k208_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type DMV_K200;
extern const device_type DMV_K202;
extern const device_type DMV_K208;

#endif  /* __DMV_RAM_H__ */
=======
DECLARE_DEVICE_TYPE(DMV_K200, dmv_k200_device)
DECLARE_DEVICE_TYPE(DMV_K202, dmv_k202_device)
DECLARE_DEVICE_TYPE(DMV_K208, dmv_k208_device)

#endif // MAME_BUS_DMV_RAM_H
>>>>>>> upstream/master
