// license:BSD-3-Clause
// copyright-holders:Nathan Woods
<<<<<<< HEAD
#pragma once

#ifndef __WAVE_H__
#define __WAVE_H__
=======
#ifndef MAME_SOUND_WAVE_H
#define MAME_SOUND_WAVE_H

#pragma once
>>>>>>> upstream/master

#include "imagedev/cassette.h"


/*****************************************************************************
 *  CassetteWave interface
 *****************************************************************************/

<<<<<<< HEAD
class wave_device : public device_t,
									public device_sound_interface
{
public:
	wave_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class wave_device : public device_t, public device_sound_interface
{
public:
	wave_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	static void static_set_cassette_tag(device_t &device, const char *cassette_tag);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_config_complete();
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

private:
	const char *m_cassette_tag;
	cassette_image_device *m_cass;
};

<<<<<<< HEAD
extern const device_type WAVE;
=======
DECLARE_DEVICE_TYPE(WAVE, wave_device)
>>>>>>> upstream/master


#define WAVE_TAG        "wave"
#define WAVE2_TAG       "wave2"


#define MCFG_SOUND_WAVE_ADD(_tag, _cass_tag) \
	MCFG_SOUND_ADD( _tag, WAVE, 0 ) \
	wave_device::static_set_cassette_tag(*device, _cass_tag);

<<<<<<< HEAD
#endif /* __WAVE_H__ */
=======
#endif // MAME_SOUND_WAVE_H
>>>>>>> upstream/master
