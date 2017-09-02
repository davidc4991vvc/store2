// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria

<<<<<<< HEAD
=======
#include "machine/gen_latch.h"
#include "machine/input_merger.h"
#include "machine/taito68705interface.h"

>>>>>>> upstream/master
class lsasquad_state : public driver_device
{
public:
	lsasquad_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_scrollram(*this, "scrollram"),
		m_spriteram(*this, "spriteram"),
<<<<<<< HEAD
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_mcu(*this, "mcu"),
=======
		m_priority_prom(*this, "prio_prom"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_soundlatch(*this, "soundlatch"),
		m_soundlatch2(*this, "soundlatch2"),
		m_soundnmi(*this, "soundnmi"),
		m_bmcu(*this, "bmcu"),
>>>>>>> upstream/master
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette") { }

	/* memory pointers */
<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_scrollram;
	required_shared_ptr<UINT8> m_spriteram;

	/* misc */
	int m_sound_pending;
	int m_sound_nmi_enable;
	int m_pending_nmi;
	int m_sound_cmd;
	int m_sound_result;

	/* mcu */
	UINT8 m_from_main;
	UINT8 m_from_mcu;
	int m_mcu_sent;
	int m_main_sent;
	UINT8 m_port_a_in;
	UINT8 m_port_a_out;
	UINT8 m_ddr_a;
	UINT8 m_port_b_in;
	UINT8 m_port_b_out;
	UINT8 m_ddr_b;
=======
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_scrollram;
	required_shared_ptr<uint8_t> m_spriteram;
	required_region_ptr<uint8_t> m_priority_prom;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
<<<<<<< HEAD
	optional_device<cpu_device> m_mcu;
=======
	required_device<generic_latch_8_device> m_soundlatch;
	optional_device<generic_latch_8_device> m_soundlatch2;
	optional_device<input_merger_device> m_soundnmi;
	optional_device<taito68705_mcu_device> m_bmcu;
>>>>>>> upstream/master
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	DECLARE_WRITE8_MEMBER(lsasquad_bankswitch_w);
	DECLARE_WRITE8_MEMBER(lsasquad_sh_nmi_disable_w);
	DECLARE_WRITE8_MEMBER(lsasquad_sh_nmi_enable_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(lsasquad_sound_command_w);
	DECLARE_READ8_MEMBER(lsasquad_sh_sound_command_r);
	DECLARE_WRITE8_MEMBER(lsasquad_sh_result_w);
	DECLARE_READ8_MEMBER(lsasquad_sound_result_r);
	DECLARE_READ8_MEMBER(lsasquad_sound_status_r);
	DECLARE_READ8_MEMBER(daikaiju_sh_sound_command_r);
	DECLARE_READ8_MEMBER(daikaiju_sound_status_r);
	DECLARE_READ8_MEMBER(lsasquad_68705_port_a_r);
	DECLARE_WRITE8_MEMBER(lsasquad_68705_port_a_w);
	DECLARE_WRITE8_MEMBER(lsasquad_68705_ddr_a_w);
	DECLARE_READ8_MEMBER(lsasquad_68705_port_b_r);
	DECLARE_WRITE8_MEMBER(lsasquad_68705_port_b_w);
	DECLARE_WRITE8_MEMBER(lsasquad_68705_ddr_b_w);
	DECLARE_WRITE8_MEMBER(lsasquad_mcu_w);
	DECLARE_READ8_MEMBER(lsasquad_mcu_r);
=======
	DECLARE_READ8_MEMBER(lsasquad_sound_status_r);
	DECLARE_READ8_MEMBER(daikaiju_sound_status_r);

>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(lsasquad_mcu_status_r);
	DECLARE_READ8_MEMBER(daikaiju_mcu_status_r);
	DECLARE_WRITE8_MEMBER(unk);
	DECLARE_MACHINE_START(lsasquad);
	DECLARE_MACHINE_RESET(lsasquad);
<<<<<<< HEAD
	UINT32 screen_update_lsasquad(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_daikaiju(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(nmi_callback);
	void draw_layer( bitmap_ind16 &bitmap, const rectangle &cliprect, UINT8 *scrollram );
	int draw_layer_daikaiju( bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int  * previd, int type );
	void drawbg( bitmap_ind16 &bitmap, const rectangle &cliprect, int type );
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
=======
	uint32_t screen_update_lsasquad(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_daikaiju(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(nmi_callback);
	void draw_layer( bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t *scrollram );
	int draw_layer_daikaiju( bitmap_ind16 &bitmap, const rectangle &cliprect, int offs, int  * previd, int type );
	void drawbg( bitmap_ind16 &bitmap, const rectangle &cliprect, int type );
	void draw_sprites( bitmap_ind16 &bitmap, const rectangle &cliprect, uint8_t priority );
>>>>>>> upstream/master
};
