// license:BSD-3-Clause
// copyright-holders:Tomasz Slanina
<<<<<<< HEAD
#pragma once

#ifndef __NILE_H__
#define __NILE_H__
=======
#ifndef MAME_SOUND_NILE_H
#define MAME_SOUND_NILE_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_NILE_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, NILE, _clock)
#define MCFG_NILE_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, NILE, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
#define NILE_VOICES 8

=======
>>>>>>> upstream/master
// ======================> nile_device

class nile_device : public device_t,
					public device_sound_interface
{
public:
<<<<<<< HEAD
	nile_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~nile_device() { }

protected:
	// device-level overrides
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	nile_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

public:
	DECLARE_WRITE16_MEMBER( nile_snd_w );
	DECLARE_READ16_MEMBER( nile_snd_r );
	DECLARE_WRITE16_MEMBER( nile_sndctrl_w );
	DECLARE_READ16_MEMBER( nile_sndctrl_r );

private:
<<<<<<< HEAD
	sound_stream *m_stream;
	UINT8 *m_sound_ram;
	UINT16 m_sound_regs[0x80];
	int m_vpos[NILE_VOICES];
	int m_frac[NILE_VOICES];
	int m_lponce[NILE_VOICES];
	UINT16 m_ctrl;
};

extern const device_type NILE;


#endif /* __NILE_H__ */
=======
	static constexpr unsigned NILE_VOICES = 8;

	sound_stream *m_stream;
	required_region_ptr<uint8_t> m_sound_ram;
	uint16_t m_sound_regs[0x80];
	int m_vpos[NILE_VOICES];
	int m_frac[NILE_VOICES];
	int m_lponce[NILE_VOICES];
	uint16_t m_ctrl;
};

DECLARE_DEVICE_TYPE(NILE, nile_device)

#endif // MAME_SOUND_NILE_H
>>>>>>> upstream/master
