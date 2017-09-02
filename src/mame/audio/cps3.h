// license:BSD-3-Clause
// copyright-holders:David Haywood, Andreas Naive, Tomasz Slanina, ElSemi
/***************************************************************************

    Capcom CPS-3 Sound Hardware

****************************************************************************/
<<<<<<< HEAD
=======
#ifndef MAME_AUDIO_CPS3_H
#define MAME_AUDIO_CPS3_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

struct cps3_voice
{
	cps3_voice() :
		pos(0),
		frac(0)
	{
<<<<<<< HEAD
		memset(regs, 0, sizeof(UINT32)*8);
	}

	UINT32 regs[8];
	UINT32 pos;
	UINT32 frac;
=======
		memset(regs, 0, sizeof(uint32_t)*8);
	}

	uint32_t regs[8];
	uint32_t pos;
	uint32_t frac;
>>>>>>> upstream/master
};

// ======================> cps3_sound_device

<<<<<<< HEAD
class cps3_sound_device : public device_t,
							public device_sound_interface
{
public:
	cps3_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~cps3_sound_device() { }

	void set_base(INT8* base) { m_base = base; }
=======
class cps3_sound_device : public device_t, public device_sound_interface
{
public:
	cps3_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	~cps3_sound_device() { }

	void set_base(int8_t* base) { m_base = base; }
>>>>>>> upstream/master

	DECLARE_WRITE32_MEMBER( cps3_sound_w );
	DECLARE_READ32_MEMBER( cps3_sound_r );

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
	sound_stream *m_stream;
	cps3_voice m_voice[16];
<<<<<<< HEAD
	UINT16     m_key;
	INT8*      m_base;
};

extern const device_type CPS3;
=======
	uint16_t     m_key;
	int8_t*      m_base;
};

DECLARE_DEVICE_TYPE(CPS3, cps3_sound_device)

#endif // MAME_AUDIO_CPS3_H
>>>>>>> upstream/master
