// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    i8243.c

<<<<<<< HEAD
    Intel 8243 Port Expander
=======
    Intel 8243 Port Expander (for MCS-48)
>>>>>>> upstream/master

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
=======
#include "cpu/mcs48/mcs48.h"
>>>>>>> upstream/master
#include "i8243.h"

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type I8243 = &device_creator<i8243_device>;
=======
DEFINE_DEVICE_TYPE(I8243, i8243_device, "i8243", "Intel 8243 I/O Expander")
>>>>>>> upstream/master

//-------------------------------------------------
//  i8243_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
i8243_device::i8243_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, I8243, "8243 I/O Expander", tag, owner, clock, "i8243", __FILE__), m_p2out(0), m_p2(0), m_opcode(0), m_prog(0),
		m_readhandler(*this),
		m_writehandler(*this)
=======
i8243_device::i8243_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, I8243, tag, owner, clock)
	, m_p2out(0), m_p2(0), m_opcode(0), m_prog(0)
	, m_readhandler(*this)
	, m_writehandler(*this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void i8243_device::device_start()
{
	m_readhandler.resolve_safe(0);
	m_writehandler.resolve_safe();
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void i8243_device::device_reset()
{
	m_p2 = 0x0f;
	m_p2out = 0x0f;
	m_prog = 1;
}


/*-------------------------------------------------
    i8243_p2_r - handle a read from port 2
-------------------------------------------------*/

<<<<<<< HEAD
READ8_MEMBER(i8243_device::i8243_p2_r)
=======
READ8_MEMBER(i8243_device::p2_r)
>>>>>>> upstream/master
{
	return m_p2out;
}


/*-------------------------------------------------
    i8243_p2_r - handle a write to port 2
-------------------------------------------------*/

<<<<<<< HEAD
WRITE8_MEMBER(i8243_device::i8243_p2_w)
=======
WRITE8_MEMBER(i8243_device::p2_w)
>>>>>>> upstream/master
{
	m_p2 = data & 0x0f;
}


/*-------------------------------------------------
    i8243_prog_w - handle a change in the PROG
    line state
-------------------------------------------------*/

<<<<<<< HEAD
WRITE8_MEMBER(i8243_device::i8243_prog_w)
{
	/* only care about low bit */
	data &= 1;

	/* on high->low transition state, latch opcode/port */
	if(m_prog && !data)
=======
WRITE_LINE_MEMBER(i8243_device::prog_w)
{
	/* on high->low transition state, latch opcode/port */
	if (m_prog && !state)
>>>>>>> upstream/master
	{
		m_opcode = m_p2;

		/* if this is a read opcode, copy result to p2out */
<<<<<<< HEAD
		if((m_opcode >> 2) == MCS48_EXPANDER_OP_READ)
=======
		if ((m_opcode >> 2) == mcs48_cpu_device::EXPANDER_OP_READ)
>>>>>>> upstream/master
		{
			if (m_readhandler.isnull())
			{
				m_p[m_opcode & 3] = m_readhandler(m_opcode & 3);
			}
			m_p2out = m_p[m_opcode & 3] & 0x0f;
		}
	}

	/* on low->high transition state, act on opcode */
<<<<<<< HEAD
	else if(!m_prog && data)
	{
		switch(m_opcode >> 2)
		{
			case MCS48_EXPANDER_OP_WRITE:
=======
	else if (!m_prog && state)
	{
		switch (m_opcode >> 2)
		{
			case mcs48_cpu_device::EXPANDER_OP_READ:
				break; // handled above

			case mcs48_cpu_device::EXPANDER_OP_WRITE:
>>>>>>> upstream/master
				m_p[m_opcode & 3] = m_p2 & 0x0f;
				m_writehandler((offs_t)(m_opcode & 3), m_p[m_opcode & 3]);
				break;

<<<<<<< HEAD
			case MCS48_EXPANDER_OP_OR:
=======
			case mcs48_cpu_device::EXPANDER_OP_OR:
>>>>>>> upstream/master
				m_p[m_opcode & 3] |= m_p2 & 0x0f;
				m_writehandler((offs_t)(m_opcode & 3), m_p[m_opcode & 3]);
				break;

<<<<<<< HEAD
			case MCS48_EXPANDER_OP_AND:
=======
			case mcs48_cpu_device::EXPANDER_OP_AND:
>>>>>>> upstream/master
				m_p[m_opcode & 3] &= m_p2 & 0x0f;
				m_writehandler((offs_t)(m_opcode & 3), m_p[m_opcode & 3]);
				break;
		}
	}

	/* remember the state */
<<<<<<< HEAD
	m_prog = data;
=======
	m_prog = state;
>>>>>>> upstream/master
}
