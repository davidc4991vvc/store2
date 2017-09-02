// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Miodrag Milanovic
/*********************************************************************

    bitbngr.c

*********************************************************************/

#include "emu.h"
#include "bitbngr.h"



/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

<<<<<<< HEAD
const device_type BITBANGER = &device_creator<bitbanger_device>;
=======
DEFINE_DEVICE_TYPE(BITBANGER, bitbanger_device, "bitbanger", "Bitbanger")
>>>>>>> upstream/master

/*-------------------------------------------------
    ctor
-------------------------------------------------*/

<<<<<<< HEAD
bitbanger_device::bitbanger_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, BITBANGER, "Bitbanger", tag, owner, clock, "bitbanger", __FILE__),
	device_image_interface(mconfig, *this)
=======
bitbanger_device::bitbanger_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, BITBANGER, tag, owner, clock),
	device_image_interface(mconfig, *this),
	m_interface(nullptr),
	m_is_readonly(false)
>>>>>>> upstream/master
{
}



/*-------------------------------------------------
    native_output - outputs data to a file
-------------------------------------------------*/

<<<<<<< HEAD
void bitbanger_device::output(UINT8 data)
=======
void bitbanger_device::output(uint8_t data)
>>>>>>> upstream/master
{
	if (exists())
	{
		fwrite(&data, 1);
	}
}


/*-------------------------------------------------
    native_input - inputs data from a file
-------------------------------------------------*/

<<<<<<< HEAD
UINT32 bitbanger_device::input(void *buffer, UINT32 length)
=======
uint32_t bitbanger_device::input(void *buffer, uint32_t length)
>>>>>>> upstream/master
{
	if (exists())
	{
		return fread(buffer, length);
	}
	return 0;
}



/*-------------------------------------------------
    device_start
-------------------------------------------------*/

void bitbanger_device::device_start(void)
{
}



/*-------------------------------------------------
<<<<<<< HEAD
    device_config_complete
-------------------------------------------------*/

void bitbanger_device::device_config_complete(void)
{
	update_names(BITBANGER, "bitbngr", "bitb");
}



/*-------------------------------------------------
    call_load
-------------------------------------------------*/

bool bitbanger_device::call_load(void)
{
	/* we don't need to do anything special */
	return IMAGE_INIT_PASS;
}

bool bitbanger_device::call_create(int format_type, option_resolution *format_options)
{
	/* we don't need to do anything special */
	return IMAGE_INIT_PASS;
=======
    call_load
-------------------------------------------------*/

image_init_result bitbanger_device::call_load(void)
{
	/* we don't need to do anything special */
	return image_init_result::PASS;
}

image_init_result bitbanger_device::call_create(int format_type, util::option_resolution *format_options)
{
	/* we don't need to do anything special */
	return image_init_result::PASS;
>>>>>>> upstream/master
}

/*-------------------------------------------------
    call_unload
-------------------------------------------------*/

void bitbanger_device::call_unload(void)
{
}
