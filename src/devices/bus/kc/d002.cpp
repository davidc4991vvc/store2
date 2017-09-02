// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/***************************************************************************

    d002.c

    KC85 D002 Bus Driver emulation

***************************************************************************/

#include "emu.h"
#include "d002.h"

<<<<<<< HEAD
=======
#include "ram.h"
#include "rom.h"
#include "d004.h"


>>>>>>> upstream/master
/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

static INPUT_PORTS_START( kc_d002 )
	// device ID is selected using 4 jumpers on the board
	// 0x00 and 0xf0 should not be used because they are
	// reserved for base system and FDC the others
	// 14 ID are theoretically usable.
	PORT_START("ID")
	PORT_DIPNAME( 0xf0, 0x10, "Device ID" )
	PORT_DIPSETTING( 0x00, "0x00" )     // reserved for base system
	PORT_DIPSETTING( 0x10, "0x10" )
	PORT_DIPSETTING( 0x20, "0x20" )
	PORT_DIPSETTING( 0x30, "0x30" )
	PORT_DIPSETTING( 0x40, "0x40" )
	PORT_DIPSETTING( 0x50, "0x50" )
	PORT_DIPSETTING( 0x60, "0x60" )
	PORT_DIPSETTING( 0x70, "0x70" )
	PORT_DIPSETTING( 0x80, "0x80" )
	PORT_DIPSETTING( 0x90, "0x90" )
	PORT_DIPSETTING( 0xA0, "0xA0" )
	PORT_DIPSETTING( 0xB0, "0xB0" )
	PORT_DIPSETTING( 0xC0, "0xC0" )
	PORT_DIPSETTING( 0xD0, "0xD0" )
	PORT_DIPSETTING( 0xE0, "0xE0" )
	PORT_DIPSETTING( 0xF0, "0xF0" )     // reserved for FDC D004
INPUT_PORTS_END

// defined in drivers/kc.c
SLOT_INTERFACE_EXTERN(kc85_cart);
SLOT_INTERFACE_EXTERN(kc85_exp);

WRITE_LINE_MEMBER(kc_d002_device::out_irq_w)
{
	m_slot->m_out_irq_cb(state);
}

WRITE_LINE_MEMBER(kc_d002_device::out_nmi_w)
{
	m_slot->m_out_nmi_cb(state);
}

WRITE_LINE_MEMBER(kc_d002_device::out_halt_w)
{
	m_slot->m_out_halt_cb(state);
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( kc_d002 )
	MCFG_DEVICE_ADD("m0", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, NULL, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("m4")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("m4", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, NULL, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("m8")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("m8", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, NULL, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("mc")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("mc", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, NULL, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("exp")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))

	// expansion interface
	MCFG_DEVICE_ADD("exp", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_exp, NULL, false)
	MCFG_KCEXP_SLOT_NEXT_SLOT(NULL)
	MCFG_KCEXP_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCEXP_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCEXP_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
MACHINE_CONFIG_END
=======
>>>>>>> upstream/master

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type KC_D002 = &device_creator<kc_d002_device>;
=======
DEFINE_DEVICE_TYPE(KC_D002, kc_d002_device, "kc_d002", "D002 Bus Driver")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  kc_d002_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
kc_d002_device::kc_d002_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, KC_D002, "D002 Bus Driver", tag, owner, clock, "kc_d002", __FILE__),
		device_kcexp_interface( mconfig, *this ), m_slot(nullptr)
	{
=======
kc_d002_device::kc_d002_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, KC_D002, tag, owner, clock)
	, device_kcexp_interface(mconfig, *this)
	, m_slot(nullptr)
	, m_expansions(*this, { "m0", "m4", "m8", "mc", "exp" })
{
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void kc_d002_device::device_start()
{
	m_slot = dynamic_cast<kcexp_slot_device *>(owner());
<<<<<<< HEAD

	m_expansions[0] = downcast<kcexp_slot_device *>(subdevice("m0"));
	m_expansions[1] = downcast<kcexp_slot_device *>(subdevice("m4"));
	m_expansions[2] = downcast<kcexp_slot_device *>(subdevice("m8"));
	m_expansions[3] = downcast<kcexp_slot_device *>(subdevice("mc"));
	m_expansions[4] = downcast<kcexp_slot_device *>(subdevice("exp"));
=======
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void kc_d002_device::device_reset()
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  device_mconfig_additions
//-------------------------------------------------

machine_config_constructor kc_d002_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( kc_d002 );
}
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( kc_d002_device::device_add_mconfig )
	MCFG_DEVICE_ADD("m0", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, nullptr, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("m4")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("m4", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, nullptr, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("m8")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("m8", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, nullptr, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("mc")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
	MCFG_DEVICE_ADD("mc", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_cart, nullptr, false)
	MCFG_KCCART_SLOT_NEXT_SLOT("exp")
	MCFG_KCCART_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCCART_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCCART_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))

	// expansion interface
	MCFG_DEVICE_ADD("exp", KCCART_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(kc85_exp, nullptr, false)
	MCFG_KCEXP_SLOT_NEXT_SLOT(nullptr)
	MCFG_KCEXP_SLOT_OUT_IRQ_CB(WRITELINE(kc_d002_device, out_irq_w))
	MCFG_KCEXP_SLOT_OUT_NMI_CB(WRITELINE(kc_d002_device, out_nmi_w))
	MCFG_KCEXP_SLOT_OUT_HALT_CB(WRITELINE(kc_d002_device, out_halt_w))
MACHINE_CONFIG_END
>>>>>>> upstream/master

//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor kc_d002_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( kc_d002 );
}

//-------------------------------------------------
//  read
//-------------------------------------------------

<<<<<<< HEAD
void kc_d002_device::read(offs_t offset, UINT8 &data)
{
	for (int i=0; i<5; i++)
		m_expansions[i]->read(offset, data);
=======
void kc_d002_device::read(offs_t offset, uint8_t &data)
{
	for (auto & elem : m_expansions)
		elem->read(offset, data);
>>>>>>> upstream/master
}

//-------------------------------------------------
//  write
//-------------------------------------------------

<<<<<<< HEAD
void kc_d002_device::write(offs_t offset, UINT8 data)
{
	for (int i=0; i<5; i++)
		m_expansions[i]->write(offset, data);
=======
void kc_d002_device::write(offs_t offset, uint8_t data)
{
	for (auto & elem : m_expansions)
		elem->write(offset, data);
>>>>>>> upstream/master
}

//-------------------------------------------------
//  IO read
//-------------------------------------------------

<<<<<<< HEAD
void kc_d002_device::io_read(offs_t offset, UINT8 &data)
{
	if ((offset & 0xff) == 0x80)
	{
		UINT8 slot_id = (offset>>8) & 0xff;
=======
void kc_d002_device::io_read(offs_t offset, uint8_t &data)
{
	if ((offset & 0xff) == 0x80)
	{
		uint8_t slot_id = (offset>>8) & 0xff;
>>>>>>> upstream/master

		if ((slot_id & 0xf0) == ioport("ID")->read() && !(slot_id & 0x03))
			data = m_expansions[(slot_id>>2) & 3]->module_id_r();
		else
			m_expansions[4]->io_read(offset, data);
	}
	else
	{
<<<<<<< HEAD
		for (int i=0; i<5; i++)
			m_expansions[i]->io_read(offset, data);
=======
		for (auto & elem : m_expansions)
			elem->io_read(offset, data);
>>>>>>> upstream/master
	}
}

//-------------------------------------------------
//  IO write
//-------------------------------------------------

<<<<<<< HEAD
void kc_d002_device::io_write(offs_t offset, UINT8 data)
{
	if ((offset & 0xff) == 0x80)
	{
		UINT8 slot_id = (offset>>8) & 0xff;
=======
void kc_d002_device::io_write(offs_t offset, uint8_t data)
{
	if ((offset & 0xff) == 0x80)
	{
		uint8_t slot_id = (offset>>8) & 0xff;
>>>>>>> upstream/master

		if ((slot_id & 0xf0) == ioport("ID")->read() && !(slot_id & 0x03))
			m_expansions[(slot_id>>2) & 3]->control_w(data);
		else
			m_expansions[4]->io_write(offset, data);
	}
	else
	{
<<<<<<< HEAD
		for (int i=0; i<5; i++)
			m_expansions[i]->io_write(offset, data);
=======
		for (auto & elem : m_expansions)
			elem->io_write(offset, data);
>>>>>>> upstream/master
	}

}

/*-------------------------------------------------
   MEI line write
-------------------------------------------------*/

WRITE_LINE_MEMBER( kc_d002_device::mei_w )
{
	m_expansions[0]->mei_w(state);
}
