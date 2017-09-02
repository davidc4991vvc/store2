// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Phil Stroffolino, Mirko Buffoni

<<<<<<< HEAD
// later, this might be merged with segas1x_state in segas16.h

#include "video/sega16sp.h"
=======
#include "video/sega16sp.h"
#include "machine/74157.h"
#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "machine/segaic16.h"
#include "sound/msm5205.h"
#include "sound/upd7759.h"

class segas1x_bootleg_state : public sega_16bit_common_base
{
public:
	segas1x_bootleg_state(const machine_config &mconfig, device_type type, const char *tag)
		: sega_16bit_common_base(mconfig, type, tag) ,
		m_textram(*this, "textram"),
		m_bg0_tileram(*this, "bg0_tileram"),
		m_bg1_tileram(*this, "bg1_tileram"),
		m_tileram(*this, "tileram"),
		m_goldnaxeb2_bgpage(*this, "gab2_bgpage"),
		m_goldnaxeb2_fgpage(*this, "gab2_fgpage"),
<<<<<<< HEAD
=======
		m_soundbank(*this, "soundbank"),
>>>>>>> upstream/master
		m_sprites(*this, "sprites"),
		m_maincpu(*this, "maincpu"),
		m_soundcpu(*this, "soundcpu"),
		m_msm(*this, "5205"),
		m_upd7759(*this, "7759"),
		m_gfxdecode(*this, "gfxdecode"),
<<<<<<< HEAD
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }

	required_shared_ptr<UINT16> m_textram;
	optional_shared_ptr<UINT16> m_bg0_tileram;
	optional_shared_ptr<UINT16> m_bg1_tileram;
	optional_shared_ptr<UINT16> m_tileram;
	optional_shared_ptr<UINT16> m_goldnaxeb2_bgpage;
	optional_shared_ptr<UINT16> m_goldnaxeb2_fgpage;

	required_device<sega_16bit_sprite_device> m_sprites;

	UINT16 m_coinctrl;
=======
		m_soundlatch(*this, "soundlatch"),
		m_adpcm_select(*this, "adpcm_select"),
		m_decrypted_opcodes(*this, "decrypted_opcodes") { }

	required_shared_ptr<uint16_t> m_textram;
	optional_shared_ptr<uint16_t> m_bg0_tileram;
	optional_shared_ptr<uint16_t> m_bg1_tileram;
	optional_shared_ptr<uint16_t> m_tileram;
	optional_shared_ptr<uint16_t> m_goldnaxeb2_bgpage;
	optional_shared_ptr<uint16_t> m_goldnaxeb2_fgpage;

	optional_memory_bank m_soundbank;

	required_device<sega_16bit_sprite_device> m_sprites;

	uint16_t m_coinctrl;
>>>>>>> upstream/master

	/* game specific */
	int m_passht4b_io1_val;
	int m_passht4b_io2_val;
	int m_passht4b_io3_val;

	int m_beautyb_unkx;

	int m_shinobl_kludge;

	int m_eswat_tilebank0;


	/* video-related */
	tilemap_t *m_background;
	tilemap_t *m_foreground;
	tilemap_t *m_text_layer;
	tilemap_t *m_background2;
	tilemap_t *m_foreground2;
	tilemap_t *m_bg_tilemaps[2];
	tilemap_t *m_text_tilemap;
	double m_weights[2][3][6];

	int m_spritebank_type;
	int m_back_yscroll;
	int m_fore_yscroll;
	int m_text_yscroll;

	int m_bg1_trans; // alien syn + sys18

	int m_tile_bank1;
	int m_tile_bank0;
	int m_bg_page[4];
	int m_fg_page[4];

<<<<<<< HEAD
	UINT16 m_datsu_page[4];
=======
	uint16_t m_datsu_page[4];
>>>>>>> upstream/master

	int m_bg2_page[4];
	int m_fg2_page[4];

	int m_old_bg_page[4];
	int m_old_fg_page[4];
	int m_old_tile_bank1;
	int m_old_tile_bank0;
	int m_old_bg2_page[4];
	int m_old_fg2_page[4];

	int m_bg_scrollx;
	int m_bg_scrolly;
	int m_fg_scrollx;
	int m_fg_scrolly;
<<<<<<< HEAD
	UINT16 m_tilemapselect;
=======
	uint16_t m_tilemapselect;
>>>>>>> upstream/master

	int m_textlayer_lo_min;
	int m_textlayer_lo_max;
	int m_textlayer_hi_min;
	int m_textlayer_hi_max;

	int m_tilebank_switch;


	/* sound-related */
	int m_sample_buffer;
	int m_sample_select;

<<<<<<< HEAD
	UINT8 *m_soundbank_ptr;     /* Pointer to currently selected portion of ROM */

	/* sys18 */
	UINT8 *m_sound_bank;
	UINT16 *m_splittab_bg_x;
	UINT16 *m_splittab_bg_y;
	UINT16 *m_splittab_fg_x;
	UINT16 *m_splittab_fg_y;
=======
	uint8_t *m_soundbank_ptr;     /* Pointer to currently selected portion of ROM */

	/* sys18 */
	uint8_t *m_sound_bank;
	uint16_t *m_splittab_bg_x;
	uint16_t *m_splittab_bg_y;
	uint16_t *m_splittab_fg_x;
	uint16_t *m_splittab_fg_y;
>>>>>>> upstream/master
	int     m_sound_info[4*2];
	int     m_refreshenable;
	int     m_system18;

<<<<<<< HEAD
	UINT8 *m_decrypted_region;  // goldnaxeb1 & bayrouteb1
=======
	uint8_t *m_decrypted_region;  // goldnaxeb1 & bayrouteb1
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_soundcpu;
	optional_device<msm5205_device> m_msm;
	optional_device<upd7759_device> m_upd7759;
	required_device<gfxdecode_device> m_gfxdecode;
<<<<<<< HEAD
	optional_shared_ptr<UINT16> m_decrypted_opcodes;

	DECLARE_WRITE16_MEMBER(sound_command_nmi_w);
	DECLARE_WRITE16_MEMBER(sound_command_irq_w);
=======
	optional_device<generic_latch_8_device> m_soundlatch;
	optional_device<ls157_device> m_adpcm_select;
	optional_shared_ptr<uint16_t> m_decrypted_opcodes;

	DECLARE_WRITE16_MEMBER(sound_command_nmi_w);
	DECLARE_WRITE16_MEMBER(sound_command_irq_w);
	DECLARE_READ8_MEMBER(sound_command_irq_r);
	DECLARE_WRITE8_MEMBER(soundbank_msm_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(sys16_coinctrl_w);
	DECLARE_READ16_MEMBER(passht4b_service_r);
	DECLARE_READ16_MEMBER(passht4b_io1_r);
	DECLARE_READ16_MEMBER(passht4b_io2_r);
	DECLARE_READ16_MEMBER(passht4b_io3_r);
	DECLARE_WRITE16_MEMBER(sys16_tilebank_w);
<<<<<<< HEAD
=======
	DECLARE_WRITE16_MEMBER(ddcrewbl_spritebank_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(tturfbl_msm5205_data_w);
	DECLARE_READ8_MEMBER(tturfbl_soundbank_r);
	DECLARE_WRITE8_MEMBER(tturfbl_soundbank_w);
	DECLARE_WRITE16_MEMBER(s16bl_bgpage_w);
	DECLARE_WRITE16_MEMBER(s16bl_fgpage_w);
	DECLARE_WRITE16_MEMBER(s16bl_fgscrollx_bank_w);
	DECLARE_WRITE16_MEMBER(s16bl_fgscrollx_w);
	DECLARE_WRITE16_MEMBER(s16bl_fgscrolly_w);
	DECLARE_WRITE16_MEMBER(s16bl_bgscrollx_w);
	DECLARE_WRITE16_MEMBER(s16bl_bgscrolly_w);
	DECLARE_WRITE16_MEMBER(datsu_page0_w);
	DECLARE_WRITE16_MEMBER(datsu_page1_w);
	DECLARE_WRITE16_MEMBER(datsu_page2_w);
	DECLARE_WRITE16_MEMBER(datsu_page3_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_fgscrollx_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_bgscrollx_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_fgscrolly_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_bgscrolly_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_fgpage_w);
	DECLARE_WRITE16_MEMBER(goldnaxeb2_bgpage_w);
	DECLARE_WRITE16_MEMBER(eswat_tilebank0_w);
	DECLARE_WRITE16_MEMBER(altbeastbl_gfx_w);
	DECLARE_READ16_MEMBER(beautyb_unkx_r);
	DECLARE_WRITE16_MEMBER(sys18_refreshenable_w);
	DECLARE_WRITE16_MEMBER(sys18_tilebank_w);
	DECLARE_READ8_MEMBER(system18_bank_r);
	DECLARE_WRITE8_MEMBER(sys18_soundbank_w);
	DECLARE_WRITE8_MEMBER(shdancbl_msm5205_data_w);
	DECLARE_READ8_MEMBER(shdancbl_soundbank_r);
	DECLARE_WRITE8_MEMBER(shdancbl_bankctrl_w);
<<<<<<< HEAD
	DECLARE_WRITE16_MEMBER(sys16_paletteram_w);
=======
	DECLARE_WRITE8_MEMBER(sys18bl_okibank_w);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(sys16_tileram_w);
	DECLARE_WRITE16_MEMBER(sys16_textram_w);
	DECLARE_WRITE16_MEMBER(s16a_bootleg_bgscrolly_w);
	DECLARE_WRITE16_MEMBER(s16a_bootleg_bgscrollx_w);
	DECLARE_WRITE16_MEMBER(s16a_bootleg_fgscrolly_w);
	DECLARE_WRITE16_MEMBER(s16a_bootleg_fgscrollx_w);
	DECLARE_WRITE16_MEMBER(s16a_bootleg_tilemapselect_w);
	DECLARE_WRITE8_MEMBER(upd7759_bank_w);
	DECLARE_DRIVER_INIT(passsht);
	DECLARE_DRIVER_INIT(wb3bbl);
	DECLARE_DRIVER_INIT(fpointbl);
	DECLARE_DRIVER_INIT(eswatbl);
	DECLARE_DRIVER_INIT(astormbl);
<<<<<<< HEAD
=======
	DECLARE_DRIVER_INIT(sys18bl_oki);
	DECLARE_DRIVER_INIT(astormb2);
>>>>>>> upstream/master
	DECLARE_DRIVER_INIT(shdancbl);
	DECLARE_DRIVER_INIT(dduxbl);
	DECLARE_DRIVER_INIT(altbeastbl);
	DECLARE_DRIVER_INIT(goldnaxeb2);
	DECLARE_DRIVER_INIT(bayrouteb1);
	DECLARE_DRIVER_INIT(beautyb);
<<<<<<< HEAD
	DECLARE_DRIVER_INIT(mwalkbl);
=======
>>>>>>> upstream/master
	DECLARE_DRIVER_INIT(bayrouteb2);
	DECLARE_DRIVER_INIT(shinobl);
	DECLARE_DRIVER_INIT(tturfbl);
	DECLARE_DRIVER_INIT(goldnaxeb1);
<<<<<<< HEAD
	DECLARE_DRIVER_INIT(common);
=======
	DECLARE_DRIVER_INIT(ddcrewbl);
	DECLARE_DRIVER_INIT(common);
	DECLARE_MACHINE_RESET(ddcrewbl);
>>>>>>> upstream/master
	TILEMAP_MAPPER_MEMBER(sys16_bg_map);
	TILEMAP_MAPPER_MEMBER(sys16_text_map);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_bg2_tile_info);
	TILE_GET_INFO_MEMBER(get_fg2_tile_info);
	TILE_GET_INFO_MEMBER(get_text_tile_info);
	TILE_GET_INFO_MEMBER(get_s16a_bootleg_tile_infotxt);
	TILE_GET_INFO_MEMBER(get_s16a_bootleg_tile_info0);
	TILE_GET_INFO_MEMBER(get_s16a_bootleg_tile_info1);
	DECLARE_VIDEO_START(system16);
	DECLARE_VIDEO_START(system18old);
	DECLARE_VIDEO_START(s16a_bootleg_shinobi);
	DECLARE_VIDEO_START(s16a_bootleg_passsht);
	DECLARE_VIDEO_START(s16a_bootleg_wb3bl);
	DECLARE_VIDEO_START(s16a_bootleg);
<<<<<<< HEAD
	UINT32 screen_update_system16(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_system18old(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_s16a_bootleg(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_s16a_bootleg_passht4b(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(sys16_interrupt);
=======
	uint32_t screen_update_system16(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_system18old(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_s16a_bootleg(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_s16a_bootleg_passht4b(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	void setup_system16_bootleg_spritebanking(  );
	void update_page(  );
	void set_tile_bank( int data );
	void set_fg_page( int data );
	void set_bg_page( int data );
	void datsu_set_pages(  );
	DECLARE_WRITE_LINE_MEMBER(tturfbl_msm5205_callback);
<<<<<<< HEAD
=======
	DECLARE_WRITE_LINE_MEMBER(datsu_msm5205_callback);
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER(shdancbl_msm5205_callback);
	DECLARE_WRITE_LINE_MEMBER(sound_cause_nmi);
};
