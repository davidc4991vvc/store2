// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
// Lindbergh Sega baseboard

<<<<<<< HEAD
#ifndef SEGABB_H
#define SEGABB_H
=======
#ifndef MAME_MACHINE_SEGABB_H
#define MAME_MACHINE_SEGABB_H

#pragma once
>>>>>>> upstream/master

#include "machine/pci.h"

#define MCFG_SEGA_LINDBERGH_BASEBOARD_ADD(_tag) \
	MCFG_PCI_DEVICE_ADD(_tag, SEGA_LINDBERGH_BASEBOARD, 0x105718c1, 0x10, 0x068000, 0x11db067b)

class sega_lindbergh_baseboard_device : public pci_device {
public:
<<<<<<< HEAD
	sega_lindbergh_baseboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	virtual void device_start();
	virtual void device_reset();
=======
	sega_lindbergh_baseboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	DECLARE_ADDRESS_MAP(map1, 32);
	DECLARE_ADDRESS_MAP(map2, 32);
	DECLARE_ADDRESS_MAP(map3, 32);
};

<<<<<<< HEAD
extern const device_type SEGA_LINDBERGH_BASEBOARD;

#endif
=======
DECLARE_DEVICE_TYPE(SEGA_LINDBERGH_BASEBOARD, sega_lindbergh_baseboard_device)

#endif // MAME_MACHINE_SEGABB_H
>>>>>>> upstream/master
