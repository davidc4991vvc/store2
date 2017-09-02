// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m6504.c

    Mostek 6502, NMOS variant with reduced address bus

***************************************************************************/

#include "emu.h"
#include "m6504.h"

<<<<<<< HEAD
const device_type M6504 = &device_creator<m6504_device>;

m6504_device::m6504_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	m6502_device(mconfig, M6504, "M6504", tag, owner, clock, "m6504", __FILE__)
=======
DEFINE_DEVICE_TYPE(M6504, m6504_device, "m6504", "M6504")

m6504_device::m6504_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	m6502_device(mconfig, M6504, tag, owner, clock)
>>>>>>> upstream/master
{
	program_config.m_addrbus_width = 13;
	sprogram_config.m_addrbus_width = 13;
}

void m6504_device::device_start()
{
	if(direct_disabled)
		mintf = new mi_6504_nd;
	else
		mintf = new mi_6504_normal;

	init();
}

<<<<<<< HEAD
UINT8 m6504_device::mi_6504_normal::read(UINT16 adr)
=======
uint8_t m6504_device::mi_6504_normal::read(uint16_t adr)
>>>>>>> upstream/master
{
	return program->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6504_device::mi_6504_normal::read_sync(UINT16 adr)
=======
uint8_t m6504_device::mi_6504_normal::read_sync(uint16_t adr)
>>>>>>> upstream/master
{
	return sdirect->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6504_device::mi_6504_normal::read_arg(UINT16 adr)
=======
uint8_t m6504_device::mi_6504_normal::read_arg(uint16_t adr)
>>>>>>> upstream/master
{
	return direct->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
void m6504_device::mi_6504_normal::write(UINT16 adr, UINT8 val)
=======
void m6504_device::mi_6504_normal::write(uint16_t adr, uint8_t val)
>>>>>>> upstream/master
{
	program->write_byte(adr & 0x1fff, val);
}

<<<<<<< HEAD
UINT8 m6504_device::mi_6504_nd::read_sync(UINT16 adr)
=======
uint8_t m6504_device::mi_6504_nd::read_sync(uint16_t adr)
>>>>>>> upstream/master
{
	return sprogram->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6504_device::mi_6504_nd::read_arg(UINT16 adr)
=======
uint8_t m6504_device::mi_6504_nd::read_arg(uint16_t adr)
>>>>>>> upstream/master
{
	return program->read_byte(adr & 0x1fff);
}
