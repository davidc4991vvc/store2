// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/***************************************************************************

    Time Pilot

***************************************************************************/

#include "sound/tc8830f.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class timeplt_state : public driver_device
{
public:
	timeplt_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_tc8830f(*this, "tc8830f"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_colorram(*this, "colorram"),
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_spriteram2(*this, "spriteram2")
	{ }

	required_device<cpu_device> m_maincpu;
	optional_device<tc8830f_device> m_tc8830f;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_spriteram2;
=======
	required_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_spriteram2;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t  *m_bg_tilemap;

	/* misc */
<<<<<<< HEAD
	UINT8    m_nmi_enable;
	bool    m_video_enable;

	/* common */
	DECLARE_WRITE8_MEMBER(coincounter_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(colorram_w);
	DECLARE_WRITE8_MEMBER(flipscreen_w);
	DECLARE_READ8_MEMBER(scanline_r);

	/* all but psurge */
	DECLARE_WRITE8_MEMBER(nmi_enable_w);
	DECLARE_WRITE8_MEMBER(video_enable_w);
=======
	uint8_t    m_nmi_enable;
	bool    m_video_enable;

	/* common */
	DECLARE_WRITE8_MEMBER(mainlatch_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_2_w);
	DECLARE_WRITE8_MEMBER(videoram_w);
	DECLARE_WRITE8_MEMBER(colorram_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
	DECLARE_READ8_MEMBER(scanline_r);

	/* all but psurge */
	DECLARE_WRITE_LINE_MEMBER(nmi_enable_w);
	DECLARE_WRITE_LINE_MEMBER(video_enable_w);
>>>>>>> upstream/master

	/* psurge */
	DECLARE_READ8_MEMBER(psurge_protection_r);

	/* chkun */
	DECLARE_CUSTOM_INPUT_MEMBER(chkun_hopper_status_r);
	DECLARE_WRITE8_MEMBER(chkun_sound_w);

	TILE_GET_INFO_MEMBER(get_tile_info);
	TILE_GET_INFO_MEMBER(get_chkun_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
>>>>>>> upstream/master
	DECLARE_PALETTE_INIT(timeplt);
	DECLARE_VIDEO_START(chkun);
	DECLARE_VIDEO_START(psurge);

<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );

	INTERRUPT_GEN_MEMBER(interrupt);
};
