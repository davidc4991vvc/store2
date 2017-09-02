// license:BSD-3-Clause
// copyright-holders:Philip Bennett
/***************************************************************************

    qs1000.h

    QS1000 device emulator.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __QS1000_H__
#define __QS1000_H__
=======
#ifndef MAME_SOUND_QS1000_H
#define MAME_SOUND_QS1000_H

#pragma once
>>>>>>> upstream/master

#include "cpu/mcs51/mcs51.h"
#include "sound/okiadpcm.h"

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_QS1000_EXTERNAL_ROM(_bool) \
	qs1000_device::set_external_rom(*device, _bool);

#define MCFG_QS1000_IN_P1_CB(_devcb) \
	devcb = &qs1000_device::set_in_p1_callback(*device, DEVCB_##_devcb);

#define MCFG_QS1000_IN_P2_CB(_devcb) \
	devcb = &qs1000_device::set_in_p2_callback(*device, DEVCB_##_devcb);

#define MCFG_QS1000_IN_P3_CB(_devcb) \
	devcb = &qs1000_device::set_in_p3_callback(*device, DEVCB_##_devcb);

#define MCFG_QS1000_OUT_P1_CB(_devcb) \
	devcb = &qs1000_device::set_out_p1_callback(*device, DEVCB_##_devcb);

#define MCFG_QS1000_OUT_P2_CB(_devcb) \
	devcb = &qs1000_device::set_out_p2_callback(*device, DEVCB_##_devcb);

#define MCFG_QS1000_OUT_P3_CB(_devcb) \
	devcb = &qs1000_device::set_out_p3_callback(*device, DEVCB_##_devcb);

/*#define MCFG_QS1000_SERIAL_W_CB(_devcb) \
    devcb = &qs1000_device::set_serial_w_callback(*device, DEVCB_##_devcb);*/

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
#define QS1000_CHANNELS         32
#define QS1000_ADDRESS_MASK     0xffffff

=======
>>>>>>> upstream/master
// ======================> qs1000_device

class qs1000_device :   public device_t,
						public device_sound_interface,
<<<<<<< HEAD
						public device_memory_interface
{
public:
	// construction/destruction
	qs1000_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void set_external_rom(device_t &device, bool external_rom) { downcast<qs1000_device &>(device).m_external_rom = external_rom; }
	template<class _Object> static devcb_base &set_in_p1_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_in_p1_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_in_p2_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_in_p2_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_in_p3_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_in_p3_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_p1_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_out_p1_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_p2_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_out_p2_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_p3_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_out_p3_cb.set_callback(object); }
	//template<class _Object> static devcb_base &set_serial_w_callback(device_t &device, _Object object) { return downcast<qs1000_device &>(device).m_serial_w_cb.set_callback(object); }

	// external
	void serial_in(UINT8 data);
	void set_irq(int state);

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

	DECLARE_READ8_MEMBER( data_to_i8052 );
public:
=======
						public device_rom_interface
{
public:
	// construction/destruction
	qs1000_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void set_external_rom(device_t &device, bool external_rom) { downcast<qs1000_device &>(device).m_external_rom = external_rom; }
	template <class Object> static devcb_base &set_in_p1_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_in_p1_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_in_p2_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_in_p2_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_in_p3_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_in_p3_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_out_p1_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_out_p1_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_out_p2_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_out_p2_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_out_p3_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_out_p3_cb.set_callback(std::forward<Object>(cb)); }
	//template <class Object> static devcb_base &set_serial_w_callback(device_t &device, Object &&cb) { return downcast<qs1000_device &>(device).m_serial_w_cb.set_callback(std::forward<Object>(cb)); }

	// external
	void serial_in(uint8_t data);
	void set_irq(int state);

>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER( wave_w );

	DECLARE_READ8_MEMBER( p0_r );
	DECLARE_WRITE8_MEMBER( p0_w );

	DECLARE_READ8_MEMBER( p1_r );
	DECLARE_WRITE8_MEMBER( p1_w );

	DECLARE_READ8_MEMBER( p2_r );
	DECLARE_WRITE8_MEMBER( p2_w );

	DECLARE_READ8_MEMBER( p3_r );
	DECLARE_WRITE8_MEMBER( p3_w );

<<<<<<< HEAD
=======
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

private:
	static constexpr unsigned QS1000_CHANNELS       = 32;
	static constexpr offs_t   QS1000_ADDRESS_MASK   = 0x00ffffff;

>>>>>>> upstream/master
	enum
	{
		QS1000_KEYON   = 1,
		QS1000_PLAYING = 2,
		QS1000_ADPCM   = 4
	};

	void start_voice(int ch);
<<<<<<< HEAD
	void set_voice_regs(int ch);
=======
>>>>>>> upstream/master

	bool                    m_external_rom;

	// Callbacks
	devcb_read8             m_in_p1_cb;
	devcb_read8             m_in_p2_cb;
	devcb_read8             m_in_p3_cb;

	devcb_write8            m_out_p1_cb;
	devcb_write8            m_out_p2_cb;
	devcb_write8            m_out_p3_cb;

	//devcb_write8            m_serial_w_cb;

	// Internal state
<<<<<<< HEAD
	const address_space_config      m_space_config;
	sound_stream *                  m_stream;
	direct_read_data *              m_direct;
	required_device<i8052_device>   m_cpu;

	// Wavetable engine
	UINT8                           m_serial_data_in;
	UINT8                           m_wave_regs[18];

	struct qs1000_channel
	{
		UINT32          m_acc;
		INT32           m_adpcm_signal;
		UINT32          m_start;
		UINT32          m_addr;
		UINT32          m_adpcm_addr;
		UINT32          m_loop_start;
		UINT32          m_loop_end;
		UINT16          m_freq;
		UINT16          m_flags;

		UINT8           m_regs[16]; // FIXME
=======
	sound_stream *                  m_stream;
	required_device<i8052_device>   m_cpu;

	// Wavetable engine
	uint8_t                           m_serial_data_in;
	uint8_t                           m_wave_regs[18];

	struct qs1000_channel
	{
		uint32_t          m_acc;
		int32_t           m_adpcm_signal;
		uint32_t          m_start;
		uint32_t          m_addr;
		uint32_t          m_adpcm_addr;
		uint32_t          m_loop_start;
		uint32_t          m_loop_end;
		uint16_t          m_freq;
		uint16_t          m_flags;

		uint8_t           m_regs[16]; // FIXME
>>>>>>> upstream/master

		oki_adpcm_state m_adpcm;
	};

	qs1000_channel                  m_channels[QS1000_CHANNELS];
<<<<<<< HEAD
=======

	DECLARE_READ8_MEMBER( data_to_i8052 );
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type QS1000;


#endif /* __QS1000_H__ */
=======
DECLARE_DEVICE_TYPE(QS1000, qs1000_device)

#endif // MAME_SOUND_QS1000_H
>>>>>>> upstream/master
