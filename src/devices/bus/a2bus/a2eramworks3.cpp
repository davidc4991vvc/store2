// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2eramworks3.c

    Applied Engineering RamWorks III


*********************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "includes/apple2.h"
=======
>>>>>>> upstream/master
#include "a2eramworks3.h"


/***************************************************************************
    PARAMETERS
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type A2EAUX_RAMWORKS3 = &device_creator<a2eaux_ramworks3_device>;
=======
DEFINE_DEVICE_TYPE(A2EAUX_RAMWORKS3, a2eaux_ramworks3_device, "a2erwks3", "Applied Engineering RamWorks III")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
a2eaux_ramworks3_device::a2eaux_ramworks3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, A2EAUX_RAMWORKS3, "Applied Engineering RamWorks III", tag, owner, clock, "a2erwks3", __FILE__),
		device_a2eauxslot_card_interface(mconfig, *this),
	m_bank(0)
{
}

a2eaux_ramworks3_device::a2eaux_ramworks3_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
		device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_a2eauxslot_card_interface(mconfig, *this), m_bank(0)
=======
a2eaux_ramworks3_device::a2eaux_ramworks3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
		a2eaux_ramworks3_device(mconfig, A2EAUX_RAMWORKS3, tag, owner, clock)
{
}

a2eaux_ramworks3_device::a2eaux_ramworks3_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
		device_t(mconfig, type, tag, owner, clock),
		device_a2eauxslot_card_interface(mconfig, *this),
		m_bank(0)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void a2eaux_ramworks3_device::device_start()
{
	set_a2eauxslot_device();
	save_item(NAME(m_ram));
	save_item(NAME(m_bank));
}

void a2eaux_ramworks3_device::device_reset()
{
	m_bank = 0;
}

<<<<<<< HEAD
UINT8 a2eaux_ramworks3_device::read_auxram(UINT16 offset)
=======
uint8_t a2eaux_ramworks3_device::read_auxram(uint16_t offset)
>>>>>>> upstream/master
{
	return m_ram[offset+m_bank];
}

<<<<<<< HEAD
void a2eaux_ramworks3_device::write_auxram(UINT16 offset, UINT8 data)
=======
void a2eaux_ramworks3_device::write_auxram(uint16_t offset, uint8_t data)
>>>>>>> upstream/master
{
	m_ram[offset+m_bank] = data;
}

<<<<<<< HEAD
UINT8 *a2eaux_ramworks3_device::get_vram_ptr()
=======
uint8_t *a2eaux_ramworks3_device::get_vram_ptr()
>>>>>>> upstream/master
{
	return &m_ram[0];
}

<<<<<<< HEAD
UINT8 *a2eaux_ramworks3_device::get_auxbank_ptr()
=======
uint8_t *a2eaux_ramworks3_device::get_auxbank_ptr()
>>>>>>> upstream/master
{
	return &m_ram[m_bank];
}

/*
    These cards are split into 64k logical banks.

    On a RW3:
    Banks 00-0F is the first MB
    Banks 10-17 are the next 512K
    Banks 30-37 are the next 512K
    Banks 50-57 are the next 512K
    Banks 70-77 are the next 512K

    However, the software will recognize and correctly use a configuration in which
    all of banks 00-7F are populated for a total of 8 megabytes.  So that's what we do.
*/
<<<<<<< HEAD
void a2eaux_ramworks3_device::write_c07x(address_space &space, UINT8 offset, UINT8 data)
=======
void a2eaux_ramworks3_device::write_c07x(address_space &space, uint8_t offset, uint8_t data)
>>>>>>> upstream/master
{
	// write to C073?
	if (offset == 3)
	{
		m_bank = 0x10000 * (data & 0x7f);
	}
}
