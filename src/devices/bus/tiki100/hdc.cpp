// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    TIKI-100 Winchester controller card emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "hdc.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define WD1010_TAG  "hdc"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type TIKI100_HDC = &device_creator<tiki100_hdc_t>;


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( tiki100_hdc )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( tiki100_hdc )
=======
DEFINE_DEVICE_TYPE(TIKI100_HDC, tiki100_hdc_device, "tiki100_hdc", "TIKI-100 Winchester controller")


//-------------------------------------------------
//  MACHINE_CONFIG_START( tiki100_hdc )
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( tiki100_hdc_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_DEVICE_ADD(WD1010_TAG, WD2010, 5000000)
	//MCFG_WD2010_OUT_INTRQ_CB()
	MCFG_WD2010_IN_DRDY_CB(VCC)
	MCFG_WD2010_IN_INDEX_CB(VCC)
	MCFG_WD2010_IN_WF_CB(VCC)
	MCFG_WD2010_IN_TK000_CB(VCC)
	MCFG_WD2010_IN_SC_CB(VCC)

	MCFG_HARDDISK_ADD("hard0")
	MCFG_HARDDISK_ADD("hard1")
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor tiki100_hdc_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( tiki100_hdc );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  tiki100_hdc_t - constructor
//-------------------------------------------------

tiki100_hdc_t::tiki100_hdc_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, TIKI100_HDC, "TIKI-100 Winchester controller", tag, owner, clock, "tiki100_hdc", __FILE__),
=======
//  tiki100_hdc_device - constructor
//-------------------------------------------------

tiki100_hdc_device::tiki100_hdc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, TIKI100_HDC, tag, owner, clock),
>>>>>>> upstream/master
	device_tiki100bus_card_interface(mconfig, *this),
	m_hdc(*this, WD1010_TAG)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_hdc_t::device_start()
=======
void tiki100_hdc_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_hdc_t::device_reset()
=======
void tiki100_hdc_device::device_reset()
>>>>>>> upstream/master
{
	m_hdc->reset();
}


//-------------------------------------------------
//  tiki100bus_iorq_r - I/O read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 tiki100_hdc_t::iorq_r(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t tiki100_hdc_device::iorq_r(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if ((offset & 0xf8) == 0x20)
	{
		data = m_hdc->read(space, offset & 0x07);
	}

	return data;
}


//-------------------------------------------------
//  tiki100bus_iorq_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
void tiki100_hdc_t::iorq_w(address_space &space, offs_t offset, UINT8 data)
=======
void tiki100_hdc_device::iorq_w(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if ((offset & 0xf8) == 0x20)
	{
		m_hdc->write(space, offset, data);
	}
}
