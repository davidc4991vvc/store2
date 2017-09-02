// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

<<<<<<< HEAD
    CMOS 40105 FIFO Register emulation

**********************************************************************/

=======
    CD40105/HC40105 4-bit x 16-word FIFO Register

    Part of the 4000B series of CMOS TTL devices, the 40105 includes
    an asynchronous master reset pin intended to be connected to the
    system bus.

    Word size can be expanded from 4 bits to 8 bits by connecting two
    40105s in parallel, with external AND gates to combine the DIR and
    DOR outputs. They can also be connected in series to extend the
    FIFO capacity, with DOR -> SI and /SO <- DIR.

**********************************************************************/

#include "emu.h"
>>>>>>> upstream/master
#include "40105.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CMOS_40105 = &device_creator<cmos_40105_device>;

=======
DEFINE_DEVICE_TYPE(CD40105, cmos_40105_device, "cd40105", "40105 FIFO")
const device_type HC40105 = CD40105;
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  cmos_40105_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
cmos_40105_device::cmos_40105_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, CMOS_40105, "40105", tag, owner, clock, "40105", __FILE__),
		m_write_dir(*this),
		m_write_dor(*this), m_d(0), m_q(0), m_dir(0), m_dor(0), m_si(0), m_so(0)
=======
cmos_40105_device::cmos_40105_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, CD40105, tag, owner, clock),
		m_write_dir(*this),
		m_write_dor(*this),
		m_write_q(*this),
		m_d(0),
		m_q(0),
		m_dir(false),
		m_dor(false),
		m_si(false),
		m_so(false)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cmos_40105_device::device_start()
{
	// resolve callbacks
	m_write_dir.resolve_safe();
	m_write_dor.resolve_safe();
<<<<<<< HEAD
=======
	m_write_q.resolve_safe();
>>>>>>> upstream/master

	// state saving
	save_item(NAME(m_d));
	save_item(NAME(m_q));
	save_item(NAME(m_dir));
	save_item(NAME(m_dor));
	save_item(NAME(m_si));
	save_item(NAME(m_so));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void cmos_40105_device::device_reset()
{
<<<<<<< HEAD
	m_fifo = std::queue<UINT8>();

	m_dir = 1;
	m_dor = 0;
	m_si = 0;

	m_write_dir(m_dir);
	m_write_dor(m_dor);
=======
	// invalidate data in queue
	m_fifo = std::queue<u8>();

	// reset control flip-flops
	m_dir = true;
	m_dor = false;
	m_write_dir(1);
	m_write_dor(0);
>>>>>>> upstream/master
}


//-------------------------------------------------
<<<<<<< HEAD
//  read - read Q
//-------------------------------------------------

UINT8 cmos_40105_device::read()
=======
//  read - read output buffer (Q0 to Q3)
//-------------------------------------------------

u8 cmos_40105_device::read()
>>>>>>> upstream/master
{
	return m_q;
}


//-------------------------------------------------
<<<<<<< HEAD
//  write - write D
//-------------------------------------------------

void cmos_40105_device::write(UINT8 data)
=======
//  write - write input buffer (D0 to D3)
//-------------------------------------------------

void cmos_40105_device::write(u8 data)
>>>>>>> upstream/master
{
	m_d = data & 0x0f;
}

<<<<<<< HEAD
=======
WRITE8_MEMBER(cmos_40105_device::write)
{
	write(data);
}


//-------------------------------------------------
//  load_input - load new data into FIFO
//-------------------------------------------------

void cmos_40105_device::load_input()
{
	if (m_fifo.size() == 16)
	{
		logerror("Attempt to load data into full FIFO\n");
		return;
	}

	m_fifo.push(m_d);

	// DIR remains low if FIFO is full, or else briefly pulses low
	m_write_dir(0);
	if (m_fifo.size() == 16)
		m_dir = false;
	else
		m_write_dir(1);
}


//-------------------------------------------------
//  output_ready - place new data at output
//-------------------------------------------------

void cmos_40105_device::output_ready()
{
	if (m_fifo.size() == 0)
	{
		logerror("Attempt to output data from empty FIFO\n");
		return;
	}

	m_q = m_fifo.front();
	m_write_q(m_q);

	m_dor = true;
	m_write_dor(1);
}

>>>>>>> upstream/master

//-------------------------------------------------
//  si_w - shift in write
//-------------------------------------------------

WRITE_LINE_MEMBER( cmos_40105_device::si_w )
{
<<<<<<< HEAD
	if (m_dir && !m_si && state)
	{
		m_fifo.push(m_d);

		if (m_fifo.size() == 16)
		{
			m_dir = 0;
			m_write_dir(m_dir);
		}

		if (!m_dor)
		{
			m_dor = 1;
			m_write_dor(m_dor);
		}

=======
	// load input on rising edge when ready
	if (m_dir && !m_si && state)
	{
		load_input();
	}
	else if (m_si && !state && m_fifo.size() > 0)
	{
		// data propagates through FIFO when SI goes low
		if (!m_dor)
			output_ready();
>>>>>>> upstream/master
	}

	m_si = state;
}


//-------------------------------------------------
//  so_w - shift out write
//-------------------------------------------------

WRITE_LINE_MEMBER( cmos_40105_device::so_w )
{
<<<<<<< HEAD
	if (m_dor && m_so && !m_so)
	{
		m_dor = 0;
		m_write_dor(m_dor);

		m_q = m_fifo.front();
		m_fifo.pop();

		if (m_fifo.size() > 0)
		{
			m_dor = 1;
			m_write_dor(m_dor);
=======
	// shift out on falling edge when ready
	if (m_dor && m_so && !state)
	{
		m_fifo.pop();
		m_dor = false;
		m_write_dor(0);

		// DOR remains low if FIFO is now empty, or else briefly pulses low
		if (m_fifo.size() > 0)
			output_ready();

		if (!m_dir)
		{
			// raise DIR since FIFO is no longer full
			m_dir = true;
			m_write_dir(1);

			// load new input immediately if SI is held high
			if (m_si)
				load_input();
>>>>>>> upstream/master
		}
	}

	m_so = state;
}


//-------------------------------------------------
//  dir_r - data in ready read
//-------------------------------------------------

READ_LINE_MEMBER( cmos_40105_device::dir_r )
{
	return m_dir;
}


//-------------------------------------------------
//  dor_r - data out ready read
//-------------------------------------------------

READ_LINE_MEMBER( cmos_40105_device::dor_r )
{
	return m_dor;
}
