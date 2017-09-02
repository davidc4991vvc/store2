// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

    K200 64K RAM expansion
    K202 192K RAM expansion
    K208 448K RAM expansion

***************************************************************************/

#include "emu.h"
#include "ram.h"


/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type DMV_K200 = &device_creator<dmv_k200_device>;
const device_type DMV_K202 = &device_creator<dmv_k202_device>;
const device_type DMV_K208 = &device_creator<dmv_k208_device>;
=======
DEFINE_DEVICE_TYPE(DMV_K200, dmv_k200_device, "dmv_k200", "K200 64K RAM expansion")
DEFINE_DEVICE_TYPE(DMV_K202, dmv_k202_device, "dmv_k202", "K202 192K RAM expansion")
DEFINE_DEVICE_TYPE(DMV_K208, dmv_k208_device, "dmv_k208", "K208 448K RAM expansion")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  dmv_ram_device - constructor
//-------------------------------------------------

dmv_ram_device::dmv_ram_device(const machine_config &mconfig, device_type type, UINT32 size, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source)
		: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_dmvslot_interface( mconfig, *this ), m_ram(nullptr),
		m_size(size)
=======
//  dmv_ram_device_base - constructor
//-------------------------------------------------

dmv_ram_device_base::dmv_ram_device_base(const machine_config &mconfig, device_type type, uint32_t size, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, device_dmvslot_interface(mconfig, *this)
	, m_ram(nullptr)
	, m_size(size)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  dmv_k200_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
dmv_k200_device::dmv_k200_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: dmv_ram_device(mconfig, DMV_K200, 1, "K200 64K RAM expansion", tag, owner, clock, "dmv_k200", __FILE__)
=======
dmv_k200_device::dmv_k200_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: dmv_ram_device_base(mconfig, DMV_K200, 1, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  dmv_k202_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
dmv_k202_device::dmv_k202_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: dmv_ram_device(mconfig, DMV_K202, 3, "K202 192K RAM expansion", tag, owner, clock, "dmv_k202", __FILE__)
=======
dmv_k202_device::dmv_k202_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: dmv_ram_device_base(mconfig, DMV_K202, 3, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  dmv_k208_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
dmv_k208_device::dmv_k208_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: dmv_ram_device(mconfig, DMV_K208, 7 , "K208 448K RAM expansion", tag, owner, clock, "dmv_k208", __FILE__)
=======
dmv_k208_device::dmv_k208_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: dmv_ram_device_base(mconfig, DMV_K208, 7, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void dmv_ram_device::device_start()
=======
void dmv_ram_device_base::device_start()
>>>>>>> upstream/master
{
	m_ram = machine().memory().region_alloc( "expram", m_size * 0x10000, 1, ENDIANNESS_LITTLE )->base();
}

//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
void dmv_ram_device::ram_read(UINT8 cas, offs_t offset, UINT8 &data)
=======
void dmv_ram_device_base::ram_read(uint8_t cas, offs_t offset, uint8_t &data)
>>>>>>> upstream/master
{
	if (cas && cas <= m_size)
		data = m_ram[((cas - 1) << 16) | (offset & 0xffff)];
}

//-------------------------------------------------
//  write
//-------------------------------------------------

<<<<<<< HEAD
void dmv_ram_device::ram_write(UINT8 cas, offs_t offset, UINT8 data)
=======
void dmv_ram_device_base::ram_write(uint8_t cas, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (cas && cas <= m_size)
		m_ram[((cas - 1) << 16) | (offset & 0xffff)] = data;
}
