// license:BSD-3-Clause
// copyright-holders:Pierpaolo Prazzoli, David Haywood
/*************************************************************************

    Goal! '92

*************************************************************************/
<<<<<<< HEAD
#include "sound/msm5205.h"
=======

#include "machine/gen_latch.h"
#include "sound/msm5205.h"

>>>>>>> upstream/master
class goal92_state : public driver_device
{
public:
	goal92_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_bg_data(*this, "bg_data"),
		m_fg_data(*this, "fg_data"),
		m_tx_data(*this, "tx_data"),
		m_spriteram(*this, "spriteram"),
		m_scrollram(*this, "scrollram"),
<<<<<<< HEAD
		m_audiocpu(*this, "audiocpu"),
		m_maincpu(*this, "maincpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_shared_ptr<UINT16> m_bg_data;
	required_shared_ptr<UINT16> m_fg_data;
	required_shared_ptr<UINT16> m_tx_data;
	required_shared_ptr<UINT16> m_spriteram;
	required_shared_ptr<UINT16> m_scrollram;
	UINT16 *    m_buffered_spriteram;
=======
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch") { }

	/* memory pointers */
	required_shared_ptr<uint16_t> m_bg_data;
	required_shared_ptr<uint16_t> m_fg_data;
	required_shared_ptr<uint16_t> m_tx_data;
	required_shared_ptr<uint16_t> m_spriteram;
	required_shared_ptr<uint16_t> m_scrollram;
	std::unique_ptr<uint16_t[]>    m_buffered_spriteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t     *m_bg_layer;
	tilemap_t     *m_fg_layer;
	tilemap_t     *m_tx_layer;
<<<<<<< HEAD
	UINT16      m_fg_bank;
=======
	uint16_t      m_fg_bank;
>>>>>>> upstream/master

	/* misc */
	int         m_msm5205next;
	int         m_adpcm_toggle;

	/* devices */
<<<<<<< HEAD
	required_device<cpu_device> m_audiocpu;
=======
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<msm5205_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	required_device<generic_latch_8_device> m_soundlatch;

>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(goal92_sound_command_w);
	DECLARE_READ16_MEMBER(goal92_inputs_r);
	DECLARE_WRITE8_MEMBER(adpcm_data_w);
	DECLARE_READ16_MEMBER(goal92_fg_bank_r);
	DECLARE_WRITE16_MEMBER(goal92_fg_bank_w);
	DECLARE_WRITE16_MEMBER(goal92_text_w);
	DECLARE_WRITE16_MEMBER(goal92_background_w);
	DECLARE_WRITE16_MEMBER(goal92_foreground_w);
	DECLARE_WRITE8_MEMBER(adpcm_control_w);
	TILE_GET_INFO_MEMBER(get_text_tile_info);
	TILE_GET_INFO_MEMBER(get_back_tile_info);
	TILE_GET_INFO_MEMBER(get_fore_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_goal92(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_goal92(screen_device &screen, bool state);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, int pri );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	DECLARE_WRITE_LINE_MEMBER(goal92_adpcm_int);
	required_device<cpu_device> m_maincpu;
	required_device<msm5205_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update_goal92(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank_goal92);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, int pri );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	DECLARE_WRITE_LINE_MEMBER(goal92_adpcm_int);
>>>>>>> upstream/master
};
