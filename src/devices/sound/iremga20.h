// license:BSD-3-Clause
// copyright-holders:Acho A. Tang,R. Belmont
/*********************************************************

    Irem GA20 PCM Sound Chip

*********************************************************/
<<<<<<< HEAD
#pragma once

#ifndef __IREMGA20_H__
#define __IREMGA20_H__
=======
#ifndef MAME_SOUND_IREMGA20_H
#define MAME_SOUND_IREMGA20_H

#pragma once
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_IREMGA20_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, IREMGA20, _clock)
#define MCFG_IREMGA20_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, IREMGA20, _clock)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
struct IremGA20_channel_def
{
	UINT32 rate;
	UINT32 size;
	UINT32 start;
	UINT32 pos;
	UINT32 frac;
	UINT32 end;
	UINT32 volume;
	UINT32 pan;
	UINT32 effect;
	UINT32 play;
};

=======
>>>>>>> upstream/master

// ======================> iremga20_device

class iremga20_device : public device_t,
						public device_sound_interface
{
public:
<<<<<<< HEAD
	iremga20_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~iremga20_device() { }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

public:
	DECLARE_WRITE8_MEMBER( irem_ga20_w );
	DECLARE_READ8_MEMBER( irem_ga20_r );

private:
	void iremga20_reset();

private:
	UINT8 *m_rom;
	INT32 m_rom_size;
	sound_stream *m_stream;
	UINT16 m_regs[0x40];
	IremGA20_channel_def m_channel[4];
};

extern const device_type IREMGA20;


#endif /* __IREMGA20_H__ */
=======
	iremga20_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER( irem_ga20_w );
	DECLARE_READ8_MEMBER( irem_ga20_r );

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct channel_def
	{
		uint32_t rate;
		uint32_t size;
		uint32_t start;
		uint32_t pos;
		uint32_t frac;
		uint32_t end;
		uint32_t volume;
		uint32_t pan;
		uint32_t effect;
		uint32_t play;
	};

	void iremga20_reset();

	required_region_ptr<uint8_t> m_rom;
	sound_stream *m_stream;
	uint16_t m_regs[0x40];
	channel_def m_channel[4];
};

DECLARE_DEVICE_TYPE(IREMGA20, iremga20_device)

#endif // MAME_SOUND_IREMGA20_H
>>>>>>> upstream/master
