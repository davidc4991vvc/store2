// license:GPL-2.0+
// copyright-holders:Dirk Best,Carl
/***************************************************************************

    Intel 8089 I/O Processor

    Opcode implementations

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
=======
#include "i8089.h"
>>>>>>> upstream/master
#include "i8089_channel.h"

#define UNIMPLEMENTED logerror("%s('%s'): unimplemented opcode: %s\n", shortname(), tag(), __FUNCTION__);

<<<<<<< HEAD
#define LWR(m, o) ((INT16)m_iop->read_word(m_r[m].t, o))
#define LBR(m, o) ((INT8)m_iop->read_byte(m_r[m].t, o))
#define SWR(m, o, d) (m_iop->write_word(m_r[m].t, o, d))
#define SBR(m, o, d) (m_iop->write_byte(m_r[m].t, o, d))

void i8089_channel::add_rm(int r, int m, int o)
=======
#define LWR(m, o) ((int16_t)m_iop->read_word(m_r[m].t, o))
#define LBR(m, o) ((int8_t)m_iop->read_byte(m_r[m].t, o))
#define SWR(m, o, d) (m_iop->write_word(m_r[m].t, o, d))
#define SBR(m, o, d) (m_iop->write_byte(m_r[m].t, o, d))

void i8089_channel_device::add_rm(int r, int m, int o)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w + LWR(m, o));
}

<<<<<<< HEAD
void i8089_channel::add_mr(int m, int r, int o)
=======
void i8089_channel_device::add_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) + m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::addb_rm(int r, int m, int o)
=======
void i8089_channel_device::addb_rm(int r, int m, int o)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w + LBR(m, o));
}

<<<<<<< HEAD
void i8089_channel::addb_mr(int m, int r, int o)
=======
void i8089_channel_device::addb_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) + m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::addbi_ri(int r, INT8 i)
=======
void i8089_channel_device::addbi_ri(int r, int8_t i)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w + i);
}

<<<<<<< HEAD
void i8089_channel::addbi_mi(int m, INT8 i, int o)
=======
void i8089_channel_device::addbi_mi(int m, int8_t i, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) + i);
}

<<<<<<< HEAD
void i8089_channel::addi_ri(int r, INT16 i)
=======
void i8089_channel_device::addi_ri(int r, int16_t i)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w + i);
}

<<<<<<< HEAD
void i8089_channel::addi_mi(int m, INT16 i, int o)
=======
void i8089_channel_device::addi_mi(int m, int16_t i, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) + i);
}

<<<<<<< HEAD
void i8089_channel::and_rm(int r, int m, int o)
=======
void i8089_channel_device::and_rm(int r, int m, int o)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w & LWR(m, o));
}

<<<<<<< HEAD
void i8089_channel::and_mr(int m, int r, int o)
=======
void i8089_channel_device::and_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) & m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::andb_rm(int r, int m, int o)
{
	set_reg(r, m_r[r].w & (INT16)LBR(m, o));
}

void i8089_channel::andb_mr(int m, int r, int o)
=======
void i8089_channel_device::andb_rm(int r, int m, int o)
{
	set_reg(r, m_r[r].w & (int16_t)LBR(m, o));
}

void i8089_channel_device::andb_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) & m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::andbi_ri(int r, INT8 i)
{
	set_reg(r, m_r[r].w & (INT16)i);
}

void i8089_channel::andbi_mi(int m, INT8 i, int o)
=======
void i8089_channel_device::andbi_ri(int r, int8_t i)
{
	set_reg(r, m_r[r].w & (int16_t)i);
}

void i8089_channel_device::andbi_mi(int m, int8_t i, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) & i);
}

<<<<<<< HEAD
void i8089_channel::andi_ri(int r, INT16 i)
=======
void i8089_channel_device::andi_ri(int r, int16_t i)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w & i);
}

<<<<<<< HEAD
void i8089_channel::andi_mi(int m, INT16 i, int o)
=======
void i8089_channel_device::andi_mi(int m, int16_t i, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) & i);
}

<<<<<<< HEAD
void i8089_channel::call(int m, INT16 d, int o)
=======
void i8089_channel_device::call(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	movp_mp(m, TP, o);
	set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::clr(int m, int b, int o)
=======
void i8089_channel_device::clr(int m, int b, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) & ~(1<<b));
}

<<<<<<< HEAD
void i8089_channel::dec_r(int r)
=======
void i8089_channel_device::dec_r(int r)
>>>>>>> upstream/master
{
	m_icount += 3;
	set_reg(r, m_r[r].w - 1);
}

<<<<<<< HEAD
void i8089_channel::dec_m(int m, int o)
=======
void i8089_channel_device::dec_m(int m, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) - 1);
}

<<<<<<< HEAD
void i8089_channel::decb(int m, int o)
=======
void i8089_channel_device::decb(int m, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) - 1);
}

// halt
<<<<<<< HEAD
void i8089_channel::hlt()
=======
void i8089_channel_device::hlt()
>>>>>>> upstream/master
{
	movbi_mi(CP, 0x00, m_r[CP].w + 1);
	m_r[PSW].w &= ~(1 << 2);
	m_prio = PRIO_IDLE;
}

<<<<<<< HEAD
void i8089_channel::inc_r(int r)
=======
void i8089_channel_device::inc_r(int r)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w + 1);
}

<<<<<<< HEAD
void i8089_channel::inc_m(int m, int o)
=======
void i8089_channel_device::inc_m(int m, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) + 1);
}

<<<<<<< HEAD
void i8089_channel::incb(int m, int o)
=======
void i8089_channel_device::incb(int m, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) + 1);
}

<<<<<<< HEAD
void i8089_channel::jbt(int m, int b, INT16 d, int o)
=======
void i8089_channel_device::jbt(int m, int b, int16_t d, int o)
>>>>>>> upstream/master
{
	if(LBR(m, o) & (1<<b))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jmce(int m, INT16 d, int o)
=======
void i8089_channel_device::jmce(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if(!((LBR(m, o) ^ (m_r[MC].w & 0xff)) & (m_r[MC].w >> 8)))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jmcne(int m, INT16 d, int o)
=======
void i8089_channel_device::jmcne(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if((LBR(m, o) ^ (m_r[MC].w & 0xff)) & (m_r[MC].w >> 8))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jnbt(int m, int b, INT16 d, int o)
=======
void i8089_channel_device::jnbt(int m, int b, int16_t d, int o)
>>>>>>> upstream/master
{
	if(!(LBR(m, o) & (1<<b)))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jnz_r(int r, INT16 d)
=======
void i8089_channel_device::jnz_r(int r, int16_t d)
>>>>>>> upstream/master
{
	m_icount += 5;
	if(m_r[r].w & 0xffff)
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jnz_m(int m, INT16 d, int o)
=======
void i8089_channel_device::jnz_m(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if(LWR(m, o))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jnzb(int m, INT16 d, int o)
=======
void i8089_channel_device::jnzb(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if(LBR(m, o))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jz_r(int r, INT16 d)
=======
void i8089_channel_device::jz_r(int r, int16_t d)
>>>>>>> upstream/master
{
	if(!(m_r[r].w & 0xffff))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jz_m(int m, INT16 d, int o)
=======
void i8089_channel_device::jz_m(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if(!LWR(m, o))
		set_reg(TP, m_r[TP].w + d);
}

<<<<<<< HEAD
void i8089_channel::jzb(int m, INT16 d, int o)
=======
void i8089_channel_device::jzb(int m, int16_t d, int o)
>>>>>>> upstream/master
{
	if(!LBR(m, o))
		set_reg(TP, m_r[TP].w + d);
}


// load pointer from memory
<<<<<<< HEAD
void i8089_channel::lpd(int p, int m, int o)
{
	UINT16 offset = m_iop->read_word(m_r[m].t, o);
	UINT16 segment = m_iop->read_word(m_r[m].t, o + 2);
=======
void i8089_channel_device::lpd(int p, int m, int o)
{
	uint16_t offset = m_iop->read_word(m_r[m].t, o);
	uint16_t segment = m_iop->read_word(m_r[m].t, o + 2);
>>>>>>> upstream/master

	set_reg(p, ((segment << 4) + offset) & 0xfffff, 0);
}

// load pointer from immediate data
<<<<<<< HEAD
void i8089_channel::lpdi(int p, int s, int o)
=======
void i8089_channel_device::lpdi(int p, int s, int o)
>>>>>>> upstream/master
{
	set_reg(p, (s << 4) + (o & 0xffff), 0);
}

<<<<<<< HEAD
void i8089_channel::mov_mr(int m, int r, int o)
=======
void i8089_channel_device::mov_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SWR(m, o, m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::mov_rm(int r, int m, int o)
{
	set_reg(r, (INT32)LWR(m, o), 1);
}

void i8089_channel::mov_mm(int m1, int m2, int o1, int o2)
=======
void i8089_channel_device::mov_rm(int r, int m, int o)
{
	set_reg(r, (int32_t)LWR(m, o), 1);
}

void i8089_channel_device::mov_mm(int m1, int m2, int o1, int o2)
>>>>>>> upstream/master
{
	SWR(m2, o2, LWR(m1, o1));
}

// move register to memory byte
<<<<<<< HEAD
void i8089_channel::movb_mr(int m, int r, int o)
=======
void i8089_channel_device::movb_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	m_iop->write_byte(m_r[m].t, o, m_r[r].w & 0xff);
}

// move memory byte to register
<<<<<<< HEAD
void i8089_channel::movb_rm(int r, int m, int o)
{
	UINT8 byte = m_iop->read_byte(m_r[m].t, o);
=======
void i8089_channel_device::movb_rm(int r, int m, int o)
{
	uint8_t byte = m_iop->read_byte(m_r[m].t, o);
>>>>>>> upstream/master
	set_reg(r, (BIT(byte, 7) ? 0xfff00 : 0x00000) | byte, 1);
}

// move memory byte to memory byte
<<<<<<< HEAD
void i8089_channel::movb_mm(int m1, int m2, int o1, int o2)
{
	UINT8 byte = m_iop->read_byte(m_r[m1].t, o1);
=======
void i8089_channel_device::movb_mm(int m1, int m2, int o1, int o2)
{
	uint8_t byte = m_iop->read_byte(m_r[m1].t, o1);
>>>>>>> upstream/master
	m_iop->write_byte(m_r[m2].t, o2, byte);
}

// move immediate byte to register
<<<<<<< HEAD
void i8089_channel::movbi_ri(int r, INT8 i)
=======
void i8089_channel_device::movbi_ri(int r, int8_t i)
>>>>>>> upstream/master
{
	set_reg(r, (BIT(i, 7) ? 0xfff00 : 0x00000) | (i & 0xff), 1);
}

// move immediate byte to memory byte
<<<<<<< HEAD
void i8089_channel::movbi_mi(int m, INT8 i, int o)
=======
void i8089_channel_device::movbi_mi(int m, int8_t i, int o)
>>>>>>> upstream/master
{
	m_iop->write_byte(m_r[m].t, o, i & 0xff);
}

// move immediate word to register
<<<<<<< HEAD
void i8089_channel::movi_ri(int r, INT16 i)
=======
void i8089_channel_device::movi_ri(int r, int16_t i)
>>>>>>> upstream/master
{
	set_reg(r, (BIT(i, 15) ? 0xf0000 : 0x00000) | (i & 0xffff), 1);
}

// move immediate word to memory word
<<<<<<< HEAD
void i8089_channel::movi_mi(int m, INT16 i, int o)
=======
void i8089_channel_device::movi_mi(int m, int16_t i, int o)
>>>>>>> upstream/master
{
	m_iop->write_word(m_r[m].t, o, (BIT(i, 15) ? 0xf0000 : 0x00000) | (i & 0xffff));
}

// move pointer to memory (store)
<<<<<<< HEAD
void i8089_channel::movp_mp(int m, int p, int o)
=======
void i8089_channel_device::movp_mp(int m, int p, int o)
>>>>>>> upstream/master
{
	m_iop->write_word(m_r[m].t, o, m_r[p].w & 0xffff);
	m_iop->write_byte(m_r[m].t, o + 2, ((m_r[p].w >> 12) & 0xf0) | (m_r[p].t << 3));
}

// move memory to pointer (restore)
<<<<<<< HEAD
void i8089_channel::movp_pm(int p, int m, int o)
{
	UINT16 offset = m_iop->read_word(m_r[m].t, o);
	UINT16 segment = m_iop->read_byte(m_r[m].t, o + 2);
=======
void i8089_channel_device::movp_pm(int p, int m, int o)
{
	uint16_t offset = m_iop->read_word(m_r[m].t, o);
	uint16_t segment = m_iop->read_byte(m_r[m].t, o + 2);
>>>>>>> upstream/master

	set_reg(p, (((segment & 0xf0) << 12) + offset) & 0xfffff, segment >> 3 & 0x01);
}

// no operation
<<<<<<< HEAD
void i8089_channel::nop()
{
}

void i8089_channel::not_r(int r)
=======
void i8089_channel_device::nop()
{
}

void i8089_channel_device::not_r(int r)
>>>>>>> upstream/master
{
	set_reg(r, ~m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::not_m(int m, int o)
=======
void i8089_channel_device::not_m(int m, int o)
>>>>>>> upstream/master
{
	SWR(m, o, ~LWR(m, o));
}

<<<<<<< HEAD
void i8089_channel::not_rm(int r, int m, int o)
{
	set_reg(r, ~(INT32)LWR(m, o));
}

void i8089_channel::notb_m(int m, int o)
=======
void i8089_channel_device::not_rm(int r, int m, int o)
{
	set_reg(r, ~(int32_t)LWR(m, o));
}

void i8089_channel_device::notb_m(int m, int o)
>>>>>>> upstream/master
{
	SBR(m, o, ~LBR(m, o));
}

<<<<<<< HEAD
void i8089_channel::notb_rm(int r, int m, int o)
{
	set_reg(r, ~(INT32)LBR(m, o));
}

void i8089_channel::or_rm(int r, int m, int o)
=======
void i8089_channel_device::notb_rm(int r, int m, int o)
{
	set_reg(r, ~(int32_t)LBR(m, o));
}

void i8089_channel_device::or_rm(int r, int m, int o)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w | LWR(m, o));
}

<<<<<<< HEAD
void i8089_channel::or_mr(int m, int r, int o)
=======
void i8089_channel_device::or_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) | m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::orb_rm(int r, int m, int o)
{
	set_reg(r, m_r[r].w | (INT16)LBR(m, o));
}

void i8089_channel::orb_mr(int m, int r, int o)
=======
void i8089_channel_device::orb_rm(int r, int m, int o)
{
	set_reg(r, m_r[r].w | (int16_t)LBR(m, o));
}

void i8089_channel_device::orb_mr(int m, int r, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) | m_r[r].w);
}

<<<<<<< HEAD
void i8089_channel::orbi_ri(int r, INT8 i)
{
	set_reg(r, m_r[r].w | (INT16)i);
}

void i8089_channel::orbi_mi(int m, INT8 i, int o)
=======
void i8089_channel_device::orbi_ri(int r, int8_t i)
{
	set_reg(r, m_r[r].w | (int16_t)i);
}

void i8089_channel_device::orbi_mi(int m, int8_t i, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) | i);
}

<<<<<<< HEAD
void i8089_channel::ori_ri(int r, INT16 i)
=======
void i8089_channel_device::ori_ri(int r, int16_t i)
>>>>>>> upstream/master
{
	set_reg(r, m_r[r].w | i);
}

<<<<<<< HEAD
void i8089_channel::ori_mi(int m, INT16 i, int o)
=======
void i8089_channel_device::ori_mi(int m, int16_t i, int o)
>>>>>>> upstream/master
{
	SWR(m, o, LWR(m, o) | i);
}

<<<<<<< HEAD
void i8089_channel::setb(int m, int b, int o)
=======
void i8089_channel_device::setb(int m, int b, int o)
>>>>>>> upstream/master
{
	SBR(m, o, LBR(m, o) | (1<<b));
}


// set interrupt service flip-flop
<<<<<<< HEAD
void i8089_channel::sintr()
=======
void i8089_channel_device::sintr()
>>>>>>> upstream/master
{
	if (BIT(m_r[PSW].w, 4))
	{
		m_r[PSW].w |= 1 << 5;
		m_write_sintr(1);
	}
}

<<<<<<< HEAD
void i8089_channel::tsl(int m, INT8 i, INT8 d, int o)
=======
void i8089_channel_device::tsl(int m, int8_t i, int8_t d, int o)
>>>>>>> upstream/master
{
	if(LBR(m, o))
		set_reg(TP, m_r[TP].w + d);
	else
		SBR(m, o, i);
}


// set source and destination logical widths
<<<<<<< HEAD
void i8089_channel::wid(int s, int d)
=======
void i8089_channel_device::wid(int s, int d)
>>>>>>> upstream/master
{
	m_r[PSW].w &= 0x3f;
	m_r[PSW].w |= d << 0;
	m_r[PSW].w |= s << 1;
}

// enter dma transfer mode after next instruction
<<<<<<< HEAD
void i8089_channel::xfer()
=======
void i8089_channel_device::xfer()
>>>>>>> upstream/master
{
	m_xfer_pending = true;
}

<<<<<<< HEAD
void i8089_channel::invalid(int opc)
=======
void i8089_channel_device::invalid(int opc)
>>>>>>> upstream/master
{
	logerror("%s('%s'): invalid opcode: %02x\n", shortname(), tag(), opc);
}
