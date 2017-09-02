// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    ataintf.c

    ATA Interface implementation.

***************************************************************************/

#include "emu.h"
#include "ataintf.h"
<<<<<<< HEAD
#include "debugger.h"
#include "idehd.h"
#include "atapicdr.h"

void ata_interface_device::set_irq(int state)
{
//  printf( "%s: irq %d\n", machine().describe_context(), state );
=======

#include "atapicdr.h"
#include "idehd.h"

#include "debugger.h"


void ata_interface_device::set_irq(int state)
{
//  logerror( "%s: irq %d\n", machine().describe_context(), state );
>>>>>>> upstream/master

	m_irq_handler(state);
}

void ata_interface_device::set_dmarq(int state)
{
<<<<<<< HEAD
//  printf( "%s: dmarq %d\n", machine().describe_context(), state );
=======
//  logerror( "%s: dmarq %d\n", machine().describe_context(), state );
>>>>>>> upstream/master

	m_dmarq_handler(state);
}

void ata_interface_device::set_dasp(int state)
{
<<<<<<< HEAD
//  printf( "%s: dasp %d\n", machine().describe_context(), state );
=======
//  logerror( "%s: dasp %d\n", machine().describe_context(), state );
>>>>>>> upstream/master

	m_dasp_handler(state);
}

WRITE_LINE_MEMBER( ata_interface_device::irq0_write_line )
{
	if (m_irq[0] != state)
	{
		m_irq[0] = state;

		set_irq(m_irq[0] == ASSERT_LINE || m_irq[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::irq1_write_line )
{
	if (m_irq[1] != state)
	{
		m_irq[1] = state;

		set_irq(m_irq[0] == ASSERT_LINE || m_irq[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::dasp0_write_line )
{
	if (m_dasp[0] != state)
	{
		m_dasp[0] = state;

		set_dasp(m_dasp[0] == ASSERT_LINE || m_dasp[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::dasp1_write_line )
{
	if (m_dasp[1] != state)
	{
		m_dasp[1] = state;

<<<<<<< HEAD
		ata_device_interface *dev = m_slot[0]->dev();
		if (dev != NULL)
=======
		device_ata_interface *dev = m_slot[0]->dev();
		if (dev != nullptr)
>>>>>>> upstream/master
			dev->write_dasp(state);

		set_dasp(m_dasp[0] == ASSERT_LINE || m_dasp[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::dmarq0_write_line )
{
	if (m_dmarq[0] != state)
	{
		m_dmarq[0] = state;

		set_dmarq(m_dmarq[0] == ASSERT_LINE || m_dmarq[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::dmarq1_write_line )
{
	if (m_dmarq[1] != state)
	{
		m_dmarq[1] = state;

		set_dmarq(m_dmarq[0] == ASSERT_LINE || m_dmarq[1] == ASSERT_LINE);
	}
}

WRITE_LINE_MEMBER( ata_interface_device::pdiag0_write_line )
{
	m_pdiag[0] = state;
}

WRITE_LINE_MEMBER( ata_interface_device::pdiag1_write_line )
{
	if (m_pdiag[1] != state)
	{
		m_pdiag[1] = state;

<<<<<<< HEAD
		ata_device_interface *dev = m_slot[0]->dev();
		if (dev != NULL)
=======
		device_ata_interface *dev = m_slot[0]->dev();
		if (dev != nullptr)
>>>>>>> upstream/master
			dev->write_pdiag(state);
	}
}

/*************************************
 *
 *  ATA interface read
 *
 *************************************/

<<<<<<< HEAD
UINT16 ata_interface_device::read_dma()
{
	UINT16 result = 0xffff;
	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			result &= m_slot[i]->dev()->read_dma();

//  printf( "%s: read_dma %04x\n", machine().describe_context(), result );
=======
uint16_t ata_interface_device::read_dma()
{
	uint16_t result = 0xffff;
	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			result &= elem->dev()->read_dma();

//  logerror( "%s: read_dma %04x\n", machine().describe_context(), result );
>>>>>>> upstream/master
	return result;
}

READ16_MEMBER( ata_interface_device::read_cs0 )
{
<<<<<<< HEAD
	UINT16 result = mem_mask;
	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			result &= m_slot[i]->dev()->read_cs0(space, offset, mem_mask);

//  { static int last_status = -1; if (offset == 7 ) { if( result == last_status ) return last_status; last_status = result; } else last_status = -1; }

//  printf( "%s: read cs0 %04x %04x %04x\n", machine().describe_context(), offset, result, mem_mask );
=======
	uint16_t result = mem_mask;
	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			result &= elem->dev()->read_cs0(space, offset, mem_mask);

//  { static int last_status = -1; if (offset == 7 ) { if( result == last_status ) return last_status; last_status = result; } else last_status = -1; }

//  logerror( "%s: read cs0 %04x %04x %04x\n", machine().describe_context(), offset, result, mem_mask );
>>>>>>> upstream/master

	return result;
}

READ16_MEMBER( ata_interface_device::read_cs1 )
{
<<<<<<< HEAD
	UINT16 result = mem_mask;
	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			result &= m_slot[i]->dev()->read_cs1(space, offset, mem_mask);

//  printf( "%s: read cs1 %04x %04x %04x\n", machine().describe_context(), offset, result, mem_mask );
=======
	uint16_t result = mem_mask;
	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			result &= elem->dev()->read_cs1(space, offset, mem_mask);

//  logerror( "%s: read cs1 %04x %04x %04x\n", machine().describe_context(), offset, result, mem_mask );
>>>>>>> upstream/master

	return result;
}


/*************************************
 *
 *  ATA interface write
 *
 *************************************/

<<<<<<< HEAD
void ata_interface_device::write_dma( UINT16 data )
{
//  printf( "%s: write_dma %04x\n", machine().describe_context(), data );

	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			m_slot[i]->dev()->write_dma(data);
=======
void ata_interface_device::write_dma( uint16_t data )
{
//  logerror( "%s: write_dma %04x\n", machine().describe_context(), data );

	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			elem->dev()->write_dma(data);
>>>>>>> upstream/master
}

WRITE16_MEMBER( ata_interface_device::write_cs0 )
{
<<<<<<< HEAD
//  printf( "%s: write cs0 %04x %04x %04x\n", machine().describe_context(), offset, data, mem_mask );

	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			m_slot[i]->dev()->write_cs0(space, offset, data, mem_mask);
=======
//  logerror( "%s: write cs0 %04x %04x %04x\n", machine().describe_context(), offset, data, mem_mask );

	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			elem->dev()->write_cs0(space, offset, data, mem_mask);
>>>>>>> upstream/master
}

WRITE16_MEMBER( ata_interface_device::write_cs1 )
{
<<<<<<< HEAD
//  printf( "%s: write cs1 %04x %04x %04x\n", machine().describe_context(), offset, data, mem_mask );

	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			m_slot[i]->dev()->write_cs1(space, offset, data, mem_mask);
=======
//  logerror( "%s: write cs1 %04x %04x %04x\n", machine().describe_context(), offset, data, mem_mask );

	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			elem->dev()->write_cs1(space, offset, data, mem_mask);
>>>>>>> upstream/master
}

WRITE_LINE_MEMBER( ata_interface_device::write_dmack )
{
<<<<<<< HEAD
//  printf( "%s: write_dmack %04x\n", machine().describe_context(), state );

	for (int i = 0; i < 2; i++)
		if (m_slot[i]->dev() != NULL)
			m_slot[i]->dev()->write_dmack(state);
=======
//  logerror( "%s: write_dmack %04x\n", machine().describe_context(), state );

	for (auto & elem : m_slot)
		if (elem->dev() != nullptr)
			elem->dev()->write_dmack(state);
>>>>>>> upstream/master
}

SLOT_INTERFACE_START(ata_devices)
	SLOT_INTERFACE("hdd", IDE_HARDDISK)
	SLOT_INTERFACE("cdrom", ATAPI_CDROM)
SLOT_INTERFACE_END

<<<<<<< HEAD
ata_interface_device::ata_interface_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
=======
ata_interface_device::ata_interface_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
	m_irq_handler(*this),
	m_dmarq_handler(*this),
	m_dasp_handler(*this){
}


<<<<<<< HEAD
const device_type ATA_INTERFACE = &device_creator<ata_interface_device>;

ata_interface_device::ata_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, ATA_INTERFACE, "ATA Interface", tag, owner, clock, "ata_interface", __FILE__),
	m_irq_handler(*this),
	m_dmarq_handler(*this),
	m_dasp_handler(*this)
=======
DEFINE_DEVICE_TYPE(ATA_INTERFACE, ata_interface_device, "ata_interface", "ATA Interface")

ata_interface_device::ata_interface_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	ata_interface_device(mconfig, ATA_INTERFACE, tag, owner, clock)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ata_interface_device::device_start()
{
	m_irq_handler.resolve_safe();
	m_dmarq_handler.resolve_safe();
	m_dasp_handler.resolve_safe();

	/* set MAME harddisk handle */
	m_slot[0] = subdevice<ata_slot_device>("0");
	m_slot[1] = subdevice<ata_slot_device>("1");

	for (int i = 0; i < 2; i++)
	{
		m_irq[i] = 0;
		m_dmarq[i] = 0;
		m_dasp[i] = 0;
		m_pdiag[i] = 0;

<<<<<<< HEAD
		ata_device_interface *dev = m_slot[i]->dev();
		if (dev != NULL)
=======
		device_ata_interface *dev = m_slot[i]->dev();
		if (dev != nullptr)
>>>>>>> upstream/master
		{
			if (i == 0)
			{
				dev->m_irq_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, irq0_write_line));
				dev->m_dmarq_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, dmarq0_write_line));
				dev->m_dasp_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, dasp0_write_line));
				dev->m_pdiag_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, pdiag0_write_line));
			}
			else
			{
				dev->m_irq_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, irq1_write_line));
				dev->m_dmarq_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, dmarq1_write_line));
				dev->m_dasp_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, dasp1_write_line));
				dev->m_pdiag_handler.set_callback(DEVCB_DEVWRITELINE("^", ata_interface_device, pdiag1_write_line));
			}

			dev->write_csel(i);
		}
	}
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( ata_interface )
	MCFG_DEVICE_ADD( "0", ATA_SLOT, 0 )
	MCFG_DEVICE_ADD( "1", ATA_SLOT, 0 )
MACHINE_CONFIG_END

//-------------------------------------------------
//  machine_config_additions - return a pointer to
//  the device's machine fragment
//-------------------------------------------------

machine_config_constructor ata_interface_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( ata_interface );
}
=======

//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( ata_interface_device::device_add_mconfig )
	MCFG_DEVICE_ADD( "0", ATA_SLOT, 0 )
	MCFG_DEVICE_ADD( "1", ATA_SLOT, 0 )
MACHINE_CONFIG_END
>>>>>>> upstream/master


//**************************************************************************
//  ATA SLOT DEVICE
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type ATA_SLOT = &device_creator<ata_slot_device>;
=======
DEFINE_DEVICE_TYPE(ATA_SLOT, ata_slot_device, "ata_slot", "ATA Connector")
>>>>>>> upstream/master

//-------------------------------------------------
//  ata_slot_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
ata_slot_device::ata_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, ATA_SLOT, "ATA Connector", tag, owner, clock, "ata_slot", __FILE__),
		device_slot_interface(mconfig, *this),
		m_dev(NULL)
=======
ata_slot_device::ata_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, ATA_SLOT, tag, owner, clock),
		device_slot_interface(mconfig, *this),
		m_dev(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void ata_slot_device::device_config_complete()
{
<<<<<<< HEAD
	m_dev = dynamic_cast<ata_device_interface *>(get_card_device());
=======
	m_dev = dynamic_cast<device_ata_interface *>(get_card_device());
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void ata_slot_device::device_start()
{
}
