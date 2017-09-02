// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2estd80col.c

    Apple IIe Standard 80 Column Card (2K of RAM, no double-hi-res)

*********************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "includes/apple2.h"
=======
>>>>>>> upstream/master
#include "a2estd80col.h"


/***************************************************************************
    PARAMETERS
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type A2EAUX_STD80COL = &device_creator<a2eaux_std80col_device>;
=======
DEFINE_DEVICE_TYPE(A2EAUX_STD80COL, a2eaux_std80col_device, "a2estd80", "Apple IIe Standard 80-Column Card")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
a2eaux_std80col_device::a2eaux_std80col_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, A2EAUX_STD80COL, "Apple IIe Standard 80-Column Card", tag, owner, clock, "a2estd80", __FILE__),
		device_a2eauxslot_card_interface(mconfig, *this)
{
}

a2eaux_std80col_device::a2eaux_std80col_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
		device_t(mconfig, type, name, tag, owner, clock, shortname, source),
=======
a2eaux_std80col_device::a2eaux_std80col_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
		a2eaux_std80col_device(mconfig, A2EAUX_STD80COL, tag, owner, clock)
{
}

a2eaux_std80col_device::a2eaux_std80col_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
		device_t(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
		device_a2eauxslot_card_interface(mconfig, *this)
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void a2eaux_std80col_device::device_start()
{
	set_a2eauxslot_device();
	save_item(NAME(m_ram));
}

void a2eaux_std80col_device::device_reset()
{
}

<<<<<<< HEAD
UINT8 a2eaux_std80col_device::read_auxram(UINT16 offset)
=======
uint8_t a2eaux_std80col_device::read_auxram(uint16_t offset)
>>>>>>> upstream/master
{
	if (offset < 0x800)
	{
		return m_ram[offset];
	}

	return 0xff;
}

<<<<<<< HEAD
void a2eaux_std80col_device::write_auxram(UINT16 offset, UINT8 data)
=======
void a2eaux_std80col_device::write_auxram(uint16_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (offset < 0x800)
	{
		m_ram[offset] = data;
	}
}

<<<<<<< HEAD
UINT8 *a2eaux_std80col_device::get_vram_ptr()
=======
uint8_t *a2eaux_std80col_device::get_vram_ptr()
>>>>>>> upstream/master
{
	return &m_ram[0];
}

<<<<<<< HEAD
UINT8 *a2eaux_std80col_device::get_auxbank_ptr()
=======
uint8_t *a2eaux_std80col_device::get_auxbank_ptr()
>>>>>>> upstream/master
{
	return &m_ram[0];
}
