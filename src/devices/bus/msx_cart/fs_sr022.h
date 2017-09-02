// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_FS_SR022_H
#define __MSX_CART_FS_SR022_H
=======
#ifndef MAME_BUS_MSX_CART_FS_SR022_H
#define MAME_BUS_MSX_CART_FS_SR022_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"


<<<<<<< HEAD
extern const device_type MSX_CART_FS_SR022;


class msx_cart_fs_sr022 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_fs_sr022(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);

private:
	const UINT8 *m_bunsetsu_rom;
	UINT32 m_bunsetsu_address;
};


#endif
=======
DECLARE_DEVICE_TYPE(MSX_CART_FS_SR022, msx_cart_fs_sr022_device)


class msx_cart_fs_sr022_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_fs_sr022_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	const uint8_t *m_bunsetsu_rom;
	uint32_t m_bunsetsu_address;
};


#endif // MAME_BUS_MSX_CART_FS_SR022_H
>>>>>>> upstream/master
