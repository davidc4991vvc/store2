// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Simple Sound Board VP595 emulation

**********************************************************************/

<<<<<<< HEAD
#include "vp595.h"

=======
#include "emu.h"
#include "vp595.h"

#include "speaker.h"

>>>>>>> upstream/master


//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define CDP1863_TAG     "u1"
#define CDP1863_XTAL    440560



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type VP595 = &device_creator<vp595_device>;


//-------------------------------------------------
//  MACHINE_CONFIG_FRAGMENT( vp595 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( vp595 )
=======
DEFINE_DEVICE_TYPE(VP595, vp595_device, "vp595", "VP-595 Simple Sound")


//-------------------------------------------------
//  MACHINE_CONFIG_START( vp595 )
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( vp595_device::device_add_mconfig )
>>>>>>> upstream/master
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_CDP1863_ADD(CDP1863_TAG, 0, CDP1863_XTAL)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)
MACHINE_CONFIG_END


<<<<<<< HEAD
//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor vp595_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( vp595 );
}


=======
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  vp595_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
vp595_device::vp595_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, VP595, "VP595", tag, owner, clock, "vp595", __FILE__),
=======
vp595_device::vp595_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, VP595, tag, owner, clock),
>>>>>>> upstream/master
	device_vip_expansion_card_interface(mconfig, *this),
	m_pfg(*this, CDP1863_TAG)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void vp595_device::device_start()
{
}


//-------------------------------------------------
//  vip_io_w - I/O write
//-------------------------------------------------

<<<<<<< HEAD
void vp595_device::vip_io_w(address_space &space, offs_t offset, UINT8 data)
=======
void vp595_device::vip_io_w(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (offset == 0x03)
	{
		if (!data) data = 0x80;

		m_pfg->str_w(data);
	}
}


//-------------------------------------------------
//  vip_q_w - Q write
//-------------------------------------------------

void vp595_device::vip_q_w(int state)
{
	m_pfg->oe_w(state);
}
