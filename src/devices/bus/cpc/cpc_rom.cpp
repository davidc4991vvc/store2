// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
<<<<<<< HEAD
 * cpc_rom.c
=======
 * cpc_rom.cpp
>>>>>>> upstream/master
 * Amstrad CPC mountable ROM image device
 *
 */

#include "emu.h"
#include "cpc_rom.h"
<<<<<<< HEAD
#include "includes/amstrad.h"

const device_type CPC_ROM = &device_creator<cpc_rom_device>;

=======

DEFINE_DEVICE_TYPE(CPC_ROM, cpc_rom_device, "cpc_rom", "CPC ROM Box")

SLOT_INTERFACE_EXTERN(cpc_exp_cards);
>>>>>>> upstream/master

//**************************************************************************
//  DEVICE CONFIG INTERFACE
//**************************************************************************

// device machine config
<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT( cpc_rom )
	MCFG_ROMSLOT_ADD("rom1")
	MCFG_ROMSLOT_ADD("rom2")
	MCFG_ROMSLOT_ADD("rom3")
	MCFG_ROMSLOT_ADD("rom4")
	MCFG_ROMSLOT_ADD("rom5")
	MCFG_ROMSLOT_ADD("rom6")
	MCFG_ROMSLOT_ADD("rom7")
	MCFG_ROMSLOT_ADD("rom8")

	// pass-through
	MCFG_DEVICE_ADD("exp", CPC_EXPANSION_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(cpc_exp_cards, NULL, false)
=======
MACHINE_CONFIG_MEMBER( cpc_rom_device::device_add_mconfig )
	MCFG_CPC_ROMSLOT_ADD("rom1")
	MCFG_CPC_ROMSLOT_ADD("rom2")
	MCFG_CPC_ROMSLOT_ADD("rom3")
	MCFG_CPC_ROMSLOT_ADD("rom4")
	MCFG_CPC_ROMSLOT_ADD("rom5")
	MCFG_CPC_ROMSLOT_ADD("rom6")
	MCFG_CPC_ROMSLOT_ADD("rom7")
	MCFG_CPC_ROMSLOT_ADD("rom8")

	// pass-through
	MCFG_DEVICE_ADD("exp", CPC_EXPANSION_SLOT, 0)
	MCFG_DEVICE_SLOT_INTERFACE(cpc_exp_cards, nullptr, false)
>>>>>>> upstream/master
	MCFG_CPC_EXPANSION_SLOT_OUT_IRQ_CB(DEVWRITELINE("^", cpc_expansion_slot_device, irq_w))
	MCFG_CPC_EXPANSION_SLOT_OUT_NMI_CB(DEVWRITELINE("^", cpc_expansion_slot_device, nmi_w))
	MCFG_CPC_EXPANSION_SLOT_OUT_ROMDIS_CB(DEVWRITELINE("^", cpc_expansion_slot_device, romdis_w))  // ROMDIS

MACHINE_CONFIG_END


<<<<<<< HEAD
machine_config_constructor cpc_rom_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( cpc_rom );
}

=======
>>>>>>> upstream/master
//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

<<<<<<< HEAD
cpc_rom_device::cpc_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, CPC_ROM, "ROM Box", tag, owner, clock, "cpc_rom", __FILE__),
	device_cpc_expansion_card_interface(mconfig, *this)
=======
cpc_rom_device::cpc_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, CPC_ROM, tag, owner, clock),
	device_cpc_expansion_card_interface(mconfig, *this),
	m_rom(*this, "rom%u", 1)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cpc_rom_device::device_start()
{
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void cpc_rom_device::device_reset()
{
}


/*** ROM image device ***/

// device type definition
<<<<<<< HEAD
const device_type ROMSLOT = &device_creator<rom_image_device>;

//-------------------------------------------------
//  rom_image_device - constructor
//-------------------------------------------------

rom_image_device::rom_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, ROMSLOT, "ROM image", tag, owner, clock, "rom_image", __FILE__),
		device_image_interface(mconfig, *this), m_base(nullptr)
=======
DEFINE_DEVICE_TYPE(CPC_ROMSLOT, cpc_rom_image_device, "cpc_rom_image", "CPC ROM image")

//-------------------------------------------------
//  cpc_rom_image_device - constructor
//-------------------------------------------------

cpc_rom_image_device::cpc_rom_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, CPC_ROMSLOT, tag, owner, clock)
	, device_image_interface(mconfig, *this)
	, m_base(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
<<<<<<< HEAD
//  rom_image_device - destructor
//-------------------------------------------------

rom_image_device::~rom_image_device()
=======
//  cpc_rom_image_device - destructor
//-------------------------------------------------

cpc_rom_image_device::~cpc_rom_image_device()
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void rom_image_device::device_start()
{
	m_base = NULL;
=======
void cpc_rom_image_device::device_start()
{
	m_base = nullptr;
>>>>>>> upstream/master
}

/*-------------------------------------------------
    DEVICE_IMAGE_LOAD( rom )
-------------------------------------------------*/
<<<<<<< HEAD
bool rom_image_device::call_load()
{
	device_image_interface* image = this;
	UINT64 size = image->length();

	m_base = global_alloc_array(UINT8, 16384);
	if(size <= 16384)
	{
		image->fread(m_base,size);
=======
image_init_result cpc_rom_image_device::call_load()
{
	device_image_interface* image = this;
	uint64_t size = image->length();

	m_base = std::make_unique<uint8_t[]>(16384);
	if(size <= 16384)
	{
		image->fread(m_base.get(),size);
>>>>>>> upstream/master
	}
	else
	{
		image->fseek(size-16384,SEEK_SET);
<<<<<<< HEAD
		image->fread(m_base,16384);
	}

	return IMAGE_INIT_PASS;
=======
		image->fread(m_base.get(),16384);
	}

	return image_init_result::PASS;
>>>>>>> upstream/master
}


/*-------------------------------------------------
    DEVICE_IMAGE_UNLOAD( rom )
-------------------------------------------------*/
<<<<<<< HEAD
void rom_image_device::call_unload()
{
	global_free_array(m_base);
	m_base = NULL;
=======
void cpc_rom_image_device::call_unload()
{
	m_base = nullptr;
>>>>>>> upstream/master
}
