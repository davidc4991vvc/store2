// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:smf
/***************************************************************************

    NEC uPD4701

    Incremental Encoder Control

    2009-06 Converted to be a device
=======
// copyright-holders:smf,AJR
/***************************************************************************

    NEC µPD4701A 2-Axis Incremental Encoder Counter
>>>>>>> upstream/master

***************************************************************************/

#include "emu.h"
#include "upd4701.h"

<<<<<<< HEAD
#define MASK_SWITCHES ( 7 )
#define MASK_COUNTER ( 0xfff )

const device_type UPD4701 = &device_creator<upd4701_device>;

upd4701_device::upd4701_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, UPD4701, "uPD4701 Encoder", tag, owner, clock, "upd4701", __FILE__), m_cs(0), m_xy(0), m_ul(0), m_resetx(0), m_resety(0), m_latchx(0), m_latchy(0),
	m_startx(0), m_starty(0), m_x(0), m_y(0), m_switches(0), m_latchswitches(0), m_cf(0)
{
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void upd4701_device::device_config_complete()
=======
#define MASK_COUNTER ( 0xfff )

DEFINE_DEVICE_TYPE(UPD4701A, upd4701_device, "upd4701a", "uPD4701A Incremental Encoder")

upd4701_device::upd4701_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, UPD4701A, tag, owner, clock)
	, m_cs(true)
	, m_xy(false)
	, m_ul(false)
	, m_resetx(false)
	, m_resety(false)
	, m_portx(*this, finder_base::DUMMY_TAG)
	, m_porty(*this, finder_base::DUMMY_TAG)
	, m_latchx(0)
	, m_latchy(0)
	, m_startx(0)
	, m_starty(0)
	, m_x(0)
	, m_y(0)
	, m_switches(0)
	, m_latchswitches(0)
	, m_cf(true)
	, m_cf_cb(*this)
	, m_sf_cb(*this)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void upd4701_device::device_start()
{
<<<<<<< HEAD
=======
	// resolve callbacks
	m_cf_cb.resolve_safe();
	m_sf_cb.resolve_safe();

	// register state for saving
>>>>>>> upstream/master
	save_item(NAME(m_cs));
	save_item(NAME(m_xy));
	save_item(NAME(m_ul));
	save_item(NAME(m_resetx));
	save_item(NAME(m_resety));
	save_item(NAME(m_latchx));
	save_item(NAME(m_latchy));
	save_item(NAME(m_startx));
	save_item(NAME(m_starty));
	save_item(NAME(m_x));
	save_item(NAME(m_y));
	save_item(NAME(m_switches));
	save_item(NAME(m_latchswitches));
	save_item(NAME(m_cf));
<<<<<<< HEAD
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void upd4701_device::device_reset()
{
	m_cs = 1;
	m_xy = 0;
	m_ul = 0;
	m_resetx = 0;
	m_resety = 0;
	m_latchx = 0;
	m_latchy = 0;
	m_startx = 0;
	m_starty = 0;
	m_x = 0;
	m_y = 0;
	m_switches = 0;
	m_latchswitches = 0;
	m_cf = 1;
}

/* x,y increments can be 12bit (see MASK_COUNTER), hence we need a couple of
16bit handlers in the following  */

/*-------------------------------------------------
    ul_w
-------------------------------------------------*/

WRITE_LINE_MEMBER( upd4701_device::ul_w )
=======

	// register special callback for analog inputs
	if (m_portx.found() || m_porty.found())
		machine().add_notifier(MACHINE_NOTIFY_FRAME, machine_notify_delegate(&upd4701_device::analog_update, this));
}

//-------------------------------------------------
//  ul_w - write to counter select line
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::ul_w)
>>>>>>> upstream/master
{
	m_ul = state;
}

<<<<<<< HEAD
/*-------------------------------------------------
    xy_w
-------------------------------------------------*/

WRITE_LINE_MEMBER( upd4701_device::xy_w )
=======
//-------------------------------------------------
//  xy_w - write to byte select line
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::xy_w)
>>>>>>> upstream/master
{
	m_xy = state;
}

<<<<<<< HEAD
/*-------------------------------------------------
    cs_w
-------------------------------------------------*/

WRITE_LINE_MEMBER( upd4701_device::cs_w )
=======
//-------------------------------------------------
//  cs_w - write to chip select line
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::cs_w)
>>>>>>> upstream/master
{
	if (m_cs != state)
	{
		m_cs = state;

		if (!m_cs)
		{
			m_latchx = (m_x - m_startx) & MASK_COUNTER;
			m_latchy = (m_y - m_starty) & MASK_COUNTER;

<<<<<<< HEAD
			m_latchswitches = (~m_switches) & MASK_SWITCHES;
			if (m_latchswitches != 0)
			{
				m_latchswitches |= 8;
			}

			m_cf = 1;
=======
			m_latchswitches = m_switches;
			if (m_switches != 0)
				m_latchswitches |= 8;

			if (!m_cf)
			{
				// CF remains inactive while CS is low
				m_cf = true;
				m_cf_cb(1);
			}
>>>>>>> upstream/master
		}
	}
}

<<<<<<< HEAD
/*-------------------------------------------------
    resetx_w
-------------------------------------------------*/

WRITE_LINE_MEMBER( upd4701_device::resetx_w )
=======
//-------------------------------------------------
//  resetx_w - write to X counter reset line
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::resetx_w)
>>>>>>> upstream/master
{
	if (m_resetx != state)
	{
		m_resetx = state;

		if (m_resetx)
<<<<<<< HEAD
		{
			m_startx = m_x;
		}
	}
}

/*-------------------------------------------------
    resety_w
-------------------------------------------------*/

WRITE_LINE_MEMBER( upd4701_device::resety_w )
=======
			m_startx = m_x;
	}
}

//-------------------------------------------------
//  resety_w - write to Y counter reset line
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::resety_w)
>>>>>>> upstream/master
{
	if (m_resety != state)
	{
		m_resety = state;

		if (m_resety)
<<<<<<< HEAD
		{
			m_starty = m_y;
		}
	}
}

/*-------------------------------------------------
    x_add
-------------------------------------------------*/

void upd4701_device::x_add( INT16 data )
=======
			m_starty = m_y;
	}
}

//-------------------------------------------------
//  reset_x - pulse the X counter reset line
//-------------------------------------------------

READ8_MEMBER(upd4701_device::reset_x)
{
	if (!machine().side_effect_disabled())
	{
		resetx_w(1);
		resetx_w(0);
	}
	return space.unmap();
}

WRITE8_MEMBER(upd4701_device::reset_x)
{
	resetx_w(1);
	resetx_w(0);
}

//-------------------------------------------------
//  reset_y - pulse the Y counter reset line
//-------------------------------------------------

READ8_MEMBER(upd4701_device::reset_y)
{
	if (!machine().side_effect_disabled())
	{
		resety_w(1);
		resety_w(0);
	}
	return space.unmap();
}

WRITE8_MEMBER(upd4701_device::reset_y)
{
	resety_w(1);
	resety_w(0);
}

//-------------------------------------------------
//  reset_xy - pulse the counter reset lines
//-------------------------------------------------

READ8_MEMBER(upd4701_device::reset_xy)
{
	if (!machine().side_effect_disabled())
	{
		resetx_w(1);
		resety_w(1);
		resetx_w(0);
		resety_w(0);
	}
	return space.unmap();
}

WRITE8_MEMBER(upd4701_device::reset_xy)
{
	resetx_w(1);
	resety_w(1);
	resetx_w(0);
	resety_w(0);
}

//-------------------------------------------------
//  analog_update - per-frame input update
//-------------------------------------------------

void upd4701_device::analog_update()
{
	if (m_portx.found())
		x_add(m_portx->read() & MASK_COUNTER);
	if (m_porty.found())
		y_add(m_porty->read() & MASK_COUNTER);
}

//-------------------------------------------------
//  x_add - count X-axis input
//-------------------------------------------------

void upd4701_device::x_add(s16 data)
>>>>>>> upstream/master
{
	if (!m_resetx && data != 0)
	{
		m_x += data;

<<<<<<< HEAD
		if (m_cs)
		{
			m_cf = 0;
=======
		if (m_cs && m_cf)
		{
			m_cf = false;
			m_cf_cb(0);
>>>>>>> upstream/master
		}
	}
}

<<<<<<< HEAD
/*-------------------------------------------------
    y_add
-------------------------------------------------*/

void upd4701_device::y_add( INT16 data )
=======
//-------------------------------------------------
//  y_add - count Y-axis input
//-------------------------------------------------

void upd4701_device::y_add(s16 data)
>>>>>>> upstream/master
{
	if (!m_resety && data != 0)
	{
		m_y += data;

<<<<<<< HEAD
		if (m_cs)
		{
			m_cf = 0;
=======
		if (m_cs && m_cf)
		{
			m_cf = false;
			m_cf_cb(0);
>>>>>>> upstream/master
		}
	}
}

<<<<<<< HEAD
/*-------------------------------------------------
    switches_set
-------------------------------------------------*/

void upd4701_device::switches_set( UINT8 data )
{
	m_switches = data;
}

/*-------------------------------------------------
    d_r
-------------------------------------------------*/

READ16_MEMBER( upd4701_device::d_r )
{
	int data;

	if (m_cs)
	{
		return 0xff;
	}

	if (m_xy)
	{
		data = m_latchy;
	}
	else
	{
		data = m_latchx;
	}

	data |= m_latchswitches << 12;

	if (m_ul)
	{
		return data >> 8;
	}
	else
	{
		return data & 0xff;
	}
}

/*-------------------------------------------------
    sf_r
-------------------------------------------------*/

READ_LINE_MEMBER( upd4701_device::sf_r )
{
	if ((m_switches & MASK_SWITCHES) != MASK_SWITCHES)
	{
		return 0;
	}
=======
//-------------------------------------------------
//  switch_update - update one of three switches
//-------------------------------------------------

void upd4701_device::switch_update(u8 mask, bool state)
{
	if (!state && (m_switches & mask) == 0)
	{
		// active low
		m_switches |= mask;

		// update SF output if other switches were not active
		if ((m_switches & ~mask) == 0)
			m_sf_cb(0);
	}
	else if (state && (m_switches & mask) == mask)
	{
		// inactive high
		m_switches &= ~mask;

		// update SF output if other switches are also inactive
		if ((m_switches & ~mask) == 0)
			m_sf_cb(1);
	}
}

//-------------------------------------------------
//  left_w - update left switch state
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::left_w)
{
	switch_update(4, state);
}

//-------------------------------------------------
//  right_w - update right switch state
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::right_w)
{
	switch_update(2, state);
}

//-------------------------------------------------
//  middle_w - update middle switch state
//-------------------------------------------------

WRITE_LINE_MEMBER(upd4701_device::middle_w)
{
	switch_update(1, state);
}

//-------------------------------------------------
//  d_r - read data lines directly
//-------------------------------------------------

READ8_MEMBER(upd4701_device::d_r)
{
	if (m_cs)
	{
		logerror("Read while CS inactive\n");
		return space.unmap();
	}

	u16 data = m_xy ? m_latchy : m_latchx;
	data |= m_latchswitches << 12;

	if (m_ul)
		return data >> 8;
	else
		return data & 0xff;
}

//-------------------------------------------------
//  read_x - read X axis through data/address bus
//-------------------------------------------------

READ8_MEMBER(upd4701_device::read_x)
{
	return read_xy(space, (offset & 1) | 0);
}

//-------------------------------------------------
//  read_y - read Y axis through data/address bus
//-------------------------------------------------

READ8_MEMBER(upd4701_device::read_y)
{
	return read_xy(space, (offset & 1) | 2);
}

//-------------------------------------------------
//  read_xy - read either axis through bus
//-------------------------------------------------

READ8_MEMBER(upd4701_device::read_xy)
{
	cs_w(0);
	xy_w(BIT(offset, 1));
	ul_w(BIT(offset, 0));
	u8 result = d_r(space, 0);
	cs_w(1);
	return result;
}

//-------------------------------------------------
//  sf_r - read switch flag
//-------------------------------------------------

READ_LINE_MEMBER(upd4701_device::sf_r)
{
	if (m_switches != 0)
		return 0;
>>>>>>> upstream/master

	return 1;
}

<<<<<<< HEAD
/*-------------------------------------------------
    cf_r
-------------------------------------------------*/

READ_LINE_MEMBER( upd4701_device::cf_r )
=======
//-------------------------------------------------
//  cf_r - read counter flag
//-------------------------------------------------

READ_LINE_MEMBER(upd4701_device::cf_r)
>>>>>>> upstream/master
{
	return m_cf;
}
