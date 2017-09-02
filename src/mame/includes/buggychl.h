// license:BSD-3-Clause
// copyright-holders:Ernesto Corvi, Nicola Salmoria
/*
    buggychl
*/

<<<<<<< HEAD
#include "machine/buggychl.h"
#include "sound/msm5232.h"
=======
#include "machine/taito68705interface.h"
#include "machine/input_merger.h"
#include "machine/gen_latch.h"
#include "sound/msm5232.h"
#include "screen.h"
>>>>>>> upstream/master

class buggychl_state : public driver_device
{
public:
	buggychl_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_charram(*this, "charram"),
		m_videoram(*this, "videoram"),
		m_spriteram(*this, "spriteram"),
		m_scrollv(*this, "scrollv"),
		m_scrollh(*this, "scrollh"),
		m_audiocpu(*this, "audiocpu"),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_mcu(*this, "mcu"),
=======
>>>>>>> upstream/master
		m_bmcu(*this, "bmcu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
<<<<<<< HEAD
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_shared_ptr<UINT8> m_charram;
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_scrollv;
	required_shared_ptr<UINT8> m_scrollh;
=======
		m_palette(*this, "palette"),
		m_soundnmi(*this, "soundnmi"),
		m_soundlatch(*this, "soundlatch"),
		m_soundlatch2(*this, "soundlatch2") { }

	/* memory pointers */
	required_shared_ptr<uint8_t> m_charram;
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_scrollv;
	required_shared_ptr<uint8_t> m_scrollh;
>>>>>>> upstream/master

	/* video-related */
	bitmap_ind16 m_tmp_bitmap1;
	bitmap_ind16 m_tmp_bitmap2;
	tilemap_t     *m_bg_tilemap;
	int         m_sl_bank;
	int         m_bg_on;
	int         m_sky_on;
	int         m_sprite_color_base;
	int         m_bg_scrollx;
<<<<<<< HEAD
	UINT8       m_sprite_lookup[0x2000];

	/* sound-related */
	int         m_sound_nmi_enable;
	int         m_pending_nmi;
=======
	uint8_t       m_sprite_lookup[0x2000];
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_audiocpu;
	required_device<cpu_device> m_maincpu;
<<<<<<< HEAD
	required_device<cpu_device> m_mcu;
	required_device<buggychl_mcu_device> m_bmcu;
=======
	required_device<taito68705_mcu_device> m_bmcu;
>>>>>>> upstream/master
	required_device<msm5232_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD


	DECLARE_WRITE8_MEMBER(bankswitch_w);
	DECLARE_WRITE8_MEMBER(sound_command_w);
	DECLARE_WRITE8_MEMBER(nmi_disable_w);
	DECLARE_WRITE8_MEMBER(nmi_enable_w);
	DECLARE_WRITE8_MEMBER(sound_enable_w);
=======
	required_device<input_merger_device> m_soundnmi;
	required_device<generic_latch_8_device> m_soundlatch;
	required_device<generic_latch_8_device> m_soundlatch2;

	DECLARE_WRITE8_MEMBER(bankswitch_w);
	DECLARE_WRITE8_MEMBER(sound_enable_w);
	DECLARE_READ8_MEMBER(mcu_status_r);
	DECLARE_READ8_MEMBER(sound_status_main_r);
	DECLARE_READ8_MEMBER(sound_status_sound_r);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(buggychl_chargen_w);
	DECLARE_WRITE8_MEMBER(buggychl_sprite_lookup_bank_w);
	DECLARE_WRITE8_MEMBER(buggychl_sprite_lookup_w);
	DECLARE_WRITE8_MEMBER(buggychl_ctrl_w);
	DECLARE_WRITE8_MEMBER(buggychl_bg_scrollx_w);
	DECLARE_WRITE8_MEMBER(port_a_0_w);
	DECLARE_WRITE8_MEMBER(port_b_0_w);
	DECLARE_WRITE8_MEMBER(port_a_1_w);
	DECLARE_WRITE8_MEMBER(port_b_1_w);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(buggychl);
	UINT32 screen_update_buggychl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	DECLARE_PALETTE_INIT(buggychl);
	uint32_t screen_update_buggychl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	TIMER_CALLBACK_MEMBER(nmi_callback);
	void draw_sky( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void draw_bg( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void draw_fg( bitmap_ind16 &bitmap, const rectangle &cliprect );
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
};
