// license:BSD-3-Clause
// copyright-holders:Luca Elia, Mirko Buffoni, Takahiro Nogi
<<<<<<< HEAD
=======

#pragma once

#ifndef MAME_INCLUDES_TNZS_H
#define MAME_INCLUDES_TNZS_H

>>>>>>> upstream/master
#include "sound/dac.h"
#include "sound/samples.h"
#include "video/seta001.h"
#include "cpu/mcs48/mcs48.h"
#include "machine/bankdev.h"
<<<<<<< HEAD

#define MAX_SAMPLES 0x2f        /* max samples */

enum
{
	MCU_NONE_INSECTX = 0,
	MCU_NONE_KAGEKI,
	MCU_NONE_TNZSB,
	MCU_NONE_KABUKIZ,
	MCU_EXTRMATN,
	MCU_ARKANOID,
	MCU_PLUMPOP,
	MCU_DRTOPPEL,
	MCU_CHUKATAI,
	MCU_TNZS
};

class tnzs_state : public driver_device
{
public:
	tnzs_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_subcpu(*this, "sub"),
		m_mcu(*this, "mcu"),
		m_seta001(*this, "spritegen"),
		m_dac(*this, "dac"),
		m_samples(*this, "samples"),
		m_palette(*this, "palette"),
		m_mainbank(*this, "mainbank"),
		m_subbank(*this, "subbank"),
		m_audiobank(*this, "audiobank"),
		m_dswa(*this, "DSWA"),
		m_dswb(*this, "DSWB"),
		m_in0(*this, "IN0"),
		m_in1(*this, "IN1"),
		m_in2(*this, "IN2"),
		m_coin1(*this, "COIN1"),
		m_coin2(*this, "COIN2"),
		m_an1(*this, "AN1"),
		m_an2(*this, "AN2")
		{ }

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	optional_device<cpu_device> m_subcpu;
	optional_device<upi41_cpu_device> m_mcu;
	optional_device<seta001_device> m_seta001;
	optional_device<dac_device> m_dac;
	optional_device<samples_device> m_samples;
	required_device<palette_device> m_palette;
	optional_device<address_map_bank_device> m_mainbank;
	optional_memory_bank m_subbank; /* optional because of reuse from cchance.c */
	optional_memory_bank m_audiobank;
	required_ioport m_dswa;
	required_ioport m_dswb;
	required_ioport m_in0;
	required_ioport m_in1;
	required_ioport m_in2;
	optional_ioport m_coin1;
	optional_ioport m_coin2;
	optional_ioport m_an1;
	optional_ioport m_an2;

	/* sound-related */
	INT16    *m_sampledata[MAX_SAMPLES];
	int      m_samplesize[MAX_SAMPLES];

	/* misc / mcu */
	int      m_kageki_csport_sel;
	int      m_input_select;
	int      m_mcu_type;
=======
#include "machine/gen_latch.h"
#include "machine/upd4701.h"

#define MAX_SAMPLES 0x2f        /* max samples */

class tnzs_base_state : public driver_device
{
public:
	tnzs_base_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_subcpu(*this, "sub")
		, m_seta001(*this, "spritegen")
		, m_palette(*this, "palette")
		, m_mainbank(*this, "mainbank")
		, m_subbank(*this, "subbank")
	{ }

	virtual void machine_start() override;

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w);

	DECLARE_WRITE8_MEMBER(ramrom_bankswitch_w);

	uint32_t screen_update_tnzs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank_tnzs);

	DECLARE_PALETTE_INIT(prompalette);

protected:
	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_subcpu;
	optional_device<seta001_device> m_seta001;
	required_device<palette_device> m_palette;
	optional_device<address_map_bank_device> m_mainbank; /* FIXME: optional because of reuse from cchance.cpp */
	optional_memory_bank m_subbank; /* FIXME: optional because of reuse from cchance.cpp */

	/* misc / mcu */
	int      m_bank2;
};

class tnzs_mcu_state : public tnzs_base_state
{
public:
	tnzs_mcu_state(const machine_config &mconfig, device_type type, const char *tag, bool lockout_level)
		: tnzs_base_state(mconfig, type, tag)
		, m_mcu(*this, "mcu")
		, m_upd4701(*this, "upd4701")
		, m_in0(*this, "IN0")
		, m_in1(*this, "IN1")
		, m_in2(*this, "IN2")
		, m_input_select(0)
		, m_lockout_level(lockout_level)
	{ }

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w) override;

	DECLARE_READ8_MEMBER(mcu_port1_r);
	DECLARE_READ8_MEMBER(mcu_port2_r);
	DECLARE_WRITE8_MEMBER(mcu_port2_w );
	DECLARE_READ8_MEMBER(mcu_r);
	DECLARE_WRITE8_MEMBER(mcu_w);

	DECLARE_READ8_MEMBER(analog_r);

protected:
	required_device<upi41_cpu_device> m_mcu;
	optional_device<upd4701_device> m_upd4701;

	required_ioport m_in0;
	required_ioport m_in1;
	required_ioport m_in2;

	int      m_input_select;
	bool     m_lockout_level;
};

class tnzs_state : public tnzs_mcu_state
{
public:
	tnzs_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_mcu_state(mconfig, type, tag, true)
	{ }
};

class extrmatn_state : public tnzs_mcu_state
{
public:
	extrmatn_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_mcu_state(mconfig, type, tag, false)
	{ }
};

class arknoid2_state : public extrmatn_state
{
public:
	arknoid2_state(const machine_config &mconfig, device_type type, const char *tag)
		: extrmatn_state(mconfig, type, tag)
		, m_coin1(*this, "COIN1")
		, m_coin2(*this, "COIN2")
		, m_in0(*this, "IN0")
		, m_in1(*this, "IN1")
		, m_in2(*this, "IN2")
	{ }

	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w) override;

	DECLARE_READ8_MEMBER(mcu_r);
	DECLARE_WRITE8_MEMBER(mcu_w);
	INTERRUPT_GEN_MEMBER(mcu_interrupt);

private:
	required_ioport m_coin1;
	required_ioport m_coin2;
	required_ioport m_in0;
	required_ioport m_in1;
	required_ioport m_in2;

	void mcu_reset();

>>>>>>> upstream/master
	int      m_mcu_initializing;
	int      m_mcu_coinage_init;
	int      m_mcu_command;
	int      m_mcu_readcredits;
	int      m_mcu_reportcoin;
	int      m_insertcoin;
<<<<<<< HEAD
	UINT8    m_mcu_coinage[4];
	UINT8    m_mcu_coins_a;
	UINT8    m_mcu_coins_b;
	UINT8    m_mcu_credits;
	int      m_bank2;

	DECLARE_WRITE8_MEMBER(tnzsb_sound_command_w);
	DECLARE_WRITE8_MEMBER(jpopnics_subbankswitch_w);
	DECLARE_READ8_MEMBER(tnzs_port1_r);
	DECLARE_READ8_MEMBER(tnzs_port2_r);
	DECLARE_WRITE8_MEMBER(tnzs_port2_w);
	DECLARE_READ8_MEMBER(arknoid2_sh_f000_r);
	DECLARE_READ8_MEMBER(tnzs_mcu_r);
	DECLARE_WRITE8_MEMBER(tnzs_mcu_w);
	DECLARE_WRITE8_MEMBER(tnzs_ramrom_bankswitch_w);
	DECLARE_WRITE8_MEMBER(tnzs_bankswitch1_w);
	DECLARE_READ8_MEMBER(mcu_tnzs_r);
	DECLARE_WRITE8_MEMBER(mcu_tnzs_w);
	DECLARE_READ8_MEMBER(mcu_arknoid2_r);
	DECLARE_WRITE8_MEMBER(mcu_arknoid2_w);
	DECLARE_READ8_MEMBER(mcu_extrmatn_r);
	DECLARE_WRITE8_MEMBER(mcu_extrmatn_w);
	DECLARE_WRITE8_MEMBER(tnzs_sync_kludge_w);
	DECLARE_READ8_MEMBER(kageki_csport_r);
	DECLARE_WRITE8_MEMBER(kageki_csport_w);
	DECLARE_WRITE8_MEMBER(kabukiz_sound_bank_w);
	DECLARE_WRITE8_MEMBER(kabukiz_sample_w);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);

	SAMPLES_START_CB_MEMBER(kageki_init_samples);

	DECLARE_DRIVER_INIT(arknoid2);
	DECLARE_DRIVER_INIT(extrmatn);
	DECLARE_DRIVER_INIT(drtoppel);
	DECLARE_DRIVER_INIT(kabukiz);
	DECLARE_DRIVER_INIT(plumpop);
	DECLARE_DRIVER_INIT(insectx);
	DECLARE_DRIVER_INIT(tnzs);
	DECLARE_DRIVER_INIT(kageki);
	DECLARE_DRIVER_INIT(chukatai);
	DECLARE_DRIVER_INIT(tnzsb);
	DECLARE_MACHINE_START(tnzs);
	DECLARE_MACHINE_RESET(tnzs);
	DECLARE_PALETTE_INIT(arknoid2);
	DECLARE_MACHINE_START(tnzs_common);
	DECLARE_MACHINE_RESET(jpopnics);

	UINT32 screen_update_tnzs(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_tnzs(screen_device &screen, bool state);

	INTERRUPT_GEN_MEMBER(arknoid2_interrupt);
	TIMER_CALLBACK_MEMBER(kludge_callback);

	void tnzs_postload();
	void mcu_reset();
	void mcu_handle_coins(int coin);
};
=======
	uint8_t    m_mcu_coinage[4];
	uint8_t    m_mcu_coins_a;
	uint8_t    m_mcu_coins_b;
	uint8_t    m_mcu_credits;

	void mcu_handle_coins(int coin);
};

class kageki_state : public tnzs_base_state
{
public:
	kageki_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_base_state(mconfig, type, tag)
		, m_samples(*this, "samples")
		, m_dswa(*this, "DSWA")
		, m_dswb(*this, "DSWB")
		, m_csport_sel(0)
	{ }

	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w) override;

	DECLARE_READ8_MEMBER(csport_r);
	DECLARE_WRITE8_MEMBER(csport_w);

	DECLARE_MACHINE_RESET(kageki);
	DECLARE_DRIVER_INIT(kageki);

	SAMPLES_START_CB_MEMBER(init_samples);

private:
	required_device<samples_device> m_samples;

	required_ioport m_dswa;
	required_ioport m_dswb;

	/* sound-related */
	std::unique_ptr<int16_t[]>    m_sampledata[MAX_SAMPLES];
	int      m_samplesize[MAX_SAMPLES];

	int      m_csport_sel;
};

class jpopnics_state : public tnzs_base_state
{
public:
	jpopnics_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_base_state(mconfig, type, tag)
		, m_upd4701(*this, "upd4701")
	{ }

	virtual void machine_reset() override;

	DECLARE_WRITE8_MEMBER(subbankswitch_w);

private:
	required_device<upd4701_device> m_upd4701;
};

class insectx_state : public tnzs_base_state
{
public:
	insectx_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_base_state(mconfig, type, tag)
	{ }

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w) override;
};

class tnzsb_state : public tnzs_base_state
{
public:
	tnzsb_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzs_base_state(mconfig, type, tag)
		, m_audiocpu(*this, "audiocpu")
		, m_soundlatch(*this, "soundlatch")
	{ }

	DECLARE_WRITE_LINE_MEMBER(ym2203_irqhandler);

	DECLARE_WRITE8_MEMBER(sound_command_w);

	virtual DECLARE_WRITE8_MEMBER(bankswitch1_w) override;

protected:
	required_device<cpu_device> m_audiocpu;
	required_device<generic_latch_8_device> m_soundlatch;
};

class kabukiz_state : public tnzsb_state
{
public:
	kabukiz_state(const machine_config &mconfig, device_type type, const char *tag)
		: tnzsb_state(mconfig, type, tag)
		, m_audiobank(*this, "audiobank")
	{ }

	virtual void machine_start() override;

	DECLARE_WRITE8_MEMBER(sound_bank_w);

protected:
	required_memory_bank m_audiobank;
};

#endif // MAME_INCLUDES_TNZS_H
>>>>>>> upstream/master
