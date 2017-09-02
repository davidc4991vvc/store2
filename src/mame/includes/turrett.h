// license:BSD-3-Clause
// copyright-holders:Philip Bennett
/***************************************************************************

    Turret Tower hardware

****************************************************************************/
<<<<<<< HEAD

#include "machine/ataintf.h"
=======
#ifndef MAME_INCLUDES_TURRETT_H
#define MAME_INCLUDES_TURRETT_H

#pragma once

#include "machine/ataintf.h"
#include "screen.h"
>>>>>>> upstream/master


class turrett_state : public driver_device
{
public:
	turrett_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_ata(*this, "ata"),
			m_bank_a(*this, "bank_a"),
			m_bank_b(*this, "bank_b"),
			m_screen(*this, "screen") {}

	// constants
<<<<<<< HEAD
	static const UINT32 X_VISIBLE = 336;
	static const UINT32 Y_VISIBLE = 244;
	static const UINT32 DIMM_BANK_WORDS = 128 * 1024 * 1024 / 2;
	static const UINT32 DIMM_BANK_MASK  = DIMM_BANK_WORDS - 1;
	static const UINT32 VRAM_BANK_WORDS = 256 * 1024;
=======
	static const uint32_t X_VISIBLE = 336;
	static const uint32_t Y_VISIBLE = 244;
	static const uint32_t DIMM_BANK_WORDS = 128 * 1024 * 1024 / 2;
	static const uint32_t DIMM_BANK_MASK  = DIMM_BANK_WORDS - 1;
	static const uint32_t VRAM_BANK_WORDS = 256 * 1024;
>>>>>>> upstream/master

	// devices
	required_device<cpu_device> m_maincpu;
	required_device<ata_interface_device> m_ata;
<<<<<<< HEAD
	required_shared_ptr<UINT16> m_bank_a;
	required_shared_ptr<UINT16> m_bank_b;
=======
	required_shared_ptr<uint16_t> m_bank_a;
	required_shared_ptr<uint16_t> m_bank_b;
>>>>>>> upstream/master
	required_device<screen_device> m_screen;

	// handlers
	DECLARE_WRITE32_MEMBER(dma_w);
	DECLARE_READ32_MEMBER(video_r);
	DECLARE_WRITE32_MEMBER(video_w);
	DECLARE_READ32_MEMBER(int_r);
	DECLARE_WRITE32_MEMBER(int_w);
<<<<<<< HEAD
	DECLARE_READ32_MEMBER(sound_r);
	DECLARE_WRITE32_MEMBER(sound_w);
=======
>>>>>>> upstream/master
	INPUT_CHANGED_MEMBER(ipt_change);
	DECLARE_READ_LINE_MEMBER(sbrc2_r);
	DECLARE_READ_LINE_MEMBER(sbrc3_r);

	TIMER_CALLBACK_MEMBER(dma_complete);
	INTERRUPT_GEN_MEMBER(vblank);
	INTERRUPT_GEN_MEMBER(adc);

	// functions
<<<<<<< HEAD
	UINT32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	UINT32 write_video_ram(UINT16 data);
	void update_video_addr(void);
	UINT32 update_inputs(void);

	// members
	emu_timer *m_dma_timer;
	UINT32  m_inputs_active;
	UINT16  *m_video_ram[2];
	UINT16  m_last_pixel;
	INT32   m_video_ctrl;
	UINT16  m_video_fade;
	INT16   m_x_pos;
	INT16   m_x_start;
	INT16   m_x_mod;
	INT16   m_dx;
	INT16   m_y_pos;
	INT16   m_scale_cnt_y;
	INT16   m_scale_cnt_x;
	bool    m_skip_x;
	bool    m_skip_y;
	INT16   m_scale;
	INT16   m_hotspot_x;
	INT16   m_hotspot_y;
	bool    m_dma_idle;
	UINT32  m_dma_addr[2];
	UINT32  m_ipt_val;
	UINT8   m_frame;
	UINT8   m_adc;

protected:
	// driver_device overrides
	virtual void machine_reset();
	virtual void machine_start();
=======
	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t write_video_ram(uint16_t data);
	void update_video_addr(void);
	uint32_t update_inputs(void);

	// members
	emu_timer *m_dma_timer;
	uint32_t  m_inputs_active;
	std::unique_ptr<uint16_t[]>  m_video_ram[2];
	uint16_t  m_last_pixel;
	int32_t   m_video_ctrl;
	uint16_t  m_video_fade;
	int16_t   m_x_pos;
	int16_t   m_x_start;
	int16_t   m_x_mod;
	int16_t   m_dx;
	int16_t   m_y_pos;
	int16_t   m_scale_cnt_y;
	int16_t   m_scale_cnt_x;
	bool    m_skip_x;
	bool    m_skip_y;
	int16_t   m_scale;
	int16_t   m_hotspot_x;
	int16_t   m_hotspot_y;
	bool    m_dma_idle;
	uint32_t  m_dma_addr[2];
	uint32_t  m_ipt_val;
	uint8_t   m_frame;
	uint8_t   m_adc;

protected:
	// driver_device overrides
	virtual void machine_reset() override;
	virtual void machine_start() override;
>>>>>>> upstream/master
};


class turrett_device : public device_t,
						public device_sound_interface,
						public device_memory_interface
{
<<<<<<< HEAD
	static const UINT32 SOUND_CHANNELS = 32;

public:
	// construction/destruction
	turrett_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	static const uint32_t SOUND_CHANNELS = 32;

public:
	// construction/destruction
	turrett_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER(read);
	DECLARE_WRITE32_MEMBER(write);

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;
>>>>>>> upstream/master

	const address_space_config  m_space_config;

private:
	direct_read_data *m_direct;
	sound_stream *m_stream;

	struct
	{
<<<<<<< HEAD
		UINT32  m_address;
		UINT32  m_volume;
		bool    m_playing;
	} m_channels[SOUND_CHANNELS];

	INT32 m_volume_table[0x50];
};

// device type definition
const device_type TURRETT = &device_creator<turrett_device>;
=======
		uint32_t  m_address;
		uint32_t  m_volume;
		bool    m_playing;
	} m_channels[SOUND_CHANNELS];

	int32_t m_volume_table[0x50];
};

// device type definition
DECLARE_DEVICE_TYPE(TURRETT, turrett_device)

#endif // MAME_INCLUDES_TURRETT_H
>>>>>>> upstream/master
