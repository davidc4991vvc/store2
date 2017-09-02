// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
<<<<<<< HEAD
#include "includes/kaneko16.h"
=======

#include "video/kan_pand.h"
#include "screen.h"
>>>>>>> upstream/master

class galpanic_state : public driver_device
{
public:
	galpanic_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_bgvideoram(*this, "bgvideoram"),
			m_fgvideoram(*this, "fgvideoram"),
<<<<<<< HEAD
			m_spriteram(*this, "spriteram"),
=======
>>>>>>> upstream/master
			m_gfxdecode(*this, "gfxdecode"),
			m_screen(*this, "screen"),
			m_palette(*this, "palette"),
			m_pandora(*this, "pandora")
	{ }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_bgvideoram;
	required_shared_ptr<UINT16> m_fgvideoram;
	bitmap_ind16 m_bitmap;
	bitmap_ind16 m_sprites_bitmap;
	optional_shared_ptr<UINT16> m_spriteram;
=======
	required_shared_ptr<uint16_t> m_bgvideoram;
	required_shared_ptr<uint16_t> m_fgvideoram;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	required_device<kaneko_pandora_device> m_pandora;

<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER(galpanic_6295_bankswitch_w);
	DECLARE_WRITE16_MEMBER(galpanic_coin_w);

	DECLARE_VIDEO_START(galpanic);
	DECLARE_PALETTE_INIT(galpanic);
	UINT32 screen_update_galpanic(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_galpanic(screen_device &screen, bool state);
	TIMER_DEVICE_CALLBACK_MEMBER(galpanic_scanline);
	void draw_fgbitmap(bitmap_ind16 &bitmap, const rectangle &cliprect);
	/*----------- defined in video/galpanic.c -----------*/
	DECLARE_WRITE16_MEMBER( galpanic_bgvideoram_w );
=======
	bitmap_ind16 m_bitmap;

	DECLARE_WRITE16_MEMBER(m6295_bankswitch_w);
	DECLARE_WRITE16_MEMBER(coin_w);
	DECLARE_WRITE16_MEMBER(bgvideoram_w);

	virtual void machine_start() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(galpanic);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank);
	TIMER_DEVICE_CALLBACK_MEMBER(scanline);
	void draw_fgbitmap(bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
};
