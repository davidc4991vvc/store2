// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m6507.c

    Mostek 6502, NMOS variant with reduced address bus

***************************************************************************/

#include "emu.h"
#include "m6507.h"

<<<<<<< HEAD
const device_type M6507 = &device_creator<m6507_device>;

m6507_device::m6507_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	m6502_device(mconfig, M6507, "M6507", tag, owner, clock, "m6507", __FILE__)
=======
DEFINE_DEVICE_TYPE(M6507, m6507_device, "m6507", "M6507")

m6507_device::m6507_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	m6502_device(mconfig, M6507, tag, owner, clock)
>>>>>>> upstream/master
{
	program_config.m_addrbus_width = 13;
	sprogram_config.m_addrbus_width = 13;
}

void m6507_device::device_start()
{
	if(direct_disabled)
		mintf = new mi_6507_nd;
	else
		mintf = new mi_6507_normal;

	init();
}

<<<<<<< HEAD
UINT8 m6507_device::mi_6507_normal::read(UINT16 adr)
=======
uint8_t m6507_device::mi_6507_normal::read(uint16_t adr)
>>>>>>> upstream/master
{
	return program->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6507_device::mi_6507_normal::read_sync(UINT16 adr)
=======
uint8_t m6507_device::mi_6507_normal::read_sync(uint16_t adr)
>>>>>>> upstream/master
{
	return sdirect->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6507_device::mi_6507_normal::read_arg(UINT16 adr)
=======
uint8_t m6507_device::mi_6507_normal::read_arg(uint16_t adr)
>>>>>>> upstream/master
{
	return direct->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
void m6507_device::mi_6507_normal::write(UINT16 adr, UINT8 val)
=======
void m6507_device::mi_6507_normal::write(uint16_t adr, uint8_t val)
>>>>>>> upstream/master
{
	program->write_byte(adr & 0x1fff, val);
}

<<<<<<< HEAD
UINT8 m6507_device::mi_6507_nd::read_sync(UINT16 adr)
=======
uint8_t m6507_device::mi_6507_nd::read_sync(uint16_t adr)
>>>>>>> upstream/master
{
	return sprogram->read_byte(adr & 0x1fff);
}

<<<<<<< HEAD
UINT8 m6507_device::mi_6507_nd::read_arg(UINT16 adr)
=======
uint8_t m6507_device::mi_6507_nd::read_arg(uint16_t adr)
>>>>>>> upstream/master
{
	return program->read_byte(adr & 0x1fff);
}
