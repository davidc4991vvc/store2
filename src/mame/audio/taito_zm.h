// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, hap
/***************************************************************************

    Taito Zoom ZSG-2 sound board

***************************************************************************/
<<<<<<< HEAD
=======
#ifndef MAME_AUDIO_TAITO_ZM_H
#define MAME_AUDIO_TAITO_ZM_H

#pragma once
>>>>>>> upstream/master

#include "cpu/mn10200/mn10200.h"
#include "cpu/tms57002/tms57002.h"
#include "sound/zsg2.h"

ADDRESS_MAP_EXTERN(taitozoom_mn_map, 16);

class taito_zoom_device : public device_t

{
public:
<<<<<<< HEAD
	taito_zoom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~taito_zoom_device() {}
=======
	taito_zoom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(sound_irq_w);
	DECLARE_READ16_MEMBER(sound_irq_r);
	DECLARE_WRITE16_MEMBER(reg_data_w);
	DECLARE_WRITE16_MEMBER(reg_address_w);

	DECLARE_READ8_MEMBER(shared_ram_r);
	DECLARE_WRITE8_MEMBER(shared_ram_w);
	DECLARE_READ8_MEMBER(tms_ctrl_r);
	DECLARE_WRITE8_MEMBER(tms_ctrl_w);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

private:
	// inherited devices/pointers
	required_device<mn10200_device> m_soundcpu;
	required_device<zsg2_device> m_zsg2;

	// internal state
<<<<<<< HEAD
	UINT16 m_reg_address;
	UINT8 m_tms_ctrl;
	UINT8* m_snd_shared_ram;
};

extern const device_type TAITO_ZOOM;
=======
	uint16_t m_reg_address;
	uint8_t m_tms_ctrl;
	std::unique_ptr<uint8_t[]> m_snd_shared_ram;
};

DECLARE_DEVICE_TYPE(TAITO_ZOOM, taito_zoom_device)
>>>>>>> upstream/master

MACHINE_CONFIG_EXTERN( taito_zoom_sound );

#define MCFG_TAITO_ZOOM_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, TAITO_ZOOM, 0)
<<<<<<< HEAD
=======

#endif // MAME_AUDIO_TAITO_ZM_H
>>>>>>> upstream/master
