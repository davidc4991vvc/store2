// license:LGPL-2.1+
// copyright-holders:David Haywood, Angelo Salese, ElSemi
<<<<<<< HEAD
=======
#ifndef MAME_SOUND_L7A1045_L6028_DSP_A_H
#define MAME_SOUND_L7A1045_L6028_DSP_A_H

#pragma once

>>>>>>> upstream/master
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
struct l7a1045_voice
{
	l7a1045_voice() : end(0), mode(false),
						pos(0),
		frac(0), l_volume(0), r_volume(0)
	{
		//memset(regs, 0, sizeof(UINT32)*8);
		start = 0;
	}

	UINT32 start;
	UINT32 end;
	bool mode;
	UINT32 pos;
	UINT32 frac;
	UINT16 l_volume;
	UINT16 r_volume;
};

=======
>>>>>>> upstream/master
// ======================> l7a1045_sound_device

class l7a1045_sound_device : public device_t,
							public device_sound_interface
{
public:
<<<<<<< HEAD
	l7a1045_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~l7a1045_sound_device() { }

//  void set_base(INT8* base) { m_base = base; }
=======
	l7a1045_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

//  void set_base(int8_t* base) { m_base = base; }
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER( l7a1045_sound_w );
	DECLARE_READ16_MEMBER( l7a1045_sound_r );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

private:
	sound_stream *m_stream;
	l7a1045_voice m_voice[32];
	UINT32    m_key;
	UINT8 *m_rom;
	INT32 m_rom_size;

	UINT8 m_audiochannel;
	UINT8 m_audioregister;

	struct l7a1045_48bit_data {
		UINT16 dat[3];
=======
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

private:
	struct l7a1045_voice
	{
		l7a1045_voice() { }

		uint32_t start = 0;
		uint32_t end = 0;
		bool mode = false;
		uint32_t pos = 0;
		uint32_t frac = 0;
		uint16_t l_volume = 0;
		uint16_t r_volume = 0;
	};

	sound_stream *m_stream;
	l7a1045_voice m_voice[32];
	uint32_t    m_key;
	required_region_ptr<uint8_t> m_rom;

	uint8_t m_audiochannel;
	uint8_t m_audioregister;

	struct l7a1045_48bit_data {
		uint16_t dat[3];
>>>>>>> upstream/master
	};

	l7a1045_48bit_data m_audiodat[0x10][0x20];

	DECLARE_WRITE16_MEMBER(sound_select_w);
	DECLARE_WRITE16_MEMBER(sound_data_w);
	DECLARE_READ16_MEMBER(sound_data_r);
	DECLARE_WRITE16_MEMBER(sound_status_w);
};

<<<<<<< HEAD
extern const device_type L7A1045;
=======
DECLARE_DEVICE_TYPE(L7A1045, l7a1045_sound_device)

#endif // MAME_SOUND_L7A1045_L6028_DSP_A_H
>>>>>>> upstream/master
