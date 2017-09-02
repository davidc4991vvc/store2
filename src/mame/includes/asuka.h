// license:BSD-3-Clause
// copyright-holders:David Graves, Brian Troha
/*************************************************************************

    Asuka & Asuka  (+ Taito/Visco games on similar hardware)

*************************************************************************/
<<<<<<< HEAD

#include "machine/taitoio.h"
#include "sound/msm5205.h"
=======
#ifndef MAME_INCLUDES_ASUKA_H
#define MAME_INCLUDES_ASUKA_H

#pragma once


#include "machine/taitocchip.h"
#include "machine/taitoio.h"

#include "sound/msm5205.h"
#include "machine/74157.h"
>>>>>>> upstream/master
#include "video/pc090oj.h"
#include "video/tc0100scn.h"
#include "video/tc0110pcr.h"

<<<<<<< HEAD
=======

>>>>>>> upstream/master
class asuka_state : public driver_device
{
public:
	enum
	{
		TIMER_CADASH_INTERRUPT5
	};

	asuka_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_cadash_shared_ram(*this, "sharedram"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
<<<<<<< HEAD
		m_msm(*this, "msm"),
=======
		m_cchip(*this, "cchip"),
		m_msm(*this, "msm"),
		m_adpcm_select(*this, "adpcm_select"),
		m_sound_data(*this, "ymsnd"),
>>>>>>> upstream/master
		m_pc090oj(*this, "pc090oj"),
		m_tc0100scn(*this, "tc0100scn"),
		m_tc0110pcr(*this, "tc0110pcr"),
		m_tc0220ioc(*this, "tc0220ioc") { }

	/* video-related */
<<<<<<< HEAD
	UINT16      m_video_ctrl;
	UINT16      m_video_mask;
=======
	u16         m_video_ctrl;
	u16         m_video_mask;
>>>>>>> upstream/master

	/* c-chip */
	int         m_current_round;
	int         m_current_bank;

<<<<<<< HEAD
	UINT8       m_cval[26];
	UINT8       m_cc_port;
	UINT8       m_restart_status;

	/* misc */
	int         m_adpcm_pos;
	int         m_adpcm_data;

	optional_shared_ptr<UINT8> m_cadash_shared_ram;
=======
	u8          m_cval[26];
	u8          m_cc_port;
	u8          m_restart_status;

	/* misc */
	u16         m_adpcm_pos;
	bool        m_adpcm_ff;

	emu_timer *m_cadash_int5_timer;

	optional_shared_ptr<uint8_t> m_cadash_shared_ram;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
<<<<<<< HEAD
	optional_device<msm5205_device> m_msm;
=======
	optional_device<taito_cchip_device> m_cchip;
	optional_device<msm5205_device> m_msm;
	optional_device<ls157_device> m_adpcm_select;
	optional_region_ptr<u8> m_sound_data;
>>>>>>> upstream/master
	required_device<pc090oj_device> m_pc090oj;
	required_device<tc0100scn_device> m_tc0100scn;
	required_device<tc0110pcr_device> m_tc0110pcr;
	optional_device<tc0220ioc_device> m_tc0220ioc;
<<<<<<< HEAD
=======
	DECLARE_WRITE8_MEMBER(coin_control_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(sound_bankswitch_w);
	DECLARE_WRITE8_MEMBER(asuka_msm5205_address_w);
	DECLARE_READ16_MEMBER(cadash_share_r);
	DECLARE_WRITE16_MEMBER(cadash_share_w);
	DECLARE_WRITE16_MEMBER(asuka_spritectrl_w);
	DECLARE_WRITE8_MEMBER(sound_bankswitch_2151_w);
	DECLARE_WRITE8_MEMBER(asuka_msm5205_start_w);
	DECLARE_WRITE8_MEMBER(asuka_msm5205_stop_w);
<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
	UINT32 screen_update_bonzeadv(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 screen_update_asuka(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void screen_eof_asuka(screen_device &screen, bool state);
	INTERRUPT_GEN_MEMBER(cadash_interrupt);
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
	uint32_t screen_update_bonzeadv(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_asuka(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank_asuka);
	INTERRUPT_GEN_MEMBER(cadash_interrupt);
	DECLARE_DRIVER_INIT(cadash);
>>>>>>> upstream/master

	/*----------- defined in machine/bonzeadv.c -----------*/
	void WriteLevelData();
	void WriteRestartPos(int level );

	DECLARE_READ16_MEMBER( bonzeadv_cchip_ctrl_r );
	DECLARE_READ16_MEMBER( bonzeadv_cchip_ram_r );
	DECLARE_WRITE16_MEMBER( bonzeadv_cchip_ctrl_w );
	DECLARE_WRITE16_MEMBER( bonzeadv_cchip_bank_w );
	DECLARE_WRITE16_MEMBER( bonzeadv_cchip_ram_w );
<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	DECLARE_WRITE_LINE_MEMBER(asuka_msm5205_vck);

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
};
=======
	DECLARE_WRITE_LINE_MEMBER(asuka_msm5205_vck);

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
};

#endif // MAME_INCLUDES_ASUKA_H
>>>>>>> upstream/master
