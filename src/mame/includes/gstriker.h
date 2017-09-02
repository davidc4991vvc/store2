// license:BSD-3-Clause
// copyright-holders:Farfetch'd, David Haywood
<<<<<<< HEAD
#ifndef __GSTRIKER_H
#define __GSTRIKER_H

#include "video/vsystem_spr.h"
#include "video/mb60553.h"
#include "video/vs920a.h"
=======

#ifndef __GSTRIKER_H
#define __GSTRIKER_H

#include "machine/gen_latch.h"
#include "machine/mb3773.h"
#include "video/vsystem_spr.h"
#include "video/mb60553.h"
#include "video/vs920a.h"
#include "screen.h"
>>>>>>> upstream/master



class gstriker_state : public driver_device
{
public:
	gstriker_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_spr(*this, "vsystem_spr"),
		m_bg(*this, "zoomtilemap"),
		m_tx(*this, "texttilemap"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
<<<<<<< HEAD
=======
		m_soundlatch(*this, "soundlatch"),
		m_watchdog(*this, "watchdog"),
>>>>>>> upstream/master
		m_CG10103_m_vram(*this, "cg10103_m_vram"),
		m_work_ram(*this, "work_ram"),
		m_mixerregs1(*this, "mixerregs1"),
		m_mixerregs2(*this, "mixerregs2")
	{ }

	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<vsystem_spr_device> m_spr;
	required_device<mb60553_zooming_tilemap_device> m_bg;
	required_device<vs920a_text_tilemap_device> m_tx;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
<<<<<<< HEAD

	required_shared_ptr<UINT16> m_CG10103_m_vram;
	required_shared_ptr<UINT16> m_work_ram;
	required_shared_ptr<UINT16> m_mixerregs1;
	required_shared_ptr<UINT16> m_mixerregs2;

	UINT16 m_dmmy_8f_ret;
	int m_pending_command;
	int m_gametype;
	UINT16 m_mcu_data;
	UINT16 m_prot_reg[2];

	// common
	DECLARE_READ16_MEMBER(dmmy_8f);
	DECLARE_WRITE16_MEMBER(sound_command_w);
	DECLARE_READ16_MEMBER(pending_command_r);
	DECLARE_WRITE8_MEMBER(sh_pending_command_clear_w);
	DECLARE_WRITE8_MEMBER(sh_bankswitch_w);

	// vgoalsoc and twrldc
	DECLARE_WRITE16_MEMBER(twrldc94_mcu_w);
	DECLARE_READ16_MEMBER(twrldc94_mcu_r);
	DECLARE_WRITE16_MEMBER(twrldc94_prot_reg_w);
	DECLARE_READ16_MEMBER(twrldc94_prot_reg_r);
=======
	required_device<generic_latch_8_device> m_soundlatch;
	required_device<mb3773_device> m_watchdog;

	required_shared_ptr<uint16_t> m_CG10103_m_vram;
	std::unique_ptr<uint16_t[]>    m_buffered_spriteram;
	std::unique_ptr<uint16_t[]>    m_buffered_spriteram2;
	required_shared_ptr<uint16_t> m_work_ram;
	required_shared_ptr<uint16_t> m_mixerregs1;
	required_shared_ptr<uint16_t> m_mixerregs2;

	enum {
		TECMO_WCUP94_MCU = 1,
		TECMO_WCUP94A_MCU,
		VGOAL_SOCCER_MCU
	}m_mcutype;
	int m_gametype;
	uint16_t m_prot_reg[2];

	// common
	DECLARE_WRITE8_MEMBER(sh_bankswitch_w);

	// vgoalsoc and twrldc
	DECLARE_WRITE8_MEMBER(twcup94_prot_reg_w);
>>>>>>> upstream/master

	// vgoalsoc only
	DECLARE_READ16_MEMBER(vbl_toggle_r);
	DECLARE_WRITE16_MEMBER(vbl_toggle_w);

<<<<<<< HEAD
	virtual void machine_start();
	virtual void video_start();
	DECLARE_DRIVER_INIT(twrldc94a);
	DECLARE_DRIVER_INIT(vgoalsoc);
	DECLARE_DRIVER_INIT(twrldc94);

	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void machine_start() override;
	virtual void video_start() override;
	DECLARE_DRIVER_INIT(twcup94a);
	DECLARE_DRIVER_INIT(vgoalsoc);
	DECLARE_DRIVER_INIT(twcup94);

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank);
>>>>>>> upstream/master

	void mcu_init();
};

#endif
