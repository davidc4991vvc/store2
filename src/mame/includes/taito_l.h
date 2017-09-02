// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#include "sound/msm5205.h"
#include "sound/2203intf.h"

#define TAITOL_SPRITERAM_SIZE 0x400
=======
#include "machine/74157.h"
#include "machine/upd4701.h"
#include "sound/msm5205.h"
#include "sound/2203intf.h"

>>>>>>> upstream/master

class taitol_state : public driver_device
{
public:
	taitol_state(const machine_config &mconfig, device_type type, const char *tag)
<<<<<<< HEAD
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_msm(*this, "msm"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")
	{
	}

	/* memory pointers */
	UINT8 *       m_shared_ram;
=======
		: driver_device(mconfig, type, tag)
		, m_main_cpu(*this, "maincpu")
		, m_main_prg(*this, "maincpu")
		, m_main_bnk(*this, "bank1")
		, m_ram_bnks(*this, "bank%u", 2)
		, m_gfxdecode(*this, "gfxdecode")
		, m_palette(*this, "palette")
	{
	}

	static constexpr size_t SPRITERAM_SIZE = 0x400;

	/* memory pointers */
	u8 *       m_shared_ram;
>>>>>>> upstream/master

	/* video-related */
	tilemap_t *m_bg18_tilemap;
	tilemap_t *m_bg19_tilemap;
	tilemap_t *m_ch1a_tilemap;
<<<<<<< HEAD
	UINT8 m_buff_spriteram[TAITOL_SPRITERAM_SIZE];
=======
	u8 m_buff_spriteram[SPRITERAM_SIZE];
>>>>>>> upstream/master
	int m_cur_ctrl;
	int m_horshoes_gfxbank;
	int m_bankc[4];
	int m_flipscreen;

	/* misc */
	void (taitol_state::*m_current_notifier[4])(int);
<<<<<<< HEAD
	UINT8 *m_current_base[4];

	int m_cur_rombank;
	int m_cur_rombank2;
	int m_cur_rambank[4];
	int m_irq_adr_table[3];
	int m_irq_enable;
	int m_adpcm_pos;
	int m_adpcm_data;
	int m_trackx;
	int m_tracky;
	int m_mux_ctrl;
	int m_extport;
	int m_last_irq_level;
	int m_high;
	int m_high2;
	int m_last_data_adr;
	int m_last_data;
	int m_cur_bank;

	const UINT8 *m_mcu_reply;
	int m_mcu_pos;
	int m_mcu_reply_len;

	const char *m_porte0_tag;
	const char *m_porte1_tag;
	const char *m_portf0_tag;
	const char *m_portf1_tag;

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	optional_device<msm5205_device> m_msm;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	/* memory buffers */
	UINT8         m_rambanks[0x1000 * 12];
	UINT8         m_palette_ram[0x1000];
	UINT8         m_empty_ram[0x1000];
=======
	u8 *m_current_base[4];

	int m_cur_rombank;
	int m_cur_rambank[4];
	int m_irq_adr_table[3];
	int m_irq_enable;
	int m_last_irq_level;
	int m_high;

	/* memory buffers */
	u8 m_rambanks[0x1000 * 12];
	u8 m_palette_ram[0x1000];
	u8 m_empty_ram[0x1000];
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(irq_adr_w);
	DECLARE_READ8_MEMBER(irq_adr_r);
	DECLARE_WRITE8_MEMBER(irq_enable_w);
	DECLARE_READ8_MEMBER(irq_enable_r);
	DECLARE_WRITE8_MEMBER(rombankswitch_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(rombank2switch_w);
	DECLARE_READ8_MEMBER(rombankswitch_r);
	DECLARE_READ8_MEMBER(rombank2switch_r);
=======
	DECLARE_READ8_MEMBER(rombankswitch_r);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(rambankswitch_w);
	DECLARE_READ8_MEMBER(rambankswitch_r);
	DECLARE_WRITE8_MEMBER(bank0_w);
	DECLARE_WRITE8_MEMBER(bank1_w);
	DECLARE_WRITE8_MEMBER(bank2_w);
	DECLARE_WRITE8_MEMBER(bank3_w);
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(control2_w);
	DECLARE_WRITE8_MEMBER(mcu_data_w);
	DECLARE_WRITE8_MEMBER(mcu_control_w);
	DECLARE_READ8_MEMBER(mcu_data_r);
	DECLARE_READ8_MEMBER(mcu_control_r);
	DECLARE_WRITE8_MEMBER(sound_w);
	DECLARE_READ8_MEMBER(mux_r);
	DECLARE_WRITE8_MEMBER(mux_w);
	DECLARE_WRITE8_MEMBER(mux_ctrl_w);
	DECLARE_WRITE8_MEMBER(champwr_msm5205_lo_w);
	DECLARE_WRITE8_MEMBER(champwr_msm5205_hi_w);
	DECLARE_READ8_MEMBER(horshoes_tracky_reset_r);
	DECLARE_READ8_MEMBER(horshoes_trackx_reset_r);
	DECLARE_READ8_MEMBER(horshoes_tracky_lo_r);
	DECLARE_READ8_MEMBER(horshoes_tracky_hi_r);
	DECLARE_READ8_MEMBER(horshoes_trackx_lo_r);
	DECLARE_READ8_MEMBER(horshoes_trackx_hi_r);
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	DECLARE_WRITE8_MEMBER(horshoes_bankg_w);
=======
	DECLARE_WRITE8_MEMBER(coin_control_w);
	DECLARE_WRITE8_MEMBER(mcu_control_w);
	DECLARE_READ8_MEMBER(mcu_control_r);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(taitol_bankc_w);
	DECLARE_READ8_MEMBER(taitol_bankc_r);
	DECLARE_WRITE8_MEMBER(taitol_control_w);
	DECLARE_READ8_MEMBER(taitol_control_r);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(portA_r);
	DECLARE_READ8_MEMBER(portB_r);
	DECLARE_READ8_MEMBER(extport_select_and_ym2203_r);
	DECLARE_WRITE8_MEMBER(champwr_msm5205_start_w);
	DECLARE_WRITE8_MEMBER(champwr_msm5205_stop_w);
	DECLARE_WRITE8_MEMBER(champwr_msm5205_volume_w);
	DECLARE_WRITE8_MEMBER(portA_w);
	DECLARE_DRIVER_INIT(plottinga);
=======
>>>>>>> upstream/master
	TILE_GET_INFO_MEMBER(get_bg18_tile_info);
	TILE_GET_INFO_MEMBER(get_bg19_tile_info);
	TILE_GET_INFO_MEMBER(get_ch1a_tile_info);
	DECLARE_MACHINE_START(taito_l);
<<<<<<< HEAD
	DECLARE_MACHINE_RESET(fhawk);
	DECLARE_VIDEO_START(taitol);
	DECLARE_MACHINE_RESET(kurikint);
	DECLARE_MACHINE_RESET(plotting);
	DECLARE_MACHINE_RESET(evilston);
	DECLARE_MACHINE_RESET(champwr);
	DECLARE_MACHINE_RESET(raimais);
	DECLARE_MACHINE_RESET(puzznic);
	DECLARE_MACHINE_RESET(horshoes);
	DECLARE_MACHINE_RESET(palamed);
	DECLARE_MACHINE_RESET(cachat);
	UINT32 screen_update_taitol(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_taitol(screen_device &screen, bool state);
	TIMER_DEVICE_CALLBACK_MEMBER(vbl_interrupt);
	IRQ_CALLBACK_MEMBER(irq_callback);
	void taitol_chardef14_m( int offset );
	void taitol_chardef15_m( int offset );
	void taitol_chardef16_m( int offset );
	void taitol_chardef17_m( int offset );
	void taitol_chardef1c_m( int offset );
	void taitol_chardef1d_m( int offset );
	void taitol_chardef1e_m( int offset );
	void taitol_chardef1f_m( int offset );
	void taitol_bg18_m( int offset );
	void taitol_bg19_m( int offset );
	void taitol_char1a_m( int offset );
	void taitol_obj1b_m( int offset );
	void draw_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect );
	void palette_notifier(int addr);
	void state_register(  );
	void taito_machine_reset();
	void bank_w(address_space &space, offs_t offset, UINT8 data, int banknum );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	DECLARE_WRITE_LINE_MEMBER(champwr_msm5205_vck);
=======
	DECLARE_VIDEO_START(taito_l);
	DECLARE_MACHINE_RESET(taito_l);
	u32 screen_update_taitol(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank_taitol);
	TIMER_DEVICE_CALLBACK_MEMBER(vbl_interrupt);
	IRQ_CALLBACK_MEMBER(irq_callback);
	void taitol_chardef14_m(int offset);
	void taitol_chardef15_m(int offset);
	void taitol_chardef16_m(int offset);
	void taitol_chardef17_m(int offset);
	void taitol_chardef1c_m(int offset);
	void taitol_chardef1d_m(int offset);
	void taitol_chardef1e_m(int offset);
	void taitol_chardef1f_m(int offset);
	void taitol_bg18_m(int offset);
	void taitol_bg19_m(int offset);
	void taitol_char1a_m(int offset);
	void taitol_obj1b_m(int offset);
	void draw_sprites(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void palette_notifier(int addr);
	void bank_w(address_space &space, offs_t offset, u8 data, int banknum);

protected:
	virtual void state_register();
	virtual void taito_machine_reset();

	required_device<cpu_device>         m_main_cpu;
	required_region_ptr<u8>             m_main_prg;
	required_memory_bank                m_main_bnk;
	required_memory_bank_array<4>       m_ram_bnks;
	required_device<gfxdecode_device>   m_gfxdecode;
	required_device<palette_device>     m_palette;
};


class taitol_2cpu_state : public taitol_state
{
public:
	taitol_2cpu_state(const machine_config &mconfig, device_type type, const char *tag)
		: taitol_state(mconfig, type, tag)
		, m_audio_cpu(*this, "audiocpu")
		, m_audio_prg(*this, "audiocpu")
		, m_audio_bnk(*this, "bank7")
	{
	}

	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);

protected:
	virtual void state_register() override;
	virtual void taito_machine_reset() override;

	required_device<cpu_device> m_audio_cpu;
	required_region_ptr<u8>     m_audio_prg;
	optional_memory_bank        m_audio_bnk;
};


class fhawk_state : public taitol_2cpu_state
{
public:
	fhawk_state(const machine_config &mconfig, device_type type, const char *tag)
		: taitol_2cpu_state(mconfig, type, tag)
		, m_slave_prg(*this, "slave")
		, m_slave_bnk(*this, "bank6")
		, m_cur_rombank2(0)
		, m_high2(0)
		, m_cur_audio_bnk(0)
	{
	}

	DECLARE_WRITE8_MEMBER(rombank2switch_w);
	DECLARE_READ8_MEMBER(rombank2switch_r);
	DECLARE_WRITE8_MEMBER(portA_w);

protected:
	virtual void state_register() override;
	virtual void taito_machine_reset() override;

	required_region_ptr<u8>     m_slave_prg;
	required_memory_bank        m_slave_bnk;

	u8  m_cur_rombank2;
	u8  m_high2;
	u8  m_cur_audio_bnk;
};


class champwr_state : public fhawk_state
{
public:
	champwr_state(const machine_config &mconfig, device_type type, const char *tag)
		: fhawk_state(mconfig, type, tag)
		, m_msm(*this, "msm")
		, m_adpcm_rgn(*this, "adpcm")
		, m_adpcm_pos(0)
		, m_adpcm_data(-1)
	{
	}

	DECLARE_WRITE_LINE_MEMBER(msm5205_vck);

	DECLARE_WRITE8_MEMBER(msm5205_lo_w);
	DECLARE_WRITE8_MEMBER(msm5205_hi_w);
	DECLARE_WRITE8_MEMBER(msm5205_start_w);
	DECLARE_WRITE8_MEMBER(msm5205_stop_w);
	DECLARE_WRITE8_MEMBER(msm5205_volume_w);

protected:
	virtual void state_register() override;
	virtual void taito_machine_reset() override;

	required_device<msm5205_device> m_msm;
	required_region_ptr<u8>         m_adpcm_rgn;

	int m_adpcm_pos;
	int m_adpcm_data;
};


class taitol_1cpu_state : public taitol_state
{
public:
	taitol_1cpu_state(const machine_config &mconfig, device_type type, const char *tag)
		: taitol_state(mconfig, type, tag)
		, m_ymsnd(*this, "ymsnd")
		, m_mux(*this, {"dswmuxl", "dswmuxh", "inmuxl", "inmuxh"})
	{
	}

	DECLARE_READ8_MEMBER(extport_select_and_ym2203_r);

	DECLARE_DRIVER_INIT(plottinga);

	DECLARE_MACHINE_RESET(plotting);
	DECLARE_MACHINE_RESET(puzznic);
	DECLARE_MACHINE_RESET(palamed);
	DECLARE_MACHINE_RESET(cachat);

protected:
	virtual void state_register() override;
	virtual void taito_machine_reset() override;

	required_device<ym2203_device>  m_ymsnd;
	optional_device_array<ls157_device, 4> m_mux;
};


class horshoes_state : public taitol_1cpu_state
{
public:
	horshoes_state(const machine_config &mconfig, device_type type, const char *tag)
		: taitol_1cpu_state(mconfig, type, tag)
	{
	}

	DECLARE_WRITE8_MEMBER(bankg_w);

	DECLARE_MACHINE_RESET(horshoes);
>>>>>>> upstream/master
};
