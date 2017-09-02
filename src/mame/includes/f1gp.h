// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
<<<<<<< HEAD
=======

#include "machine/6850acia.h"
#include "machine/gen_latch.h"
>>>>>>> upstream/master
#include "video/vsystem_spr.h"
#include "video/vsystem_spr2.h"
#include "video/k053936.h"

class f1gp_state : public driver_device
{
public:
	f1gp_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_sharedram(*this, "sharedram"),
		m_spr1vram(*this, "spr1vram"),
		m_spr2vram(*this, "spr2vram"),
		m_spr1cgram(*this, "spr1cgram"),
		m_spr2cgram(*this, "spr2cgram"),
		m_fgvideoram(*this, "fgvideoram"),
		m_rozvideoram(*this, "rozvideoram"),
		m_sprcgram(*this, "sprcgram"),
		m_spritelist(*this, "spritelist"),
		m_spriteram(*this, "spriteram"),
		m_fgregs(*this, "fgregs"),
		m_rozregs(*this, "rozregs"),
		m_z80bank(*this, "bank1"),
<<<<<<< HEAD
		m_spr_old(*this, "vsystem_spr_old"),
		m_spr_old2(*this, "vsystem_spr_ol2"),
		m_spr(*this, "vsystem_spr"),
		m_maincpu(*this, "maincpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_audiocpu(*this, "audiocpu"),
		m_k053936(*this, "k053936"),
		m_palette(*this, "palette")  { }

	/* memory pointers */
	required_shared_ptr<UINT16> m_sharedram;
	optional_shared_ptr<UINT16> m_spr1vram;
	optional_shared_ptr<UINT16> m_spr2vram;
	optional_shared_ptr<UINT16> m_spr1cgram;
	optional_shared_ptr<UINT16> m_spr2cgram;
	required_shared_ptr<UINT16> m_fgvideoram;
	required_shared_ptr<UINT16> m_rozvideoram;
	optional_shared_ptr<UINT16> m_sprcgram;
	optional_shared_ptr<UINT16> m_spritelist;
	optional_shared_ptr<UINT16> m_spriteram;
	optional_shared_ptr<UINT16> m_fgregs;
	optional_shared_ptr<UINT16> m_rozregs;

	optional_memory_bank m_z80bank;

	/* devices referenced above */
	optional_device<vsystem_spr2_device> m_spr_old; // f1gp
	optional_device<vsystem_spr2_device> m_spr_old2; // f1gp
	optional_device<vsystem_spr_device> m_spr; // f1gp2


	UINT16 *  m_zoomdata;
=======
		m_maincpu(*this, "maincpu"),
		m_spr_old(*this, "vsystem_spr_old"),
		m_spr_old2(*this, "vsystem_spr_ol2"),
		m_spr(*this, "vsystem_spr"),
		m_gfxdecode(*this, "gfxdecode"),
		m_audiocpu(*this, "audiocpu"),
		m_k053936(*this, "k053936"),
		m_palette(*this, "palette"),
		m_soundlatch(*this, "soundlatch"),
		m_acia(*this, "acia") { }

	/* memory pointers */
	required_shared_ptr<uint16_t> m_sharedram;
	optional_shared_ptr<uint16_t> m_spr1vram;
	optional_shared_ptr<uint16_t> m_spr2vram;
	optional_shared_ptr<uint16_t> m_spr1cgram;
	optional_shared_ptr<uint16_t> m_spr2cgram;
	required_shared_ptr<uint16_t> m_fgvideoram;
	required_shared_ptr<uint16_t> m_rozvideoram;
	optional_shared_ptr<uint16_t> m_sprcgram;
	optional_shared_ptr<uint16_t> m_spritelist;
	optional_shared_ptr<uint16_t> m_spriteram;
	optional_shared_ptr<uint16_t> m_fgregs;
	optional_shared_ptr<uint16_t> m_rozregs;

	optional_memory_bank m_z80bank;

	uint16_t *  m_zoomdata;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t   *m_fg_tilemap;
	tilemap_t   *m_roz_tilemap;
	int       m_roz_bank;
	int       m_flipscreen;
	int       m_gfxctrl;
	int       m_scroll[2];
<<<<<<< HEAD
	UINT32 f1gp2_tile_callback( UINT32 code );
	UINT32 f1gp_old_tile_callback( UINT32 code );
	UINT32 f1gp_ol2_tile_callback( UINT32 code );

	/* misc */
	int       m_pending_command;

	/* devices */
	required_device<cpu_device> m_maincpu;
=======
	uint32_t f1gp2_tile_callback( uint32_t code );
	uint32_t f1gp_old_tile_callback( uint32_t code );
	uint32_t f1gp_ol2_tile_callback( uint32_t code );

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<vsystem_spr2_device> m_spr_old; // f1gp
	optional_device<vsystem_spr2_device> m_spr_old2; // f1gp
	optional_device<vsystem_spr_device> m_spr; // f1gp2
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	optional_device<cpu_device> m_audiocpu;
	optional_device<k053936_device> m_k053936;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	DECLARE_WRITE8_MEMBER(f1gp_sh_bankswitch_w);
	DECLARE_WRITE16_MEMBER(sound_command_w);
	DECLARE_READ16_MEMBER(command_pending_r);
	DECLARE_WRITE8_MEMBER(pending_command_clear_w);
=======
	optional_device<generic_latch_8_device> m_soundlatch; // not f1gpb
	required_device<acia6850_device> m_acia;

	DECLARE_WRITE8_MEMBER(f1gp_sh_bankswitch_w);
	DECLARE_READ8_MEMBER(command_pending_r);
>>>>>>> upstream/master
	DECLARE_WRITE16_MEMBER(f1gpb_misc_w);
	DECLARE_READ16_MEMBER(f1gp_zoomdata_r);
	DECLARE_WRITE16_MEMBER(f1gp_zoomdata_w);
	DECLARE_READ16_MEMBER(f1gp_rozvideoram_r);
	DECLARE_WRITE16_MEMBER(f1gp_rozvideoram_w);
	DECLARE_WRITE16_MEMBER(f1gp_fgvideoram_w);
	DECLARE_WRITE16_MEMBER(f1gp_fgscroll_w);
	DECLARE_WRITE16_MEMBER(f1gp_gfxctrl_w);
	DECLARE_WRITE16_MEMBER(f1gp2_gfxctrl_w);
	TILE_GET_INFO_MEMBER(f1gp_get_roz_tile_info);
	TILE_GET_INFO_MEMBER(f1gp2_get_roz_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	DECLARE_MACHINE_START(f1gp);
	DECLARE_MACHINE_RESET(f1gp);
	DECLARE_VIDEO_START(f1gp);
	DECLARE_MACHINE_START(f1gpb);
	DECLARE_VIDEO_START(f1gpb);
	DECLARE_VIDEO_START(f1gp2);
<<<<<<< HEAD
	UINT32 screen_update_f1gp(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_f1gpb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_f1gp2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void f1gpb_draw_sprites( screen_device &screen, bitmap_ind16 &bitmap,const rectangle &cliprect );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	uint32_t screen_update_f1gp(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_f1gpb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_f1gp2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void f1gpb_draw_sprites( screen_device &screen, bitmap_ind16 &bitmap,const rectangle &cliprect );
>>>>>>> upstream/master
};
