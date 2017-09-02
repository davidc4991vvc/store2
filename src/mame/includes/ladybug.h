// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/*************************************************************************

    Universal 8106-A2 + 8106-B PCB set

<<<<<<< HEAD
    and Zero Hour / Red Clash

=======
>>>>>>> upstream/master
*************************************************************************/

class ladybug_state : public driver_device
{
public:
	ladybug_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_spriteram(*this, "spriteram"),
		m_grid_data(*this, "grid_data"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_port_dsw0(*this, "DSW0"),
		m_p1_control(*this, "CONTP1"),
		m_p2_control(*this, "CONTP2"),
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	optional_shared_ptr<UINT8> m_colorram;
	required_shared_ptr<UINT8> m_spriteram;
	optional_shared_ptr<UINT8> m_grid_data;
=======
	required_shared_ptr<uint8_t> m_videoram;
	optional_shared_ptr<uint8_t> m_colorram;
	required_shared_ptr<uint8_t> m_spriteram;
	optional_shared_ptr<uint8_t> m_grid_data;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t    *m_bg_tilemap;
	tilemap_t    *m_grid_tilemap;   // ladybug
<<<<<<< HEAD
	tilemap_t    *m_fg_tilemap; // redclash
	UINT8      m_grid_color;
	int        m_star_speed;
	int        m_gfxbank;   // redclash only
	UINT8      m_stars_enable;
	UINT8      m_stars_speed;
	UINT32     m_stars_state;
	UINT16     m_stars_offset;
	UINT8      m_stars_count;

	/* misc */
	UINT8      m_sound_low;
	UINT8      m_sound_high;
	UINT8      m_weird_value[8];
	UINT8      m_sraider_0x30;
	UINT8      m_sraider_0x38;
=======
	uint8_t      m_grid_color;
	int        m_star_speed;
	uint8_t      m_stars_enable;
	uint8_t      m_stars_speed;
	uint32_t     m_stars_state;
	uint16_t     m_stars_offset;
	uint8_t      m_stars_count;

	/* misc */
	uint8_t      m_sound_low;
	uint8_t      m_sound_high;
	uint8_t      m_weird_value[8];
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	optional_ioport m_port_dsw0;
	optional_ioport m_p1_control;
	optional_ioport m_p2_control;
<<<<<<< HEAD
	optional_shared_ptr<UINT8> m_decrypted_opcodes;

	DECLARE_READ8_MEMBER(sraider_sound_low_r);
	DECLARE_READ8_MEMBER(sraider_sound_high_r);
	DECLARE_WRITE8_MEMBER(sraider_sound_low_w);
	DECLARE_WRITE8_MEMBER(sraider_sound_high_w);
	DECLARE_READ8_MEMBER(sraider_8005_r);
	DECLARE_WRITE8_MEMBER(sraider_misc_w);
	DECLARE_WRITE8_MEMBER(ladybug_videoram_w);
	DECLARE_WRITE8_MEMBER(ladybug_colorram_w);
	DECLARE_WRITE8_MEMBER(ladybug_flipscreen_w);
	DECLARE_WRITE8_MEMBER(sraider_io_w);
=======
	optional_shared_ptr<uint8_t> m_decrypted_opcodes;

	DECLARE_WRITE8_MEMBER(ladybug_videoram_w);
	DECLARE_WRITE8_MEMBER(ladybug_colorram_w);
	DECLARE_WRITE_LINE_MEMBER(flipscreen_w);
>>>>>>> upstream/master
	DECLARE_CUSTOM_INPUT_MEMBER(ladybug_p1_control_r);
	DECLARE_CUSTOM_INPUT_MEMBER(ladybug_p2_control_r);
	DECLARE_INPUT_CHANGED_MEMBER(coin1_inserted);
	DECLARE_INPUT_CHANGED_MEMBER(coin2_inserted);
<<<<<<< HEAD
	DECLARE_INPUT_CHANGED_MEMBER(left_coin_inserted);
	DECLARE_INPUT_CHANGED_MEMBER(right_coin_inserted);
	DECLARE_DRIVER_INIT(dorodon);
	DECLARE_DRIVER_INIT(redclash);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_grid_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	DECLARE_MACHINE_START(ladybug);
	DECLARE_VIDEO_START(ladybug);
	DECLARE_PALETTE_INIT(ladybug);
	DECLARE_MACHINE_START(sraider);
	DECLARE_MACHINE_RESET(sraider);
	DECLARE_VIDEO_START(sraider);
	DECLARE_PALETTE_INIT(sraider);
	DECLARE_MACHINE_START(redclash);
	DECLARE_MACHINE_RESET(redclash);
	DECLARE_VIDEO_START(redclash);
	DECLARE_PALETTE_INIT(redclash);
	UINT32 screen_update_ladybug(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_sraider(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_redclash(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_sraider(screen_device &screen, bool state);
	void screen_eof_redclash(screen_device &screen, bool state);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	DECLARE_WRITE8_MEMBER( redclash_videoram_w );
	DECLARE_WRITE8_MEMBER( redclash_gfxbank_w );
	DECLARE_WRITE8_MEMBER( redclash_flipscreen_w );

	DECLARE_WRITE8_MEMBER( redclash_star0_w );
	DECLARE_WRITE8_MEMBER( redclash_star1_w );
	DECLARE_WRITE8_MEMBER( redclash_star2_w );
	DECLARE_WRITE8_MEMBER( redclash_star_reset_w );
	DECLARE_WRITE8_MEMBER( irqack_w );

	/* sraider uses the zerohour star generator board */
	void redclash_set_stars_enable(UINT8 on);
	void redclash_update_stars_state();
	void redclash_set_stars_speed(UINT8 speed);
	void redclash_draw_stars(bitmap_ind16 &bitmap, const rectangle &cliprect, UINT8 palette_offset, UINT8 sraider, UINT8 firstx, UINT8 lastx);
	void redclash_draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void redclash_draw_bullets( bitmap_ind16 &bitmap, const rectangle &cliprect );
=======
	DECLARE_DRIVER_INIT(dorodon);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_grid_tile_info);
	DECLARE_MACHINE_START(ladybug);
	DECLARE_VIDEO_START(ladybug);
	DECLARE_PALETTE_INIT(ladybug);
	uint32_t screen_update_ladybug(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void palette_init_common( palette_device &palette, const uint8_t *color_prom,
								int r_bit0, int r_bit1, int g_bit0, int g_bit1, int b_bit0, int b_bit1 );

>>>>>>> upstream/master
};
