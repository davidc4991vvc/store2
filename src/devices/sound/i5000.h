// license:BSD-3-Clause
// copyright-holders:hap
/***************************************************************************

    i5000.h - Imagetek I5000 sound emulator

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __I5000_H__
#define __I5000_H__
=======
#ifndef MAME_SOUND_I5000_H
#define MAME_SOUND_I5000_H

#pragma once
>>>>>>> upstream/master

#include "sound/okiadpcm.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_I5000_SND_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, I5000_SND, _clock)

#define MCFG_I5000_SND_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, I5000_SND, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class i5000snd_device : public device_t,
						public device_sound_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	i5000snd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	i5000snd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(read);
	DECLARE_WRITE16_MEMBER(write);

<<<<<<< HEAD
	sound_stream *m_stream;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	sound_stream *m_stream;
>>>>>>> upstream/master

private:
	struct channel_t
	{
		bool is_playing;
		oki_adpcm_state m_adpcm;

<<<<<<< HEAD
		UINT32 address;
		int freq_timer;
		int freq_base;
		int freq_min;
		UINT16 sample;
		UINT8 shift_pos;
		UINT8 shift_amount;
		UINT8 shift_mask;
=======
		uint32_t address;
		int freq_timer;
		int freq_base;
		int freq_min;
		uint16_t sample;
		uint8_t shift_pos;
		uint8_t shift_amount;
		uint8_t shift_mask;
>>>>>>> upstream/master
		int vol_r;
		int vol_l;
		int output_r;
		int output_l;

	};

	channel_t m_channels[16];

<<<<<<< HEAD
	UINT16 m_regs[0x80];

	UINT16 *m_rom_base;
	UINT32 m_rom_mask;
=======
	uint16_t m_regs[0x80];

	uint16_t *m_rom_base;
	uint32_t m_rom_mask;
>>>>>>> upstream/master

	int m_lut_volume[0x100];

	bool read_sample(int ch);
<<<<<<< HEAD
	void write_reg16(UINT8 reg, UINT16 data);
=======
	void write_reg16(uint8_t reg, uint16_t data);
>>>>>>> upstream/master
};


// device type definition
extern const device_type I5000_SND;
<<<<<<< HEAD

#endif /* __I5000_H__ */
=======
DECLARE_DEVICE_TYPE(I5000_SND, i5000snd_device)

#endif // MAME_SOUND_I5000_H
>>>>>>> upstream/master
