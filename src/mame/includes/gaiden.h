// license:BSD-3-Clause
// copyright-holders:Phil Stroffolino
<<<<<<< HEAD
=======

>>>>>>> upstream/master
/***************************************************************************

    Ninja Gaiden

***************************************************************************/

<<<<<<< HEAD
#include "video/tecmo_spr.h"
#include "video/tecmo_mix.h"
=======
#include "machine/gen_latch.h"
#include "machine/74157.h"
#include "sound/msm5205.h"
#include "video/tecmo_spr.h"
#include "video/tecmo_mix.h"
#include "screen.h"
>>>>>>> upstream/master

class gaiden_state : public driver_device
{
public:
	gaiden_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_videoram2(*this, "videoram2"),
		m_videoram3(*this, "videoram3"),
		m_spriteram(*this, "spriteram"),
<<<<<<< HEAD
		m_audiocpu(*this, "audiocpu"),
		m_maincpu(*this, "maincpu"),
=======
		m_adpcm_bank(*this, "adpcm_bank"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
>>>>>>> upstream/master
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_sprgen(*this, "spritegen"),
<<<<<<< HEAD
		m_mixer(*this, "mixer")
		{ }

	/* memory pointers */
	required_shared_ptr<UINT16> m_videoram;
	required_shared_ptr<UINT16> m_videoram2;
	required_shared_ptr<UINT16> m_videoram3;
	required_shared_ptr<UINT16> m_spriteram;
=======
		m_mixer(*this, "mixer"),
		m_soundlatch(*this, "soundlatch"),
		m_msm(*this, "msm%u", 1),
		m_adpcm_select(*this, "adpcm_select%u", 1)
		{ }

	/* memory pointers */
	required_shared_ptr<uint16_t> m_videoram;
	required_shared_ptr<uint16_t> m_videoram2;
	required_shared_ptr<uint16_t> m_videoram3;
	required_shared_ptr<uint16_t> m_spriteram;
	optional_memory_bank m_adpcm_bank;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t   *m_text_layer;
	tilemap_t   *m_foreground;
	tilemap_t   *m_background;
	bitmap_ind16 m_sprite_bitmap;
	bitmap_ind16 m_tile_bitmap_bg;
	bitmap_ind16 m_tile_bitmap_fg;
<<<<<<< HEAD
	UINT16      m_tx_scroll_x;
	UINT16      m_tx_scroll_y;
	UINT16      m_bg_scroll_x;
	UINT16      m_bg_scroll_y;
	UINT16      m_fg_scroll_x;
	UINT16      m_fg_scroll_y;
	INT8        m_tx_offset_y;
	INT8        m_bg_offset_y;
	INT8        m_fg_offset_y;
	INT8        m_spr_offset_y;
=======
	uint16_t      m_tx_scroll_x;
	uint16_t      m_tx_scroll_y;
	uint16_t      m_bg_scroll_x;
	uint16_t      m_bg_scroll_y;
	uint16_t      m_fg_scroll_x;
	uint16_t      m_fg_scroll_y;
	int8_t        m_tx_offset_y;
	int8_t        m_bg_offset_y;
	int8_t        m_fg_offset_y;
	int8_t        m_spr_offset_y;
>>>>>>> upstream/master

	/* misc */
	int         m_sprite_sizey;
	int         m_prot;
	int         m_jumpcode;
	const int   *m_raiga_jumppoints;
<<<<<<< HEAD

	/* devices */
	required_device<cpu_device> m_audiocpu;
	DECLARE_WRITE16_MEMBER(gaiden_sound_command_w);
	DECLARE_WRITE16_MEMBER(drgnbowl_sound_command_w);
=======
	bool        m_adpcm_toggle;

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_device<tecmo_spr_device> m_sprgen;
	optional_device<tecmo_mix_device> m_mixer;
	required_device<generic_latch_8_device> m_soundlatch;
	optional_device_array<msm5205_device, 2> m_msm;
	optional_device_array<ls157_device, 2> m_adpcm_select;

	// mastninja ADPCM control
	DECLARE_WRITE_LINE_MEMBER(vck_flipflop_w);
	DECLARE_WRITE8_MEMBER(adpcm_bankswitch_w);

	DECLARE_WRITE16_MEMBER(irq_ack_w);
	DECLARE_WRITE8_MEMBER(drgnbowl_irq_ack_w);
	DECLARE_WRITE16_MEMBER(gaiden_sound_command_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(wildfang_protection_w);
	DECLARE_READ16_MEMBER(wildfang_protection_r);
	DECLARE_WRITE16_MEMBER(raiga_protection_w);
	DECLARE_READ16_MEMBER(raiga_protection_r);
	DECLARE_WRITE16_MEMBER(gaiden_flip_w);
	DECLARE_WRITE16_MEMBER(gaiden_txscrollx_w);
	DECLARE_WRITE16_MEMBER(gaiden_txscrolly_w);
	DECLARE_WRITE16_MEMBER(gaiden_fgscrollx_w);
	DECLARE_WRITE16_MEMBER(gaiden_fgscrolly_w);
	DECLARE_WRITE16_MEMBER(gaiden_bgscrollx_w);
	DECLARE_WRITE16_MEMBER(gaiden_bgscrolly_w);
	DECLARE_WRITE16_MEMBER(gaiden_txoffsety_w);
	DECLARE_WRITE16_MEMBER(gaiden_fgoffsety_w);
	DECLARE_WRITE16_MEMBER(gaiden_bgoffsety_w);
	DECLARE_WRITE16_MEMBER(gaiden_sproffsety_w);
	DECLARE_WRITE16_MEMBER(gaiden_videoram3_w);
	DECLARE_WRITE16_MEMBER(gaiden_videoram2_w);
	DECLARE_WRITE16_MEMBER(gaiden_videoram_w);
	DECLARE_DRIVER_INIT(raiga);
	DECLARE_DRIVER_INIT(drgnbowl);
	DECLARE_DRIVER_INIT(drgnbowla);
	DECLARE_DRIVER_INIT(mastninj);
	DECLARE_DRIVER_INIT(shadoww);
	DECLARE_DRIVER_INIT(wildfang);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info_raiga);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);
	DECLARE_MACHINE_START(raiga);
<<<<<<< HEAD
=======
	DECLARE_MACHINE_START(mastninj);
>>>>>>> upstream/master
	DECLARE_MACHINE_RESET(raiga);
	DECLARE_VIDEO_START(gaiden);
	DECLARE_VIDEO_START(drgnbowl);
	DECLARE_VIDEO_START(raiga);
<<<<<<< HEAD
	UINT32 screen_update_gaiden(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_drgnbowl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_raiga(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void drgnbowl_draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void descramble_drgnbowl(int descramble_cpu);
	void descramble_mastninj_gfx(UINT8* src);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	required_device<cpu_device> m_maincpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_device<tecmo_spr_device> m_sprgen;
	optional_device<tecmo_mix_device> m_mixer;
=======
	uint32_t screen_update_gaiden(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_drgnbowl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_raiga(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void drgnbowl_draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void descramble_drgnbowl(int descramble_cpu);
	void descramble_mastninj_gfx(uint8_t* src);
>>>>>>> upstream/master
};
