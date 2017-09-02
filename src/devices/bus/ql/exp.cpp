// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Sinclair QL expansion port emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type QL_EXPANSION_SLOT = &device_creator<ql_expansion_slot_t>;
=======
DEFINE_DEVICE_TYPE(QL_EXPANSION_SLOT, ql_expansion_slot_device, "ql_expansion_slot", "QL expansion port")
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE QL_EXPANSION CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_ql_expansion_card_interface - constructor
//-------------------------------------------------

device_ql_expansion_card_interface::device_ql_expansion_card_interface(const machine_config &mconfig, device_t &device) :
	device_slot_card_interface(mconfig, device),
	m_romoeh(0)
{
<<<<<<< HEAD
	m_slot = dynamic_cast<ql_expansion_slot_t *>(device.owner());
=======
	m_slot = dynamic_cast<ql_expansion_slot_device *>(device.owner());
>>>>>>> upstream/master
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  ql_expansion_slot_t - constructor
//-------------------------------------------------

ql_expansion_slot_t::ql_expansion_slot_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, QL_EXPANSION_SLOT, "QL expansion port", tag, owner, clock, "ql_expansion_slot", __FILE__),
=======
//  ql_expansion_slot_device - constructor
//-------------------------------------------------

ql_expansion_slot_device::ql_expansion_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, QL_EXPANSION_SLOT, tag, owner, clock),
>>>>>>> upstream/master
	device_slot_interface(mconfig, *this),
	m_write_ipl0l(*this),
	m_write_ipl1l(*this),
	m_write_berrl(*this),
	m_write_extintl(*this), m_card(nullptr)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void ql_expansion_slot_t::device_start()
=======
void ql_expansion_slot_device::device_start()
>>>>>>> upstream/master
{
	m_card = dynamic_cast<device_ql_expansion_card_interface *>(get_card_device());

	// resolve callbacks
	m_write_ipl0l.resolve_safe();
	m_write_ipl1l.resolve_safe();
	m_write_berrl.resolve_safe();
	m_write_extintl.resolve_safe();
}


//-------------------------------------------------
//  SLOT_INTERFACE( ql_expansion_cards )
//-------------------------------------------------

// slot devices
#include "cst_qdisc.h"
#include "cst_q_plus4.h"
#include "cumana_fdi.h"
#include "kempston_di.h"
#include "miracle_gold_card.h"
#include "mp_fdi.h"
#include "opd_basic_master.h"
#include "pcml_qdisk.h"
#include "qubide.h"
#include "sandy_superdisk.h"
#include "sandy_superqboard.h"
#include "trumpcard.h"

SLOT_INTERFACE_START( ql_expansion_cards )
	SLOT_INTERFACE("qdisc", CST_QL_DISC_INTERFACE)
	SLOT_INTERFACE("qplus4", CST_Q_PLUS4)
	SLOT_INTERFACE("cumanafdi", CUMANA_FLOPPY_DISK_INTERFACE)
	SLOT_INTERFACE("kdi", KEMPSTON_DISK_INTERFACE)
	SLOT_INTERFACE("mpfdi", MICRO_PERIPHERALS_FLOPPY_DISK_INTERFACE)
	SLOT_INTERFACE("gold", MIRACLE_GOLD_CARD)
	SLOT_INTERFACE("pcmlqdi", PCML_Q_DISK_INTERFACE)
	SLOT_INTERFACE("qubide", QUBIDE)
	SLOT_INTERFACE("sdisk", SANDY_SUPER_DISK)
	SLOT_INTERFACE("sqboard", SANDY_SUPERQBOARD)
	SLOT_INTERFACE("sqboard512k", SANDY_SUPERQBOARD_512K)
	SLOT_INTERFACE("sqmouse", SANDY_SUPERQMOUSE)
	SLOT_INTERFACE("sqmouse512k", SANDY_SUPERQMOUSE_512K)
	SLOT_INTERFACE("opdbasic", OPD_BASIC_MASTER)
	SLOT_INTERFACE("trump", QL_TRUMP_CARD)
	SLOT_INTERFACE("trump256k", QL_TRUMP_CARD_256K)
	SLOT_INTERFACE("trump512k", QL_TRUMP_CARD_512K)
	SLOT_INTERFACE("trump768k", QL_TRUMP_CARD_768K)
SLOT_INTERFACE_END
