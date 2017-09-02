// license:BSD-3-Clause
// copyright-holders:Bryan McPhail
<<<<<<< HEAD
#pragma once

#ifndef __K005289_H__
#define __K005289_H__
=======
#ifndef MAME_SOUND_K005289_H
#define MAME_SOUND_K005289_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_K005289_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, K005289, _clock)
#define MCFG_K005289_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, K005289, _clock)


// ======================> k005289_device

class k005289_device : public device_t,
						public device_sound_interface
{
public:
<<<<<<< HEAD
	k005289_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~k005289_device() { }

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
=======
	k005289_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( k005289_control_A_w );
	DECLARE_WRITE8_MEMBER( k005289_control_B_w );
	DECLARE_WRITE8_MEMBER( ld1_w );
	DECLARE_WRITE8_MEMBER( ld2_w );
	DECLARE_WRITE8_MEMBER( tg1_w );
	DECLARE_WRITE8_MEMBER( tg2_w );

<<<<<<< HEAD
private:
	void make_mixer_table(int voices);

	const unsigned char *m_sound_prom;
=======
protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	void make_mixer_table(int voices);

	required_region_ptr<uint8_t> m_sound_prom;
>>>>>>> upstream/master
	sound_stream *m_stream;
	int m_rate;

	/* mixer tables and internal buffers */
<<<<<<< HEAD
	INT16 *m_mixer_table;
	INT16 *m_mixer_lookup;
	short *m_mixer_buffer;

	UINT32 m_counter[2];
	UINT16 m_frequency[2];
	UINT16 m_freq_latch[2];
	UINT16 m_waveform[2];
	UINT8 m_volume[2];
};

extern const device_type K005289;


#endif /* __K005289_H__ */
=======
	std::unique_ptr<int16_t[]> m_mixer_table;
	int16_t *m_mixer_lookup;
	std::unique_ptr<short[]> m_mixer_buffer;

	uint32_t m_counter[2];
	uint16_t m_frequency[2];
	uint16_t m_freq_latch[2];
	uint16_t m_waveform[2];
	uint8_t m_volume[2];
};

DECLARE_DEVICE_TYPE(K005289, k005289_device)

#endif // MAME_SOUND_K005289_H
>>>>>>> upstream/master
