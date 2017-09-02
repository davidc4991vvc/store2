<<<<<<< HEAD
// license:???
// copyright-holders:Derrick Renaud, Couriersud
#pragma once

#ifndef __FLT_VOL_H__
#define __FLT_VOL_H__
=======
// license:BSD-3-Clause
// copyright-holders:Derrick Renaud, Couriersud
#ifndef MAME_SOUND_FLT_VOL_H
#define MAME_SOUND_FLT_VOL_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_FILTER_VOLUME_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, FILTER_VOLUME, _clock)
#define MCFG_FILTER_VOLUME_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, FILTER_VOLUME, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> filter_volume_device

<<<<<<< HEAD
class filter_volume_device : public device_t,
								public device_sound_interface
{
public:
	filter_volume_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~filter_volume_device() { }
=======
class filter_volume_device : public device_t, public device_sound_interface
{
public:
	filter_volume_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	void flt_volume_set_volume(float volume);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

private:
	sound_stream*  m_stream;
	int            m_gain;
};

<<<<<<< HEAD
extern const device_type FILTER_VOLUME;


#endif /* __FLT_VOL_H__ */
=======
DECLARE_DEVICE_TYPE(FILTER_VOLUME, filter_volume_device)


#endif // MAME_SOUND_FLT_VOL_H
>>>>>>> upstream/master
