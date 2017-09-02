// license:BSD-3-Clause
// copyright-holders:Luca Elia
<<<<<<< HEAD
#ifndef TMP68301_H
#define TMP68301_H
=======
#ifndef MAME_MACHINE_TMP68301_H
#define MAME_MACHINE_TMP68301_H

#pragma once
>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

/* TODO: serial ports, frequency & hook it up with m68k */
<<<<<<< HEAD
#define MCFG_TMP68301_IN_PARALLEL_CB(_devcb) \
	devcb = &tmp68301_device::set_in_parallel_callback(*device, DEVCB_##_devcb);

#define MCFG_TMP68301_OUT_PARALLEL_CB(_devcb) \
	devcb = &tmp68301_device::set_out_parallel_callback(*device, DEVCB_##_devcb);
=======
#define MCFG_TMP68301_IN_PARALLEL_CB(cb) \
		devcb = &tmp68301_device::set_in_parallel_callback(*device, (DEVCB_##cb));

#define MCFG_TMP68301_OUT_PARALLEL_CB(cb) \
		devcb = &tmp68301_device::set_out_parallel_callback(*device, (DEVCB_##cb));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************



class tmp68301_device : public device_t,
						public device_memory_interface
{
public:
<<<<<<< HEAD
	tmp68301_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	~tmp68301_device() {}

	template<class _Object> static devcb_base &set_in_parallel_callback(device_t &device, _Object object) { return downcast<tmp68301_device &>(device).m_in_parallel_cb.set_callback(object); }
	template<class _Object> static devcb_base &set_out_parallel_callback(device_t &device, _Object object) { return downcast<tmp68301_device &>(device).m_out_parallel_cb.set_callback(object); }
=======
	tmp68301_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_in_parallel_callback(device_t &device, Object &&cb) { return downcast<tmp68301_device &>(device).m_in_parallel_cb.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_out_parallel_callback(device_t &device, Object &&cb) { return downcast<tmp68301_device &>(device).m_out_parallel_cb.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	// Hardware Registers
	DECLARE_READ16_MEMBER( regs_r );
	DECLARE_WRITE16_MEMBER( regs_w );

	// Interrupts
	void external_interrupt_0();
	void external_interrupt_1();
	void external_interrupt_2();

	DECLARE_READ16_MEMBER(imr_r);
	DECLARE_WRITE16_MEMBER(imr_w);
	DECLARE_READ16_MEMBER(iisr_r);
	DECLARE_WRITE16_MEMBER(iisr_w);
	DECLARE_READ16_MEMBER(scr_r);
	DECLARE_WRITE16_MEMBER(scr_w);
	DECLARE_READ16_MEMBER(pdr_r);
	DECLARE_WRITE16_MEMBER(pdr_w);
	DECLARE_READ16_MEMBER(pdir_r);
	DECLARE_WRITE16_MEMBER(pdir_w);
<<<<<<< HEAD

	IRQ_CALLBACK_MEMBER(irq_callback);
protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

private:
=======
	DECLARE_READ8_MEMBER(icr_r);
	DECLARE_WRITE8_MEMBER(icr_w);

	IRQ_CALLBACK_MEMBER(irq_callback);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual space_config_vector memory_space_config() const override;

private:
	TIMER_CALLBACK_MEMBER( timer_callback );
	void update_timer( int i );
	void update_irq_state(uint16_t cause);
	void update_irq_serial(uint16_t cause, uint8_t type);

	static constexpr uint16_t EXT_IRQ0 = 1 << 0;
	static constexpr uint16_t EXT_IRQ1 = 1 << 1;
	static constexpr uint16_t EXT_IRQ2 = 1 << 2;
	static constexpr uint16_t SERIAL_IRQ_CH0 = 1 << 4;
	static constexpr uint16_t SERIAL_IRQ_CH1 = 1 << 5;
	static constexpr uint16_t SERIAL_IRQ_CH2 = 1 << 6;
	static constexpr uint16_t PARALLEL_IRQ = 1 << 7;
	static constexpr uint16_t TIMER0_IRQ = 1 << 8;
	static constexpr uint16_t TIMER1_IRQ = 1 << 9;
	static constexpr uint16_t TIMER2_IRQ = 1 << 10;

	inline uint16_t read_word(offs_t address);
	inline void write_word(offs_t address, uint16_t data);

>>>>>>> upstream/master
	devcb_read16         m_in_parallel_cb;
	devcb_write16        m_out_parallel_cb;

	// internal state
<<<<<<< HEAD
	UINT16 m_regs[0x400];

	UINT8 m_IE[3];        // 3 External Interrupt Lines
	emu_timer *m_tmp68301_timer[3];        // 3 Timers

	UINT16 m_irq_vector[8];

	TIMER_CALLBACK_MEMBER( timer_callback );
	void update_timer( int i );
	void update_irq_state();

	UINT16 m_imr;
	UINT16 m_iisr;
	UINT16 m_scr;
	UINT16 m_pdir;
	UINT16 m_pdr;

	inline UINT16 read_word(offs_t address);
	inline void write_word(offs_t address, UINT16 data);
	const address_space_config      m_space_config;
};

extern const device_type TMP68301;

#endif
=======
	uint16_t m_regs[0x400];

	emu_timer *m_tmp68301_timer[3];        // 3 Timers

	uint16_t m_irq_vector[8];

	uint16_t m_imr;
	uint16_t m_iisr;
	uint16_t m_scr;
	uint16_t m_pdir;
	uint16_t m_pdr;
	uint8_t m_icr[10];

	const address_space_config      m_space_config;
};

DECLARE_DEVICE_TYPE(TMP68301, tmp68301_device)

#endif // MAME_MACHINE_TMP68301_H
>>>>>>> upstream/master
