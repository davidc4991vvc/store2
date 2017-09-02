<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Stefan Jokisch
/*************************************************************************

    Atari Pool Shark hardware

*************************************************************************/

<<<<<<< HEAD
=======
#include "machine/watchdog.h"
>>>>>>> upstream/master
#include "sound/discrete.h"

/* Discrete Sound Input Nodes */

class poolshrk_state : public driver_device
{
public:
	poolshrk_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
=======
		m_watchdog(*this, "watchdog"),
>>>>>>> upstream/master
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_discrete(*this, "discrete"),
		m_playfield_ram(*this, "playfield_ram"),
		m_hpos_ram(*this, "hpos_ram"),
		m_vpos_ram(*this, "vpos_ram") { }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
=======
	required_device<watchdog_timer_device> m_watchdog;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<discrete_device> m_discrete;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_playfield_ram;
	required_shared_ptr<UINT8> m_hpos_ram;
	required_shared_ptr<UINT8> m_vpos_ram;
=======
	required_shared_ptr<uint8_t> m_playfield_ram;
	required_shared_ptr<uint8_t> m_hpos_ram;
	required_shared_ptr<uint8_t> m_vpos_ram;
>>>>>>> upstream/master

	tilemap_t* m_bg_tilemap;
	int m_da_latch;

	DECLARE_WRITE8_MEMBER(da_latch_w);
	DECLARE_WRITE8_MEMBER(led_w);
	DECLARE_WRITE8_MEMBER(watchdog_w);
	DECLARE_READ8_MEMBER(input_r);
	DECLARE_READ8_MEMBER(irq_reset_r);
	DECLARE_WRITE8_MEMBER(scratch_sound_w);
	DECLARE_WRITE8_MEMBER(score_sound_w);
	DECLARE_WRITE8_MEMBER(click_sound_w);
	DECLARE_WRITE8_MEMBER(bump_sound_w);

	TILE_GET_INFO_MEMBER(get_tile_info);

	DECLARE_DRIVER_INIT(poolshrk);
<<<<<<< HEAD
	virtual void video_start();
	DECLARE_PALETTE_INIT(poolshrk);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(poolshrk);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
};


/*----------- defined in audio/poolshrk.c -----------*/
DISCRETE_SOUND_EXTERN( poolshrk );
