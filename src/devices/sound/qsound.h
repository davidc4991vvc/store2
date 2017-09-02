<<<<<<< HEAD
// license:???
=======
// license:BSD-3-Clause
>>>>>>> upstream/master
// copyright-holders:Paul Leaman, Miguel Angel Horna
/*********************************************************

    Capcom Q-Sound system

*********************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __QSOUND_H__
#define __QSOUND_H__
=======
#ifndef MAME_SOUND_QSOUND_H
#define MAME_SOUND_QSOUND_H

#pragma once
>>>>>>> upstream/master

#include "cpu/dsp16/dsp16.h"

#define QSOUND_CLOCK 4000000    /* default 4MHz clock (60MHz/15?) */


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_QSOUND_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, QSOUND, _clock)
#define MCFG_QSOUND_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, QSOUND, _clock)


// ======================> qsound_device

<<<<<<< HEAD
class qsound_device : public device_t,
						public device_sound_interface
{
public:
	qsound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~qsound_device() { }
=======
class qsound_device : public device_t, public device_sound_interface
{
public:
	qsound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(qsound_w);
	DECLARE_READ8_MEMBER(qsound_r);

protected:
	// device-level overrides
<<<<<<< HEAD
	const rom_entry *device_rom_region() const;
	machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
	const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;
>>>>>>> upstream/master

private:
	struct qsound_channel
	{
<<<<<<< HEAD
		UINT32 bank;        // bank
		UINT32 address;     // start/cur address
		UINT16 loop;        // loop address
		UINT16 end;         // end address
		UINT32 freq;        // frequency
		UINT16 vol;         // master volume
=======
		uint32_t bank;        // bank
		uint32_t address;     // start/cur address
		uint16_t loop;        // loop address
		uint16_t end;         // end address
		uint32_t freq;        // frequency
		uint16_t vol;         // master volume
>>>>>>> upstream/master

		// work variables
		bool enabled;       // key on / key off
		int lvol;           // left volume
		int rvol;           // right volume
<<<<<<< HEAD
		UINT32 step_ptr;    // current offset counter
	} m_channel[16];

	required_device<dsp16_device> m_cpu;
	required_region_ptr<INT8> m_sample_rom;

	int m_pan_table[33];    // pan volume table
	UINT16 m_data;          // register latch data
	sound_stream *m_stream; // audio stream

	inline INT8 read_sample(UINT32 offset) { return m_sample_rom[offset & m_sample_rom.mask()]; }
	void write_data(UINT8 address, UINT16 data);
};

extern const device_type QSOUND;


#endif /* __QSOUND_H__ */
=======
		uint32_t step_ptr;    // current offset counter
	} m_channel[16];

	required_device<dsp16_device> m_cpu;
	required_region_ptr<int8_t> m_sample_rom;

	int m_pan_table[33];    // pan volume table
	uint16_t m_data;          // register latch data
	sound_stream *m_stream; // audio stream

	inline int8_t read_sample(uint32_t offset) { return m_sample_rom[offset & m_sample_rom.mask()]; }
	void write_data(uint8_t address, uint16_t data);
};

DECLARE_DEVICE_TYPE(QSOUND, qsound_device)

#endif // MAME_SOUND_QSOUND_H
>>>>>>> upstream/master
