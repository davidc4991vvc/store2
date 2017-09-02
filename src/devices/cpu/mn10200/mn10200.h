// license:BSD-3-Clause
// copyright-holders:Olivier Galibert, R. Belmont, hap
/*
    Panasonic MN10200 emulator

    Written by Olivier Galibert
    MAME conversion by R. Belmont

*/

<<<<<<< HEAD
#ifndef MN10200_H
#define MN10200_H

// port setup
#define MCFG_MN10200_READ_PORT_CB(X, _devcb) \
	mn10200_device::set_read_port##X##_callback(*device, DEVCB_##_devcb);
#define MCFG_MN10200_WRITE_PORT_CB(X, _devcb) \
	mn10200_device::set_write_port##X##_callback(*device, DEVCB_##_devcb);
=======
#ifndef MAME_CPU_MN10200_MN10200_H
#define MAME_CPU_MN10200_MN10200_H

#pragma once

// port setup
#define MCFG_MN10200_READ_PORT_CB(X, _devcb) \
	devcb = &mn10200_device::set_read_port##X##_callback(*device, DEVCB_##_devcb);
#define MCFG_MN10200_WRITE_PORT_CB(X, _devcb) \
	devcb = &mn10200_device::set_write_port##X##_callback(*device, DEVCB_##_devcb);
>>>>>>> upstream/master

enum
{
	MN10200_PORT0 = 0,
	MN10200_PORT1,
	MN10200_PORT2,
	MN10200_PORT3,
	MN10200_PORT4
};

enum
{
	MN10200_IRQ0 = 0,
	MN10200_IRQ1,
	MN10200_IRQ2,
	MN10200_IRQ3,

	MN10200_MAX_EXT_IRQ
};


<<<<<<< HEAD
#define MN10200_NUM_PRESCALERS (2)
#define MN10200_NUM_TIMERS_8BIT (10)
#define MN10200_NUM_IRQ_GROUPS (31)


class mn10200_device : public cpu_device
{
public:
	// construction/destruction
	mn10200_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, address_map_constructor program, const char *shortname, const char *source)
		: cpu_device(mconfig, type, name, tag, owner, clock, shortname, source)
		, m_program_config("program", ENDIANNESS_LITTLE, 16, 24, 0, program), m_program(nullptr)
			, m_read_port0(*this), m_read_port1(*this), m_read_port2(*this), m_read_port3(*this), m_read_port4(*this)
		, m_write_port0(*this), m_write_port1(*this), m_write_port2(*this), m_write_port3(*this), m_write_port4(*this), m_cycles(0), m_pc(0), m_psw(0), m_mdr(0), m_nmicr(0), m_iagr(0),
		m_extmdl(0), m_extmdh(0), m_possible_irq(false), m_pplul(0), m_ppluh(0), m_p3md(0), m_p4(0)
	{ }

	// static configuration helpers
	template<class _Object> static devcb_base &set_read_port0_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_read_port0.set_callback(object); }
	template<class _Object> static devcb_base &set_read_port1_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_read_port1.set_callback(object); }
	template<class _Object> static devcb_base &set_read_port2_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_read_port2.set_callback(object); }
	template<class _Object> static devcb_base &set_read_port3_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_read_port3.set_callback(object); }
	template<class _Object> static devcb_base &set_read_port4_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_read_port4.set_callback(object); }

	template<class _Object> static devcb_base &set_write_port0_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_write_port0.set_callback(object); }
	template<class _Object> static devcb_base &set_write_port1_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_write_port1.set_callback(object); }
	template<class _Object> static devcb_base &set_write_port2_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_write_port2.set_callback(object); }
	template<class _Object> static devcb_base &set_write_port3_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_write_port3.set_callback(object); }
	template<class _Object> static devcb_base &set_write_port4_callback(device_t &device, _Object object) { return downcast<mn10200_device &>(device).m_write_port4.set_callback(object); }
=======
class mn10200_device : public cpu_device
{
public:
	// static configuration helpers
	template <class Object> static devcb_base &set_read_port0_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_read_port0.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_read_port1_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_read_port1.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_read_port2_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_read_port2.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_read_port3_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_read_port3.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_read_port4_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_read_port4.set_callback(std::forward<Object>(cb)); }

	template <class Object> static devcb_base &set_write_port0_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_write_port0.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_write_port1_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_write_port1.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_write_port2_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_write_port2.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_write_port3_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_write_port3.set_callback(std::forward<Object>(cb)); }
	template <class Object> static devcb_base &set_write_port4_callback(device_t &device, Object &&cb) { return downcast<mn10200_device &>(device).m_write_port4.set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(io_control_r);
	DECLARE_WRITE8_MEMBER(io_control_w);

protected:
<<<<<<< HEAD
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_execute_interface overrides
	virtual UINT64 execute_clocks_to_cycles(UINT64 clocks) const { return (clocks + 2 - 1) / 2; } // internal /2 divider
	virtual UINT64 execute_cycles_to_clocks(UINT64 cycles) const { return (cycles * 2); } // internal /2 divider
	virtual UINT32 execute_min_cycles() const { return 1; }
	virtual UINT32 execute_max_cycles() const { return 13+7; } // max opcode cycles + interrupt duration
	virtual UINT32 execute_input_lines() const { return 4; }
	virtual void execute_run();
	virtual void execute_set_input(int inputnum, int state);

	// device_memory_interface overrides
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const { return (spacenum == AS_PROGRAM) ? &m_program_config : NULL; }

	// device_state_interface overrides
	void state_string_export(const device_state_entry &entry, std::string &str);

	// device_disasm_interface overrides
	virtual UINT32 disasm_min_opcode_bytes() const { return 1; }
	virtual UINT32 disasm_max_opcode_bytes() const { return 7; }
	virtual offs_t disasm_disassemble(char *buffer, offs_t pc, const UINT8 *oprom, const UINT8 *opram, UINT32 options);
=======
	static constexpr unsigned MN10200_NUM_PRESCALERS = 2;
	static constexpr unsigned MN10200_NUM_TIMERS_8BIT = 10;
	static constexpr unsigned MN10200_NUM_IRQ_GROUPS = 31;


	// construction/destruction
	mn10200_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, address_map_constructor program);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_execute_interface overrides
	virtual uint64_t execute_clocks_to_cycles(uint64_t clocks) const override { return (clocks + 2 - 1) / 2; } // internal /2 divider
	virtual uint64_t execute_cycles_to_clocks(uint64_t cycles) const override { return (cycles * 2); } // internal /2 divider
	virtual uint32_t execute_min_cycles() const override { return 1; }
	virtual uint32_t execute_max_cycles() const override { return 13+7; } // max opcode cycles + interrupt duration
	virtual uint32_t execute_input_lines() const override { return 4; }
	virtual void execute_run() override;
	virtual void execute_set_input(int inputnum, int state) override;

	// device_memory_interface overrides
	virtual space_config_vector memory_space_config() const override;

	// device_state_interface overrides
	virtual void state_string_export(const device_state_entry &entry, std::string &str) const override;

	// device_disasm_interface overrides
	virtual uint32_t disasm_min_opcode_bytes() const override { return 1; }
	virtual uint32_t disasm_max_opcode_bytes() const override { return 7; }
	virtual offs_t disasm_disassemble(std::ostream &stream, offs_t pc, const uint8_t *oprom, const uint8_t *opram, uint32_t options) override;
>>>>>>> upstream/master

private:
	address_space_config m_program_config;
	address_space *m_program;

	// i/o handlers
	devcb_read8 m_read_port0, m_read_port1, m_read_port2, m_read_port3, m_read_port4;
	devcb_write8 m_write_port0, m_write_port1, m_write_port2, m_write_port3, m_write_port4;

	int m_cycles;

	// The UINT32s are really UINT24
<<<<<<< HEAD
	UINT32 m_pc;
	UINT32 m_d[4];
	UINT32 m_a[4];
	UINT16 m_psw;
	UINT16 m_mdr;
=======
	uint32_t m_pc;
	uint32_t m_d[4];
	uint32_t m_a[4];
	uint16_t m_psw;
	uint16_t m_mdr;
>>>>>>> upstream/master

	// interrupts
	void take_irq(int level, int group);
	void check_irq();
	void check_ext_irq();

<<<<<<< HEAD
	UINT8 m_icrl[MN10200_NUM_IRQ_GROUPS];
	UINT8 m_icrh[MN10200_NUM_IRQ_GROUPS];

	UINT8 m_nmicr;
	UINT8 m_iagr;
	UINT8 m_extmdl;
	UINT8 m_extmdh;
=======
	uint8_t m_icrl[MN10200_NUM_IRQ_GROUPS];
	uint8_t m_icrh[MN10200_NUM_IRQ_GROUPS];

	uint8_t m_nmicr;
	uint8_t m_iagr;
	uint8_t m_extmdl;
	uint8_t m_extmdh;
>>>>>>> upstream/master
	bool m_possible_irq;

	// timers
	void refresh_timer(int tmr);
	void refresh_all_timers();
	int timer_tick_simple(int tmr);
	TIMER_CALLBACK_MEMBER( simple_timer_cb );

	attotime m_sysclock_base;
	emu_timer *m_timer_timers[MN10200_NUM_TIMERS_8BIT];

	struct
	{
<<<<<<< HEAD
		UINT8 mode;
		UINT8 base;
		UINT8 cur;
=======
		uint8_t mode;
		uint8_t base;
		uint8_t cur;
>>>>>>> upstream/master
	} m_simple_timer[MN10200_NUM_TIMERS_8BIT];

	struct
	{
<<<<<<< HEAD
		UINT8 mode;
		UINT8 base;
		UINT8 cur;
=======
		uint8_t mode;
		uint8_t base;
		uint8_t cur;
>>>>>>> upstream/master
	} m_prescaler[MN10200_NUM_PRESCALERS];

	// dma
	struct
	{
<<<<<<< HEAD
		UINT32 adr;
		UINT32 count;
		UINT16 iadr;
		UINT8 ctrll;
		UINT8 ctrlh;
		UINT8 irq;
=======
		uint32_t adr;
		uint32_t count;
		uint16_t iadr;
		uint8_t ctrll;
		uint8_t ctrlh;
		uint8_t irq;
>>>>>>> upstream/master
	} m_dma[8];

	// serial
	struct
	{
<<<<<<< HEAD
		UINT8 ctrll;
		UINT8 ctrlh;
		UINT8 buf;
	} m_serial[2];

	// ports
	UINT8 m_pplul;
	UINT8 m_ppluh;
	UINT8 m_p3md;
	UINT8 m_p4;

	struct
	{
		UINT8 out;
		UINT8 dir;
	} m_port[4];

	// internal read/write
	inline UINT8 read_arg8(UINT32 address) { return m_program->read_byte(address); }
	inline UINT16 read_arg16(UINT32 address) { return m_program->read_byte(address) | m_program->read_byte(address + 1) << 8; }
	inline UINT32 read_arg24(UINT32 address) { return m_program->read_byte(address) | m_program->read_byte(address + 1) << 8 | m_program->read_byte(address + 2) << 16; }

	inline UINT8 read_mem8(UINT32 address) { return m_program->read_byte(address); }
	inline UINT16 read_mem16(UINT32 address) { return m_program->read_word(address & ~1); }
	inline UINT32 read_mem24(UINT32 address) { return m_program->read_word(address & ~1) | m_program->read_byte((address & ~1) + 2) << 16; }

	inline void write_mem8(UINT32 address, UINT8 data) { m_program->write_byte(address, data); }
	inline void write_mem16(UINT32 address, UINT16 data) { m_program->write_word(address & ~1, data); }
	inline void write_mem24(UINT32 address, UINT32 data) { m_program->write_word(address & ~1, data); m_program->write_byte((address & ~1) + 2, data >> 16); }

	inline void change_pc(UINT32 pc) { m_pc = pc & 0xffffff; }

	// opcode helpers
	void illegal(UINT8 prefix, UINT8 op);
	UINT32 do_add(UINT32 a, UINT32 b, UINT32 c = 0);
	UINT32 do_sub(UINT32 a, UINT32 b, UINT32 c = 0);
	void test_nz16(UINT16 v);
	void do_jsr(UINT32 to, UINT32 ret);
=======
		uint8_t ctrll;
		uint8_t ctrlh;
		uint8_t buf;
	} m_serial[2];

	// ports
	uint8_t m_pplul;
	uint8_t m_ppluh;
	uint8_t m_p3md;
	uint8_t m_p4;

	struct
	{
		uint8_t out;
		uint8_t dir;
	} m_port[4];

	// internal read/write
	inline uint8_t read_arg8(uint32_t address) { return m_program->read_byte(address); }
	inline uint16_t read_arg16(uint32_t address) { return m_program->read_byte(address) | m_program->read_byte(address + 1) << 8; }
	inline uint32_t read_arg24(uint32_t address) { return m_program->read_byte(address) | m_program->read_byte(address + 1) << 8 | m_program->read_byte(address + 2) << 16; }

	inline uint8_t read_mem8(uint32_t address) { return m_program->read_byte(address); }
	inline uint16_t read_mem16(uint32_t address) { return m_program->read_word(address & ~1); }
	inline uint32_t read_mem24(uint32_t address) { return m_program->read_word(address & ~1) | m_program->read_byte((address & ~1) + 2) << 16; }

	inline void write_mem8(uint32_t address, uint8_t data) { m_program->write_byte(address, data); }
	inline void write_mem16(uint32_t address, uint16_t data) { m_program->write_word(address & ~1, data); }
	inline void write_mem24(uint32_t address, uint32_t data) { m_program->write_word(address & ~1, data); m_program->write_byte((address & ~1) + 2, data >> 16); }

	inline void change_pc(uint32_t pc) { m_pc = pc & 0xffffff; }

	// opcode helpers
	void illegal(uint8_t prefix, uint8_t op);
	uint32_t do_add(uint32_t a, uint32_t b, uint32_t c = 0);
	uint32_t do_sub(uint32_t a, uint32_t b, uint32_t c = 0);
	void test_nz16(uint16_t v);
	void do_jsr(uint32_t to, uint32_t ret);
>>>>>>> upstream/master
	void do_branch(int condition = 1);
};


class mn1020012a_device : public mn10200_device
{
public:
<<<<<<< HEAD
	mn1020012a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	mn1020012a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};



<<<<<<< HEAD
extern const device_type MN1020012A;


#endif // MN10200_H
=======
DECLARE_DEVICE_TYPE(MN1020012A, mn1020012a_device)


#endif // MAME_CPU_MN10200_MN10200_H
>>>>>>> upstream/master
