// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    midiout.c

    MIDI Out image device and serial receiver

*********************************************************************/

#include "emu.h"
#include "osdepend.h"
#include "midiout.h"

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

<<<<<<< HEAD
const device_type MIDIOUT = &device_creator<midiout_device>;
=======
DEFINE_DEVICE_TYPE(MIDIOUT, midiout_device, "midiout", "MIDI Out image device")
>>>>>>> upstream/master

/*-------------------------------------------------
    ctor
-------------------------------------------------*/

<<<<<<< HEAD
midiout_device::midiout_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MIDIOUT, "MIDI Out image device", tag, owner, clock, "midiout", __FILE__),
		device_image_interface(mconfig, *this),
		device_serial_interface(mconfig, *this),
		m_midi(NULL)
=======
midiout_device::midiout_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, MIDIOUT, tag, owner, clock),
		device_image_interface(mconfig, *this),
		device_serial_interface(mconfig, *this),
		m_midi(nullptr)
>>>>>>> upstream/master
{
}

/*-------------------------------------------------
    device_start
-------------------------------------------------*/

void midiout_device::device_start()
{
<<<<<<< HEAD
	m_midi = NULL;
=======
	m_midi = nullptr;
>>>>>>> upstream/master
}

void midiout_device::device_reset()
{
	// we don't Tx, we Rx at 31250 8-N-1
	set_data_frame(1, 8, PARITY_NONE, STOP_BITS_1);
	set_rcv_rate(31250);
	set_tra_rate(0);
}

<<<<<<< HEAD
void midiout_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	device_serial_interface::device_timer(timer, id, param, ptr);
}

/*-------------------------------------------------
    device_config_complete
-------------------------------------------------*/

void midiout_device::device_config_complete(void)
{
	update_names();
}

=======
>>>>>>> upstream/master
/*-------------------------------------------------
    call_load
-------------------------------------------------*/

<<<<<<< HEAD
bool midiout_device::call_load(void)
=======
image_init_result midiout_device::call_load(void)
>>>>>>> upstream/master
{
	m_midi = machine().osd().create_midi_device();

	if (!m_midi->open_output(filename()))
	{
		global_free(m_midi);
<<<<<<< HEAD
		m_midi = NULL;
		return IMAGE_INIT_FAIL;
	}

	return IMAGE_INIT_PASS;
=======
		m_midi = nullptr;
		return image_init_result::FAIL;
	}

	return image_init_result::PASS;
>>>>>>> upstream/master
}

/*-------------------------------------------------
    call_unload
-------------------------------------------------*/

void midiout_device::call_unload(void)
{
	if (m_midi)
	{
		m_midi->close();
		global_free(m_midi);
<<<<<<< HEAD
		m_midi = NULL;
=======
		m_midi = nullptr;
>>>>>>> upstream/master
	}
}

void midiout_device::rcv_complete()    // Rx completed receiving byte
{
	receive_register_extract();
<<<<<<< HEAD
	UINT8 data = get_received_char();
=======
	uint8_t data = get_received_char();
>>>>>>> upstream/master

	if (m_midi)
	{
		m_midi->write(data);
	}
}
