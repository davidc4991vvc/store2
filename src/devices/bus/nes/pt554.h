// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_PT554_H
#define __NES_PT554_H
=======
#ifndef MAME_BUS_NES_PT554_H
#define MAME_BUS_NES_PT554_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_bandai_pt554_device

class nes_bandai_pt554_device : public nes_cnrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_bandai_pt554_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual DECLARE_WRITE8_MEMBER(write_m);
=======
	nes_bandai_pt554_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

protected:
	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<samples_device> m_samples;
};


<<<<<<< HEAD


// device type definition
extern const device_type NES_BANDAI_PT554;

#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(NES_BANDAI_PT554, nes_bandai_pt554_device)

#endif // MAME_BUS_NES_PT554_H
>>>>>>> upstream/master
