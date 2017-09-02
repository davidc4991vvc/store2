// license:BSD-3-Clause
// copyright-holders:Olivier Galibert

// Namco system 12/23 settings device

<<<<<<< HEAD
#ifndef __NAMCO_SETTINGS_H__
#define __NAMCO_SETTINGS_H__
=======
#ifndef MAME_MACHINE_NAMCO_SETTINGS_H
#define MAME_MACHINE_NAMCO_SETTINGS_H

#pragma once
>>>>>>> upstream/master

#define MCFG_NAMCO_SETTINGS_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, NAMCO_SETTINGS, 0)

class namco_settings_device : public device_t {
public:
<<<<<<< HEAD
	namco_settings_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	namco_settings_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE_LINE_MEMBER( ce_w );
	DECLARE_WRITE_LINE_MEMBER( clk_w );
	DECLARE_WRITE_LINE_MEMBER( data_w );

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	int ce, clk, data;
	int cur_bit;
<<<<<<< HEAD
	UINT8 adr, value;
};

extern const device_type NAMCO_SETTINGS;

#endif
=======
	uint8_t adr, value;
};

DECLARE_DEVICE_TYPE(NAMCO_SETTINGS, namco_settings_device)

#endif // MAME_MACHINE_NAMCO_SETTINGS_H
>>>>>>> upstream/master
