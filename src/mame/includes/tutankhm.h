// license:BSD-3-Clause
// copyright-holders:Mirko Buffoni
<<<<<<< HEAD
=======

#include "audio/timeplt.h"

>>>>>>> upstream/master
class tutankhm_state : public driver_device
{
public:
	tutankhm_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_scroll(*this, "scroll"),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_palette(*this, "palette") { }

	/* memory pointers */
	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_scroll;

	/* video-related */
	tilemap_t  *m_bg_tilemap;
	UINT8     m_flip_x;
	UINT8     m_flip_y;

	/* misc */
	UINT8    m_irq_toggle;
	UINT8    m_irq_enable;
=======
		m_palette(*this, "palette"),
		m_timeplt_audio(*this, "timeplt_audio") { }

	/* memory pointers */
	required_shared_ptr<uint8_t> m_videoram;
	optional_shared_ptr<uint8_t> m_scroll;

	/* video-related */
	tilemap_t  *m_bg_tilemap;
	uint8_t     m_flip_x;
	uint8_t     m_flip_y;

	/* misc */
	uint8_t    m_irq_toggle;
	uint8_t    m_irq_enable;
>>>>>>> upstream/master

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<palette_device> m_palette;
<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(irq_enable_w);
	DECLARE_WRITE8_MEMBER(tutankhm_bankselect_w);
	DECLARE_WRITE8_MEMBER(sound_mute_w);
	DECLARE_WRITE8_MEMBER(tutankhm_coin_counter_w);
	DECLARE_WRITE8_MEMBER(tutankhm_flip_screen_x_w);
	DECLARE_WRITE8_MEMBER(tutankhm_flip_screen_y_w);
	DECLARE_MACHINE_START(tutankhm);
	DECLARE_MACHINE_RESET(tutankhm);
	UINT32 screen_update_tutankhm(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
=======
	optional_device<timeplt_audio_device> m_timeplt_audio;
	DECLARE_WRITE_LINE_MEMBER(irq_enable_w);
	DECLARE_WRITE8_MEMBER(tutankhm_bankselect_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_1_w);
	DECLARE_WRITE_LINE_MEMBER(coin_counter_2_w);
	DECLARE_WRITE8_MEMBER(sound_on_w);
	DECLARE_WRITE_LINE_MEMBER(flip_screen_x_w);
	DECLARE_WRITE_LINE_MEMBER(flip_screen_y_w);
	DECLARE_MACHINE_START(tutankhm);
	DECLARE_MACHINE_RESET(tutankhm);
	uint32_t screen_update_tutankhm(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	INTERRUPT_GEN_MEMBER(tutankhm_interrupt);
};
