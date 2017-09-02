<<<<<<< HEAD
// license:???
// copyright-holders:Martin Buchholz
#include "sound/samples.h"

#define SAMPLE_LENGTH 32
=======
// license:BSD-3-Clause
// copyright-holders:Martin Buchholz
// thanks-to:James Wallace, Martin Buchholz, Juergen Oppermann, Volker Hann, Jan-Ole Christian
#ifndef MAME_INCLUDES_POLYPLAY_H
#define MAME_INCLUDES_POLYPLAY_H

#include "machine/z80ctc.h"
#include "machine/z80pio.h"
#include "machine/z80sio.h"
#include "sound/spkrdev.h"

#define POLYPLAY_MAIN_CLOCK XTAL_9_8304MHz

#define Z80CPU_TAG     "maincpu"
#define Z80CTC_TAG     "z80ctc"
#define Z80PIO_TAG     "z80pio"
#define Z80SIO_TAG     "z80sio"
>>>>>>> upstream/master

class polyplay_state : public driver_device
{
public:
	polyplay_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_videoram(*this, "videoram"),
		m_characterram(*this, "characterram"),
<<<<<<< HEAD
		m_maincpu(*this, "maincpu"),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")  { }

	required_shared_ptr<UINT8> m_videoram;
	required_shared_ptr<UINT8> m_characterram;

	required_device<cpu_device> m_maincpu;
	required_device<samples_device> m_samples;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	int m_freq1;
	int m_freq2;
	int m_channel_playing1;
	int m_channel_playing2;
	INT16 m_backgroundwave[SAMPLE_LENGTH];
	int m_prescale1;
	int m_prescale2;
	int m_channel1_active;
	int m_channel1_const;
	int m_channel2_active;
	int m_channel2_const;
	timer_device* m_timer;
	int m_last;

	DECLARE_WRITE8_MEMBER(polyplay_sound_channel);
	DECLARE_WRITE8_MEMBER(polyplay_start_timer2);
	DECLARE_READ8_MEMBER(polyplay_random_read);
	DECLARE_WRITE8_MEMBER(polyplay_characterram_w);
	SAMPLES_START_CB_MEMBER(sh_start);
	void set_channel1(int active);
	void set_channel2(int active);
	void play_channel1(int data);
	void play_channel2(int data);
	virtual void machine_reset();
	virtual void video_start();
	DECLARE_PALETTE_INIT(polyplay);
	UINT32 screen_update_polyplay(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(periodic_interrupt);
	INTERRUPT_GEN_MEMBER(coin_interrupt);
	TIMER_DEVICE_CALLBACK_MEMBER(polyplay_timer_callback);
};
=======
		m_maincpu(*this, Z80CPU_TAG),
		m_z80ctc(*this, Z80CTC_TAG),
		m_z80pio(*this, Z80PIO_TAG),
		m_z80sio(*this, Z80SIO_TAG),
		m_in0_port(*this, "IN0"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_speaker1(*this, "speaker1"),
		m_speaker2(*this, "speaker2")  { }

	required_shared_ptr<uint8_t> m_videoram;
	required_shared_ptr<uint8_t> m_characterram;

	required_device<cpu_device> m_maincpu;
	required_device<z80ctc_device> m_z80ctc;
	required_device<z80pio_device> m_z80pio;
	optional_device<z80sio_device> m_z80sio;
	required_ioport m_in0_port;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	INTERRUPT_GEN_MEMBER(nmi_handler);

	/* devices */
	DECLARE_WRITE_LINE_MEMBER(ctc_zc0_w);
	DECLARE_WRITE_LINE_MEMBER(ctc_zc1_w);
	DECLARE_WRITE_LINE_MEMBER(ctc_zc2_w);

	DECLARE_READ8_MEMBER(pio_porta_r);
	DECLARE_WRITE8_MEMBER(pio_porta_w);
	DECLARE_READ8_MEMBER(pio_portb_r);
	DECLARE_WRITE8_MEMBER(pio_portb_w);

	DECLARE_INPUT_CHANGED_MEMBER(input_changed);

	/* audio */
	uint8_t m_flipflop1;
	uint8_t m_flipflop2;
	required_device<speaker_sound_device> m_speaker1;
	required_device<speaker_sound_device> m_speaker2;

	/* video */
	virtual void video_start() override;
	DECLARE_WRITE8_MEMBER(polyplay_characterram_w);
	DECLARE_PALETTE_INIT(polyplay);
	uint32_t screen_update_polyplay(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
};

#endif // MAME_INCLUDES_POLYPLAY_H
>>>>>>> upstream/master
