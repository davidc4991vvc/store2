// license:BSD-3-Clause
// copyright-holders:Mike Balfour
/*************************************************************************

    Atari Avalanche hardware

*************************************************************************/

#include "sound/discrete.h"


<<<<<<< HEAD
=======

>>>>>>> upstream/master
class avalnche_state : public driver_device
{
public:
	avalnche_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_discrete(*this, "discrete"),
		m_maincpu(*this, "maincpu") { }

<<<<<<< HEAD
	required_shared_ptr<UINT8> m_videoram;
	optional_device<discrete_device> m_discrete;

	UINT8 m_avalance_video_inverted;

	DECLARE_WRITE8_MEMBER(avalance_video_invert_w);
	DECLARE_WRITE8_MEMBER(catch_coin_counter_w);
	DECLARE_WRITE8_MEMBER(avalance_credit_1_lamp_w);
	DECLARE_WRITE8_MEMBER(avalance_credit_2_lamp_w);
	DECLARE_WRITE8_MEMBER(avalance_start_lamp_w);
	virtual void machine_start();
	virtual void machine_reset();
	UINT32 screen_update_avalnche(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE8_MEMBER(avalnche_noise_amplitude_w);
	DECLARE_WRITE8_MEMBER(avalnche_attract_enable_w);
	DECLARE_WRITE8_MEMBER(avalnche_audio_w);
	DECLARE_WRITE8_MEMBER(catch_audio_w);
=======
	required_shared_ptr<uint8_t> m_videoram;
	optional_device<discrete_device> m_discrete;

	uint8_t m_avalance_video_inverted;

	DECLARE_WRITE_LINE_MEMBER(video_invert_w);
	DECLARE_WRITE8_MEMBER(catch_coin_counter_w);
	DECLARE_WRITE_LINE_MEMBER(credit_1_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(credit_2_lamp_w);
	DECLARE_WRITE_LINE_MEMBER(start_lamp_w);
	virtual void machine_start() override;
	uint32_t screen_update_avalnche(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE8_MEMBER(avalnche_noise_amplitude_w);
	DECLARE_WRITE_LINE_MEMBER(catch_aud0_w);
	DECLARE_WRITE_LINE_MEMBER(catch_aud1_w);
	DECLARE_WRITE_LINE_MEMBER(catch_aud2_w);
>>>>>>> upstream/master
	required_device<cpu_device> m_maincpu;
};


<<<<<<< HEAD
/*----------- defined in audio/avalnche.c -----------*/

DISCRETE_SOUND_EXTERN( avalnche );
=======
/*----------- defined in audio/avalnche.cpp -----------*/

MACHINE_CONFIG_EXTERN(avalnche_sound);
MACHINE_CONFIG_EXTERN(catch_sound);
>>>>>>> upstream/master
