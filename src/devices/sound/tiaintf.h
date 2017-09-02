// license:GPL-2.0+
// copyright-holders:Ron Fries,Dan Boris
<<<<<<< HEAD
#pragma once

#ifndef __TIAINTF_H__
#define __TIAINTF_H__
=======
#ifndef MAME_SOUND_TIAINTF_H
#define MAME_SOUND_TIAINTF_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_SOUND_TIA_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, TIA, _clock)
#define MCFG_SOUND_TIA_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, TIA, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> tia_device

<<<<<<< HEAD
class tia_device : public device_t,
					public device_sound_interface
{
public:
	tia_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~tia_device() { }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_stop();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
	DECLARE_WRITE8_MEMBER( tia_sound_w );
=======
class tia_device : public device_t, public device_sound_interface
{
public:
	tia_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER( tia_sound_w );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_stop() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

private:
	sound_stream *m_channel;
	void *m_chip;
};

<<<<<<< HEAD
extern const device_type TIA;


#endif /* __TIAINTF_H__ */
=======
DECLARE_DEVICE_TYPE(TIA, tia_device)

#endif // MAME_SOUND_TIAINTF_H
>>>>>>> upstream/master
