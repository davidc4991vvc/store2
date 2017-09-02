// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
/******************************************************************************


    CD-i Mono-I CDIC MCU simulation
    -------------------

    written by Ryan Holtz


*******************************************************************************

STATUS:

- Just enough for the Mono-I CD-i board to work somewhat properly.

TODO:

- Decapping and proper emulation.

*******************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CDICDIC_H__
#define __CDICDIC_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_CDICDIC_H
#define MAME_MACHINE_CDICDIC_H

#pragma once

>>>>>>> upstream/master
#include "cdrom.h"
#include "sound/cdda.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_CDICDIC_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MACHINE_CDICDIC, 0)
#define MCFG_CDICDIC_REPLACE(_tag) \
	MCFG_DEVICE_REPLACE(_tag, MACHINE_CDICDIC, 0)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> cdicdic_device

class cdicdic_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	cdicdic_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	cdicdic_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// non-static internal members
	void sample_trigger();
	void process_delayed_command();
<<<<<<< HEAD
	void ram_write(const UINT32 offset, const UINT16 data, const UINT16 mem_mask);
	UINT16 ram_read(const UINT32 offset, const UINT16 mem_mask);
	void register_write(const UINT32 offset, const UINT16 data, const UINT16 mem_mask);
	UINT16 register_read(const UINT32 offset, const UINT16 mem_mask);
=======
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER( regs_r );
	DECLARE_WRITE16_MEMBER( regs_w );
	DECLARE_READ16_MEMBER( ram_r );
	DECLARE_WRITE16_MEMBER( ram_w );


protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
=======
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master

	// internal callbacks
	TIMER_CALLBACK_MEMBER( audio_sample_trigger );
	TIMER_CALLBACK_MEMBER( trigger_readback_int );

private:
	// internal state
<<<<<<< HEAD
	UINT16 m_command;           // CDIC Command Register            (0x303c00)
	UINT32 m_time;              // CDIC Time Register               (0x303c02)
	UINT16 m_file;              // CDIC File Register               (0x303c06)
	UINT32 m_channel;           // CDIC Channel Register            (0x303c08)
	UINT16 m_audio_channel;     // CDIC Audio Channel Register      (0x303c0c)

	UINT16 m_audio_buffer;      // CDIC Audio Buffer Register       (0x303ff4)
	UINT16 m_x_buffer;          // CDIC X-Buffer Register           (0x303ff6)
	UINT16 m_dma_control;       // CDIC DMA Control Register        (0x303ff8)
	UINT16 m_z_buffer;          // CDIC Z-Buffer Register           (0x303ffa)
	UINT16 m_interrupt_vector;  // CDIC Interrupt Vector Register   (0x303ffc)
	UINT16 m_data_buffer;       // CDIC Data Buffer Register        (0x303ffe)
=======
	uint16_t m_command;           // CDIC Command Register            (0x303c00)
	uint32_t m_time;              // CDIC Time Register               (0x303c02)
	uint16_t m_file;              // CDIC File Register               (0x303c06)
	uint32_t m_channel;           // CDIC Channel Register            (0x303c08)
	uint16_t m_audio_channel;     // CDIC Audio Channel Register      (0x303c0c)

	uint16_t m_audio_buffer;      // CDIC Audio Buffer Register       (0x303ff4)
	uint16_t m_x_buffer;          // CDIC X-Buffer Register           (0x303ff6)
	uint16_t m_dma_control;       // CDIC DMA Control Register        (0x303ff8)
	uint16_t m_z_buffer;          // CDIC Z-Buffer Register           (0x303ffa)
	uint16_t m_interrupt_vector;  // CDIC Interrupt Vector Register   (0x303ffc)
	uint16_t m_data_buffer;       // CDIC Data Buffer Register        (0x303ffe)
>>>>>>> upstream/master

	emu_timer *m_interrupt_timer;
	cdrom_file *m_cd;

	emu_timer *m_audio_sample_timer;
<<<<<<< HEAD
	INT32 m_audio_sample_freq;
	INT32 m_audio_sample_size;

	UINT16 m_decode_addr;
	UINT8 m_decode_delay;
	attotime m_decode_period;

	int m_xa_last[4];
	UINT16 *m_ram;

	// static internal members
	static void decode_xa_mono(INT32 *cdic_xa_last, const UINT8 *xa, INT16 *dp);
	static void decode_xa_mono8(INT32 *cdic_xa_last, const UINT8 *xa, INT16 *dp);
	static void decode_xa_stereo(INT32 *cdic_xa_last, const UINT8 *xa, INT16 *dp);
	static void decode_xa_stereo8(INT32 *cdic_xa_last, const UINT8 *xa, INT16 *dp);

	static const INT32 s_cdic_adpcm_filter_coef[5][2];

	// non-static internal members
	UINT32 increment_cdda_frame_bcd(UINT32 bcd);
	UINT32 increment_cdda_sector_bcd(UINT32 bcd);
	void decode_audio_sector(const UINT8 *xa, INT32 triggered);
};

// device type definition
extern const device_type MACHINE_CDICDIC;

#endif // __CDICDIC_H__
=======
	int32_t m_audio_sample_freq;
	int32_t m_audio_sample_size;

	uint16_t m_decode_addr;
	uint8_t m_decode_delay;
	attotime m_decode_period;

	int m_xa_last[4];
	std::unique_ptr<uint16_t[]> m_ram;

	// static internal members
	static void decode_xa_mono(int32_t *cdic_xa_last, const uint8_t *xa, int16_t *dp);
	static void decode_xa_mono8(int32_t *cdic_xa_last, const uint8_t *xa, int16_t *dp);
	static void decode_xa_stereo(int32_t *cdic_xa_last, const uint8_t *xa, int16_t *dp);
	static void decode_xa_stereo8(int32_t *cdic_xa_last, const uint8_t *xa, int16_t *dp);

	static const int32_t s_cdic_adpcm_filter_coef[5][2];

	// non-static internal members
	uint32_t increment_cdda_frame_bcd(uint32_t bcd);
	uint32_t increment_cdda_sector_bcd(uint32_t bcd);
	void decode_audio_sector(const uint8_t *xa, int32_t triggered);
};

// device type definition
DECLARE_DEVICE_TYPE(MACHINE_CDICDIC, cdicdic_device)

#endif // MAME_MACHINE_CDICDIC_H
>>>>>>> upstream/master
