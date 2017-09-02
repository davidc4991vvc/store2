// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Luxor ABC 890 bus expander emulation

*********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "abc890.h"



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
const device_type ABC890 = &device_creator<abc890_t>;
const device_type ABC_EXPANSION_UNIT = &device_creator<abc_expansion_unit_t>;
const device_type ABC894 = &device_creator<abc894_t>;
const device_type ABC850 = &device_creator<abc850_t>;
const device_type ABC852 = &device_creator<abc852_t>;
const device_type ABC856 = &device_creator<abc856_t>;


//-------------------------------------------------
//  MACHINE_DRIVER( abc890 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc890 )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("mem1", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("mem2", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("mem3", abcbus_cards, NULL)
=======
DEFINE_DEVICE_TYPE(ABC_EXPANSION_UNIT, abc_expansion_unit_device, "abcexp", "ABC Expansion Unit")
DEFINE_DEVICE_TYPE(ABC890,             abc890_device,             "abc890", "ABC 890")
DEFINE_DEVICE_TYPE(ABC894,             abc894_device,             "abc894", "ABC 894")
DEFINE_DEVICE_TYPE(ABC850,             abc850_device,             "abc850", "ABC 850")
DEFINE_DEVICE_TYPE(ABC852,             abc852_device,             "abc852", "ABC 852")
DEFINE_DEVICE_TYPE(ABC856,             abc856_device,             "abc856", "ABC 856")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc890_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("mem1", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("mem2", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("mem3", abcbus_cards, nullptr)
>>>>>>> upstream/master
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc890_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc890 );
}


//-------------------------------------------------
//  MACHINE_DRIVER( abc_expansion_unit )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc_expansion_unit )
	MCFG_ABCBUS_SLOT_ADD("io1", abc80_cards, "abc830")
	MCFG_ABCBUS_SLOT_ADD("io2", abc80_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io3", abc80_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io4", abc80_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("mem1", abc80_cards, "memcard")
	MCFG_ABCBUS_SLOT_ADD("mem2", abc80_cards, "16k")
	MCFG_ABCBUS_SLOT_ADD("mem3", abc80_cards, NULL)
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc_expansion_unit_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abc80_cards, "abc830")
	MCFG_ABCBUS_SLOT_ADD("io2", abc80_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io3", abc80_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io4", abc80_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("mem1", abc80_cards, "memcard")
	MCFG_ABCBUS_SLOT_ADD("mem2", abc80_cards, "16k")
	MCFG_ABCBUS_SLOT_ADD("mem3", abc80_cards, nullptr)
>>>>>>> upstream/master
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc_expansion_unit_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc_expansion_unit );
}


//-------------------------------------------------
//  MACHINE_DRIVER( abc894 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc894 )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, NULL)
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc894_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, nullptr)
>>>>>>> upstream/master
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc894_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc894 );
}


//-------------------------------------------------
//  MACHINE_DRIVER( abc850 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc850 )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "ro202")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, NULL)
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc850_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "ro202")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, nullptr)
>>>>>>> upstream/master
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc850_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc850 );
}


//-------------------------------------------------
//  MACHINE_DRIVER( abc852 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc852 )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "basf6185")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, NULL)
=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc852_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "basf6185")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, nullptr)
>>>>>>> upstream/master
MACHINE_CONFIG_END


//-------------------------------------------------
<<<<<<< HEAD
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc852_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc852 );
}


//-------------------------------------------------
//  MACHINE_DRIVER( abc856 )
//-------------------------------------------------

static MACHINE_CONFIG_FRAGMENT( abc856 )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "micr1325")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, NULL)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, NULL)
MACHINE_CONFIG_END


//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor abc856_t::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( abc856 );
}


=======
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( abc856_device::device_add_mconfig )
	MCFG_ABCBUS_SLOT_ADD("io1", abcbus_cards, "abc850fdd")
	MCFG_ABCBUS_SLOT_ADD("io2", abcbus_cards, "xebec")
	MCFG_DEVICE_CARD_DEFAULT_BIOS("xebec", "micr1325")
	MCFG_ABCBUS_SLOT_ADD("io3", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io4", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io5", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io6", abcbus_cards, nullptr)
	MCFG_ABCBUS_SLOT_ADD("io7", abcbus_cards, nullptr)
MACHINE_CONFIG_END


>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
<<<<<<< HEAD
//  abc890_t - constructor
//-------------------------------------------------

abc890_t::abc890_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
=======
//  abc890_device - constructor
//-------------------------------------------------

abc890_device::abc890_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
>>>>>>> upstream/master
	device_abcbus_card_interface(mconfig, *this)
{
}

<<<<<<< HEAD
abc890_t::abc890_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, ABC890, "ABC 890", tag, owner, clock, "abc890", __FILE__),
	device_abcbus_card_interface(mconfig, *this)
{
}

abc_expansion_unit_t::abc_expansion_unit_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	abc890_t(mconfig, ABC_EXPANSION_UNIT, "ABC Expansion Unit", tag, owner, clock, "abcexp", __FILE__)
{
}

abc894_t::abc894_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	abc890_t(mconfig, ABC894, "ABC 894", tag, owner, clock, "abc894", __FILE__)
{
}

abc850_t::abc850_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	abc890_t(mconfig, ABC850, "ABC 850", tag, owner, clock, "abc850", __FILE__)
{
}

abc852_t::abc852_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	abc890_t(mconfig, ABC852, "ABC 852", tag, owner, clock, "abc852", __FILE__)
{
}

abc856_t::abc856_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	abc890_t(mconfig, ABC856, "ABC 856", tag, owner, clock, "abc856", __FILE__)
=======
abc890_device::abc890_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC890, tag, owner, clock)
{
}

abc_expansion_unit_device::abc_expansion_unit_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC_EXPANSION_UNIT, tag, owner, clock)
{
}

abc894_device::abc894_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC894, tag, owner, clock)
{
}

abc850_device::abc850_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC850, tag, owner, clock)
{
}

abc852_device::abc852_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC852, tag, owner, clock)
{
}

abc856_device::abc856_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	abc890_device(mconfig, ABC856, tag, owner, clock)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::device_start()
=======
void abc890_device::device_start()
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::device_reset()
{
	for (device_t *device = first_subdevice(); device != NULL; device = device->next())
	{
		device->reset();
=======
void abc890_device::device_reset()
{
	for (device_t &device : subdevices())
	{
		device.reset();
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_cs - card select
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_cs(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->cs_w(data);
=======
void abc890_device::abcbus_cs(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.cs_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_inp - input
//-------------------------------------------------

<<<<<<< HEAD
UINT8 abc890_t::abcbus_inp()
{
	UINT8 data = 0xff;

	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		data &= slot->inp_r();
=======
uint8_t abc890_device::abcbus_inp()
{
	uint8_t data = 0xff;

	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		data &= slot.inp_r();
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  abcbus_out - output
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_out(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->out_w(data);
=======
void abc890_device::abcbus_out(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.out_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_stat - status
//-------------------------------------------------

<<<<<<< HEAD
UINT8 abc890_t::abcbus_stat()
{
	UINT8 data = 0xff;

	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		data &= slot->stat_r();
=======
uint8_t abc890_device::abcbus_stat()
{
	uint8_t data = 0xff;

	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		data &= slot.stat_r();
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  abcbus_c1 - command 1
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_c1(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->c1_w(data);
=======
void abc890_device::abcbus_c1(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.c1_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_c2 - command 2
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_c2(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->c2_w(data);
=======
void abc890_device::abcbus_c2(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.c2_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_c3 - command 3
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_c3(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->c3_w(data);
=======
void abc890_device::abcbus_c3(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.c3_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_c4 - command 4
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_c4(UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->c4_w(data);
=======
void abc890_device::abcbus_c4(uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.c4_w(data);
>>>>>>> upstream/master
	}
}


//-------------------------------------------------
//  abcbus_xmemfl - extended memory read
//-------------------------------------------------

<<<<<<< HEAD
UINT8 abc890_t::abcbus_xmemfl(offs_t offset)
{
	UINT8 data = 0xff;

	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		data &= slot->xmemfl_r(offset);
=======
uint8_t abc890_device::abcbus_xmemfl(offs_t offset)
{
	uint8_t data = 0xff;

	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		data &= slot.xmemfl_r(offset);
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  abcbus_xmemw - extended memory write
//-------------------------------------------------

<<<<<<< HEAD
void abc890_t::abcbus_xmemw(offs_t offset, UINT8 data)
{
	abcbus_slot_device_iterator iter(*this);

	for (abcbus_slot_t *slot = iter.first(); slot != NULL; slot = iter.next())
	{
		slot->xmemw_w(offset, data);
=======
void abc890_device::abcbus_xmemw(offs_t offset, uint8_t data)
{
	for (abcbus_slot_device &slot : abcbus_slot_device_iterator(*this))
	{
		slot.xmemw_w(offset, data);
>>>>>>> upstream/master
	}
}
