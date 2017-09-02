// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/***************************************************************************

    Sega Zaxxon hardware

***************************************************************************/
<<<<<<< HEAD
=======

#include "machine/74259.h"
>>>>>>> upstream/master
#include "sound/samples.h"

class zaxxon_state : public driver_device
{
public:
	zaxxon_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_dials(*this, "DIAL"),
=======
		m_mainlatch(*this, "mainlatch%u", 1),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_dials(*this, "DIAL.%u", 0),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_colorram(*this, "colorram"),
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }

	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
=======
	required_device_array<ls259_device, 2> m_mainlatch;
>>>>>>> upstream/master
	optional_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	optional_ioport_array<2> m_dials;

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	optional_shared_ptr<UINT8> m_spriteram;
	optional_shared_ptr<UINT8> m_colorram;
	optional_shared_ptr<UINT8> m_decrypted_opcodes;

	UINT8 m_int_enabled;
	UINT8 m_coin_status[3];
	UINT8 m_coin_enable[3];

	UINT8 m_razmataz_dial_pos[2];
	UINT16 m_razmataz_counter;

	UINT8 m_sound_state[3];
	UINT8 m_bg_enable;
	UINT8 m_bg_color;
	UINT16 m_bg_position;
	UINT8 m_fg_color;

	UINT8 m_congo_fg_bank;
	UINT8 m_congo_color_bank;
	UINT8 m_congo_custom[4];

	const UINT8 *m_color_codes;
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	DECLARE_WRITE8_MEMBER(int_enable_w);
	DECLARE_READ8_MEMBER(razmataz_counter_r);
	DECLARE_WRITE8_MEMBER(zaxxon_coin_counter_w);
	DECLARE_WRITE8_MEMBER(zaxxon_coin_enable_w);
	DECLARE_WRITE8_MEMBER(zaxxon_flipscreen_w);
	DECLARE_WRITE8_MEMBER(zaxxon_fg_color_w);
	DECLARE_WRITE8_MEMBER(zaxxon_bg_position_w);
	DECLARE_WRITE8_MEMBER(zaxxon_bg_color_w);
	DECLARE_WRITE8_MEMBER(zaxxon_bg_enable_w);
	DECLARE_WRITE8_MEMBER(congo_fg_bank_w);
	DECLARE_WRITE8_MEMBER(congo_color_bank_w);
=======
	required_shared_ptr<uint8_t> m_videoram;
	optional_shared_ptr<uint8_t> m_spriteram;
	optional_shared_ptr<uint8_t> m_colorram;
	optional_shared_ptr<uint8_t> m_decrypted_opcodes;

	uint8_t m_int_enabled;
	uint8_t m_coin_status[3];

	uint8_t m_razmataz_dial_pos[2];
	uint16_t m_razmataz_counter;

	uint8_t m_sound_state[3];
	uint8_t m_bg_enable;
	uint8_t m_bg_color;
	uint16_t m_bg_position;
	uint8_t m_fg_color;

	uint8_t m_congo_fg_bank;
	uint8_t m_congo_color_bank;
	uint8_t m_congo_custom[4];

	const uint8_t *m_color_codes;
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	DECLARE_WRITE_LINE_MEMBER(int_enable_w);
	DECLARE_READ8_MEMBER(razmataz_counter_r);
	DECLARE_WRITE8_MEMBER(zaxxon_control_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_a_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_b_w);
	DECLARE_WRITE_LINE_MEMBER(coin_enable_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
	DECLARE_WRITE_LINE_MEMBER(fg_color_w);
	DECLARE_WRITE8_MEMBER(bg_position_w);
	DECLARE_WRITE_LINE_MEMBER(bg_color_w);
	DECLARE_WRITE_LINE_MEMBER(bg_enable_w);
	DECLARE_WRITE_LINE_MEMBER(congo_fg_bank_w);
	DECLARE_WRITE_LINE_MEMBER(congo_color_bank_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(zaxxon_videoram_w);
	DECLARE_WRITE8_MEMBER(congo_colorram_w);
	DECLARE_WRITE8_MEMBER(congo_sprite_custom_w);
	DECLARE_CUSTOM_INPUT_MEMBER(razmataz_dial_r);
	DECLARE_CUSTOM_INPUT_MEMBER(zaxxon_coin_r);
	DECLARE_INPUT_CHANGED_MEMBER(service_switch);
	DECLARE_INPUT_CHANGED_MEMBER(zaxxon_coin_inserted);
	DECLARE_DRIVER_INIT(razmataz);
<<<<<<< HEAD
	DECLARE_DRIVER_INIT(futspy);
	DECLARE_DRIVER_INIT(zaxxonj);
	DECLARE_DRIVER_INIT(szaxxon);
=======
	DECLARE_DRIVER_INIT(zaxxonj);
>>>>>>> upstream/master
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(zaxxon_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(razmataz_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(congo_get_fg_tile_info);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
	DECLARE_PALETTE_INIT(zaxxon);
	DECLARE_VIDEO_START(razmataz);
	DECLARE_VIDEO_START(congo);
	UINT32 screen_update_zaxxon(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_futspy(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_razmataz(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_congo(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(vblank_int);
=======
	virtual void machine_start() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(zaxxon);
	DECLARE_VIDEO_START(razmataz);
	DECLARE_VIDEO_START(congo);
	uint32_t screen_update_zaxxon(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_futspy(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_razmataz(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_congo(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(vblank_int);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(zaxxon_sound_a_w);
	DECLARE_WRITE8_MEMBER(zaxxon_sound_b_w);
	DECLARE_WRITE8_MEMBER(zaxxon_sound_c_w);
	DECLARE_WRITE8_MEMBER(congo_sound_b_w);
	DECLARE_WRITE8_MEMBER(congo_sound_c_w);
	void video_start_common(tilemap_get_info_delegate fg_tile_info);
	void draw_background(bitmap_ind16 &bitmap, const rectangle &cliprect, int skew);
<<<<<<< HEAD
	inline int find_minimum_y(UINT8 value, int flip);
	inline int find_minimum_x(UINT8 value, int flip);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, UINT16 flipxmask, UINT16 flipymask);
	void zaxxonj_decode(const char *cputag);
=======
	inline int find_minimum_y(uint8_t value, int flip);
	inline int find_minimum_x(uint8_t value, int flip);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, uint16_t flipxmask, uint16_t flipymask);
>>>>>>> upstream/master
};


/*----------- defined in audio/zaxxon.c -----------*/
MACHINE_CONFIG_EXTERN( zaxxon_samples );
MACHINE_CONFIG_EXTERN( congo_samples );
