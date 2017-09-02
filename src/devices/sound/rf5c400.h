// license:BSD-3-Clause
// copyright-holders:Ville Linde
/* Ricoh RF5C400 emulator */

<<<<<<< HEAD
#pragma once

#ifndef __RF5C400_H__
#define __RF5C400_H__
=======
#ifndef MAME_SOUND_RF5C400_H
#define MAME_SOUND_RF5C400_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_RF5C400_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, RF5C400, _clock)
#define MCFG_RF5C400_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, RF5C400, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
struct rf5c400_channel
{
	rf5c400_channel() :
		startH(0),
		startL(0),
		freq(0),
		endL(0),
		endHloopH(0),
		loopL(0),
		pan(0),
		effect(0),
		volume(0),
		attack(0),
		decay(0),
		release(0),
		cutoff(0),
		pos(0),
		step(0),
		keyon(0),
		env_phase(0),
		env_level(0.0),
		env_step(0.0),
		env_scale(0.0)
	{ }

	UINT16  startH;
	UINT16  startL;
	UINT16  freq;
	UINT16  endL;
	UINT16  endHloopH;
	UINT16  loopL;
	UINT16  pan;
	UINT16  effect;
	UINT16  volume;

	UINT16  attack;
	UINT16  decay;
	UINT16  release;

	UINT16  cutoff;

	UINT64 pos;
	UINT64 step;
	UINT16 keyon;

	UINT8 env_phase;
	double env_level;
	double env_step;
	double env_scale;
};

=======
>>>>>>> upstream/master

// ======================> rf5c400_device

class rf5c400_device : public device_t,
						public device_sound_interface
{
public:
<<<<<<< HEAD
	rf5c400_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~rf5c400_device() { }

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
	DECLARE_READ16_MEMBER( rf5c400_r );
	DECLARE_WRITE16_MEMBER( rf5c400_w );

private:
	void rf5c400_init_chip();
	UINT8 decode80(UINT8 val);

private:
	required_region_ptr<INT16> m_rom;

	UINT32 m_rommask;

	sound_stream *m_stream;

	double m_env_ar_table[0x9f];
	double m_env_dr_table[0x9f];
	double m_env_rr_table[0x9f];

	rf5c400_channel m_channels[32];
};

extern const device_type RF5C400;


#endif /* __RF5C400_H__ */
=======
	rf5c400_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_READ16_MEMBER( rf5c400_r );
	DECLARE_WRITE16_MEMBER( rf5c400_w );

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct rf5c400_channel
	{
		rf5c400_channel() { }

		uint16_t startH = 0;
		uint16_t startL = 0;
		uint16_t freq = 0;
		uint16_t endL = 0;
		uint16_t endHloopH = 0;
		uint16_t loopL = 0;
		uint16_t pan = 0;
		uint16_t effect = 0;
		uint16_t volume = 0;

		uint16_t attack = 0;
		uint16_t decay = 0;
		uint16_t release = 0;

		uint16_t cutoff = 0;

		uint64_t pos = 0;
		uint64_t step = 0;
		uint16_t keyon = 0;

		uint8_t env_phase = 0;
		double env_level = 0.0;
		double env_step = 0.0;
		double env_scale = 0.0;
	};

	class envelope_tables
	{
	public:
		envelope_tables();
		void init(uint32_t clock);
		double ar(rf5c400_channel const &chan) const { return m_ar[decode80(chan.attack >> 8)]; }
		double dr(rf5c400_channel const &chan) const { return m_dr[decode80(chan.decay >> 8)]; }
		double rr(rf5c400_channel const &chan) const { return m_rr[decode80(chan.release >> 8)]; }
	private:
		static constexpr uint8_t decode80(uint8_t val) { return (val & 0x80) ? ((val & 0x7f) + 0x1f) : val; }
		double m_ar[0x9f];
		double m_dr[0x9f];
		double m_rr[0x9f];
	};

	uint8_t decode80(uint8_t val);

	required_region_ptr<int16_t> m_rom;

	uint32_t m_rommask;

	sound_stream *m_stream;

	envelope_tables m_env_tables;

	rf5c400_channel m_channels[32];

	uint32_t m_ext_mem_address;
	uint16_t m_ext_mem_data;
};

DECLARE_DEVICE_TYPE(RF5C400, rf5c400_device)

#endif // MAME_SOUND_RF5C400_H
>>>>>>> upstream/master
