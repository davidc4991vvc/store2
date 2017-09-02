// license:GPL-2.0+
// copyright-holders:Juergen Buchmueller
/*************************************************************************

    Meadows S2650 hardware

*************************************************************************/
<<<<<<< HEAD
#include "emu.h"
#include "cpu/s2650/s2650.h"
#include "sound/dac.h"
#include "sound/samples.h"
=======
#include "cpu/s2650/s2650.h"
#include "sound/dac.h"
#include "sound/samples.h"
#include "screen.h"
>>>>>>> upstream/master

class meadows_state : public driver_device
{
public:
	meadows_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_dac(*this, "dac"),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_spriteram(*this, "spriteram"),
		m_videoram(*this, "videoram")
	{
	}

	required_device<s2650_device> m_maincpu;
	optional_device<s2650_device> m_audiocpu;
<<<<<<< HEAD
	optional_device<dac_device> m_dac;
=======
	optional_device<dac_8bit_r2r_device> m_dac;
>>>>>>> upstream/master
	optional_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;

<<<<<<< HEAD
	optional_shared_ptr<UINT8> m_spriteram;
	required_shared_ptr<UINT8> m_videoram;

	UINT8 m_dac_data;
	int m_dac_enable;
	int m_channel;
	int m_freq1;
	int m_freq2;
	UINT8 m_latched_0c01;
	UINT8 m_latched_0c02;
	UINT8 m_latched_0c03;
	UINT8 m_main_sense_state;
	UINT8 m_audio_sense_state;
	UINT8 m_0c00;
	UINT8 m_0c01;
	UINT8 m_0c02;
	UINT8 m_0c03;
=======
	optional_shared_ptr<uint8_t> m_spriteram;
	required_shared_ptr<uint8_t> m_videoram;

	int m_channel;
	int m_freq1;
	int m_freq2;
	uint8_t m_latched_0c01;
	uint8_t m_latched_0c02;
	uint8_t m_latched_0c03;
	uint8_t m_main_sense_state;
	uint8_t m_audio_sense_state;
	uint8_t m_0c00;
	uint8_t m_0c01;
	uint8_t m_0c02;
	uint8_t m_0c03;
>>>>>>> upstream/master
	tilemap_t *m_bg_tilemap;
	DECLARE_READ8_MEMBER(hsync_chain_r);
	DECLARE_READ8_MEMBER(vsync_chain_hi_r);
	DECLARE_READ8_MEMBER(vsync_chain_lo_r);
	DECLARE_WRITE8_MEMBER(meadows_audio_w);
	DECLARE_WRITE8_MEMBER(audio_hardware_w);
	DECLARE_READ8_MEMBER(audio_hardware_r);
	DECLARE_WRITE8_MEMBER(meadows_videoram_w);
	DECLARE_WRITE8_MEMBER(meadows_spriteram_w);
	DECLARE_INPUT_CHANGED_MEMBER(coin_inserted);
	DECLARE_DRIVER_INIT(minferno);
	DECLARE_DRIVER_INIT(gypsyjug);
	TILE_GET_INFO_MEMBER(get_tile_info);
<<<<<<< HEAD
	virtual void video_start();
	UINT32 screen_update_meadows(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
=======
	virtual void video_start() override;
	uint32_t screen_update_meadows(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
>>>>>>> upstream/master
	INTERRUPT_GEN_MEMBER(meadows_interrupt);
	INTERRUPT_GEN_MEMBER(minferno_interrupt);
	INTERRUPT_GEN_MEMBER(audio_interrupt);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &clip);
<<<<<<< HEAD
	void meadows_sh_dac_w(int data);
=======
>>>>>>> upstream/master
	void meadows_sh_update();
	SAMPLES_START_CB_MEMBER(meadows_sh_start);
};
