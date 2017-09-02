// license:BSD-3-Clause
// copyright-holders:David Haywood
/* 68340 */

<<<<<<< HEAD
#include "68340.h"




int m68340_calc_cs(m68340cpu_device *m68k, offs_t address)
{
	m68340_sim* sim = m68k->m68340SIM;

	if ( !(sim->m_ba[0] & 1) ) return 1;

	for (int i=0;i<4;i++)
	{
		if (sim->m_ba[i] & 1)
		{
			int mask = ((sim->m_am[i]&0xffffff00) | 0xff);
			int base = sim->m_ba[i] & 0xffffff00;
			int fcmask = (sim->m_am[i] & 0xf0);
			int fcbase = (sim->m_ba[i] & 0xf0) & ~(sim->m_am[i] & 0xf0);
			int fc = m68k->mmu_tmp_fc;
=======
#include "emu.h"
#include "68340.h"

DEFINE_DEVICE_TYPE(M68340, m68340_cpu_device, "mc68340", "MC68340")


int m68340_cpu_device::calc_cs(offs_t address) const
{
	if ( !(m68340SIM->m_ba[0] & 1) ) return 1;

	for (int i=0;i<4;i++)
	{
		if (m68340SIM->m_ba[i] & 1)
		{
			int mask = ((m68340SIM->m_am[i]&0xffffff00) | 0xff);
			int base = m68340SIM->m_ba[i] & 0xffffff00;
			int fcmask = (m68340SIM->m_am[i] & 0xf0);
			int fcbase = (m68340SIM->m_ba[i] & 0xf0) & ~(m68340SIM->m_am[i] & 0xf0);
			int fc = mmu_tmp_fc;
>>>>>>> upstream/master

			if ((address & ~mask) == base && ((fc << 4) & ~fcmask ) == fcbase ) return i+1;
		}
	}

	return 0;
}



<<<<<<< HEAD
UINT16 m68340_get_cs(m68340cpu_device *device, offs_t address)
{
	device->m68340_currentcs = m68340_calc_cs(device, address);

	return device->m68340_currentcs;
=======
uint16_t m68340_cpu_device::get_cs(offs_t address)
{
	m_currentcs = calc_cs(address);

	return m_currentcs;
>>>>>>> upstream/master
}



/* 68340 specifics - MOVE */

<<<<<<< HEAD
READ32_MEMBER( m68340cpu_device::m68340_internal_base_r )
{
	m68340cpu_device *m68k = this;
	int pc = space.device().safe_pc();
	logerror("%08x m68340_internal_base_r %08x, (%08x)\n", pc, offset*4,mem_mask);
	return m68k->m68340_base;
}

WRITE32_MEMBER( m68340cpu_device::m68340_internal_base_w )
{
	m68340cpu_device *m68k = this;

=======
READ32_MEMBER( m68340_cpu_device::m68340_internal_base_r )
{
	int pc = space.device().safe_pc();
	logerror("%08x m68340_internal_base_r %08x, (%08x)\n", pc, offset*4,mem_mask);
	return m68340_base;
}

WRITE32_MEMBER( m68340_cpu_device::m68340_internal_base_w )
{
>>>>>>> upstream/master
	int pc = space.device().safe_pc();
	logerror("%08x m68340_internal_base_w %08x, %08x (%08x)\n", pc, offset*4,data,mem_mask);

	// other conditions?
<<<<<<< HEAD
	if (m68k->dfc==0x7)
	{
		// unmap old modules
		if (m68k->m68340_base&1)
		{
			int base = m68k->m68340_base & 0xfffff000;

			m68k->internal->unmap_readwrite(base + 0x000, base + 0x05f);
			m68k->internal->unmap_readwrite(base + 0x600, base + 0x67f);
			m68k->internal->unmap_readwrite(base + 0x700, base + 0x723);
			m68k->internal->unmap_readwrite(base + 0x780, base + 0x7bf);

		}

		COMBINE_DATA(&m68k->m68340_base);
		logerror("%08x m68340_internal_base_w %08x, %08x (%08x) (m68340_base write)\n", pc, offset*4,data,mem_mask);

		// map new modules
		if (m68k->m68340_base&1)
		{
			int base = m68k->m68340_base & 0xfffff000;

			m68k->internal->install_readwrite_handler(base + 0x000, base + 0x03f, read16_delegate(FUNC(m68340cpu_device::m68340_internal_sim_r),this),     write16_delegate(FUNC(m68340cpu_device::m68340_internal_sim_w),this),0xffffffff);
			m68k->internal->install_readwrite_handler(base + 0x010, base + 0x01f, read8_delegate(FUNC(m68340cpu_device::m68340_internal_sim_ports_r),this),write8_delegate(FUNC(m68340cpu_device::m68340_internal_sim_ports_w),this),0xffffffff);
			m68k->internal->install_readwrite_handler(base + 0x040, base + 0x05f, read32_delegate(FUNC(m68340cpu_device::m68340_internal_sim_cs_r),this),  write32_delegate(FUNC(m68340cpu_device::m68340_internal_sim_cs_w),this));
			m68k->internal->install_readwrite_handler(base + 0x600, base + 0x67f, read32_delegate(FUNC(m68340cpu_device::m68340_internal_timer_r),this),   write32_delegate(FUNC(m68340cpu_device::m68340_internal_timer_w),this));
			m68k->internal->install_readwrite_handler(base + 0x700, base + 0x723, read32_delegate(FUNC(m68340cpu_device::m68340_internal_serial_r),this),  write32_delegate(FUNC(m68340cpu_device::m68340_internal_serial_w),this));
			m68k->internal->install_readwrite_handler(base + 0x780, base + 0x7bf, read32_delegate(FUNC(m68340cpu_device::m68340_internal_dma_r),this),     write32_delegate(FUNC(m68340cpu_device::m68340_internal_dma_w),this));
=======
	if (dfc==0x7)
	{
		// unmap old modules
		if (m68340_base&1)
		{
			int base = m68340_base & 0xfffff000;

			internal->unmap_readwrite(base + 0x000, base + 0x05f);
			internal->unmap_readwrite(base + 0x600, base + 0x67f);
			internal->unmap_readwrite(base + 0x700, base + 0x723);
			internal->unmap_readwrite(base + 0x780, base + 0x7bf);

		}

		COMBINE_DATA(&m68340_base);
		logerror("%08x m68340_internal_base_w %08x, %08x (%08x) (m68340_base write)\n", pc, offset*4,data,mem_mask);

		// map new modules
		if (m68340_base&1)
		{
			int base = m68340_base & 0xfffff000;

			internal->install_readwrite_handler(base + 0x000, base + 0x03f,
												read16_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_r),this),
												write16_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_w),this),0xffffffff);
			internal->install_readwrite_handler(base + 0x010, base + 0x01f, // Intentionally punches a hole in previous address mapping
												read8_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_ports_r),this),
												write8_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_ports_w),this),0xffffffff);
			internal->install_readwrite_handler(base + 0x040, base + 0x05f,
												read32_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_cs_r),this),
												write32_delegate(FUNC(m68340_cpu_device::m68340_internal_sim_cs_w),this));
			internal->install_readwrite_handler(base + 0x600, base + 0x67f,
												read16_delegate(FUNC(m68340_cpu_device::m68340_internal_timer_r),this),
												write16_delegate(FUNC(m68340_cpu_device::m68340_internal_timer_w),this),0xffffffff);
			internal->install_readwrite_handler(base + 0x700, base + 0x723,
												read32_delegate(FUNC(m68340_cpu_device::m68340_internal_serial_r),this),
												write32_delegate(FUNC(m68340_cpu_device::m68340_internal_serial_w),this));
			internal->install_readwrite_handler(base + 0x780, base + 0x7bf,
												read32_delegate(FUNC(m68340_cpu_device::m68340_internal_dma_r),this),
												write32_delegate(FUNC(m68340_cpu_device::m68340_internal_dma_w),this));
>>>>>>> upstream/master

		}

	}
	else
	{
		logerror("%08x m68340_internal_base_w %08x, %04x (%04x) (should fall through?)\n", pc, offset*4,data,mem_mask);
	}



}


<<<<<<< HEAD
static ADDRESS_MAP_START( m68340_internal_map, AS_PROGRAM, 32, m68340cpu_device )
=======
static ADDRESS_MAP_START( m68340_internal_map, AS_PROGRAM, 32, m68340_cpu_device )
>>>>>>> upstream/master
	AM_RANGE(0x0003ff00, 0x0003ff03) AM_READWRITE( m68340_internal_base_r, m68340_internal_base_w)
ADDRESS_MAP_END





<<<<<<< HEAD
m68340cpu_device::m68340cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: fscpu32_device(mconfig, "MC68340", tag, owner, clock, M68340, 32,32, ADDRESS_MAP_NAME(m68340_internal_map), "mc68340", __FILE__)
{
	m68340SIM = 0;
	m68340DMA = 0;
	m68340SERIAL = 0;
	m68340TIMER = 0;
=======
m68340_cpu_device::m68340_cpu_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: fscpu32_device(mconfig, tag, owner, clock, M68340, 32,32, ADDRESS_MAP_NAME(m68340_internal_map))
	, m_clock_mode(0)
	, m_crystal(0)
	, m_extal(0)
	, m_pa_out_cb(*this)
	, m_pa_in_cb(*this)
	, m_pb_out_cb(*this)
	, m_pb_in_cb(*this)
	, m_tout1_out_cb(*this)
	, m_tin1_in_cb(*this)
	, m_tgate1_in_cb(*this)
	, m_tout2_out_cb(*this)
	, m_tin2_in_cb(*this)
	, m_tgate2_in_cb(*this)
{
	m68340SIM = nullptr;
	m68340DMA = nullptr;
	m68340SERIAL = nullptr;
	m68340TIMER = nullptr;
>>>>>>> upstream/master
	m68340_base = 0;
}






<<<<<<< HEAD
void m68340cpu_device::device_reset()
=======
void m68340_cpu_device::device_reset()
>>>>>>> upstream/master
{
	fscpu32_device::device_reset();
}

<<<<<<< HEAD

void m68340cpu_device::device_start()
=======
// Some hardwares pulls this low when resetting peripherals, most just ties this line to GND or VCC
// TODO: Support Limp mode and external clock with no PLL
WRITE_LINE_MEMBER( m68340_cpu_device::set_modck )
{
	m_modck = state;
	m_clock_mode &= ~(m68340_sim::CLOCK_MODCK | m68340_sim::CLOCK_PLL);
	m_clock_mode |= ((m_modck == ASSERT_LINE) ? (m68340_sim::CLOCK_MODCK | m68340_sim::CLOCK_PLL) : 0);
}

void m68340_cpu_device::device_start()
>>>>>>> upstream/master
{
	fscpu32_device::device_start();

	m68340SIM    = new m68340_sim();
	m68340DMA    = new m68340_dma();
	m68340SERIAL = new m68340_serial();
	m68340TIMER  = new m68340_timer();

	m68340SIM->reset();
	m68340DMA->reset();
	m68340SERIAL->reset();
	m68340TIMER->reset();

	start_68340_sim();
<<<<<<< HEAD
=======
	start_68340_timer();
>>>>>>> upstream/master

	m68340_base = 0x00000000;

	internal = &this->space(AS_PROGRAM);
}
