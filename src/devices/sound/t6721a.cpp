// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Toshiba T6721A C2MOS Voice Synthesizing LSI emulation

**********************************************************************/

<<<<<<< HEAD
#include "t6721a.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0
=======
#include "emu.h"
#include "t6721a.h"

//#define VERBOSE 1
#include "logmacro.h"
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type T6721A = &device_creator<t6721a_device>;
=======
DEFINE_DEVICE_TYPE(T6721A, t6721a_device, "t6721a", "Toshiba T6721A")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  t6721a_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
t6721a_device::t6721a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, T6721A, "T6721A", tag, owner, clock, "t6721a", __FILE__),
=======
t6721a_device::t6721a_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, T6721A, tag, owner, clock),
>>>>>>> upstream/master
		device_sound_interface(mconfig, *this),
		m_write_eos(*this),
		m_write_phi2(*this),
		m_write_dtrd(*this),
		m_write_apd(*this),
<<<<<<< HEAD
		m_stream(NULL)
=======
		m_stream(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void t6721a_device::device_start()
{
	// resolve callbacks
	m_write_eos.resolve_safe();
	m_write_phi2.resolve_safe();
	m_write_dtrd.resolve_safe();
	m_write_apd.resolve_safe();

	// create sound stream
	m_stream = machine().sound().stream_alloc(*this, 0, 1, machine().sample_rate());
}


//-------------------------------------------------
//  sound_stream_update - handle update requests for
//  our sound stream
//-------------------------------------------------

void t6721a_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

READ8_MEMBER( t6721a_device::read )
{
	return 0;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

WRITE8_MEMBER( t6721a_device::write )
{
}


//-------------------------------------------------
//  di_w - data input write
//-------------------------------------------------

WRITE_LINE_MEMBER( t6721a_device::di_w )
{
}


//-------------------------------------------------
//  eos_r - eos read
//-------------------------------------------------

READ_LINE_MEMBER( t6721a_device::eos_r )
{
	return 1;
}
