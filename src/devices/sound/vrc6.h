// license:BSD-3-Clause
// copyright-holders:R. Belmont
/***************************************************************************

    vrc6.h
    Konami VRC6 add-on sound

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VRC6_H__
#define __VRC6_H__
=======
#ifndef MAME_SOUND_VRC6_H
#define MAME_SOUND_VRC6_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_VRC6_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, VRC6, _clock)

#define MCFG_VRC6_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, VRC6, _clock)

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vrc6snd_device

class vrc6snd_device : public device_t, public device_sound_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vrc6snd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	vrc6snd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(write);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	UINT8 m_freqctrl, m_pulsectrl[2], m_sawrate;
	UINT8 m_pulsefrql[2], m_pulsefrqh[2], m_pulseduty[2];
	UINT8 m_sawfrql, m_sawfrqh, m_sawclock, m_sawaccum;
	UINT16 m_ticks[3];
	UINT8 m_output[3];
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	uint8_t m_freqctrl, m_pulsectrl[2], m_sawrate;
	uint8_t m_pulsefrql[2], m_pulsefrqh[2], m_pulseduty[2];
	uint8_t m_sawfrql, m_sawfrqh, m_sawclock, m_sawaccum;
	uint16_t m_ticks[3];
	uint8_t m_output[3];
>>>>>>> upstream/master

	sound_stream *m_stream;
};


// device type definition
extern const device_type VRC6;

<<<<<<< HEAD

#endif /* __VRC6_H__ */
=======
#endif // MAME_SOUND_VRC6_H
>>>>>>> upstream/master
