// license:GPL-2.0+
// copyright-holders:Juergen Buchmueller
<<<<<<< HEAD
#include "sound/tms36xx.h"

struct pl_t_state
{
		pl_t_state():
		counter(0),
		output(0),
		max_freq(0) {}

	int counter;
	int output;
	int max_freq;
};

struct pl_c_state
{
		pl_c_state():
		counter(0),
		level(0),
		charge_time(0),
		discharge_time(0) {}

	int counter;
	int level;
	double charge_time;
	double discharge_time;
};

struct pl_n_state
{
		pl_n_state():
		counter(0),
		polyoffs(0),
		freq(0) {}

	int counter;
	int polyoffs;
	int freq;
};

class pleiads_sound_device : public device_t,
									public device_sound_interface
{
public:
	pleiads_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	pleiads_sound_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~pleiads_sound_device() {}
=======
#ifndef MAME_AUDIO_PLEIADS_H
#define MAME_AUDIO_PLEIADS_H

#pragma once

#include "sound/tms36xx.h"

class pleiads_sound_device : public device_t, public device_sound_interface
{
public:
	pleiads_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( control_a_w );
	DECLARE_WRITE8_MEMBER( control_b_w );
	DECLARE_WRITE8_MEMBER( control_c_w );

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	struct pl_t_state
	{
		pl_t_state() { }

		int counter = 0;
		int output = 0;
		int max_freq = 0;
	};

	struct pl_c_state
	{
		pl_c_state() { }

		int counter = 0;
		int level = 0;
		double charge_time = 0;
		double discharge_time = 0;
	};

	struct pl_n_state
	{
		pl_n_state() { }

		int counter = 0;
		int polyoffs = 0;
		int freq = 0;
	};

	pleiads_sound_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

	void common_start();
	inline int tone1(int samplerate);
	inline int update_pb4(int samplerate);
	inline int tone23(int samplerate);
	inline int update_c_pc4(int samplerate);
	inline int update_c_pc5(int samplerate);
	inline int update_c_pa5(int samplerate);
	inline int tone4(int samplerate);
	inline int update_c_pa6(int samplerate);
	inline int noise(int samplerate);

	// internal state
	tms36xx_device *m_tms;
	sound_stream *m_channel;

	int m_sound_latch_a;
	int m_sound_latch_b;
	int m_sound_latch_c;    /* part of the videoreg_w latch */

<<<<<<< HEAD
	UINT32 *m_poly18;
=======
	std::unique_ptr<uint32_t[]> m_poly18;
>>>>>>> upstream/master
	int m_polybit;

	pl_t_state m_tone1;
	pl_t_state m_tone2;
	pl_t_state m_tone3;
	pl_t_state m_tone4;

	pl_c_state m_pa5;
	pl_c_state m_pa6;
	pl_c_state m_pb4;
	pl_c_state m_pc4;
	pl_c_state m_pc5;

	pl_n_state m_noise;

	int m_pa5_resistor;
	int m_pc5_resistor;
	int m_polybit_resistor;
	int m_opamp_resistor;
};

<<<<<<< HEAD
extern const device_type PLEIADS;
=======
DECLARE_DEVICE_TYPE(PLEIADS, pleiads_sound_device)
>>>>>>> upstream/master

class naughtyb_sound_device : public pleiads_sound_device
{
public:
<<<<<<< HEAD
	naughtyb_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
private:
	// internal state
};

extern const device_type NAUGHTYB;
=======
	naughtyb_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
};

DECLARE_DEVICE_TYPE(NAUGHTYB, naughtyb_sound_device)
>>>>>>> upstream/master

class popflame_sound_device : public pleiads_sound_device
{
public:
<<<<<<< HEAD
	popflame_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
private:
	// internal state
};

extern const device_type POPFLAME;
=======
	popflame_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
};

DECLARE_DEVICE_TYPE(POPFLAME, popflame_sound_device)

#endif // MAME_AUDIO_PLEIADS_H
>>>>>>> upstream/master
