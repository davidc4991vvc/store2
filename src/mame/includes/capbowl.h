// license:BSD-3-Clause
// copyright-holders:Zsolt Vasvari
/*************************************************************************

    Coors Light Bowling/Bowl-O-Rama hardware

*************************************************************************/
<<<<<<< HEAD

#include "machine/nvram.h"
#include "video/tms34061.h"
=======
#ifndef MAME_INCLUDES_CAPBOWL_H
#define MAME_INCLUDES_CAPBOWL_H

#pragma once

#include "machine/gen_latch.h"
#include "machine/nvram.h"
#include "machine/watchdog.h"
#include "video/tms34061.h"
#include "screen.h"
>>>>>>> upstream/master

class capbowl_state : public driver_device
{
public:
	enum
	{
		TIMER_UPDATE
	};

	capbowl_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_audiocpu(*this, "audiocpu"),
		m_tms34061(*this, "tms34061"),
		m_screen(*this, "screen"),
=======
		m_watchdog(*this, "watchdog"),
		m_audiocpu(*this, "audiocpu"),
		m_tms34061(*this, "tms34061"),
		m_screen(*this, "screen"),
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_rowaddress(*this, "rowaddress") { }

	/* devices */
	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
	required_device<cpu_device> m_audiocpu;
	required_device<tms34061_device> m_tms34061;
	required_device<screen_device> m_screen;

	/* memory pointers */
	required_shared_ptr<UINT8> m_rowaddress;
=======
	required_device<watchdog_timer_device> m_watchdog;
	required_device<cpu_device> m_audiocpu;
	required_device<tms34061_device> m_tms34061;
	required_device<screen_device> m_screen;
	required_device<generic_latch_8_device> m_soundlatch;

	/* memory pointers */
	required_shared_ptr<uint8_t> m_rowaddress;
>>>>>>> upstream/master

	/* video-related */
	offs_t m_blitter_addr;

	/* input-related */
<<<<<<< HEAD
	UINT8 m_last_trackball_val[2];
=======
	uint8_t m_last_trackball_val[2];
>>>>>>> upstream/master

	emu_timer *m_update_timer;

	// common
	DECLARE_READ8_MEMBER(track_0_r);
	DECLARE_READ8_MEMBER(track_1_r);
	DECLARE_WRITE8_MEMBER(track_reset_w);
	DECLARE_WRITE8_MEMBER(sndcmd_w);
	DECLARE_WRITE8_MEMBER(tms34061_w);
	DECLARE_READ8_MEMBER(tms34061_r);

	// capbowl specific
	DECLARE_WRITE8_MEMBER(capbowl_rom_select_w);

	// bowlrama specific
	DECLARE_WRITE8_MEMBER(bowlrama_blitter_w);
	DECLARE_READ8_MEMBER(bowlrama_blitter_r);

	DECLARE_DRIVER_INIT(capbowl);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
>>>>>>> upstream/master

	INTERRUPT_GEN_MEMBER(interrupt);
	TIMER_CALLBACK_MEMBER(update);

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	inline rgb_t pen_for_pixel( UINT8 *src, UINT8 pix );

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
};
=======
	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	inline rgb_t pen_for_pixel( uint8_t const *src, uint8_t pix );

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
};

#endif // MAME_INCLUDES_CAPBOWL_H
>>>>>>> upstream/master
