// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Intel 8355 - 16,384-Bit ROM with I/O emulation

**********************************************************************/

#include "emu.h"
#include "i8355.h"

<<<<<<< HEAD
=======
//#define VERBOSE 1
#include "logmacro.h"
>>>>>>> upstream/master


//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

<<<<<<< HEAD
#define LOG 0

=======
>>>>>>> upstream/master
enum
{
	REGISTER_PORT_A = 0,
	REGISTER_PORT_B,
	REGISTER_PORT_A_DDR,
	REGISTER_PORT_B_DDR
};

enum
{
	PORT_A = 0,
	PORT_B,
	PORT_COUNT
};



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type I8355 = &device_creator<i8355_device>;

// default address map
static ADDRESS_MAP_START( i8355, AS_0, 8, i8355_device )
	AM_RANGE(0x000, 0x7ff) AM_ROM
ADDRESS_MAP_END
=======
DEFINE_DEVICE_TYPE(I8355, i8355_device, "i8355", "Intel 8355")
>>>>>>> upstream/master



//**************************************************************************
//  INLINE HELPERS
//**************************************************************************

//-------------------------------------------------
//  read_port - read from input port
//-------------------------------------------------

<<<<<<< HEAD
inline UINT8 i8355_device::read_port(int port)
{
	UINT8 data = m_output[port] & m_ddr[port];

	if (m_ddr[port] != 0xff)
	{
		if (port == 0) {data |= m_in_pa_cb(0) & ~m_ddr[port];}
		else { data |= m_in_pb_cb(0) & ~m_ddr[port];}
=======
inline uint8_t i8355_device::read_port(int port)
{
	uint8_t data = m_output[port] & m_ddr[port];

	if (m_ddr[port] != 0xff)
	{
		if (port == 0) { data |= m_in_pa_cb(0) & ~m_ddr[port]; }
		else { data |= m_in_pb_cb(0) & ~m_ddr[port]; }
>>>>>>> upstream/master
	}

	return data;
}


//-------------------------------------------------
//  write_port - write to output port
//-------------------------------------------------

<<<<<<< HEAD
inline void i8355_device::write_port(int port, UINT8 data)
=======
inline void i8355_device::write_port(int port, uint8_t data)
>>>>>>> upstream/master
{
	m_output[port] = data;

	if (port == 0) {m_out_pa_cb((offs_t)0, m_output[port] & m_ddr[port]);}
	else {m_out_pb_cb((offs_t)0, m_output[port] & m_ddr[port]);}
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  i8355_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
i8355_device::i8355_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, I8355, "Intel 8355", tag, owner, clock, "i8355", __FILE__),
		device_memory_interface(mconfig, *this),
=======
i8355_device::i8355_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, I8355, tag, owner, clock),
>>>>>>> upstream/master
		m_in_pa_cb(*this),
		m_out_pa_cb(*this),
		m_in_pb_cb(*this),
		m_out_pb_cb(*this),
<<<<<<< HEAD
		m_space_config("ram", ENDIANNESS_LITTLE, 8, 11, 0, NULL, *ADDRESS_MAP_NAME(i8355))
=======
		m_rom(*this, DEVICE_SELF, 0x800)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void i8355_device::device_start()
{
	// resolve callbacks
	m_in_pa_cb.resolve_safe(0);
	m_in_pb_cb.resolve_safe(0);
	m_out_pa_cb.resolve_safe();
	m_out_pb_cb.resolve_safe();

	// register for state saving
	save_item(NAME(m_output));
	save_item(NAME(m_ddr));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void i8355_device::device_reset()
{
	// set ports to input mode
	m_ddr[PORT_A] = 0;
	m_ddr[PORT_B] = 0;
}


//-------------------------------------------------
<<<<<<< HEAD
//  memory_space_config - return a description of
//  any address spaces owned by this device
//-------------------------------------------------

const address_space_config *i8355_device::memory_space_config(address_spacenum spacenum) const
{
	return (spacenum == AS_0) ? &m_space_config : NULL;
}



//-------------------------------------------------
=======
>>>>>>> upstream/master
//  io_r - register read
//-------------------------------------------------

READ8_MEMBER( i8355_device::io_r )
{
	int port = offset & 0x01;

<<<<<<< HEAD
	UINT8 data = 0;
=======
	uint8_t data = 0;
>>>>>>> upstream/master

	switch (offset & 0x03)
	{
	case REGISTER_PORT_A:
	case REGISTER_PORT_B:
		data = read_port(port);
		break;

	case REGISTER_PORT_A_DDR:
	case REGISTER_PORT_B_DDR:
		// write only
		break;
	}

	return data;
}


//-------------------------------------------------
//  io_w - register write
//-------------------------------------------------

WRITE8_MEMBER( i8355_device::io_w )
{
	int port = offset & 0x01;

	switch (offset & 0x03)
	{
	case REGISTER_PORT_A:
	case REGISTER_PORT_B:
<<<<<<< HEAD
		if (LOG) logerror("I8355 '%s' Port %c Write %02x\n", tag(), 'A' + port, data);
=======
		LOG("I8355 Port %c Write %02x\n", 'A' + port, data);
>>>>>>> upstream/master

		write_port(port, data);
		break;

	case REGISTER_PORT_A_DDR:
	case REGISTER_PORT_B_DDR:
<<<<<<< HEAD
		if (LOG) logerror("I8355 '%s' Port %c DDR: %02x\n", tag(), 'A' + port, data);
=======
		LOG("I8355 Port %c DDR: %02x\n", 'A' + port, data);
>>>>>>> upstream/master

		m_ddr[port] = data;
		write_port(port, data);
		break;
	}
}


//-------------------------------------------------
//  memory_r - internal ROM read
//-------------------------------------------------

READ8_MEMBER( i8355_device::memory_r )
{
<<<<<<< HEAD
	return this->space().read_byte(offset);
=======
	return m_rom[offset];
>>>>>>> upstream/master
}
