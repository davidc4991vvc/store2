// license:BSD-3-Clause
// copyright-holders:Aaron Giles
<<<<<<< HEAD
#pragma once

#ifndef __HC55516_H__
#define __HC55516_H__

class hc55516_device : public device_t,
									public device_sound_interface
{
public:
	hc55516_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	hc55516_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	~hc55516_device() {}
=======
#ifndef MAME_SOUND_HC55516_H
#define MAME_SOUND_HC55516_H

#pragma once

class hc55516_device : public device_t, public device_sound_interface
{
public:
	hc55516_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	/* sets the digit (0 or 1) */
	void digit_w(int digit);

	/* sets the clock state (0 or 1, clocked on the rising edge) */
	void clock_w(int state);

	/* returns whether the clock is currently LO or HI */
	int clock_state_r();

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	void start_common(UINT8 _shiftreg_mask, int _active_clock_hi);
=======
	hc55516_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	void start_common(uint8_t _shiftreg_mask, int _active_clock_hi);
>>>>>>> upstream/master

	// internal state
	sound_stream *m_channel;
	int     m_active_clock_hi;
<<<<<<< HEAD
	UINT8   m_shiftreg_mask;

	UINT8   m_last_clock_state;
	UINT8   m_digit;
	UINT8   m_new_digit;
	UINT8   m_shiftreg;

	INT16   m_curr_sample;
	INT16   m_next_sample;

	UINT32  m_update_count;
=======
	uint8_t   m_shiftreg_mask;

	uint8_t   m_last_clock_state;
	uint8_t   m_digit;
	uint8_t   m_new_digit;
	uint8_t   m_shiftreg;

	int16_t   m_curr_sample;
	int16_t   m_next_sample;

	uint32_t  m_update_count;
>>>>>>> upstream/master

	double  m_filter;
	double  m_integrator;

	double  m_charge;
	double  m_decay;
	double  m_leak;

	inline int is_external_oscillator();
	inline int is_active_clock_transition(int clock_state);
	inline int current_clock_state();
	void process_digit();
};

<<<<<<< HEAD
extern const device_type HC55516;
=======
>>>>>>> upstream/master

class mc3417_device : public hc55516_device
{
public:
<<<<<<< HEAD
	mc3417_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
};

extern const device_type MC3417;
=======
	mc3417_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
};

>>>>>>> upstream/master

class mc3418_device : public hc55516_device
{
public:
<<<<<<< HEAD
	mc3418_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
};

extern const device_type MC3418;


#endif /* __HC55516_H__ */
=======
	mc3418_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
};


DECLARE_DEVICE_TYPE(HC55516, hc55516_device)
DECLARE_DEVICE_TYPE(MC3417,  mc3417_device)
DECLARE_DEVICE_TYPE(MC3418,  mc3418_device)

#endif // MAME_SOUND_HC55516_H
>>>>>>> upstream/master
