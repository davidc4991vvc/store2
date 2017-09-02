// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Curt Coder
/**********************************************************************

    MOS 6581/8580 Sound Interface Device emulation

**********************************************************************/

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "mos6581.h"
#include "sid.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define LOG 0



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

// device type definition
<<<<<<< HEAD
const device_type MOS6581 = &device_creator<mos6581_device>;
const device_type MOS8580 = &device_creator<mos8580_device>;
=======
DEFINE_DEVICE_TYPE(MOS6581, mos6581_device, "mos6581", "MOS 6581 SID")
DEFINE_DEVICE_TYPE(MOS8580, mos8580_device, "mos8580", "MOS 8580 SID")
>>>>>>> upstream/master



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  mos6581_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
mos6581_device::mos6581_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, const char *shortname, const char *source)
	: device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_sound_interface(mconfig, *this),
		m_read_potx(*this),
		m_read_poty(*this),
		m_stream(NULL),
		m_variant(variant)
{
	m_token = global_alloc_clear(SID6581_t);
}

mos6581_device::mos6581_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MOS6581, "MOS6581", tag, owner, clock, "mos6581", __FILE__),
		device_sound_interface(mconfig, *this),
		m_read_potx(*this),
		m_read_poty(*this),
		m_stream(NULL),
		m_variant(TYPE_6581)
{
	m_token = global_alloc_clear(SID6581_t);
=======
mos6581_device::mos6581_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, uint32_t variant)
	: device_t(mconfig, type, tag, owner, clock)
	, device_sound_interface(mconfig, *this)
	, m_read_potx(*this)
	, m_read_poty(*this)
	, m_stream(nullptr)
	, m_variant(variant)
	, m_token(make_unique_clear<SID6581_t>())

{
}

mos6581_device::mos6581_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: mos6581_device(mconfig, MOS6581, tag, owner, clock, TYPE_6581)
{
>>>>>>> upstream/master
}

mos6581_device::~mos6581_device()
{
<<<<<<< HEAD
	global_free(m_token);
=======
>>>>>>> upstream/master
}

//-------------------------------------------------
//  mos8580_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
mos8580_device::mos8580_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: mos6581_device(mconfig, MOS8580, "MOS8580", tag, owner, clock, TYPE_8580, "mos8580", __FILE__)
=======
mos8580_device::mos8580_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: mos6581_device(mconfig, MOS8580, tag, owner, clock, TYPE_8580)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void mos6581_device::device_start()
{
	// resolve callbacks
	m_read_potx.resolve_safe(0xff);
	m_read_poty.resolve_safe(0xff);

	// create sound stream
	m_stream = machine().sound().stream_alloc(*this, 0, 1, machine().sample_rate());

	// initialize SID engine
	m_token->device = this;
	m_token->mixer_channel = m_stream;
	m_token->PCMfreq = machine().sample_rate();
	m_token->clock = clock();
	m_token->type = m_variant;

<<<<<<< HEAD
	sid6581_init(m_token);
=======
	m_token->init();
>>>>>>> upstream/master
	sidInitWaveformTables(m_variant);
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void mos6581_device::device_reset()
{
<<<<<<< HEAD
	sidEmuReset(m_token);
=======
	m_token->reset();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  sound_stream_update - handle update requests for
//  our sound stream
//-------------------------------------------------

void mos6581_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
<<<<<<< HEAD
	sidEmuFillBuffer(m_token, outputs[0], samples);
=======
	m_token->fill_buffer(outputs[0], samples);
>>>>>>> upstream/master
}


//-------------------------------------------------
//  read -
//-------------------------------------------------

READ8_MEMBER( mos6581_device::read )
{
<<<<<<< HEAD
	UINT8 data = 0;
=======
	uint8_t data;
>>>>>>> upstream/master

	switch (offset & 0x1f)
	{
	case 0x19:
		data = m_read_potx(0);
		break;

	case 0x1a:
		data = m_read_poty(0);
		break;

	default:
<<<<<<< HEAD
		data = sid6581_port_r(machine(), m_token, offset);
=======
		data = m_token->port_r(machine(), offset);
>>>>>>> upstream/master
		break;
	}

	return data;
}


//-------------------------------------------------
//  write -
//-------------------------------------------------

WRITE8_MEMBER( mos6581_device::write )
{
<<<<<<< HEAD
	sid6581_port_w(m_token, offset, data);
=======
	m_token->port_w(offset, data);
>>>>>>> upstream/master
}
