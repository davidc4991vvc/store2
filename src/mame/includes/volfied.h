// license:BSD-3-Clause
// copyright-holders:Bryan McPhail, Nicola Salmoria
/*************************************************************************

    Volfied

*************************************************************************/
<<<<<<< HEAD

#include "video/pc090oj.h"
=======
#ifndef MAME_INCLUDES_VOLFIED_H
#define MAME_INCLUDES_VOLFIED_H

#pragma once

#include "machine/taitocchip.h"
#include "video/pc090oj.h"
#include "screen.h"
>>>>>>> upstream/master

class volfied_state : public driver_device
{
public:
	enum
	{
		TIMER_VOLFIED
	};

	volfied_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
<<<<<<< HEAD
=======
		m_cchip(*this, "cchip"),
>>>>>>> upstream/master
		m_pc090oj(*this, "pc090oj"),
		m_screen(*this, "screen") { }

	/* memory pointers */
<<<<<<< HEAD
	UINT16 *    m_video_ram;
	UINT8  *    m_cchip_ram;

	/* video-related */
	UINT16      m_video_ctrl;
	UINT16      m_video_mask;

	/* c-chip */
	UINT8       m_current_bank;
	UINT8       m_current_flag;
	UINT8       m_cc_port;
	UINT8       m_current_cmd;
=======
	std::unique_ptr<uint16_t[]>    m_video_ram;
	std::unique_ptr<uint8_t[]>    m_cchip_ram;

	/* video-related */
	uint16_t      m_video_ctrl;
	uint16_t      m_video_mask;

	/* c-chip */
	uint8_t       m_current_bank;
	uint8_t       m_current_flag;
	uint8_t       m_cc_port;
	uint8_t       m_current_cmd;
	emu_timer     *m_cchip_timer;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
<<<<<<< HEAD
	required_device<pc090oj_device> m_pc090oj;
	required_device<screen_device> m_screen;

	DECLARE_WRITE16_MEMBER(volfied_cchip_ctrl_w);
	DECLARE_WRITE16_MEMBER(volfied_cchip_bank_w);
	DECLARE_WRITE16_MEMBER(volfied_cchip_ram_w);
	DECLARE_READ16_MEMBER(volfied_cchip_ctrl_r);
	DECLARE_READ16_MEMBER(volfied_cchip_ram_r);
	DECLARE_READ16_MEMBER(volfied_video_ram_r);
	DECLARE_WRITE16_MEMBER(volfied_video_ram_w);
	DECLARE_WRITE16_MEMBER(volfied_video_ctrl_w);
	DECLARE_READ16_MEMBER(volfied_video_ctrl_r);
	DECLARE_WRITE16_MEMBER(volfied_video_mask_w);
	DECLARE_WRITE16_MEMBER(volfied_sprite_ctrl_w);
	virtual void machine_start();
	virtual void machine_reset();
	virtual void video_start();
	UINT32 screen_update_volfied(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(volfied_timer_callback);
	void refresh_pixel_layer( bitmap_ind16 &bitmap );
	void volfied_cchip_init(  );
	void volfied_cchip_reset(  );
	DECLARE_WRITE_LINE_MEMBER(irqhandler);

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
};
=======
	required_device<taito_cchip_device> m_cchip;
	required_device<pc090oj_device> m_pc090oj;
	required_device<screen_device> m_screen;

	DECLARE_WRITE16_MEMBER(cchip_ctrl_w);
	DECLARE_WRITE16_MEMBER(cchip_bank_w);
	DECLARE_WRITE16_MEMBER(cchip_ram_w);
	DECLARE_READ16_MEMBER(cchip_ctrl_r);
	DECLARE_READ16_MEMBER(cchip_ram_r);
	DECLARE_READ16_MEMBER(video_ram_r);
	DECLARE_WRITE16_MEMBER(video_ram_w);
	DECLARE_WRITE16_MEMBER(video_ctrl_w);
	DECLARE_READ16_MEMBER(video_ctrl_r);
	DECLARE_WRITE16_MEMBER(video_mask_w);
	DECLARE_WRITE16_MEMBER(sprite_ctrl_w);
	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	TIMER_CALLBACK_MEMBER(timer_callback);
	void refresh_pixel_layer( bitmap_ind16 &bitmap );
	void cchip_init();
	void cchip_reset();

protected:
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
};

#endif // MAME_INCLUDES_VOLFIED_H
>>>>>>> upstream/master
