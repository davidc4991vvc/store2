// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi
/******************************************************************************

    Data East Side Pocket hardware

******************************************************************************/

<<<<<<< HEAD
=======
#include "machine/gen_latch.h"

>>>>>>> upstream/master
class sidepckt_state : public driver_device
{
public:
	sidepckt_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_spriteram(*this, "spriteram")
	{ }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_spriteram;

	tilemap_t *m_bg_tilemap;
	const UINT8* m_prot_table[3];
	UINT8 m_i8751_return;
	UINT8 m_current_ptr;
	UINT8 m_current_table;
	UINT8 m_in_math;
	UINT8 m_math_param;

	DECLARE_WRITE8_MEMBER(sound_cpu_command_w);
=======
	required_device<generic_latch_8_device> m_soundlatch;

	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_spriteram;

	tilemap_t *m_bg_tilemap;
	const uint8_t* m_prot_table[3];
	uint8_t m_i8751_return;
	uint8_t m_current_ptr;
	uint8_t m_current_table;
	uint8_t m_in_math;
	uint8_t m_math_param;
	uint8_t m_scroll_y;

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(i8751_r);
	DECLARE_WRITE8_MEMBER(i8751_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(colorram_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(flipscreen_w);
=======
	DECLARE_READ8_MEMBER(scroll_y_r);
	DECLARE_WRITE8_MEMBER(scroll_y_w);
>>>>>>> upstream/master

	DECLARE_DRIVER_INIT(sidepckt);
	DECLARE_DRIVER_INIT(sidepcktj);

	TILE_GET_INFO_MEMBER(get_tile_info);

<<<<<<< HEAD
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(sidepckt);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(sidepckt);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites(bitmap_ind16 &bitmap,const rectangle &cliprect);
};
