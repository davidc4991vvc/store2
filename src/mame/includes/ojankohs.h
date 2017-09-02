// license:BSD-3-Clause
// copyright-holders:Takahiro Nogi, Uki
/*************************************************************************

    Ojanko High School & other Video System mahjong series

*************************************************************************/
#include "sound/msm5205.h"
<<<<<<< HEAD
=======
#include "screen.h"
>>>>>>> upstream/master

class ojankohs_state : public driver_device
{
public:
<<<<<<< HEAD
	ojankohs_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
=======
	ojankohs_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
>>>>>>> upstream/master
		m_videoram(*this, "videoram"),
		m_colorram(*this, "colorram"),
		m_paletteram(*this, "paletteram"),
		m_maincpu(*this, "maincpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
<<<<<<< HEAD
		m_palette(*this, "palette") { }

	/* memory pointers */
	optional_shared_ptr<UINT8> m_videoram;
	optional_shared_ptr<UINT8> m_colorram;
	optional_shared_ptr<UINT8> m_paletteram;
=======
		m_palette(*this, "palette"),
		m_coin(*this, "coin"),
		m_inputs_p1(*this, {"p1_0", "p1_1", "p1_2", "p1_3"}),
		m_inputs_p2(*this, {"p2_0", "p2_1", "p2_2", "p2_3"}),
		m_inputs_p1_extra(*this, "p1_4"),
		m_inputs_p2_extra(*this, "p2_4"),
		m_dsw1(*this, "dsw1"), m_dsw2(*this, "dsw2"),
		m_dsw3(*this, "dsw3"), m_dsw4(*this, "dsw4")
	{ }

	/* memory pointers */
	optional_shared_ptr<uint8_t> m_videoram;
	optional_shared_ptr<uint8_t> m_colorram;
	optional_shared_ptr<uint8_t> m_paletteram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t  *m_tilemap;
	bitmap_ind16 m_tmpbitmap;
	int       m_gfxreg;
	int       m_flipscreen;
	int       m_flipscreen_old;
	int       m_scrollx;
	int       m_scrolly;
	int       m_screen_refresh;

	/* misc */
<<<<<<< HEAD
	int       m_portselect;
=======
	uint8_t   m_port_select;
>>>>>>> upstream/master
	int       m_adpcm_reset;
	int       m_adpcm_data;
	int       m_vclk_left;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<msm5205_device> m_msm;
	optional_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD
=======
	required_ioport m_coin;
	required_ioport_array<4> m_inputs_p1;
	required_ioport_array<4> m_inputs_p2;
	optional_ioport m_inputs_p1_extra;
	optional_ioport m_inputs_p2_extra;
	required_ioport m_dsw1;
	required_ioport m_dsw2;
	optional_ioport m_dsw3;
	optional_ioport m_dsw4;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(ojankohs_rombank_w);
	DECLARE_WRITE8_MEMBER(ojankoy_rombank_w);
	DECLARE_WRITE8_MEMBER(ojankohs_msm5205_w);
	DECLARE_WRITE8_MEMBER(ojankoc_ctrl_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(ojankohs_portselect_w);
	DECLARE_READ8_MEMBER(ojankohs_keymatrix_r);
	DECLARE_READ8_MEMBER(ojankoc_keymatrix_r);
=======
	DECLARE_WRITE8_MEMBER(port_select_w);
	DECLARE_READ8_MEMBER(keymatrix_p1_r);
	DECLARE_READ8_MEMBER(keymatrix_p2_r);
	DECLARE_READ8_MEMBER(ojankoc_keymatrix_p1_r);
	DECLARE_READ8_MEMBER(ojankoc_keymatrix_p2_r);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(ccasino_dipsw3_r);
	DECLARE_READ8_MEMBER(ccasino_dipsw4_r);
	DECLARE_WRITE8_MEMBER(ojankoy_coinctr_w);
	DECLARE_WRITE8_MEMBER(ccasino_coinctr_w);
	DECLARE_WRITE8_MEMBER(ojankohs_palette_w);
	DECLARE_WRITE8_MEMBER(ccasino_palette_w);
	DECLARE_WRITE8_MEMBER(ojankoc_palette_w);
	DECLARE_WRITE8_MEMBER(ojankohs_videoram_w);
	DECLARE_WRITE8_MEMBER(ojankohs_colorram_w);
	DECLARE_WRITE8_MEMBER(ojankohs_gfxreg_w);
	DECLARE_WRITE8_MEMBER(ojankohs_flipscreen_w);
	DECLARE_WRITE8_MEMBER(ojankoc_videoram_w);
	DECLARE_WRITE8_MEMBER(ojankohs_adpcm_reset_w);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(ojankohs_ay8910_0_r);
	DECLARE_READ8_MEMBER(ojankohs_ay8910_1_r);
	TILE_GET_INFO_MEMBER(ojankohs_get_tile_info);
	TILE_GET_INFO_MEMBER(ojankoy_get_tile_info);
	virtual void machine_reset();
=======
	DECLARE_READ8_MEMBER(ojankohs_dipsw1_r);
	DECLARE_READ8_MEMBER(ojankohs_dipsw2_r);
	TILE_GET_INFO_MEMBER(ojankohs_get_tile_info);
	TILE_GET_INFO_MEMBER(ojankoy_get_tile_info);
	virtual void machine_reset() override;
>>>>>>> upstream/master
	DECLARE_MACHINE_START(ojankohs);
	DECLARE_VIDEO_START(ojankohs);
	DECLARE_MACHINE_START(ojankoy);
	DECLARE_VIDEO_START(ojankoy);
	DECLARE_PALETTE_INIT(ojankoy);
	DECLARE_MACHINE_START(ojankoc);
	DECLARE_VIDEO_START(ojankoc);
	DECLARE_MACHINE_START(common);
<<<<<<< HEAD
	UINT32 screen_update_ojankohs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_ojankoc(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	uint32_t screen_update_ojankohs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_ojankoc(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void ojankoc_flipscreen( address_space &space, int data );
	DECLARE_WRITE_LINE_MEMBER(ojankohs_adpcm_int);
};
