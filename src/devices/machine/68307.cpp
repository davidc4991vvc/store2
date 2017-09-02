// license:BSD-3-Clause
// copyright-holders:David Haywood
/* 68307 */

<<<<<<< HEAD
#include "68307.h"
=======
#include "emu.h"
#include "68307.h"
#include "68307bus.h"
#include "68307sim.h"
#include "68307tmu.h"

DEFINE_DEVICE_TYPE(M68307, m68307_cpu_device, "mc68307", "MC68307")

>>>>>>> upstream/master

/* 68307 SERIAL Module */
/* all ports on this are 8-bit? */

/* this is a 68681 'compatible' chip but with only a single channel implemented
  (writes to the other channel have no effects)

  for now at least we piggyback on the existing 68307 emulation rather than having
  a custom verson here, that may change later if subtle differences exist.

*/
<<<<<<< HEAD
READ8_MEMBER( m68307cpu_device::m68307_internal_serial_r )
{
	m68307cpu_device *m68k = this;
=======
READ8_MEMBER( m68307_cpu_device::m68307_internal_serial_r )
{
	m68307_cpu_device *m68k = this;
>>>>>>> upstream/master

	if (offset&1) return m_duart->read(*m68k->program, offset>>1);
	return 0x0000;
}

<<<<<<< HEAD
WRITE8_MEMBER(m68307cpu_device::m68307_internal_serial_w)
{
	m68307cpu_device *m68k = this;
=======
WRITE8_MEMBER(m68307_cpu_device::m68307_internal_serial_w)
{
	m68307_cpu_device *m68k = this;
>>>>>>> upstream/master

	if (offset & 1) m_duart->write(*m68k->program, offset >> 1, data);
}



<<<<<<< HEAD
static ADDRESS_MAP_START( m68307_internal_map, AS_PROGRAM, 16, m68307cpu_device )
=======
static ADDRESS_MAP_START( m68307_internal_map, AS_PROGRAM, 16, m68307_cpu_device )
>>>>>>> upstream/master
	AM_RANGE(0x000000f0, 0x000000ff) AM_READWRITE(m68307_internal_base_r, m68307_internal_base_w)
ADDRESS_MAP_END


<<<<<<< HEAD

static MACHINE_CONFIG_FRAGMENT( 68307fragment )
	MCFG_MC68681_ADD("internal68681", 16000000/4) // ?? Mhz - should be specified in inline config
	MCFG_MC68681_IRQ_CALLBACK(WRITELINE(m68307cpu_device, m68307_duart_irq_handler))
	MCFG_MC68681_A_TX_CALLBACK(WRITELINE(m68307cpu_device, m68307_duart_txa))
	MCFG_MC68681_B_TX_CALLBACK(WRITELINE(m68307cpu_device, m68307_duart_txb))
	MCFG_MC68681_INPORT_CALLBACK(READ8(m68307cpu_device, m68307_duart_input_r))
	MCFG_MC68681_OUTPORT_CALLBACK(WRITE8(m68307cpu_device, m68307_duart_output_w))
MACHINE_CONFIG_END

machine_config_constructor m68307cpu_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( 68307fragment );
}


m68307cpu_device::m68307cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: m68000_device(mconfig, "MC68307", tag, owner, clock, M68307, 16,24, ADDRESS_MAP_NAME(m68307_internal_map), "mc68307", __FILE__),
=======
MACHINE_CONFIG_MEMBER( m68307_cpu_device::device_add_mconfig )
	MCFG_MC68681_ADD("internal68681", 16000000/4) // ?? Mhz - should be specified in inline config
	MCFG_MC68681_IRQ_CALLBACK(WRITELINE(m68307_cpu_device, m68307_duart_irq_handler))
	MCFG_MC68681_A_TX_CALLBACK(WRITELINE(m68307_cpu_device, m68307_duart_txa))
	MCFG_MC68681_B_TX_CALLBACK(WRITELINE(m68307_cpu_device, m68307_duart_txb))
	MCFG_MC68681_INPORT_CALLBACK(READ8(m68307_cpu_device, m68307_duart_input_r))
	MCFG_MC68681_OUTPORT_CALLBACK(WRITE8(m68307_cpu_device, m68307_duart_output_w))
MACHINE_CONFIG_END


m68307_cpu_device::m68307_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: m68000_device(mconfig, tag, owner, clock, M68307, 16, 24, ADDRESS_MAP_NAME(m68307_internal_map)),
>>>>>>> upstream/master
	write_irq(*this),
	write_a_tx(*this),
	write_b_tx(*this),
	read_inport(*this),
	write_outport(*this),
	m_duart(*this, "internal68681")
{
<<<<<<< HEAD
	m68307SIM = 0;
	m68307MBUS = 0;
	m68307TIMER = 0;
=======
	m68307SIM = nullptr;
	m68307MBUS = nullptr;
	m68307TIMER = nullptr;
>>>>>>> upstream/master
	m68307_base = 0;
	m68307_scrhigh = 0;
	m68307_scrlow = 0;
	m68307_currentcs = 0;
}






<<<<<<< HEAD
void m68307cpu_device::device_reset()
=======
void m68307_cpu_device::device_reset()
>>>>>>> upstream/master
{
	m68000_device::device_reset();

	if (m68307SIM) m68307SIM->reset();
	if (m68307MBUS) m68307MBUS->reset();
	if (m68307TIMER) m68307TIMER->reset();

	m68307_base = 0xbfff;
	m68307_scrhigh = 0x0007;
	m68307_scrlow = 0xf010;

}


/* todo: is it possible to calculate the address map based on CS when they change
   and install handlers?  Going through this logic for every memory access is
   very slow */

<<<<<<< HEAD
int m68307_calc_cs(m68307cpu_device *m68k, offs_t address)
{
	m68307_sim* sim = m68k->m68307SIM;

	for (int i=0;i<4;i++)
	{
		int br,amask,bra;
		br = sim->m_br[i] & 1;
		amask = ((sim->m_or[i]&0x1ffc)<<11);
		bra = ((sim->m_br[i] & 0x1ffc)<<11);
		if ((br) && ((address & amask) == bra)) return i+1;
=======
inline int m68307_cpu_device::calc_cs(offs_t address) const
{
	m68307_sim const &sim = *m68307SIM;
	for (int i=0; i < 4; i++)
	{
		int const br = sim.m_br[i] & 1;
		int const amask = (sim.m_or[i] & 0x1ffc) << 11;
		int const bra = (sim.m_br[i] & 0x1ffc) << 11;
		if (br && ((address & amask) == bra)) return i + 1;
>>>>>>> upstream/master
	}
	return 0;
}



<<<<<<< HEAD
UINT16 m68307cpu_device::simple_read_immediate_16_m68307(offs_t address)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	return m_direct->read_word(address);
}

UINT8 m68307cpu_device::read_byte_m68307(offs_t address)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	return m_space->read_byte(address);
}

UINT16 m68307cpu_device::read_word_m68307(offs_t address)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	return m_space->read_word(address);
}

UINT32 m68307cpu_device::read_dword_m68307(offs_t address)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	return m_space->read_dword(address);
}

void m68307cpu_device::write_byte_m68307(offs_t address, UINT8 data)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	m_space->write_byte(address, data);
}

void m68307cpu_device::write_word_m68307(offs_t address, UINT16 data)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
	m_space->write_word(address, data);
}

void m68307cpu_device::write_dword_m68307(offs_t address, UINT32 data)
{
//  m68307_currentcs = m68307_calc_cs(this, address);
=======
uint16_t m68307_cpu_device::simple_read_immediate_16_m68307(offs_t address)
{
//  m68307_currentcs = calc_cs(address);
	return m_direct->read_word(address);
}

uint8_t m68307_cpu_device::read_byte_m68307(offs_t address)
{
//  m68307_currentcs = calc_cs(address);
	return m_space->read_byte(address);
}

uint16_t m68307_cpu_device::read_word_m68307(offs_t address)
{
//  m68307_currentcs = calc_cs(address);
	return m_space->read_word(address);
}

uint32_t m68307_cpu_device::read_dword_m68307(offs_t address)
{
//  m68307_currentcs = calc_cs(address);
	return m_space->read_dword(address);
}

void m68307_cpu_device::write_byte_m68307(offs_t address, uint8_t data)
{
//  m68307_currentcs = calc_cs(address);
	m_space->write_byte(address, data);
}

void m68307_cpu_device::write_word_m68307(offs_t address, uint16_t data)
{
//  m68307_currentcs = calc_cs(address);
	m_space->write_word(address, data);
}

void m68307_cpu_device::write_dword_m68307(offs_t address, uint32_t data)
{
//  m68307_currentcs = calc_cs(address);
>>>>>>> upstream/master
	m_space->write_dword(address, data);
}




<<<<<<< HEAD
void m68307cpu_device::init16_m68307(address_space &space)
=======
void m68307_cpu_device::init16_m68307(address_space &space)
>>>>>>> upstream/master
{
	m_space = &space;
	m_direct = &space.direct();
	opcode_xor = 0;

<<<<<<< HEAD
	readimm16 = m68k_readimm16_delegate(FUNC(m68307cpu_device::simple_read_immediate_16_m68307), this);
	read8 = m68k_read8_delegate(FUNC(m68307cpu_device::read_byte_m68307), this);
	read16 = m68k_read16_delegate(FUNC(m68307cpu_device::read_word_m68307), this);
	read32 = m68k_read32_delegate(FUNC(m68307cpu_device::read_dword_m68307), this);
	write8 = m68k_write8_delegate(FUNC(m68307cpu_device::write_byte_m68307), this);
	write16 = m68k_write16_delegate(FUNC(m68307cpu_device::write_word_m68307), this);
	write32 = m68k_write32_delegate(FUNC(m68307cpu_device::write_dword_m68307), this);
=======
	readimm16 = m68k_readimm16_delegate(&m68307_cpu_device::simple_read_immediate_16_m68307, this);
	read8 = m68k_read8_delegate(&m68307_cpu_device::read_byte_m68307, this);
	read16 = m68k_read16_delegate(&m68307_cpu_device::read_word_m68307, this);
	read32 = m68k_read32_delegate(&m68307_cpu_device::read_dword_m68307, this);
	write8 = m68k_write8_delegate(&m68307_cpu_device::write_byte_m68307, this);
	write16 = m68k_write16_delegate(&m68307_cpu_device::write_word_m68307, this);
	write32 = m68k_write32_delegate(&m68307_cpu_device::write_dword_m68307, this);
>>>>>>> upstream/master
}



<<<<<<< HEAD
void m68307cpu_device::set_port_callbacks(m68307_porta_read_delegate porta_r, m68307_porta_write_delegate porta_w, m68307_portb_read_delegate portb_r, m68307_portb_write_delegate portb_w)
{
	m_m68307_porta_r = porta_r;
	m_m68307_porta_w = porta_w;
	m_m68307_portb_r = portb_r;
	m_m68307_portb_w = portb_w;
=======
void m68307_cpu_device::set_port_callbacks(
		porta_read_delegate &&porta_r,
		porta_write_delegate &&porta_w,
		portb_read_delegate &&portb_r,
		portb_write_delegate &&portb_w)
{
	m_porta_r = std::move(porta_r);
	m_porta_w = std::move(porta_w);
	m_portb_r = std::move(portb_r);
	m_portb_w = std::move(portb_w);
>>>>>>> upstream/master
}





<<<<<<< HEAD
UINT16 m68307cpu_device::get_cs(offs_t address)
{
	m68307_currentcs = m68307_calc_cs(this, address);
=======
uint16_t m68307_cpu_device::get_cs(offs_t address)
{
	m68307_currentcs = calc_cs(address);
>>>>>>> upstream/master

	return m68307_currentcs;
}


/* 68307 specifics - MOVE */

<<<<<<< HEAD
void m68307cpu_device::set_interrupt(int level, int vector)
=======
void m68307_cpu_device::set_interrupt(int level, int vector)
>>>>>>> upstream/master
{
	set_input_line_and_vector(level, HOLD_LINE, vector);
}

<<<<<<< HEAD
void m68307cpu_device::timer0_interrupt()
=======
void m68307_cpu_device::timer0_interrupt()
>>>>>>> upstream/master
{
	int prioritylevel = (m68307SIM->m_picr & 0x7000)>>12;
	int vector        = (m68307SIM->m_pivr & 0x00f0) | 0xa;
	set_interrupt(prioritylevel, vector);
}

<<<<<<< HEAD
void m68307cpu_device::timer1_interrupt()
=======
void m68307_cpu_device::timer1_interrupt()
>>>>>>> upstream/master
{
	int prioritylevel = (m68307SIM->m_picr & 0x0700)>>8;
	int vector        = (m68307SIM->m_pivr & 0x00f0) | 0xb;
	set_interrupt(prioritylevel, vector);
}


<<<<<<< HEAD
void m68307cpu_device::serial_interrupt(int vector)
=======
void m68307_cpu_device::serial_interrupt(int vector)
>>>>>>> upstream/master
{
	int prioritylevel = (m68307SIM->m_picr & 0x0070)>>4;
	set_interrupt(prioritylevel, vector);
}

<<<<<<< HEAD
WRITE_LINE_MEMBER(m68307cpu_device::m68307_duart_irq_handler)
=======
WRITE_LINE_MEMBER(m68307_cpu_device::m68307_duart_irq_handler)
>>>>>>> upstream/master
{
	if (state == ASSERT_LINE)
	{
		serial_interrupt(m_duart->get_irq_vector());
	}
}

<<<<<<< HEAD
void m68307cpu_device::mbus_interrupt()
=======
void m68307_cpu_device::mbus_interrupt()
>>>>>>> upstream/master
{
	int prioritylevel = (m68307SIM->m_picr & 0x0007)>>0;
	int vector        = (m68307SIM->m_pivr & 0x00f0) | 0xd;
	set_interrupt(prioritylevel, vector);
}

<<<<<<< HEAD
void m68307cpu_device::licr2_interrupt()
=======
void m68307_cpu_device::licr2_interrupt()
>>>>>>> upstream/master
{
	int prioritylevel = (m68307SIM->m_licr2 & 0x0007)>>0;
	int vector        = (m68307SIM->m_pivr & 0x00f0) | 0x9;
	m68307SIM->m_licr2 |= 0x8;


	set_interrupt(prioritylevel, vector);
}

<<<<<<< HEAD
void m68307cpu_device::device_start()
=======
void m68307_cpu_device::device_start()
>>>>>>> upstream/master
{
	init_cpu_m68000();

	/* basic CS logic, timers, mbus, serial logic
	   set via remappable register
	*/

	init16_m68307(*program);

	m68307SIM    = new m68307_sim();
	m68307MBUS   = new m68307_mbus();
	m68307TIMER  = new m68307_timer();

	m68307TIMER->init(this);

	m68307SIM->reset();
	m68307MBUS->reset();
	m68307TIMER->reset();

	internal = &this->space(AS_PROGRAM);
	m68307_base = 0xbfff;
	m68307_scrhigh = 0x0007;
	m68307_scrlow = 0xf010;

	write_irq.resolve_safe();
	write_a_tx.resolve_safe();
	write_b_tx.resolve_safe();
	read_inport.resolve();
	write_outport.resolve_safe();

<<<<<<< HEAD
	set_port_callbacks(m68307_porta_read_delegate(),m68307_porta_write_delegate(),m68307_portb_read_delegate(),m68307_portb_write_delegate());
=======
	set_port_callbacks(porta_read_delegate(), porta_write_delegate(), portb_read_delegate(), portb_write_delegate());
>>>>>>> upstream/master
}



<<<<<<< HEAD
READ16_MEMBER( m68307cpu_device::m68307_internal_base_r )
{
	m68307cpu_device *m68k = this;
=======
READ16_MEMBER( m68307_cpu_device::m68307_internal_base_r )
{
	m68307_cpu_device *m68k = this;
>>>>>>> upstream/master

	int pc = space.device().safe_pc();
	logerror("%08x m68307_internal_base_r %08x, (%04x)\n", pc, offset*2,mem_mask);

	switch (offset<<1)
	{
		case 0x2: return m68k->m68307_base;
		case 0x4: return m68k->m68307_scrhigh;
		case 0x6: return m68k->m68307_scrlow;
	}

	logerror("(read was illegal?)\n");

	return 0x0000;
}

<<<<<<< HEAD
WRITE16_MEMBER( m68307cpu_device::m68307_internal_base_w )
{
	m68307cpu_device *m68k = this;

	int pc = space.device().safe_pc();
	logerror("%08x m68307_internal_base_w %08x, %04x (%04x)\n", pc, offset*2,data,mem_mask);
	int base = 0;
=======
WRITE16_MEMBER( m68307_cpu_device::m68307_internal_base_w )
{
	m68307_cpu_device *m68k = this;

	int pc = space.device().safe_pc();
	logerror("%08x m68307_internal_base_w %08x, %04x (%04x)\n", pc, offset*2,data,mem_mask);
	int base;
>>>>>>> upstream/master
	//int mask = 0;

	switch (offset<<1)
	{
		case 0x2:
			/* remove old internal handler */
			base = (m68k->m68307_base & 0x0fff) << 12;
			//mask = (m68k->m68307_base & 0xe000) >> 13;
			//if ( m68k->m68307_base & 0x1000 ) mask |= 7;
			m68k->internal->unmap_readwrite(base+0x000, base+0x04f);
			m68k->internal->unmap_readwrite(base+0x100, base+0x11f);
			m68k->internal->unmap_readwrite(base+0x120, base+0x13f);
			m68k->internal->unmap_readwrite(base+0x140, base+0x149);

			/* store new base address */
			COMBINE_DATA(&m68k->m68307_base);

			/* install new internal handler */
			base = (m68k->m68307_base & 0x0fff) << 12;
			//mask = (m68k->m68307_base & 0xe000) >> 13;
			//if ( m68k->m68307_base & 0x1000 ) mask |= 7;
<<<<<<< HEAD
			m68k->internal->install_readwrite_handler(base + 0x000, base + 0x04f, read16_delegate(FUNC(m68307cpu_device::m68307_internal_sim_r),this),    write16_delegate(FUNC(m68307cpu_device::m68307_internal_sim_w),this));
			m68k->internal->install_readwrite_handler(base + 0x100, base + 0x11f, read8_delegate(FUNC(m68307cpu_device::m68307_internal_serial_r),this), write8_delegate(FUNC(m68307cpu_device::m68307_internal_serial_w),this), 0xffff);
			m68k->internal->install_readwrite_handler(base + 0x120, base + 0x13f, read16_delegate(FUNC(m68307cpu_device::m68307_internal_timer_r),this),  write16_delegate(FUNC(m68307cpu_device::m68307_internal_timer_w),this));
			m68k->internal->install_readwrite_handler(base + 0x140, base + 0x149, read8_delegate(FUNC(m68307cpu_device::m68307_internal_mbus_r),this),   write8_delegate(FUNC(m68307cpu_device::m68307_internal_mbus_w),this), 0xffff);
=======
			m68k->internal->install_readwrite_handler(base + 0x000, base + 0x04f, read16_delegate(FUNC(m68307_cpu_device::m68307_internal_sim_r),this),    write16_delegate(FUNC(m68307_cpu_device::m68307_internal_sim_w),this));
			m68k->internal->install_readwrite_handler(base + 0x100, base + 0x11f, read8_delegate(FUNC(m68307_cpu_device::m68307_internal_serial_r),this), write8_delegate(FUNC(m68307_cpu_device::m68307_internal_serial_w),this), 0xffff);
			m68k->internal->install_readwrite_handler(base + 0x120, base + 0x13f, read16_delegate(FUNC(m68307_cpu_device::m68307_internal_timer_r),this),  write16_delegate(FUNC(m68307_cpu_device::m68307_internal_timer_w),this));
			m68k->internal->install_readwrite_handler(base + 0x140, base + 0x149, read8_delegate(FUNC(m68307_cpu_device::m68307_internal_mbus_r),this),   write8_delegate(FUNC(m68307_cpu_device::m68307_internal_mbus_w),this), 0xffff);
>>>>>>> upstream/master


			break;

		case 0x4:
			COMBINE_DATA(&m68k->m68307_scrhigh);
			break;

		case 0x6:
			COMBINE_DATA(&m68k->m68307_scrlow);
			break;

		default:
			logerror("(write was illegal?)\n");
			break;
	}
}
