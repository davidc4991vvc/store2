// license:BSD-3-Clause
// copyright-holders:Bryan McPhail
<<<<<<< HEAD
=======

#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "video/bufsprite.h"

class bbusters_state : public driver_device
{
public:
	bbusters_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_spriteram(*this, "spriteram"),
		m_spriteram2(*this, "spriteram2"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
>>>>>>> upstream/master
		m_eprom_data(*this, "eeprom"),
		m_ram(*this, "ram"),
		m_videoram(*this, "videoram"),
		m_pf1_data(*this, "pf1_data"),
		m_pf2_data(*this, "pf2_data"),
		m_pf1_scroll_data(*this, "pf1_scroll_data"),
		m_pf2_scroll_data(*this, "pf2_scroll_data") { }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<buffered_spriteram16_device> m_spriteram;
	optional_device<buffered_spriteram16_device> m_spriteram2;
<<<<<<< HEAD

	optional_shared_ptr<UINT16> m_eprom_data;
	required_shared_ptr<UINT16> m_ram;
	required_shared_ptr<UINT16> m_videoram;
	required_shared_ptr<UINT16> m_pf1_data;
	required_shared_ptr<UINT16> m_pf2_data;
	required_shared_ptr<UINT16> m_pf1_scroll_data;
	required_shared_ptr<UINT16> m_pf2_scroll_data;
=======
	required_device<generic_latch_8_device> m_soundlatch;

	optional_shared_ptr<uint16_t> m_eprom_data;
	required_shared_ptr<uint16_t> m_ram;
	required_shared_ptr<uint16_t> m_videoram;
	required_shared_ptr<uint16_t> m_pf1_data;
	required_shared_ptr<uint16_t> m_pf2_data;
	required_shared_ptr<uint16_t> m_pf1_scroll_data;
	required_shared_ptr<uint16_t> m_pf2_scroll_data;
>>>>>>> upstream/master

	int m_sound_status;
	int m_gun_select;
	tilemap_t *m_fix_tilemap;
	tilemap_t *m_pf1_tilemap;
	tilemap_t *m_pf2_tilemap;
<<<<<<< HEAD
	const UINT8 *m_scale_table_ptr;
	UINT8 m_scale_line_count;
=======
	const uint8_t *m_scale_table_ptr;
	uint8_t m_scale_line_count;
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(sound_status_r);
	DECLARE_WRITE8_MEMBER(sound_status_w);
	DECLARE_WRITE16_MEMBER(sound_cpu_w);
	DECLARE_READ16_MEMBER(eprom_r);
	DECLARE_READ16_MEMBER(control_3_r);
	DECLARE_WRITE16_MEMBER(gun_select_w);
	DECLARE_WRITE16_MEMBER(two_gun_output_w);
	DECLARE_WRITE16_MEMBER(three_gun_output_w);
	DECLARE_READ16_MEMBER(kludge_r);
	DECLARE_READ16_MEMBER(mechatt_gun_r);
	DECLARE_WRITE16_MEMBER(video_w);
	DECLARE_WRITE16_MEMBER(pf1_w);
	DECLARE_WRITE16_MEMBER(pf2_w);

	TILE_GET_INFO_MEMBER(get_tile_info);
	TILE_GET_INFO_MEMBER(get_pf1_tile_info);
	TILE_GET_INFO_MEMBER(get_pf2_tile_info);

<<<<<<< HEAD
	virtual void machine_start();
	DECLARE_VIDEO_START(bbuster);
	DECLARE_VIDEO_START(mechatt);

	UINT32 screen_update_bbuster(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_mechatt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_bbuster(screen_device &screen, bool state);
	inline const UINT8 *get_source_ptr(gfx_element *gfx, UINT32 sprite, int dx, int dy, int block);
	void draw_block(bitmap_ind16 &dest,int x,int y,int size,int flipx,int flipy,UINT32 sprite,int color,int bank,int block);
	void draw_sprites(bitmap_ind16 &bitmap, const UINT16 *source, int bank, int colval, int colmask);
=======
	virtual void machine_start() override;
	DECLARE_VIDEO_START(bbuster);
	DECLARE_VIDEO_START(mechatt);

	uint32_t screen_update_bbuster(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_mechatt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	inline const uint8_t *get_source_ptr(gfx_element *gfx, uint32_t sprite, int dx, int dy, int block);
	void draw_block(bitmap_ind16 &dest,int x,int y,int size,int flipx,int flipy,uint32_t sprite,int color,int bank,int block);
	void draw_sprites(bitmap_ind16 &bitmap, const uint16_t *source, int bank, int colval, int colmask);
>>>>>>> upstream/master
};
