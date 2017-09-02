// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/***************************************************************************

<<<<<<< HEAD
    coco_multi.c
=======
    coco_multi.cpp
>>>>>>> upstream/master

    Code for emulating CoCo's Multi-Pak Interface

     The Multi-Pak interface multiplexes all I/O lines from the Color
     Computer's expansion port to four identical ports. All I/O lines
     are continuously multiplexed except:

     Pin 36 - *SCS
     Pin 32 - *CTS
     Pin  8 - *CART

     These I/O lines are switched in one of two ways. First, is the front
     panel, four position switch. When adjusted the switch will direct the
     MPI to target these three I/O lines to the selected slot.

<<<<<<< HEAD
     Second, the MPI will listen to writes to 0xff7f and respond accordingly:
=======
     Second, the MPI will listen to writes to $FF7F and respond accordingly:
>>>>>>> upstream/master

     bit 0 --\___ Target *SCS to this slot number
     bit 1 --/
     bit 2 ------ Ignore
     bit 3 ------ Ignore
     bit 4 --\___ Target *CTS and *CART to this slot number
     bit 5 --/
     bit 6 ------ Ignore
     bit 7 ------ Ignore

<<<<<<< HEAD
     After writing to 0xff7f, the position of the physical switch has no
     effect until reset.

     Reading is supported on 0xff7f. It will reflect the position of the
     physical switch. Until data is written to 0xff7f, then it will only
=======
     After writing to $FF7F, the position of the physical switch has no
     effect until reset.

     Reading is supported on $FF7F. It will reflect the position of the
     physical switch. Until data is written to $FF7F, then it will only
>>>>>>> upstream/master
     reflect what has been written until a reset.

     A common modification users of the OS-9 operating system made was to
     tie all of the *CART pins together on the MPI motherboard. The *CART
     line is connected to the 6809's IRQ line. This allowed any hardware
     device in any slot to signal an IRQ to the CPU, no matter what the
     switch position was. OS-9 was designed from the very start to poll
     each device attached on every IRQ signal.

     Because of sloppy address decoding the original MPI also responds to
     $FF9F. No software is known to take advantage of this. After the
     introduction of the CoCo 3, which uses $FF9F internally, Tandy provided
<<<<<<< HEAD
     free upgrades to any MPI to fix this problem.

=======
     free upgrades to any MPI to fix this problem.  This behavior is not
     emulated (yet).

     Slots seem to be one-counted (i.e. - 1-4, not 0-3) by convention
>>>>>>> upstream/master

***************************************************************************/

#include "emu.h"
<<<<<<< HEAD
#include "includes/coco.h"
#include "coco_multi.h"
#include "coco_232.h"
#include "coco_orch90.h"
#include "coco_pak.h"
#include "coco_fdc.h"
=======
#include "cococart.h"
>>>>>>> upstream/master

#define SLOT1_TAG           "slot1"
#define SLOT2_TAG           "slot2"
#define SLOT3_TAG           "slot3"
#define SLOT4_TAG           "slot4"


<<<<<<< HEAD
=======
//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> coco_multipak_device

namespace
{
	class coco_multipak_device
		: public device_t
		, public device_cococart_interface
		, public device_cococart_host_interface
	{
	public:
		// construction/destruction
		coco_multipak_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

		// optional information overrides
		virtual void device_add_mconfig(machine_config &config) override;

		virtual uint8_t* get_cart_base() override;

		// these are only public so they can be in a MACHINE_CONFIG_START
		// declaration; don't think about them as publically accessable
		DECLARE_WRITE_LINE_MEMBER(multi_slot1_cart_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot1_nmi_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot1_halt_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot2_cart_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot2_nmi_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot2_halt_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot3_cart_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot3_nmi_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot3_halt_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot4_cart_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot4_nmi_w);
		DECLARE_WRITE_LINE_MEMBER(multi_slot4_halt_w);

		virtual address_space &cartridge_space() override;

	protected:
		// device-level overrides
		virtual void device_start() override;
		virtual void device_reset() override;
		virtual READ8_MEMBER(scs_read) override;
		virtual WRITE8_MEMBER(scs_write) override;
		virtual void set_sound_enable(bool sound_enable) override;

	private:
		// device references
		required_device_array<cococart_slot_device, 4> m_slots;

		// internal state
		uint8_t m_select;

		// internal accessors
		int active_scs_slot_number() const;
		int active_cts_slot_number() const;
		cococart_slot_device &slot(int slot_number);
		cococart_slot_device &active_scs_slot();
		cococart_slot_device &active_cts_slot();

		// methods
		void set_select(uint8_t new_select);
		DECLARE_WRITE8_MEMBER(ff7f_write);
		void update_line(int slot_number, line ln);
	};
};

>>>>>>> upstream/master

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

static SLOT_INTERFACE_START(coco_cart_slot1_3)
<<<<<<< HEAD
	SLOT_INTERFACE("rs232", COCO_232)
	SLOT_INTERFACE("orch90", COCO_ORCH90)
=======
	SLOT_INTERFACE("rs232", COCO_RS232)
	SLOT_INTERFACE("dcmodem", COCO_DCMODEM)
	SLOT_INTERFACE("orch90", COCO_ORCH90)
	SLOT_INTERFACE("ssc", COCO_SSC)                 MCFG_SLOT_OPTION_CLOCK("ssc", DERIVED_CLOCK(1, 1))
	SLOT_INTERFACE("games_master", COCO_PAK_GMC)
>>>>>>> upstream/master
	SLOT_INTERFACE("banked_16k", COCO_PAK_BANKED)
	SLOT_INTERFACE("pak", COCO_PAK)
SLOT_INTERFACE_END
static SLOT_INTERFACE_START(coco_cart_slot4)
	SLOT_INTERFACE("cc3hdb1", COCO3_HDB1)
	SLOT_INTERFACE("fdcv11", COCO_FDC_V11)
<<<<<<< HEAD
	SLOT_INTERFACE("rs232", COCO_232)
	SLOT_INTERFACE("orch90", COCO_ORCH90)
=======
	SLOT_INTERFACE("rs232", COCO_RS232)
	SLOT_INTERFACE("dcmodem", COCO_DCMODEM)
	SLOT_INTERFACE("orch90", COCO_ORCH90)
	SLOT_INTERFACE("ssc", COCO_SSC)                 MCFG_SLOT_OPTION_CLOCK("ssc", DERIVED_CLOCK(1, 1))
	SLOT_INTERFACE("games_master", COCO_PAK_GMC)
>>>>>>> upstream/master
	SLOT_INTERFACE("banked_16k", COCO_PAK_BANKED)
	SLOT_INTERFACE("pak", COCO_PAK)
SLOT_INTERFACE_END

<<<<<<< HEAD
WRITE_LINE_MEMBER(coco_multipak_device::multi_cart_w)
{
	cococart_slot_device *cart = dynamic_cast<cococart_slot_device *>(owner());
	cart->m_cart_callback(state);
}

WRITE_LINE_MEMBER(coco_multipak_device::multi_nmi_w)
{
	cococart_slot_device *cart = dynamic_cast<cococart_slot_device *>(owner());
	cart->m_nmi_callback(state);
}

WRITE_LINE_MEMBER(coco_multipak_device::multi_halt_w)
{
	cococart_slot_device *cart = dynamic_cast<cococart_slot_device *>(owner());
	cart->m_halt_callback(state);
}

static MACHINE_CONFIG_FRAGMENT(coco_multi)
	MCFG_COCO_CARTRIDGE_ADD(SLOT1_TAG, coco_cart_slot1_3, NULL)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT2_TAG, coco_cart_slot1_3, NULL)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT3_TAG, coco_cart_slot1_3, NULL)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT4_TAG, coco_cart_slot4, "fdcv11")
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_halt_w))
MACHINE_CONFIG_END

=======

MACHINE_CONFIG_MEMBER(coco_multipak_device::device_add_mconfig)
	MCFG_COCO_CARTRIDGE_ADD(SLOT1_TAG, coco_cart_slot1_3, nullptr)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot1_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot1_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot1_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT2_TAG, coco_cart_slot1_3, nullptr)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot2_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot2_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot2_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT3_TAG, coco_cart_slot1_3, nullptr)
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot3_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot3_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot3_halt_w))
	MCFG_COCO_CARTRIDGE_ADD(SLOT4_TAG, coco_cart_slot4, "fdcv11")
	MCFG_COCO_CARTRIDGE_CART_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot4_cart_w))
	MCFG_COCO_CARTRIDGE_NMI_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot4_nmi_w))
	MCFG_COCO_CARTRIDGE_HALT_CB(DEVWRITELINE(DEVICE_SELF, coco_multipak_device, multi_slot4_halt_w))
MACHINE_CONFIG_END


>>>>>>> upstream/master
//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type COCO_MULTIPAK = &device_creator<coco_multipak_device>;
=======
DEFINE_DEVICE_TYPE(COCO_MULTIPAK, coco_multipak_device, "coco_multipack", "CoCo Multi-Pak Interface")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  coco_multipak_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
coco_multipak_device::coco_multipak_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, COCO_MULTIPAK, "CoCo Multi-Pak Interface", tag, owner, clock, "coco_multipak", __FILE__),
		device_cococart_interface( mconfig, *this ), m_owner(nullptr), m_select(0)
	{
}



=======
coco_multipak_device::coco_multipak_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, COCO_MULTIPAK, tag, owner, clock)
	, device_cococart_interface(mconfig, *this)
	, m_slots(*this, "slot%u", 1), m_select(0)
{
}


>>>>>>> upstream/master
//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void coco_multipak_device::device_start()
{
<<<<<<< HEAD
	// identify slots
	m_slots[0] = dynamic_cast<cococart_slot_device *>(subdevice(SLOT1_TAG));
	m_slots[1] = dynamic_cast<cococart_slot_device *>(subdevice(SLOT2_TAG));
	m_slots[2] = dynamic_cast<cococart_slot_device *>(subdevice(SLOT3_TAG));
	m_slots[3] = dynamic_cast<cococart_slot_device *>(subdevice(SLOT4_TAG));
	m_owner = dynamic_cast<cococart_slot_device *>(owner());

	// install $FF7F handler
	write8_delegate wh = write8_delegate(FUNC(coco_multipak_device::ff7f_write), this);
	machine().device(MAINCPU_TAG)->memory().space(AS_PROGRAM).install_write_handler(0xFF7F, 0xFF7F, wh);
=======
	// install $FF7F handler
	install_write_handler(0xFF7F, 0xFF7F, write8_delegate(FUNC(coco_multipak_device::ff7f_write), this));
>>>>>>> upstream/master

	// initial state
	m_select = 0xFF;

	// save state
	save_item(NAME(m_select));
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void coco_multipak_device::device_reset()
{
	m_select = 0xFF;
}


<<<<<<< HEAD

//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor coco_multipak_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( coco_multi );
}



//-------------------------------------------------
//  get_cart_base
//-------------------------------------------------

UINT8* coco_multipak_device::get_cart_base()
{
	return active_cts_slot()->get_cart_base();
}



//-------------------------------------------------
//  read
//-------------------------------------------------

READ8_MEMBER(coco_multipak_device::read)
{
	return active_scs_slot()->read(space,offset);
}



//-------------------------------------------------
//  write
//-------------------------------------------------

WRITE8_MEMBER(coco_multipak_device::write)
{
	active_scs_slot()->write(space,offset,data);
}

=======
//**************************************************************************
//  INTERNAL ACCESSORS
//**************************************************************************

//-------------------------------------------------
//  active_scs_slot_number
//-------------------------------------------------

int coco_multipak_device::active_scs_slot_number() const
{
	return ((m_select >> 0) & 0x03) + 1;
}


//-------------------------------------------------
//  active_cts_slot_number
//-------------------------------------------------

int coco_multipak_device::active_cts_slot_number() const
{
	return ((m_select >> 4) & 0x03) + 1;
}


//-------------------------------------------------
//  slot
//-------------------------------------------------

cococart_slot_device &coco_multipak_device::slot(int slot_number)
{
	assert(slot_number >= 1 && slot_number <= 4);
	return *m_slots[slot_number - 1];
}


//-------------------------------------------------
//  active_scs_slot
//-------------------------------------------------

cococart_slot_device &coco_multipak_device::active_scs_slot()
{
	int slot_number = active_scs_slot_number();
	return slot(slot_number);
}


//-------------------------------------------------
//  active_cts_slot
//-------------------------------------------------

cococart_slot_device &coco_multipak_device::active_cts_slot()
{
	int slot_number = active_cts_slot_number();
	return slot(slot_number);
}


//**************************************************************************
//  METHODS
//**************************************************************************

//-------------------------------------------------
//  set_select
//-------------------------------------------------

void coco_multipak_device::set_select(uint8_t new_select)
{
	// identify old value for CART, in case this needs to change
	cococart_slot_device::line_value old_cart = active_cts_slot().get_line_value(line::CART);

	// change value
	uint8_t xorval = m_select ^ new_select;
	m_select = new_select;

	// did the cartridge base change?
	if (xorval & 0x03)
		cart_base_changed();

	// did the CART line change?
	line_value new_cart = active_cts_slot().get_line_value(line::CART);
	if (new_cart != old_cart)
		update_line(active_cts_slot_number(), line::CART);
}
>>>>>>> upstream/master


//-------------------------------------------------
//  ff7f_write
//-------------------------------------------------

WRITE8_MEMBER(coco_multipak_device::ff7f_write)
{
	set_select(data);
}


<<<<<<< HEAD

//-------------------------------------------------
//  set_select
//-------------------------------------------------

void coco_multipak_device::set_select(UINT8 new_select)
{
	UINT8 xorval = m_select ^ new_select;
	m_select = new_select;
	if (xorval & 0x30)
		cart_base_changed();
}



//-------------------------------------------------
//  active_scs_slot
//-------------------------------------------------

cococart_slot_device *coco_multipak_device::active_scs_slot(void)
{
	return m_slots[(m_select >> 0) & 0x03];
}



//-------------------------------------------------
//  active_cts_slot
//-------------------------------------------------

cococart_slot_device *coco_multipak_device::active_cts_slot(void)
{
	return m_slots[(m_select >> 4) & 0x03];
=======
//-------------------------------------------------
//  update_line
//-------------------------------------------------

void coco_multipak_device::update_line(int slot_number, line ln)
{
	bool propagate;

	// one of our child devices set a line; we may need to propagate it upwards
	switch (ln)
	{
	case line::CART:
		// only propagate if this is coming from the slot specified
		propagate = slot_number == active_cts_slot_number();
		break;

	case line::NMI:
	case line::HALT:
		// always propagate these
		propagate = true;
		break;

	default:
		// do nothing
		propagate = false;
		break;
	}

	if (propagate)
		owning_slot().set_line_value(ln, slot(slot_number).get_line_value(ln));
}


//-------------------------------------------------
//  set_sound_enable
//-------------------------------------------------

void coco_multipak_device::set_sound_enable(bool sound_enable)
{
	// the SOUND_ENABLE (SNDEN) line is different; it is controlled by the CPU
	for (cococart_slot_device *slot : m_slots)
		slot->set_line_value(line::SOUND_ENABLE, sound_enable ? line_value::ASSERT : line_value::CLEAR);
}


//-------------------------------------------------
//  get_cart_base
//-------------------------------------------------

uint8_t* coco_multipak_device::get_cart_base()
{
	return active_cts_slot().get_cart_base();
}


//-------------------------------------------------
//  scs_read
//-------------------------------------------------

READ8_MEMBER(coco_multipak_device::scs_read)
{
	return active_scs_slot().scs_read(space, offset);
}


//-------------------------------------------------
//  scs_write
//-------------------------------------------------

WRITE8_MEMBER(coco_multipak_device::scs_write)
{
	active_scs_slot().scs_write(space, offset, data);
}


//-------------------------------------------------
//  multiX_slotX_[cart|nmi|halt] trampolines
//-------------------------------------------------

WRITE_LINE_MEMBER(coco_multipak_device::multi_slot1_cart_w) { update_line(1, line::CART); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot1_nmi_w)  { update_line(1, line::NMI); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot1_halt_w) { update_line(1, line::HALT); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot2_cart_w) { update_line(2, line::CART); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot2_nmi_w)  { update_line(2, line::NMI); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot2_halt_w) { update_line(2, line::HALT); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot3_cart_w) { update_line(3, line::CART); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot3_nmi_w)  { update_line(3, line::NMI); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot3_halt_w) { update_line(3, line::HALT); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot4_cart_w) { update_line(4, line::CART); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot4_nmi_w)  { update_line(4, line::NMI); }
WRITE_LINE_MEMBER(coco_multipak_device::multi_slot4_halt_w) { update_line(4, line::HALT); }


//-------------------------------------------------
//  cartridge_space
//-------------------------------------------------

address_space &coco_multipak_device::cartridge_space()
{
	return device_cococart_interface::cartridge_space();
>>>>>>> upstream/master
}
