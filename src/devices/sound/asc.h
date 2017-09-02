// license:BSD-3-Clause
// copyright-holders:R. Belmont
/***************************************************************************

    asc.h

    Apple Sound Chip (ASC) 344S0063
    Enhanced Apple Sound Chip (EASC) 343S1063

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ASC_H__
#define __ASC_H__




//**************************************************************************
//  CONSTANTS
//**************************************************************************

// chip behavior types
enum
{
	ASC_TYPE_ASC = 0,   // original discrete Apple Sound Chip
	ASC_TYPE_EASC = 1,  // discrete Enhanced Apple Sound Chip
	ASC_TYPE_V8 = 2,    // Subset of ASC included in the V8 ASIC (LC/LCII)
	ASC_TYPE_EAGLE = 3, // Subset of ASC included in the Eagle ASIC (Classic II)
	ASC_TYPE_SPICE = 4, // Subset of ASC included in the Spice ASIC (Color Classic)
	ASC_TYPE_SONORA = 5,    // Subset of ASC included in the Sonora ASIC (LCIII)
	ASC_TYPE_VASP = 6,  // Subset of ASC included in the VASP ASIC  (IIvx/IIvi)
	ASC_TYPE_ARDBEG = 7 // Subset of ASC included in the Ardbeg ASIC (LC520)
};
=======
#ifndef MAME_SOUND_ASC_H
#define MAME_SOUND_ASC_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_ASC_ADD(_tag, _clock, _type, _irqf) \
	MCFG_DEVICE_ADD(_tag, ASC, _clock) \
	MCFG_ASC_TYPE(_type) \
	MCFG_IRQ_FUNC(_irqf)

#define MCFG_ASC_REPLACE(_tag, _clock, _type, _irqf) \
	MCFG_DEVICE_REPLACE(_tag, ASC, _clock) \
	MCFG_ASC_TYPE(_type) \
	MCFG_IRQ_FUNC(_irqf)

#define MCFG_ASC_TYPE(_type) \
<<<<<<< HEAD
	asc_device::static_set_type(*device, _type);
#define MCFG_IRQ_FUNC(_irqf) \
	downcast<asc_device *>(device)->set_irqf(DEVCB_##_irqf);
=======
	asc_device::static_set_type(*device, asc_device::asc_type::_type);

#define MCFG_IRQ_FUNC(_irqf) \
	devcb = &downcast<asc_device *>(device)->set_irqf(DEVCB_##_irqf);

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> asc_device

class asc_device : public device_t, public device_sound_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	asc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// inline configuration helpers
	static void static_set_type(device_t &device, int type);


	template<class _write> void set_irqf(_write wr)
	{
		write_irq.set_callback(wr);
	}

	devcb_write_line write_irq;

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

	sound_stream *m_stream;

=======
	// chip behavior types
	enum class asc_type : uint8_t
	{
		ASC = 0,    // original discrete Apple Sound Chip
		EASC = 1,   // discrete Enhanced Apple Sound Chip
		V8 = 2,     // Subset of ASC included in the V8 ASIC (LC/LCII)
		EAGLE = 3,  // Subset of ASC included in the Eagle ASIC (Classic II)
		SPICE = 4,  // Subset of ASC included in the Spice ASIC (Color Classic)
		SONORA = 5, // Subset of ASC included in the Sonora ASIC (LCIII)
		VASP = 6,   // Subset of ASC included in the VASP ASIC  (IIvx/IIvi)
		ARDBEG = 7  // Subset of ASC included in the Ardbeg ASIC (LC520)
	};


	// construction/destruction
	asc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// inline configuration helpers
	static void static_set_type(device_t &device, asc_type type);


	template <class Write> devcb_base &set_irqf(Write &&wr)
	{
		return write_irq.set_callback(std::forward<Write>(wr));
	}

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

>>>>>>> upstream/master
protected:
	enum
	{
		R_VERSION = 0x800,
		R_MODE,
		R_CONTROL,
		R_FIFOMODE,
		R_FIFOSTAT,
		R_WTCONTROL,
		R_VOLUME,
		R_CLOCK,
		R_REG8,
		R_REG9,
		R_PLAYRECA,
		R_REGB,
		R_REGC,
		R_REGD,
		R_REGE,
		R_TEST
	};

	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	// inline data
	UINT8   m_chip_type;

	UINT8   m_fifo_a[0x400];
	UINT8   m_fifo_b[0x400];

	UINT8   m_regs[0x800];

	UINT32  m_phase[4], m_incr[4];
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	virtual void sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples) override;

	devcb_write_line write_irq;

	sound_stream *m_stream;

	// inline data
	asc_type  m_chip_type;

	uint8_t   m_fifo_a[0x400];
	uint8_t   m_fifo_b[0x400];

	uint8_t   m_regs[0x800];

	uint32_t  m_phase[4], m_incr[4];
>>>>>>> upstream/master

	int m_fifo_a_rdptr, m_fifo_b_rdptr;
	int m_fifo_a_wrptr, m_fifo_b_wrptr;
	int     m_fifo_cap_a, m_fifo_cap_b;

	emu_timer *m_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type ASC;


#endif /* __ASC_H__ */
=======
DECLARE_DEVICE_TYPE(ASC, asc_device)

#endif // MAME_SOUND_ASC_H
>>>>>>> upstream/master
