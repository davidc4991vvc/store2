// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
<<<<<<< HEAD
#pragma once

#ifndef __Z88_FLASH_H__
#define __Z88_FLASH_H__

#include "emu.h"
=======
#ifndef MAME_BUS_Z88_FLASH_H
#define MAME_BUS_Z88_FLASH_H

#pragma once

>>>>>>> upstream/master
#include "z88.h"
#include "machine/intelfsh.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> z88_1024k_flash_device

class z88_1024k_flash_device : public device_t,
								public device_z88cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	z88_1024k_flash_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	// z88cart_interface overrides
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);
	virtual UINT8* get_cart_base();
	virtual UINT32 get_cart_size() { return 0x100000; }
=======
	z88_1024k_flash_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;

	// z88cart_interface overrides
	virtual DECLARE_READ8_MEMBER(read) override;
	virtual DECLARE_WRITE8_MEMBER(write) override;
	virtual uint8_t* get_cart_base() override;
	virtual uint32_t get_cart_size() override { return 0x100000; }
>>>>>>> upstream/master

private:
	required_device<intelfsh8_device> m_flash;
};

// device type definition
<<<<<<< HEAD
extern const device_type Z88_1024K_FLASH;


#endif  /* __Z88_FLASH_H__ */
=======
DECLARE_DEVICE_TYPE(Z88_1024K_FLASH, z88_1024k_flash_device)

#endif // MAME_BUS_Z88_FLASH_H
>>>>>>> upstream/master
