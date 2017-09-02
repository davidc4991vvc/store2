// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Miodrag Milanovic
/****************************************************************************

    printer.c

    Code for handling printer devices

****************************************************************************/

#include "emu.h"
#include "printer.h"


// device type definition
<<<<<<< HEAD
const device_type PRINTER = &device_creator<printer_image_device>;
=======
DEFINE_DEVICE_TYPE(PRINTER, printer_image_device, "printer_image", "Printer")
>>>>>>> upstream/master

//-------------------------------------------------
//  printer_image_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
printer_image_device::printer_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PRINTER, "Printer", tag, owner, clock, "printer_image", __FILE__),
=======
printer_image_device::printer_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, PRINTER, tag, owner, clock),
>>>>>>> upstream/master
	device_image_interface(mconfig, *this),
	m_online_cb(*this)
{
}

<<<<<<< HEAD
//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void printer_image_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}

=======
>>>>>>> upstream/master

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void printer_image_device::device_start()
{
	m_online_cb.resolve();
}

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

/*-------------------------------------------------
    printer_is_ready - checks to see if a printer
    is ready
-------------------------------------------------*/

int printer_image_device::is_ready()
{
	return exists() != 0;
}



/*-------------------------------------------------
    printer_output - outputs data to a printer
-------------------------------------------------*/

<<<<<<< HEAD
void printer_image_device::output(UINT8 data)
=======
void printer_image_device::output(uint8_t data)
>>>>>>> upstream/master
{
	if (exists())
	{
		fwrite(&data, 1);
	}
}

/*-------------------------------------------------
    DEVICE_IMAGE_CREATE( printer )
-------------------------------------------------*/

<<<<<<< HEAD
bool printer_image_device::call_create(int format_type, option_resolution *format_options)
=======
image_init_result printer_image_device::call_create(int format_type, util::option_resolution *format_options)
>>>>>>> upstream/master
{
	return call_load();
}

/*-------------------------------------------------
    DEVICE_IMAGE_LOAD( printer )
-------------------------------------------------*/
<<<<<<< HEAD
bool printer_image_device::call_load()
{
	/* send notify that the printer is now online */
	if (!m_online_cb.isnull())
		m_online_cb(TRUE);

	/* we don't need to do anything special */
	return IMAGE_INIT_PASS;
=======
image_init_result printer_image_device::call_load()
{
	/* send notify that the printer is now online */
	if (!m_online_cb.isnull())
		m_online_cb(true);

	/* we don't need to do anything special */
	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    DEVICE_IMAGE_UNLOAD( printer )
-------------------------------------------------*/
void printer_image_device::call_unload()
{
	/* send notify that the printer is now offline */
	if (!m_online_cb.isnull())
<<<<<<< HEAD
		m_online_cb(FALSE);
=======
		m_online_cb(false);
>>>>>>> upstream/master
}
