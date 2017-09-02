// license:BSD-3-Clause
// copyright-holders:Chris Moore, Nicola Salmoria
<<<<<<< HEAD
=======
#ifndef MAME_INCLUDES_BUBLBOBL_H
#define MAME_INCLUDES_BUBLBOBL_H

#pragma once

#include "cpu/m6805/m68705.h"
#include "machine/input_merger.h"
#include "machine/gen_latch.h"
#include "sound/2203intf.h"
#include "sound/3526intf.h"
#include "screen.h"

#include "machine/taito68705interface.h"

>>>>>>> upstream/master

class bublbobl_state : public driver_device
{
public:
	enum
	{
<<<<<<< HEAD
		TIMER_NMI,
=======
>>>>>>> upstream/master
		TIMER_M68705_IRQ_ACK
	};

	bublbobl_state(const machine_config &mconfig, device_type type, const char *tag)
<<<<<<< HEAD
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_objectram(*this, "objectram"),
		m_mcu_sharedram(*this, "mcu_sharedram"),
		m_maincpu(*this, "maincpu"),
		m_mcu(*this, "mcu"),
		m_audiocpu(*this, "audiocpu"),
		m_slave(*this, "slave"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"){ }

	/* memory pointers */
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_objectram;
	optional_shared_ptr<UINT8> m_mcu_sharedram;

	/* video-related */
	int      m_video_enable;

	/* sound-related */
	int      m_sound_nmi_enable;
	int      m_pending_nmi;
	int      m_sound_status;

	/* mcu-related */
	/* Tokio*/
	int      m_tokio_prot_count;
	/* Bubble Bobble MCU */
	UINT8    m_ddr1;
	UINT8    m_ddr2;
	UINT8    m_ddr3;
	UINT8    m_ddr4;
	UINT8    m_port1_in;
	UINT8    m_port2_in;
	UINT8    m_port3_in;
	UINT8    m_port4_in;
	UINT8    m_port1_out;
	UINT8    m_port2_out;
	UINT8    m_port3_out;
	UINT8    m_port4_out;
	/* Bubble Bobble 68705 */
	UINT8    m_port_a_in;
	UINT8    m_port_a_out;
	UINT8    m_ddr_a;
	UINT8    m_port_b_in;
	UINT8    m_port_b_out;
	UINT8    m_ddr_b;
	int      m_address;
	int      m_latch;
=======
		: driver_device(mconfig, type, tag)
		, m_videoram(*this, "videoram")
		, m_objectram(*this, "objectram")
		, m_mcu_sharedram(*this, "mcu_sharedram")
		, m_maincpu(*this, "maincpu")
		, m_mcu(*this, "mcu")
		, m_audiocpu(*this, "audiocpu")
		, m_subcpu(*this, "subcpu")
		, m_screen(*this, "screen")
		, m_gfxdecode(*this, "gfxdecode")
		, m_palette(*this, "palette")
		, m_ym2203(*this, "ym2203")
		, m_ym3526(*this, "ym3526")
		, m_soundirq(*this, "soundirq")
		, m_soundnmi(*this, "soundnmi")
		, m_main_to_sound(*this, "main_to_sound")
		, m_sound_to_main(*this, "sound_to_main")
	{ }

	/* memory pointers */
	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_objectram;
	optional_shared_ptr<uint8_t> m_mcu_sharedram;

	/* video-related */
	bool     m_video_enable;

	/* sound-related */
	int      m_sreset_old;

	/* mcu-related */

	/* Bubble Bobble MCU */
	uint8_t    m_ddr1;
	uint8_t    m_ddr2;
	uint8_t    m_ddr3;
	uint8_t    m_ddr4;
	uint8_t    m_port1_in;
	uint8_t    m_port2_in;
	uint8_t    m_port3_in;
	uint8_t    m_port4_in;
	uint8_t    m_port1_out;
	uint8_t    m_port2_out;
	uint8_t    m_port3_out;
	uint8_t    m_port4_out;
>>>>>>> upstream/master
	/* Bobble Bobble */
	int      m_ic43_a;
	int      m_ic43_b;

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_mcu;
	required_device<cpu_device> m_audiocpu;
<<<<<<< HEAD
	required_device<cpu_device> m_slave;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

=======
	required_device<cpu_device> m_subcpu;
	required_device<screen_device> m_screen;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	optional_device<ym2203_device> m_ym2203;
	optional_device<ym3526_device> m_ym3526;
	optional_device<input_merger_device> m_soundirq;
	required_device<input_merger_device> m_soundnmi;
	required_device<generic_latch_8_device> m_main_to_sound;
	required_device<generic_latch_8_device> m_sound_to_main;


	void common_sreset(int state);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(bublbobl_bankswitch_w);
	DECLARE_WRITE8_MEMBER(tokio_bankswitch_w);
	DECLARE_WRITE8_MEMBER(tokio_videoctrl_w);
	DECLARE_WRITE8_MEMBER(bublbobl_nmitrigger_w);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(tokio_mcu_r);
	DECLARE_READ8_MEMBER(tokiob_mcu_r);
	DECLARE_WRITE8_MEMBER(bublbobl_sound_command_w);
	DECLARE_WRITE8_MEMBER(bublbobl_sh_nmi_disable_w);
	DECLARE_WRITE8_MEMBER(bublbobl_sh_nmi_enable_w);
	DECLARE_WRITE8_MEMBER(bublbobl_soundcpu_reset_w);
	DECLARE_READ8_MEMBER(bublbobl_sound_status_r);
	DECLARE_WRITE8_MEMBER(bublbobl_sound_status_w);
=======
	DECLARE_READ8_MEMBER(tokiob_mcu_r);
	DECLARE_WRITE8_MEMBER(bublbobl_soundcpu_reset_w);
	DECLARE_READ8_MEMBER(common_sound_semaphores_r);
>>>>>>> upstream/master
	DECLARE_READ8_MEMBER(bublbobl_mcu_ddr1_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_ddr1_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_ddr2_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_ddr2_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_ddr3_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_ddr3_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_ddr4_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_ddr4_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_port1_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_port1_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_port2_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_port2_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_port3_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_port3_w);
	DECLARE_READ8_MEMBER(bublbobl_mcu_port4_r);
	DECLARE_WRITE8_MEMBER(bublbobl_mcu_port4_w);
	DECLARE_READ8_MEMBER(boblbobl_ic43_a_r);
	DECLARE_WRITE8_MEMBER(boblbobl_ic43_a_w);
	DECLARE_WRITE8_MEMBER(boblbobl_ic43_b_w);
	DECLARE_READ8_MEMBER(boblbobl_ic43_b_r);
<<<<<<< HEAD
	DECLARE_READ8_MEMBER(bublbobl_68705_port_a_r);
	DECLARE_WRITE8_MEMBER(bublbobl_68705_port_a_w);
	DECLARE_WRITE8_MEMBER(bublbobl_68705_ddr_a_w);
	DECLARE_READ8_MEMBER(bublbobl_68705_port_b_r);
	DECLARE_WRITE8_MEMBER(bublbobl_68705_port_b_w);
	DECLARE_WRITE8_MEMBER(bublbobl_68705_ddr_b_w);
	DECLARE_DRIVER_INIT(tokiob);
	DECLARE_DRIVER_INIT(tokio);
	DECLARE_DRIVER_INIT(dland);
	DECLARE_DRIVER_INIT(bublbobl);
=======

	DECLARE_DRIVER_INIT(dland);
	DECLARE_DRIVER_INIT(common);
>>>>>>> upstream/master
	DECLARE_MACHINE_START(tokio);
	DECLARE_MACHINE_RESET(tokio);
	DECLARE_MACHINE_START(bublbobl);
	DECLARE_MACHINE_RESET(bublbobl);
	DECLARE_MACHINE_START(boblbobl);
	DECLARE_MACHINE_RESET(boblbobl);
<<<<<<< HEAD
	DECLARE_MACHINE_START(bub68705);
	DECLARE_MACHINE_RESET(bub68705);
	DECLARE_MACHINE_START(common);
	DECLARE_MACHINE_RESET(common);
	UINT32 screen_update_bublbobl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(bublbobl_m68705_interrupt);
	void configure_banks(  );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
};
=======
	DECLARE_MACHINE_START(common);
	DECLARE_MACHINE_RESET(common);
	uint32_t screen_update_bublbobl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void configure_banks();

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
};


class bub68705_state : public bublbobl_state
{
public:
	bub68705_state(const machine_config &mconfig, device_type type, const char *tag)
		: bublbobl_state(mconfig, type, tag)
		, m_mcu(*this, "mcu")
		, m_mux_ports(*this, { "DSW0", "DSW1", "IN1", "IN2" })
		, m_port_a_out(0xff)
		, m_port_b_out(0xff)
		, m_address(0)
		, m_latch(0)
	{
	}

	DECLARE_WRITE8_MEMBER(port_a_w);
	DECLARE_WRITE8_MEMBER(port_b_w);

	INTERRUPT_GEN_MEMBER(bublbobl_m68705_interrupt);

	DECLARE_MACHINE_START(bub68705);
	DECLARE_MACHINE_RESET(bub68705);

protected:
	required_device<m68705p_device> m_mcu;
	required_ioport_array<4>        m_mux_ports;

	uint8_t     m_port_a_out;
	uint8_t     m_port_b_out;
	uint16_t    m_address;
	uint8_t     m_latch;
};

#endif // MAME_INCLUDES_BUBLBOBL_H
>>>>>>> upstream/master
