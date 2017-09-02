// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CST Q+4 emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "cst_q_plus4.h"



//**************************************************************************
//  MACROS/CONSTANTS
//**************************************************************************

#define MC6821_TAG "mc6821"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type CST_Q_PLUS4 = &device_creator<cst_q_plus4_t>;
=======
DEFINE_DEVICE_TYPE(CST_Q_PLUS4, cst_q_plus4_device, "ql_qplus4", "CST Q+4")
>>>>>>> upstream/master


//-------------------------------------------------
//  ROM( cst_q_plus4 )
//-------------------------------------------------

ROM_START( cst_q_plus4 )
	ROM_REGION( 0x2000, "rom", 0 )
	ROM_LOAD( "qplus4.rom", 0x0000, 0x2000, CRC(53a078fb) SHA1(53d6828c1b6ba052b862fd80ac8a364b0078330d) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *cst_q_plus4_t::device_rom_region() const
=======
const tiny_rom_entry *cst_q_plus4_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( cst_q_plus4 );
}


//-------------------------------------------------
<<<<<<< HEAD
//  MACHINE_CONFIG_FRAGMENT( cst_q_plus4 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( cst_q_plus4 )
	MCFG_DEVICE_ADD(MC6821_TAG, PIA6821, 0)

	MCFG_QL_EXPANSION_SLOT_ADD("exp1", ql_expansion_cards, NULL)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_t, exp1_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp2", ql_expansion_cards, NULL)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_t, exp2_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp3", ql_expansion_cards, NULL)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_t, exp3_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp4", ql_expansion_cards, NULL)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_t, exp4_extintl_w))
MACHINE_CONFIG_END


//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor cst_q_plus4_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cst_q_plus4 );
}


=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( cst_q_plus4_device::device_add_mconfig )
	MCFG_DEVICE_ADD(MC6821_TAG, PIA6821, 0)

	MCFG_QL_EXPANSION_SLOT_ADD("exp1", ql_expansion_cards, nullptr)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_device, exp1_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp2", ql_expansion_cards, nullptr)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_device, exp2_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp3", ql_expansion_cards, nullptr)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_device, exp3_extintl_w))

	MCFG_QL_EXPANSION_SLOT_ADD("exp4", ql_expansion_cards, nullptr)
	MCFG_QL_EXPANSION_SLOT_EXTINTL_CALLBACK(WRITELINE(cst_q_plus4_device, exp4_extintl_w))
MACHINE_CONFIG_END


>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  cst_q_plus4_t - constructor
//-------------------------------------------------

cst_q_plus4_t::cst_q_plus4_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CST_Q_PLUS4, "CST Q+4", tag, owner, clock, "ql_qplus4", __FILE__),
=======
//  cst_q_plus4_device - constructor
//-------------------------------------------------

cst_q_plus4_device::cst_q_plus4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CST_Q_PLUS4, tag, owner, clock),
>>>>>>> upstream/master
	device_ql_expansion_card_interface(mconfig, *this),
	m_exp1(*this, "exp1"),
	m_exp2(*this, "exp2"),
	m_exp3(*this, "exp3"),
	m_exp4(*this, "exp4"),
	m_rom(*this, "rom"),
	m_exp1_extinl(CLEAR_LINE),
	m_exp2_extinl(CLEAR_LINE),
	m_exp3_extinl(CLEAR_LINE),
	m_exp4_extinl(CLEAR_LINE)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void cst_q_plus4_t::device_start()
=======
void cst_q_plus4_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

<<<<<<< HEAD
UINT8 cst_q_plus4_t::read(address_space &space, offs_t offset, UINT8 data)
=======
uint8_t cst_q_plus4_device::read(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	if (offset >= 0xc000 && offset < 0xc200)
	{
		data = m_rom->base()[offset & 0x1fff];
	}

	data = m_exp1->read(space, offset, data);
	data = m_exp2->read(space, offset, data);
	data = m_exp3->read(space, offset, data);
	data = m_exp4->read(space, offset, data);

	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

<<<<<<< HEAD
void cst_q_plus4_t::write(address_space &space, offs_t offset, UINT8 data)
=======
void cst_q_plus4_device::write(address_space &space, offs_t offset, uint8_t data)
>>>>>>> upstream/master
{
	m_exp1->write(space, offset, data);
	m_exp2->write(space, offset, data);
	m_exp3->write(space, offset, data);
	m_exp4->write(space, offset, data);
}
