// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * wpcsnd.h - Williams WPC pinball sound
 *
 *  Created on: 4/10/2013
 */

<<<<<<< HEAD
#ifndef WPCSND_H_
#define WPCSND_H_

#include "emu.h"
#include "cpu/m6809/m6809.h"
#include "sound/2151intf.h"
#include "sound/hc55516.h"
#include "sound/dac.h"

#define MCFG_WMS_WPC_SOUND_ADD(_tag, _region) \
	MCFG_DEVICE_ADD(_tag, WPCSND, 0) \
	wpcsnd_device::static_set_gfxregion(*device, _region);
=======
#ifndef MAME_AUDIO_WPCSND_H
#define MAME_AUDIO_WPCSND_H

#pragma once

#include "cpu/m6809/m6809.h"
#include "sound/ym2151.h"
#include "sound/hc55516.h"


#define MCFG_WPC_ROM_REGION(_region) \
	wpcsnd_device::static_set_romregion(*device, _region);
>>>>>>> upstream/master

#define MCFG_WPC_SOUND_REPLY_CALLBACK(_reply) \
	downcast<wpcsnd_device *>(device)->set_reply_callback(DEVCB_##_reply);

<<<<<<< HEAD
class wpcsnd_device : public device_t
{
public:
	// construction/destruction
	wpcsnd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======

class wpcsnd_device : public device_t,
	public device_mixer_interface
{
public:
	// construction/destruction
	wpcsnd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	required_device<cpu_device> m_cpu;
	required_device<ym2151_device> m_ym2151;
	required_device<hc55516_device> m_hc55516;
<<<<<<< HEAD
	required_device<dac_device> m_dac;
	required_memory_bank m_cpubank;
	required_memory_bank m_fixedbank;
	memory_region* m_rom;
=======
	required_memory_bank m_cpubank;
	required_memory_bank m_fixedbank;
	required_memory_region m_rom;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(bg_speech_clock_w);
	DECLARE_WRITE8_MEMBER(bg_speech_digit_w);
	DECLARE_WRITE8_MEMBER(rombank_w);
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER(ym2151_irq_w);
=======
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(latch_r);
	DECLARE_WRITE8_MEMBER(latch_w);
	DECLARE_WRITE8_MEMBER(volume_w);

<<<<<<< HEAD
	void ctrl_w(UINT8 data);
	void data_w(UINT8 data);
	UINT8 ctrl_r();
	UINT8 data_r();

	static void static_set_gfxregion(device_t &device, const char *tag);

	// callbacks
	template<class _reply> void set_reply_callback(_reply reply) { m_reply_cb.set_callback(reply); }

protected:
	// overrides
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

private:
	const char* m_regiontag;
	UINT8 m_latch;
	UINT8 m_reply;
=======
	void ctrl_w(uint8_t data);
	void data_w(uint8_t data);
	uint8_t ctrl_r();
	uint8_t data_r();

	static void static_set_romregion(device_t &device, const char *tag);

	// callbacks
	template <class Reply> void set_reply_callback(Reply &&cb) { m_reply_cb.set_callback(std::forward<Reply>(cb)); }

protected:
	// overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	uint8_t m_latch;
	uint8_t m_reply;
>>>>>>> upstream/master
	bool m_reply_available;

	// callback
	devcb_write_line m_reply_cb;

<<<<<<< HEAD
};

extern const device_type WPCSND;

#endif /* WPCSND_H_ */
=======
	DECLARE_WRITE_LINE_MEMBER(ym2151_irq_w);
};

DECLARE_DEVICE_TYPE(WPCSND, wpcsnd_device)

#endif // MAME_AUDIO_WPCSND_H
>>>>>>> upstream/master
