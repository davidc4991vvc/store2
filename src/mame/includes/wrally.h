// license:BSD-3-Clause
// copyright-holders:Manuel Abadia, Mike Coates, Nicola Salmoria, Miguel Angel Horna
<<<<<<< HEAD
class wrally_state : public driver_device
{
public:
	wrally_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
=======
#ifndef MAME_INCLUDES_WRALLY_H
#define MAME_INCLUDES_WRALLY_H

#pragma once

class wrally_state : public driver_device
{
public:
	wrally_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
>>>>>>> upstream/master
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_videoram(*this, "videoram"),
		m_vregs(*this, "vregs"),
		m_spriteram(*this, "spriteram"),
<<<<<<< HEAD
		m_shareram(*this, "shareram") { }

	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	required_shared_ptr<UINT16> m_videoram;
	required_shared_ptr<UINT16> m_vregs;
	required_shared_ptr<UINT16> m_spriteram;
	required_shared_ptr<UINT16> m_shareram;

	tilemap_t *m_pant[2];

	DECLARE_READ8_MEMBER(dallas_share_r);
	DECLARE_WRITE8_MEMBER(dallas_share_w);
	DECLARE_WRITE16_MEMBER(vram_w);
	DECLARE_WRITE16_MEMBER(flipscreen_w);
	DECLARE_WRITE16_MEMBER(okim6295_bankswitch_w);
	DECLARE_WRITE16_MEMBER(wrally_coin_counter_w);
	DECLARE_WRITE16_MEMBER(wrally_coin_lockout_w);
=======
		m_shareram(*this, "shareram"),
		m_pant{ nullptr, nullptr }
	{
	}

	DECLARE_READ8_MEMBER(shareram_r);
	DECLARE_WRITE8_MEMBER(shareram_w);
	DECLARE_WRITE16_MEMBER(vram_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
	DECLARE_WRITE16_MEMBER(okim6295_bankswitch_w);
	DECLARE_WRITE_LINE_MEMBER(coin1_counter_w);
	DECLARE_WRITE_LINE_MEMBER(coin2_counter_w);
	DECLARE_WRITE_LINE_MEMBER(coin1_lockout_w);
	DECLARE_WRITE_LINE_MEMBER(coin2_lockout_w);
>>>>>>> upstream/master

	TILE_GET_INFO_MEMBER(get_tile_info_screen0);
	TILE_GET_INFO_MEMBER(get_tile_info_screen1);

<<<<<<< HEAD
	virtual void video_start();

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int priority);
};
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

protected:
	virtual void machine_start() override;
	virtual void video_start() override;

	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int priority);

private:
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	required_shared_ptr<uint16_t> m_videoram;
	required_shared_ptr<uint16_t> m_vregs;
	required_shared_ptr<uint16_t> m_spriteram;
	required_shared_ptr<uint16_t> m_shareram;

	tilemap_t *m_pant[2];
};

#endif // MAME_INCLUDES_WRALLY_H
>>>>>>> upstream/master
