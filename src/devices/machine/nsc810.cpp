// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * nsc810.c
 *
 *  Created on: 10/03/2014
 *
 *  TODO:
 *    - 128 byte RAM
 *    - other timer modes (only mode 1 - event counter - is implemented currently)
 *    - port bit set/clear
 *    - and lots of other stuff
 */

<<<<<<< HEAD
#include "nsc810.h"

=======
#include "emu.h"
#include "nsc810.h"

#define VERBOSE 1
#include "logmacro.h"


>>>>>>> upstream/master
//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
#define LOG (1)

const device_type NSC810 = &device_creator<nsc810_device>;

nsc810_device::nsc810_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, NSC810, "National Semiconductor NSC810", tag, owner, clock, "nsc810", __FILE__), m_portA_latch(0), m_portB_latch(0), m_portC_latch(0),
	m_ddrA(0), m_ddrB(0), m_ddrC(0), m_mode(0), m_timer0(nullptr), m_timer1(nullptr), m_timer0_mode(0), m_timer1_mode(0), m_timer0_counter(0), m_timer1_counter(0),
	m_timer0_base(0), m_timer1_base(0), m_timer0_running(false), m_timer1_running(false), m_timer0_clock(0), m_timer1_clock(0), m_ramselect(false),
=======
DEFINE_DEVICE_TYPE(NSC810, nsc810_device, "nsc810", "National Semiconductor NSC810 RAM-I/O-Timer")

nsc810_device::nsc810_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, NSC810, tag, owner, clock),
	m_portA_latch(0), m_portB_latch(0), m_portC_latch(0),
	m_ddrA(0), m_ddrB(0), m_ddrC(0),
	m_mode(0),
	m_timer0(nullptr), m_timer1(nullptr),
	m_timer0_mode(0), m_timer1_mode(0),
	m_timer0_counter(0), m_timer1_counter(0),
	m_timer0_base(0), m_timer1_base(0),
	m_timer0_running(false), m_timer1_running(false),
	m_timer0_clock(0), m_timer1_clock(0),
	m_ramselect(false),
>>>>>>> upstream/master
	m_portA_r(*this),
	m_portB_r(*this),
	m_portC_r(*this),
	m_portA_w(*this),
	m_portB_w(*this),
	m_portC_w(*this),
	m_timer0_out(*this),
	m_timer1_out(*this)
{
}

void nsc810_device::device_start()
{
	m_portA_r.resolve_safe(0);
	m_portB_r.resolve_safe(0);
	m_portC_r.resolve_safe(0);
	m_portA_w.resolve_safe();
	m_portB_w.resolve_safe();
	m_portC_w.resolve_safe();
	m_timer0_out.resolve_safe();
	m_timer1_out.resolve_safe();

	m_portA_w(0);
	m_portB_w(0);
	m_portC_w(0);
	m_timer0_out(0);
	m_timer1_out(0);

	m_timer0 = timer_alloc(TIMER0_CLOCK);
	m_timer1 = timer_alloc(TIMER1_CLOCK);
}

void nsc810_device::device_reset()
{
	m_portA_latch = 0;
	m_portB_latch = 0;
	m_portC_latch = 0;
	m_ddrA = 0;
	m_ddrB = 0;
	m_ddrC = 0;
	m_mode = 0;
	m_timer0_mode = 0;
	m_timer1_mode = 0;
	m_timer0_counter = 0;
	m_timer1_counter = 0;
	m_timer0_running = false;
	m_timer1_running = false;
	m_ramselect = false;
}

void nsc810_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch(id)
	{
	case TIMER0_CLOCK:
		m_timer0_counter--;
		if((m_timer0_mode & 0x07) == 0x01 || (m_timer0_mode & 0x07) == 0x02)
		{
			if(m_timer0_counter == 0)
			{
				m_timer0_out(ASSERT_LINE);
				m_timer0_counter = m_timer0_base;
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 0 output set\n",tag());
=======
				LOG("NSC810: Timer 0 output set\n");
>>>>>>> upstream/master
			}
		}
		break;
	case TIMER1_CLOCK:
		m_timer1_counter--;
		if((m_timer1_mode & 0x07) == 0x01 || (m_timer1_mode & 0x07) == 0x02)
		{
			if(m_timer1_counter == 0)
			{
				m_timer1_out(ASSERT_LINE);
				m_timer1_counter = m_timer1_base;
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 1 output set\n",tag());
=======
				LOG("NSC810: Timer 1 output set\n");
>>>>>>> upstream/master
			}
		}
		break;
	}
}

READ8_MEMBER(nsc810_device::read)
{
<<<<<<< HEAD
	UINT8 res = 0xff;
=======
	uint8_t res = 0xff;
>>>>>>> upstream/master

	if(m_ramselect)
	{
		// TODO: 128 byte RAM access
	}
	else
	{
		// Register access
		switch(offset & 0x1f)
		{
		case REG_PORTA:
			res = m_portA_latch &= m_ddrA;
			res |= (m_portA_r() & ~m_ddrA);
<<<<<<< HEAD
			//if(LOG) logerror("NSC810 '%s': Port A data read %02x\n",tag(),res);
=======
			//LOG("NSC810: Port A data read %02x\n",res);
>>>>>>> upstream/master
			break;
		case REG_PORTB:
			res = m_portB_latch &= m_ddrB;
			res |= (m_portB_r() & ~m_ddrB);
<<<<<<< HEAD
			//if(LOG) logerror("NSC810 '%s': Port B data read %02x\n",tag(),res);
=======
			//LOG("NSC810: Port B data read %02x\n",res);
>>>>>>> upstream/master
			break;
		case REG_PORTC:
			res = m_portC_latch &= m_ddrC;
			res |= (m_portC_r() & ~m_ddrC);
<<<<<<< HEAD
			//if(LOG) logerror("NSC810 '%s': Port C data read %02x\n",tag(),res);
=======
			//LOG("NSC810: Port C data read %02x\n",res);
>>>>>>> upstream/master
			break;
		case REG_MODE_TIMER0:
			res = m_timer0_mode;
			break;
		case REG_MODE_TIMER1:
			res = m_timer1_mode;
			break;
		case REG_TIMER0_LOW:
			res = m_timer0_counter & 0xff;
			if((m_timer0_mode & 0x07) == 0x01 || (m_timer0_mode & 0x07) == 0x02)
			{
				m_timer0_out(CLEAR_LINE);
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 0 output reset\n",tag());
=======
				LOG("NSC810: Timer 0 output reset\n");
>>>>>>> upstream/master
			}
			break;
		case REG_TIMER0_HIGH:
			res = m_timer0_counter >> 8;
			if((m_timer0_mode & 0x07) == 0x01 || (m_timer0_mode & 0x07) == 0x02)
			{
				m_timer0_out(CLEAR_LINE);
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 0 output reset\n",tag());
=======
				LOG("NSC810: Timer 0 output reset\n");
>>>>>>> upstream/master
			}
			break;
		case REG_TIMER1_LOW:
			res = m_timer1_counter & 0xff;
			if((m_timer1_mode & 0x07) == 0x01 || (m_timer1_mode & 0x07) == 0x02)
			{
				m_timer1_out(0);
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 1 output reset\n",tag());
=======
				LOG("NSC810: Timer 1 output reset\n");
>>>>>>> upstream/master
			}
			break;
		case REG_TIMER1_HIGH:
			res = m_timer1_counter >> 8;
			if((m_timer1_mode & 0x07) == 0x01 || (m_timer1_mode & 0x07) == 0x02)
			{
				m_timer1_out(0);
<<<<<<< HEAD
				if(LOG) logerror("NSC810 '%s': Timer 1 output reset\n",tag());
			}
			break;
		default:
			if(LOG) logerror("NSC810 '%s': unused port %02x read\n",tag(),offset);
=======
				LOG("NSC810: Timer 1 output reset\n");
			}
			break;
		default:
			LOG("NSC810: unused port %02x read\n",offset);
>>>>>>> upstream/master
		}
	}
	return res;
}

WRITE8_MEMBER(nsc810_device::write)
{
<<<<<<< HEAD
	UINT32 rate;
=======
	uint32_t rate;
>>>>>>> upstream/master

	if(m_ramselect)
	{
		// TODO: 128 byte RAM access
	}
	else
	{
		// Register access
		switch(offset & 0x1f)
		{
		case REG_PORTA:
			m_portA_latch = data & ~m_ddrA;
			m_portA_w((0xff & ~m_ddrA) | (data & m_ddrA));
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Port A data write %02x\n",tag(),data);
=======
			LOG("NSC810: Port A data write %02x\n",data);
>>>>>>> upstream/master
			break;
		case REG_PORTB:
			m_portB_latch = data & ~m_ddrB;
			m_portB_w((0xff & ~m_ddrB) | (data & m_ddrB));
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Port B data write %02x\n",tag(),data);
=======
			LOG("NSC810: Port B data write %02x\n",data);
>>>>>>> upstream/master
			break;
		case REG_PORTC:
			m_portC_latch = data & ~m_ddrC;
			m_portC_w((0xff & ~m_ddrC) | (data & m_ddrC));
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Port C data write %02x\n",tag(),data);
			break;
		case REG_DDRA:
			m_ddrA = data;
			if(LOG) logerror("NSC810 '%s': Port A direction write %02x\n",tag(),data);
			break;
		case REG_DDRB:
			m_ddrB = data;
			if(LOG) logerror("NSC810 '%s': Port B direction write %02x\n",tag(),data);
			break;
		case REG_DDRC:
			m_ddrC = data;
			if(LOG) logerror("NSC810 '%s': Port C direction write %02x\n",tag(),data);
			break;
		case REG_MODE_DEF:
			if(LOG) logerror("NSC810 '%s': Mode Definition write %02x\n",tag(),data);
			break;
		case REG_PORTA_BITCLR:
			if(LOG) logerror("NSC810 '%s': Port A bit-clear write %02x\n",tag(),data);
			break;
		case REG_PORTB_BITCLR:
			if(LOG) logerror("NSC810 '%s': Port B bit-clear write %02x\n",tag(),data);
			break;
		case REG_PORTC_BITCLR:
			if(LOG) logerror("NSC810 '%s': Port C bit-clear write %02x\n",tag(),data);
			break;
		case REG_PORTA_BITSET:
			if(LOG) logerror("NSC810 '%s': Port A bit-set write %02x\n",tag(),data);
			break;
		case REG_PORTB_BITSET:
			if(LOG) logerror("NSC810 '%s': Port B bit-set write %02x\n",tag(),data);
			break;
		case REG_PORTC_BITSET:
			if(LOG) logerror("NSC810 '%s': Port C bit-set write %02x\n",tag(),data);
=======
			LOG("NSC810: Port C data write %02x\n",data);
			break;
		case REG_DDRA:
			m_ddrA = data;
			LOG("NSC810: Port A direction write %02x\n",data);
			break;
		case REG_DDRB:
			m_ddrB = data;
			LOG("NSC810: Port B direction write %02x\n",data);
			break;
		case REG_DDRC:
			m_ddrC = data;
			LOG("NSC810: Port C direction write %02x\n",data);
			break;
		case REG_MODE_DEF:
			LOG("NSC810: Mode Definition write %02x\n",data);
			break;
		case REG_PORTA_BITCLR:
			LOG("NSC810: Port A bit-clear write %02x\n",data);
			break;
		case REG_PORTB_BITCLR:
			LOG("NSC810: Port B bit-clear write %02x\n",data);
			break;
		case REG_PORTC_BITCLR:
			LOG("NSC810: Port C bit-clear write %02x\n",data);
			break;
		case REG_PORTA_BITSET:
			LOG("NSC810: Port A bit-set write %02x\n",data);
			break;
		case REG_PORTB_BITSET:
			LOG("NSC810: Port B bit-set write %02x\n",data);
			break;
		case REG_PORTC_BITSET:
			LOG("NSC810: Port C bit-set write %02x\n",data);
>>>>>>> upstream/master
			break;
		case REG_TIMER0_LOW:
			m_timer0_base = (m_timer0_base & 0xff00) | data;
			m_timer0_counter = (m_timer0_counter & 0xff00) | data;
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 0 low-byte write %02x (base=%04x)\n",tag(),data,m_timer0_base);
=======
			LOG("NSC810: Timer 0 low-byte write %02x (base=%04x)\n",data,m_timer0_base);
>>>>>>> upstream/master
			break;
		case REG_TIMER0_HIGH:
			m_timer0_base = (m_timer0_base & 0x00ff) | (data << 8);
			m_timer0_counter = (m_timer0_counter & 0x00ff) | (data << 8);
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 0 high-byte write %02x (base=%04x)\n",tag(),data,m_timer0_base);
=======
			LOG("NSC810: Timer 0 high-byte write %02x (base=%04x)\n",data,m_timer0_base);
>>>>>>> upstream/master
			break;
		case REG_TIMER1_LOW:
			m_timer1_base = (m_timer1_base & 0xff00) | data;
			m_timer1_counter = (m_timer1_counter & 0xff00) | data;
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 1 low-byte write %02x (base=%04x)\n",tag(),data,m_timer1_base);
=======
			LOG("NSC810: Timer 1 low-byte write %02x (base=%04x)\n",data,m_timer1_base);
>>>>>>> upstream/master
			break;
		case REG_TIMER1_HIGH:
			m_timer1_base = (m_timer1_base & 0x00ff) | (data << 8);
			m_timer1_counter = (m_timer1_counter & 0x00ff) | (data << 8);
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 1 high-byte write %02x (base=%04x)\n",tag(),data,m_timer1_base);
=======
			LOG("NSC810: Timer 1 high-byte write %02x (base=%04x)\n",data,m_timer1_base);
>>>>>>> upstream/master
			break;
		case REG_TIMER0_STOP:
			m_timer0_running = false;
			m_timer0->reset();
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 0 Stop write %02x\n",tag(),data);
=======
			LOG("NSC810: Timer 0 Stop write %02x\n",tag(),data);
>>>>>>> upstream/master
			break;
		case REG_TIMER0_START:
			if((m_timer0_mode & 0x07) != 0x00 && (m_timer0_mode & 0x07) != 0x07)
			{
				m_timer0_running = true;
				if(m_timer0_mode & 0x10)
					rate = m_timer0_clock / 64;
				else
					if(m_timer0_mode & 0x08)
						rate = m_timer0_clock / 2;
					else
						rate = m_timer0_clock;
				m_timer0->adjust(attotime::zero,0,attotime::from_hz(rate));
			}
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 0 Start write %02x\n",tag(),data);
=======
			LOG("NSC810: Timer 0 Start write %02x\n",data);
>>>>>>> upstream/master
			break;
		case REG_TIMER1_STOP:
			m_timer1_running = false;
			m_timer1->reset();
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 1 Stop write %02x\n",tag(),data);
=======
			LOG("NSC810: Timer 1 Stop write %02x\n",data);
>>>>>>> upstream/master
			break;
		case REG_TIMER1_START:
			if((m_timer1_mode & 0x07) != 0x00 && (m_timer1_mode & 0x07) != 0x07)
			{
				m_timer1_running = true;
				// no /64 prescaler on timer 1
				if(m_timer0_mode & 0x08)
					rate = m_timer0_clock / 2;
				else
					rate = m_timer0_clock;
				m_timer1->adjust(attotime::zero,0,attotime::from_hz(rate));
			}
<<<<<<< HEAD
			if(LOG) logerror("NSC810 '%s': Timer 1 Start write %02x\n",tag(),data);
			break;
		case REG_MODE_TIMER0:
			m_timer0_mode = data;
			if(LOG) logerror("NSC810 '%s': Timer 0 Mode write %02x\n",tag(),data);
			break;
		case REG_MODE_TIMER1:
			m_timer1_mode = data;
			if(LOG) logerror("NSC810 '%s': Timer 1 Mode write %02x\n",tag(),data);
			break;
		default:
			logerror("NSC810 '%s': Unused register %02x write %02x\n",tag(),offset,data);
=======
			LOG("NSC810: Timer 1 Start write %02x\n",data);
			break;
		case REG_MODE_TIMER0:
			m_timer0_mode = data;
			LOG("NSC810: Timer 0 Mode write %02x\n",data);
			break;
		case REG_MODE_TIMER1:
			m_timer1_mode = data;
			LOG("NSC810: Timer 1 Mode write %02x\n",data);
			break;
		default:
			logerror("NSC810: Unused register %02x write %02x\n",offset,data);
>>>>>>> upstream/master
		}
	}
}
