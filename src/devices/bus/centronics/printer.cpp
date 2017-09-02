// license:BSD-3-Clause
// copyright-holders:smf
#include "emu.h"
#include "printer.h"

//**************************************************************************
//  CENTRONICS PRINTER DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type CENTRONICS_PRINTER = &device_creator<centronics_printer_device>;


static MACHINE_CONFIG_FRAGMENT( centronics_printer )
	MCFG_DEVICE_ADD("printer", PRINTER, 0)
	MCFG_PRINTER_ONLINE_CB(WRITELINE(centronics_printer_device, printer_online))
MACHINE_CONFIG_END
=======
DEFINE_DEVICE_TYPE(CENTRONICS_PRINTER, centronics_printer_device, "centronics_printer", "Centronics Printer")
>>>>>>> upstream/master


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/
//-------------------------------------------------
//  centronics_printer_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
centronics_printer_device::centronics_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CENTRONICS_PRINTER, "Centronics Printer", tag, owner, clock, "centronics_printer", __FILE__),
=======
centronics_printer_device::centronics_printer_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CENTRONICS_PRINTER, tag, owner, clock),
>>>>>>> upstream/master
	device_centronics_peripheral_interface( mconfig, *this ),
	m_strobe(0),
	m_data(0),
	m_busy(0),
	m_printer(*this, "printer")
{
}
//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor centronics_printer_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( centronics_printer );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------


MACHINE_CONFIG_MEMBER( centronics_printer_device::device_add_mconfig )
	MCFG_DEVICE_ADD("printer", PRINTER, 0)
	MCFG_PRINTER_ONLINE_CB(WRITELINE(centronics_printer_device, printer_online))
MACHINE_CONFIG_END
>>>>>>> upstream/master

/*-------------------------------------------------
    printer_online - callback that
    sets us busy when the printer goes offline
-------------------------------------------------*/

WRITE_LINE_MEMBER(centronics_printer_device::printer_online)
{
	output_perror(!state);
}

void centronics_printer_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch (id)
	{
	case TIMER_ACK:
		output_ack(param);

<<<<<<< HEAD
		if (param == FALSE)
=======
		if (param == false)
>>>>>>> upstream/master
		{
			/* data is now ready, output it */
			m_printer->output(m_data);

			/* ready to receive more data, return BUSY to low */
<<<<<<< HEAD
			timer_set(attotime::from_usec(7), TIMER_BUSY, FALSE);
=======
			m_busy_timer->adjust(attotime::from_usec(7), false);
>>>>>>> upstream/master
		}
		break;

	case TIMER_BUSY:
		m_busy = param;
		output_busy(m_busy);

<<<<<<< HEAD
		if (param == TRUE)
		{
			/* timer to turn ACK low to receive data */
			timer_set(attotime::from_usec(10), TIMER_ACK, FALSE);
=======
		if (param == true)
		{
			/* timer to turn ACK low to receive data */
			m_ack_timer->adjust(attotime::from_usec(10), false);
>>>>>>> upstream/master
		}
		else
		{
			/* timer to return ACK to high state */
<<<<<<< HEAD
			timer_set(attotime::from_usec(5), TIMER_ACK, TRUE);
=======
			m_ack_timer->adjust(attotime::from_usec(5), true);
>>>>>>> upstream/master
		}
	}
}

void centronics_printer_device::device_start()
{
<<<<<<< HEAD
=======
	m_ack_timer = timer_alloc(TIMER_ACK);
	m_busy_timer = timer_alloc(TIMER_BUSY);

>>>>>>> upstream/master
	/* register for state saving */
	save_item(NAME(m_strobe));
	save_item(NAME(m_data));
	save_item(NAME(m_busy));
}

void centronics_printer_device::device_reset()
{
<<<<<<< HEAD
	m_busy = FALSE;
=======
	m_busy = false;
>>>>>>> upstream/master
	output_busy(m_busy);
	output_fault(1);
	output_ack(1);
	output_select(1);
}

/*-------------------------------------------------
    centronics_strobe_w - signal that data is
    ready
-------------------------------------------------*/

WRITE_LINE_MEMBER( centronics_printer_device::input_strobe )
{
	/* look for a high -> low transition */
<<<<<<< HEAD
	if (m_strobe == TRUE && state == FALSE && m_busy == FALSE)
	{
		/* STROBE has gone low, data is ready */
		timer_set(attotime::zero, TIMER_BUSY, TRUE);
=======
	if (m_strobe == true && state == false && m_busy == false)
	{
		/* STROBE has gone low, data is ready */
		m_busy_timer->adjust(attotime::zero, true);
>>>>>>> upstream/master
	}

	m_strobe = state;
}


/*-------------------------------------------------
    centronics_prime_w - initialize and reset
    printer (centronics mode)
-------------------------------------------------*/

WRITE_LINE_MEMBER(centronics_printer_device::input_init)
{
	/* reset printer if line is low */
<<<<<<< HEAD
	if (state == FALSE)
=======
	if (state == false)
>>>>>>> upstream/master
		device_reset();
}
