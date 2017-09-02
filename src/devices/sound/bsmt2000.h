// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    bsmt2000.h

    BSMT2000 device emulator.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __BSMT2000_H__
#define __BSMT2000_H__
=======
#ifndef MAME_SOUND_BSMT2000_H
#define MAME_SOUND_BSMT2000_H

#pragma once
>>>>>>> upstream/master

#include "cpu/tms32010/tms32010.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_BSMT2000_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, BSMT2000, _clock)
#define MCFG_BSMT2000_REPLACE(_tag, _clock) \
	MCFG_DEVICE_REPLACE(_tag, BSMT2000, _clock)
<<<<<<< HEAD
#define MCFG_BSMT2000_READY_CALLBACK(_callback) \
	bsmt2000_device::static_set_ready_callback(*device, _callback);
=======
#define MCFG_BSMT2000_READY_CALLBACK(_class, _method) \
	bsmt2000_device::static_set_ready_callback(*device, bsmt2000_device::ready_callback(&_class::_method, #_class "::" #_method, nullptr, (_class *)nullptr));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************


// ======================> bsmt2000_device

class bsmt2000_device : public device_t,
						public device_sound_interface,
<<<<<<< HEAD
						public device_memory_interface
{
	typedef void (*ready_callback)(bsmt2000_device &device);

public:
	// construction/destruction
	bsmt2000_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// inline configuration helpers
	static void static_set_ready_callback(device_t &device, ready_callback callback);

	// public interface
	UINT16 read_status();
	void write_reg(UINT16 data);
	void write_data(UINT16 data);

protected:
	// device-level overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);
=======
						public device_rom_interface
{
public:
	typedef device_delegate<void ()> ready_callback;

	// construction/destruction
	bsmt2000_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// inline configuration helpers
	static void static_set_ready_callback(device_t &device, ready_callback &&callback);

	// public interface
	uint16_t read_status();
	void write_reg(uint16_t data);
	void write_data(uint16_t data);

protected:
	// device-level overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	// device_sound_interface overrides
	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	// device_rom_interface overrides
	virtual void rom_bank_updated() override;
>>>>>>> upstream/master

public:
	// internal TMS I/O callbacks
	DECLARE_READ16_MEMBER( tms_register_r );
	DECLARE_READ16_MEMBER( tms_data_r );
	DECLARE_READ16_MEMBER( tms_rom_r );
	DECLARE_WRITE16_MEMBER( tms_rom_addr_w );
	DECLARE_WRITE16_MEMBER( tms_rom_bank_w );
	DECLARE_WRITE16_MEMBER( tms_left_w );
	DECLARE_WRITE16_MEMBER( tms_right_w );
<<<<<<< HEAD
	DECLARE_READ16_MEMBER( tms_write_pending_r );
=======
>>>>>>> upstream/master

private:
	// timers
	enum
	{
		TIMER_ID_RESET,
		TIMER_ID_REG_WRITE,
		TIMER_ID_DATA_WRITE
	};

	// configuration state
<<<<<<< HEAD
	const address_space_config  m_space_config;
=======
>>>>>>> upstream/master
	ready_callback              m_ready_callback;

	// internal state
	sound_stream *              m_stream;
<<<<<<< HEAD
	direct_read_data *          m_direct;
	tms32015_device *           m_cpu;
	UINT16                      m_register_select;
	UINT16                      m_write_data;
	UINT16                      m_rom_address;
	UINT16                      m_rom_bank;
	INT16                       m_left_data;
	INT16                       m_right_data;
	bool                        m_write_pending;
=======
	required_device<tms32015_device> m_cpu;
	uint16_t                      m_register_select;
	uint16_t                      m_write_data;
	uint16_t                      m_rom_address;
	uint16_t                      m_rom_bank;
	int16_t                       m_left_data;
	int16_t                       m_right_data;
	bool                        m_write_pending;

	DECLARE_READ_LINE_MEMBER( tms_write_pending_r );
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type BSMT2000;


#endif /* __BSMT2000_H__ */
=======
DECLARE_DEVICE_TYPE(BSMT2000, bsmt2000_device)

#endif // MAME_SOUND_BSMT2000_H
>>>>>>> upstream/master
