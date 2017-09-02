// license:BSD-3-Clause
// copyright-holders:Nathan Woods
/*********************************************************************

<<<<<<< HEAD
    cococart.c

    CoCo/Dragon cartridge management
=======
    cococart.cpp

    CoCo/Dragon cartridge slot - typically used for "Program Paks"
    (which are simple ROMs) but in practice is the main extensibility
    mechanism for CoCo hardware

    CoCo and Dragon pinout listing
       ---  -------            ---  -------
         1  -12V                21  A2
         2  +12V                22  A3
         3  HALT                23  A4
         4  NMI                 24  A5
         5  RESET               25  A6
         6  EIN                 26  A7
         7  QIN                 27  A8
         8  CART                28  A9
         9  +5V                 29  A10
        10  D0                  30  A11
        11  D1                  31  A12
        12  D2                  32  CTS
        13  D3                  33  GND
        14  D4                  34  GND
        15  D5                  35  SND
        16  D6                  36  SCS
        17  D7                  37  A13
        18  R/!W                38  A14
        19  A0                  39  A15
        20  A1                  40  SLENB

    Notes:
        CTS - ROM read $C000-$FEFF ($FDFF on CoCo 3)
        SCS - Spare Chip Select:  IO space between $FF40-5F
>>>>>>> upstream/master

*********************************************************************/

#include "emu.h"
#include "cococart.h"
<<<<<<< HEAD
#include "emuopts.h"
=======

>>>>>>> upstream/master

/***************************************************************************
    PARAMETERS
***************************************************************************/

#define LOG_LINE                0


<<<<<<< HEAD
=======
/***************************************************************************
    CONSTANTS
***************************************************************************/

enum
{
	TIMER_CART,
	TIMER_NMI,
	TIMER_HALT
};

>>>>>>> upstream/master

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type COCOCART_SLOT = &device_creator<cococart_slot_device>;

=======
DEFINE_DEVICE_TYPE(COCOCART_SLOT, cococart_slot_device, "cococart_slot", "CoCo Cartridge Slot")
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  cococart_slot_device - constructor
//-------------------------------------------------
<<<<<<< HEAD
cococart_slot_device::cococart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, COCOCART_SLOT, "CoCo Cartridge Slot", tag, owner, clock, "cococart_slot", __FILE__),
		device_slot_interface(mconfig, *this),
		device_image_interface(mconfig, *this),
		m_cart_callback(*this),
		m_nmi_callback(*this),
		m_halt_callback(*this), m_cart(nullptr)
=======
cococart_slot_device::cococart_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, COCOCART_SLOT, tag, owner, clock),
	device_slot_interface(mconfig, *this),
	device_image_interface(mconfig, *this),
	m_cart_callback(*this),
	m_nmi_callback(*this),
	m_halt_callback(*this), m_cart(nullptr)
>>>>>>> upstream/master
{
}



//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void cococart_slot_device::device_start()
{
	for(int i=0; i<TIMER_POOL; i++ )
	{
		m_cart_line.timer[i]    = timer_alloc(TIMER_CART);
		m_nmi_line.timer[i]     = timer_alloc(TIMER_NMI);
		m_halt_line.timer[i]    = timer_alloc(TIMER_HALT);
	}

	m_cart_line.timer_index     = 0;
	m_cart_line.delay           = 0;
<<<<<<< HEAD
	m_cart_line.value           = COCOCART_LINE_VALUE_CLEAR;
=======
	m_cart_line.value           = line_value::CLEAR;
>>>>>>> upstream/master
	m_cart_line.line            = 0;
	m_cart_line.q_count         = 0;
	m_cart_callback.resolve();
	m_cart_line.callback = &m_cart_callback;

	m_nmi_line.timer_index      = 0;
<<<<<<< HEAD
	/* 12 allowed one more instruction to finished after the line is pulled */
	m_nmi_line.delay            = 12;
	m_nmi_line.value            = COCOCART_LINE_VALUE_CLEAR;
=======
	m_nmi_line.delay            = 0;
	m_nmi_line.value            = line_value::CLEAR;
>>>>>>> upstream/master
	m_nmi_line.line             = 0;
	m_nmi_line.q_count          = 0;
	m_nmi_callback.resolve();
	m_nmi_line.callback = &m_nmi_callback;

	m_halt_line.timer_index     = 0;
<<<<<<< HEAD
	/* 6 allowed one more instruction to finished after the line is pulled */
	m_halt_line.delay           = 6;
	m_halt_line.value           = COCOCART_LINE_VALUE_CLEAR;
=======
	m_halt_line.delay           = 0;
	m_halt_line.value           = line_value::CLEAR;
>>>>>>> upstream/master
	m_halt_line.line            = 0;
	m_halt_line.q_count         = 0;
	m_halt_callback.resolve();
	m_halt_line.callback = &m_halt_callback;

	m_cart = dynamic_cast<device_cococart_interface *>(get_card_device());
}



//-------------------------------------------------
<<<<<<< HEAD
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void cococart_slot_device::device_config_complete()
{
	// set brief and instance name
	update_names();
}



//-------------------------------------------------
=======
>>>>>>> upstream/master
//  device_timer - handle timer callbacks
//-------------------------------------------------

void cococart_slot_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	switch(id)
	{
		case TIMER_CART:
<<<<<<< HEAD
			set_line("CART", m_cart_line, (cococart_line_value) param);
			break;

		case TIMER_NMI:
			set_line("NMI", m_nmi_line, (cococart_line_value) param);
			break;

		case TIMER_HALT:
			set_line("HALT", m_halt_line, (cococart_line_value) param);
=======
			set_line("CART", m_cart_line, (line_value) param);
			break;

		case TIMER_NMI:
			set_line("NMI", m_nmi_line, (line_value) param);
			break;

		case TIMER_HALT:
			set_line("HALT", m_halt_line, (line_value) param);
>>>>>>> upstream/master
			break;
	}
}


<<<<<<< HEAD

//-------------------------------------------------
//  coco_cartridge_r
//-------------------------------------------------

READ8_MEMBER(cococart_slot_device::read)
{
	UINT8 result = 0x00;
	if (m_cart)
		result = m_cart->read(space, offset);
=======
//-------------------------------------------------
//  scs_read
//-------------------------------------------------

READ8_MEMBER(cococart_slot_device::scs_read)
{
	uint8_t result = 0x00;
	if (m_cart)
		result = m_cart->scs_read(space, offset);
>>>>>>> upstream/master
	return result;
}


//-------------------------------------------------
<<<<<<< HEAD
//  coco_cartridge_w
//-------------------------------------------------

WRITE8_MEMBER(cococart_slot_device::write)
{
	if (m_cart)
		m_cart->write(space, offset, data);
=======
//  scs_write
//-------------------------------------------------

WRITE8_MEMBER(cococart_slot_device::scs_write)
{
	if (m_cart)
		m_cart->scs_write(space, offset, data);
>>>>>>> upstream/master
}



//-------------------------------------------------
//  line_value_string
//-------------------------------------------------

<<<<<<< HEAD
static const char *line_value_string(cococart_line_value value)
{
	const char *s = NULL;
	switch(value)
	{
		case COCOCART_LINE_VALUE_CLEAR:
			s = "CLEAR";
			break;
		case COCOCART_LINE_VALUE_ASSERT:
			s = "ASSERT";
			break;
		case COCOCART_LINE_VALUE_Q:
			s = "Q";
			break;
		default:
			fatalerror("Invalid value\n");
=======
const char *cococart_slot_device::line_value_string(line_value value)
{
	const char *s;
	switch(value)
	{
		case line_value::CLEAR:
			s = "CLEAR";
			break;
		case line_value::ASSERT:
			s = "ASSERT";
			break;
		case line_value::Q:
			s = "Q";
			break;
		default:
			throw false && "Invalid value";
>>>>>>> upstream/master
	}
	return s;
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  set_line
//-------------------------------------------------

<<<<<<< HEAD
void cococart_slot_device::set_line(const char *line_name, coco_cartridge_line &line, cococart_line_value value)
{
	if ((line.value != value) || (value == COCOCART_LINE_VALUE_Q))
=======
void cococart_slot_device::set_line(const char *line_name, coco_cartridge_line &line, cococart_slot_device::line_value value)
{
	if ((line.value != value) || (value == line_value::Q))
>>>>>>> upstream/master
	{
		line.value = value;

		if (LOG_LINE)
			logerror("[%s]: set_line(): %s <= %s\n", machine().describe_context(), line_name, line_value_string(value));
<<<<<<< HEAD
		/* engage in a bit of gymnastics for this odious 'Q' value */
		switch(line.value)
		{
			case COCOCART_LINE_VALUE_CLEAR:
=======

		// engage in a bit of gymnastics for this odious 'Q' value
		switch(line.value)
		{
			case line_value::CLEAR:
>>>>>>> upstream/master
				line.line = 0x00;
				line.q_count = 0;
				break;

<<<<<<< HEAD
			case COCOCART_LINE_VALUE_ASSERT:
=======
			case line_value::ASSERT:
>>>>>>> upstream/master
				line.line = 0x01;
				line.q_count = 0;
				break;

<<<<<<< HEAD
			case COCOCART_LINE_VALUE_Q:
=======
			case line_value::Q:
>>>>>>> upstream/master
				line.line = line.line ? 0x00 : 0x01;
				if (line.q_count++ < 4)
					set_line_timer(line, value);
				break;
		}

		/* invoke the callback, if present */
		if (!(*line.callback).isnull())
			(*line.callback)(line.line);
	}
}


<<<<<<< HEAD

//-------------------------------------------------
//  set_line_timer()
//-------------------------------------------------

void cococart_slot_device::set_line_timer(coco_cartridge_line &line, cococart_line_value value)
{
	/* calculate delay; delay dependant on cycles per second */
=======
//-------------------------------------------------
//  set_line_timer
//-------------------------------------------------

void cococart_slot_device::set_line_timer(coco_cartridge_line &line, cococart_slot_device::line_value value)
{
	// calculate delay; delay dependant on cycles per second
>>>>>>> upstream/master
	attotime delay = (line.delay != 0)
		? machine().firstcpu->cycles_to_attotime(line.delay)
		: attotime::zero;

	line.timer[line.timer_index]->adjust(delay, (int) value);
	line.timer_index = (line.timer_index + 1) % TIMER_POOL;
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  twiddle_line_if_q
//-------------------------------------------------

void cococart_slot_device::twiddle_line_if_q(coco_cartridge_line &line)
{
<<<<<<< HEAD
	if (line.value == COCOCART_LINE_VALUE_Q)
	{
		line.q_count = 0;
		set_line_timer(line, COCOCART_LINE_VALUE_Q);
=======
	if (line.value == line_value::Q)
	{
		line.q_count = 0;
		set_line_timer(line, line_value::Q);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD

//-------------------------------------------------
//  coco_cartridge_twiddle_q_lines - hack to
//  support twiddling the Q line
=======
//-------------------------------------------------
//  twiddle_q_lines - hack to support twiddling the
//  Q line
>>>>>>> upstream/master
//-------------------------------------------------

void cococart_slot_device::twiddle_q_lines()
{
	twiddle_line_if_q(m_cart_line);
	twiddle_line_if_q(m_nmi_line);
	twiddle_line_if_q(m_halt_line);
}


//-------------------------------------------------
<<<<<<< HEAD
//  coco_cartridge_set_line
//-------------------------------------------------

void cococart_slot_device::cart_set_line(cococart_line line, cococart_line_value value)
{
	switch (line)
	{
		case COCOCART_LINE_CART:
			set_line_timer(m_cart_line, value);
			break;

		case COCOCART_LINE_NMI:
			set_line_timer(m_nmi_line, value);
			break;

		case COCOCART_LINE_HALT:
			set_line_timer(m_halt_line, value);
			break;

		case COCOCART_LINE_SOUND_ENABLE:
			// do nothing for now
			break;
=======
//  set_line_value
//-------------------------------------------------

void cococart_slot_device::set_line_value(cococart_slot_device::line which, cococart_slot_device::line_value value)
{
	switch (which)
	{
	case cococart_slot_device::line::CART:
		set_line_timer(m_cart_line, value);
		break;

	case cococart_slot_device::line::NMI:
		set_line_timer(m_nmi_line, value);
		break;

	case cococart_slot_device::line::HALT:
		set_line_timer(m_halt_line, value);
		break;

	case cococart_slot_device::line::SOUND_ENABLE:
		if (m_cart)
			m_cart->set_sound_enable(value != cococart_slot_device::line_value::CLEAR);
		break;
	}
}


//-------------------------------------------------
//  set_line_delay
//-------------------------------------------------

void cococart_slot_device::set_line_delay(cococart_slot_device::line which, int cycles)
{
	switch (which)
	{
	case cococart_slot_device::line::CART:
		m_cart_line.delay = cycles;
		break;

	case cococart_slot_device::line::NMI:
		m_nmi_line.delay = cycles;
		break;

	case cococart_slot_device::line::HALT:
		m_halt_line.delay = cycles;
		break;

	default:
		throw false;
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
=======
//-------------------------------------------------
//  get_line_value
//-------------------------------------------------

cococart_slot_device::line_value cococart_slot_device::get_line_value(cococart_slot_device::line which) const
{
	line_value result;
	switch (which)
	{
	case cococart_slot_device::line::CART:
		result = m_cart_line.value;
		break;

	case cococart_slot_device::line::NMI:
		result = m_nmi_line.value;
		break;

	case cococart_slot_device::line::HALT:
		result = m_halt_line.value;
		break;

	default:
		result = line_value::CLEAR;
		break;
	}
	return result;
}

>>>>>>> upstream/master

//-------------------------------------------------
//  get_cart_base
//-------------------------------------------------

<<<<<<< HEAD
UINT8* cococart_slot_device::get_cart_base()
{
	if (m_cart != NULL)
		return m_cart->get_cart_base();
	return NULL;
}



=======
uint8_t* cococart_slot_device::get_cart_base()
{
	if (m_cart != nullptr)
		return m_cart->get_cart_base();
	return nullptr;
}


>>>>>>> upstream/master
//-------------------------------------------------
//  set_cart_base_update
//-------------------------------------------------

void cococart_slot_device::set_cart_base_update(cococart_base_update_delegate update)
{
<<<<<<< HEAD
	if (m_cart != NULL)
=======
	if (m_cart)
>>>>>>> upstream/master
		m_cart->set_cart_base_update(update);
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  call_load
//-------------------------------------------------

<<<<<<< HEAD
bool cococart_slot_device::call_load()
{
	if (m_cart)
	{
		offs_t read_length = 0;
		if (software_entry() == NULL)
=======
image_init_result cococart_slot_device::call_load()
{
	if (m_cart)
	{
		offs_t read_length;
		if (!loaded_through_softlist())
>>>>>>> upstream/master
		{
			read_length = fread(m_cart->get_cart_base(), 0x8000);
		}
		else
		{
			read_length = get_software_region_length("rom");
			memcpy(m_cart->get_cart_base(), get_software_region("rom"), read_length);
		}
		while(read_length < 0x8000)
		{
<<<<<<< HEAD
			offs_t len = MIN(read_length, 0x8000 - read_length);
=======
			offs_t len = std::min(read_length, 0x8000 - read_length);
>>>>>>> upstream/master
			memcpy(m_cart->get_cart_base() + read_length, m_cart->get_cart_base(), len);
			read_length += len;
		}
	}
<<<<<<< HEAD
	return IMAGE_INIT_PASS;
}



//-------------------------------------------------
//  call_softlist_load
//-------------------------------------------------

bool cococart_slot_device::call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry)
{
	load_software_part_region(*this, swlist, swname, start_entry );
	return TRUE;
}



=======
	return image_init_result::PASS;
}


>>>>>>> upstream/master
//-------------------------------------------------
//  get_default_card_software
//-------------------------------------------------

<<<<<<< HEAD
void cococart_slot_device::get_default_card_software(std::string &result)
{
	software_get_default_slot(result, "pak");
=======
std::string cococart_slot_device::get_default_card_software(get_default_card_software_hook &hook) const
{
	return software_get_default_slot("pak");
>>>>>>> upstream/master
}



<<<<<<< HEAD

//**************************************************************************
//  DEVICE COCO CART  INTERFACE
=======
//**************************************************************************
//  DEVICE COCO CART INTERFACE - Implemented by devices that plug into
//  CoCo cartridge slots
>>>>>>> upstream/master
//**************************************************************************

//-------------------------------------------------
//  device_cococart_interface - constructor
//-------------------------------------------------

device_cococart_interface::device_cococart_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig, device)
<<<<<<< HEAD
=======
	, m_owning_slot(nullptr)
	, m_host(nullptr)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  ~device_cococart_interface - destructor
//-------------------------------------------------

device_cococart_interface::~device_cococart_interface()
{
}


<<<<<<< HEAD

//-------------------------------------------------
//  read
//-------------------------------------------------

READ8_MEMBER(device_cococart_interface::read)
{
	return 0x00;
}



//-------------------------------------------------
//  write
//-------------------------------------------------

WRITE8_MEMBER(device_cococart_interface::write)
=======
//-------------------------------------------------
//  interface_config_complete
//-------------------------------------------------

void device_cococart_interface::interface_config_complete()
{
	m_owning_slot = dynamic_cast<cococart_slot_device *>(device().owner());
	m_host = m_owning_slot
		? dynamic_cast<device_cococart_host_interface *>(m_owning_slot->owner())
		: nullptr;
}


//-------------------------------------------------
//  interface_pre_start
//-------------------------------------------------

void device_cococart_interface::interface_pre_start()
{
	if (!m_owning_slot)
		throw emu_fatalerror("Expected device().owner() to be of type cococart_slot_device");
	if (!m_host)
		throw emu_fatalerror("Expected m_owning_slot->owner() to be of type device_cococart_host_interface");
}


//-------------------------------------------------
//  scs_read - Signifies a read where the SCS pin
//  on the cartridge slot was asserted ($FF40-5F)
//-------------------------------------------------

READ8_MEMBER(device_cococart_interface::scs_read)
{
	return 0x00;
}


//-------------------------------------------------
//  scs_write - Signifies a write where the SCS pin
//  on the cartridge slot was asserted ($FF40-5F)
//-------------------------------------------------

WRITE8_MEMBER(device_cococart_interface::scs_write)
>>>>>>> upstream/master
{
}


<<<<<<< HEAD
=======
//-------------------------------------------------
//  set_sound_enable
//-------------------------------------------------

void device_cococart_interface::set_sound_enable(bool sound_enable)
{
}

>>>>>>> upstream/master

//-------------------------------------------------
//  get_cart_base
//-------------------------------------------------

<<<<<<< HEAD
UINT8* device_cococart_interface::get_cart_base()
{
	return NULL;
}



=======
uint8_t* device_cococart_interface::get_cart_base()
{
	return nullptr;
}


>>>>>>> upstream/master
//-------------------------------------------------
//  set_cart_base_update
//-------------------------------------------------

void device_cococart_interface::set_cart_base_update(cococart_base_update_delegate update)
{
	m_update = update;
}


<<<<<<< HEAD

=======
>>>>>>> upstream/master
//-------------------------------------------------
//  cart_base_changed
//-------------------------------------------------

void device_cococart_interface::cart_base_changed(void)
{
	if (!m_update.isnull())
		m_update(get_cart_base());
}
<<<<<<< HEAD
=======


//-------------------------------------------------
//  cartridge_space
//-------------------------------------------------

address_space &device_cococart_interface::cartridge_space()
{
	return host().cartridge_space();
}


//-------------------------------------------------
//  install_read_handler
//-------------------------------------------------

void device_cococart_interface::install_read_handler(uint16_t addrstart, uint16_t addrend, read8_delegate rhandler)
{
	address_space &space(cartridge_space());
	space.install_read_handler(addrstart, addrend, rhandler);
}


//-------------------------------------------------
//  install_write_handler
//-------------------------------------------------

void device_cococart_interface::install_write_handler(uint16_t addrstart, uint16_t addrend, write8_delegate whandler)
{
	address_space &space(cartridge_space());
	space.install_write_handler(addrstart, addrend, whandler);
}


//-------------------------------------------------
//  install_readwrite_handler
//-------------------------------------------------

void device_cococart_interface::install_readwrite_handler(uint16_t addrstart, uint16_t addrend, read8_delegate rhandler, write8_delegate whandler)
{
	address_space &space(cartridge_space());
	space.install_read_handler(addrstart, addrend, rhandler);
	space.install_write_handler(addrstart, addrend, whandler);
}


//-------------------------------------------------
//  set_line_value
//-------------------------------------------------

void device_cococart_interface::set_line_value(cococart_slot_device::line line, cococart_slot_device::line_value value)
{
	owning_slot().set_line_value(line, value);
}
>>>>>>> upstream/master
