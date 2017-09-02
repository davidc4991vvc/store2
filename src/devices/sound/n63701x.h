// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
<<<<<<< HEAD
#pragma once

#ifndef __N63701X_H__
#define __N63701X_H__
=======
#ifndef MAME_SOUND_N63701X_H
#define MAME_SOUND_N63701X_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_NAMCO_63701X_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, NAMCO_63701X, _clock)
#define MCFG_NAMCO_63701X_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, NAMCO_63701X, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
struct voice_63701x
{
	voice_63701x()
		: select(0),
			playing(0),
			base_addr(0),
			position(0),
			volume(0),
			silence_counter(0) {}

	int select;
	int playing;
	int base_addr;
	int position;
	int volume;
	int silence_counter;
};

=======
>>>>>>> upstream/master

// ======================> namco_63701x_device

class namco_63701x_device : public device_t,
							public device_sound_interface
{
public:
<<<<<<< HEAD
	namco_63701x_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~namco_63701x_device() { }

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
	DECLARE_WRITE8_MEMBER(namco_63701x_w);

private:
	required_region_ptr<UINT8> m_rom;
=======
	namco_63701x_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER(namco_63701x_w);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct voice_63701x
	{
		voice_63701x() { }

		int select          = 0;
		int playing         = 0;
		int base_addr       = 0;
		int position        = 0;
		int volume          = 0;
		int silence_counter = 0;
	};

	required_region_ptr<uint8_t> m_rom;
>>>>>>> upstream/master
	voice_63701x m_voices[2];
	sound_stream *m_stream; /* channel assigned by the mixer */
};

<<<<<<< HEAD
extern const device_type NAMCO_63701X;


#endif /* __N63701X_H__ */
=======
DECLARE_DEVICE_TYPE(NAMCO_63701X, namco_63701x_device)

#endif // MAME_SOUND_N63701X_H
>>>>>>> upstream/master
