// license:BSD-3-Clause
// copyright-holders:Kevin Thacker
<<<<<<< HEAD
#pragma once

#ifndef __BEEP_H__
#define __BEEP_H__
=======
#ifndef MAME_SOUND_BEEP_H
#define MAME_SOUND_BEEP_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> beep_device

class beep_device : public device_t,
					public device_sound_interface
{
public:
<<<<<<< HEAD
	beep_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~beep_device() { }

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
	void set_state(int on);
	void set_frequency(int frequency);
	void set_volume(int volume);
=======
	beep_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

public:
	DECLARE_WRITE_LINE_MEMBER(set_state);   // enable/disable sound output
	void set_clock(uint32_t frequency);       // output frequency
>>>>>>> upstream/master

private:
	sound_stream *m_stream;   /* stream number */
	int m_enable;             /* enable beep */
<<<<<<< HEAD
	int m_frequency;          /* set frequency - this can be changed using the appropiate function */
	int m_incr;               /* initial wave state */
	INT16 m_signal;           /* current signal */
};

extern const device_type BEEP;


#endif /* __BEEP_H__ */
=======
	int m_frequency;          /* set frequency - this can be changed using the appropriate function */
	int m_incr;               /* initial wave state */
	int16_t m_signal;           /* current signal */
};

DECLARE_DEVICE_TYPE(BEEP, beep_device)

#endif // MAME_SOUND_BEEP_H
>>>>>>> upstream/master
