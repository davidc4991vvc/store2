// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/**********************************************************************************************
 *
 *   OKI MSM6258 ADPCM
 *
 *   TODO:
 *   3-bit ADPCM support
 *   Recording?
 *
 **********************************************************************************************/


#include "emu.h"
#include "okim6258.h"

#define COMMAND_STOP        (1 << 0)
#define COMMAND_PLAY        (1 << 1)
#define COMMAND_RECORD      (1 << 2)

#define STATUS_PLAYING      (1 << 1)
#define STATUS_RECORDING    (1 << 2)

static const int dividers[4] = { 1024, 768, 512, 512 };

/* step size index shift table */
static const int index_shift[8] = { -1, -1, -1, -1, 2, 4, 6, 8 };

/* lookup table for the precomputed difference */
static int diff_lookup[49*16];

/* tables computed? */
static int tables_computed = 0;



// device type definition
<<<<<<< HEAD
const device_type OKIM6258 = &device_creator<okim6258_device>;
=======
DEFINE_DEVICE_TYPE(OKIM6258, okim6258_device, "okim6258", "OKI MSM6258 ADPCM")
>>>>>>> upstream/master


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  okim6258_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
okim6258_device::okim6258_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, OKIM6258, "OKI6258", tag, owner, clock, "okim6258", __FILE__),
		device_sound_interface(mconfig, *this),
		m_status(0),
		m_master_clock(0),
		m_divider(0),
		m_adpcm_type(0),
		m_data_in(0),
		m_nibble_shift(0),
		m_stream(NULL),
=======
okim6258_device::okim6258_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, OKIM6258, tag, owner, clock),
		device_sound_interface(mconfig, *this),
		m_status(0),
		m_divider(512),
		m_adpcm_type(0),
		m_data_in(0),
		m_nibble_shift(0),
		m_stream(nullptr),
>>>>>>> upstream/master
		m_output_bits(0),
		m_signal(0),
		m_step(0)
{
}



/**********************************************************************************************

     compute_tables -- compute the difference tables

***********************************************************************************************/

<<<<<<< HEAD
static void compute_tables(void)
=======
static void compute_tables()
>>>>>>> upstream/master
{
	/* nibble to bit map */
	static const int nbl2bit[16][4] =
	{
		{ 1, 0, 0, 0}, { 1, 0, 0, 1}, { 1, 0, 1, 0}, { 1, 0, 1, 1},
		{ 1, 1, 0, 0}, { 1, 1, 0, 1}, { 1, 1, 1, 0}, { 1, 1, 1, 1},
		{-1, 0, 0, 0}, {-1, 0, 0, 1}, {-1, 0, 1, 0}, {-1, 0, 1, 1},
		{-1, 1, 0, 0}, {-1, 1, 0, 1}, {-1, 1, 1, 0}, {-1, 1, 1, 1}
	};

	int step, nib;

	/* loop over all possible steps */
	for (step = 0; step <= 48; step++)
	{
		/* compute the step value */
		int stepval = floor(16.0 * pow(11.0 / 10.0, (double)step));

		/* loop over all nibbles and compute the difference */
		for (nib = 0; nib < 16; nib++)
		{
			diff_lookup[step*16 + nib] = nbl2bit[nib][0] *
				(stepval   * nbl2bit[nib][1] +
					stepval/2 * nbl2bit[nib][2] +
					stepval/4 * nbl2bit[nib][3] +
					stepval/8);
		}
	}

	tables_computed = 1;
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void okim6258_device::device_start()
{
	compute_tables();

<<<<<<< HEAD
	m_master_clock = clock();

=======
>>>>>>> upstream/master
	m_divider = dividers[m_start_divider];

	m_stream = stream_alloc(0, 1, clock()/m_divider);

	m_signal = -2;
	m_step = 0;

<<<<<<< HEAD
	okim6258_state_save_register();
=======
	state_save_register();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void okim6258_device::device_reset()
{
	m_stream->update();

	m_signal = -2;
	m_step = 0;
	m_status = 0;
}


//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------

void okim6258_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	stream_sample_t *buffer = outputs[0];

	memset(outputs[0], 0, samples * sizeof(*outputs[0]));

	if (m_status & STATUS_PLAYING)
	{
		int nibble_shift = m_nibble_shift;

		while (samples)
		{
			/* Compute the new amplitude and update the current step */
			int nibble = (m_data_in >> nibble_shift) & 0xf;

			/* Output to the buffer */
<<<<<<< HEAD
			INT16 sample = clock_adpcm(nibble);
=======
			int16_t sample = clock_adpcm(nibble);
>>>>>>> upstream/master

			nibble_shift ^= 4;

			*buffer++ = sample;
			samples--;
		}

		/* Update the parameters */
		m_nibble_shift = nibble_shift;
	}
	else
	{
		/* Fill with 0 */
		while (samples--)
			*buffer++ = 0;
	}
}



/**********************************************************************************************

     state save support for MAME

***********************************************************************************************/

<<<<<<< HEAD
void okim6258_device::okim6258_state_save_register()
{
	save_item(NAME(m_status));
	save_item(NAME(m_master_clock));
=======
void okim6258_device::state_save_register()
{
	save_item(NAME(m_status));
>>>>>>> upstream/master
	save_item(NAME(m_divider));
	save_item(NAME(m_data_in));
	save_item(NAME(m_nibble_shift));
	save_item(NAME(m_signal));
	save_item(NAME(m_step));
}


<<<<<<< HEAD
INT16 okim6258_device::clock_adpcm(UINT8 nibble)
{
	INT32 max = (1 << (m_output_bits - 1)) - 1;
	INT32 min = -(1 << (m_output_bits - 1));
=======
int16_t okim6258_device::clock_adpcm(uint8_t nibble)
{
	int32_t max = (1 << (m_output_bits - 1)) - 1;
	int32_t min = -(1 << (m_output_bits - 1));
>>>>>>> upstream/master

	m_signal += diff_lookup[m_step * 16 + (nibble & 15)];

	/* clamp to the maximum */
	if (m_signal > max)
		m_signal = max;
	else if (m_signal < min)
		m_signal = min;

	/* adjust the step size and clamp */
	m_step += index_shift[nibble & 7];
	if (m_step > 48)
		m_step = 48;
	else if (m_step < 0)
		m_step = 0;

	/* return the signal scaled up to 32767 */
	return m_signal << 4;
}


/**********************************************************************************************

     okim6258::set_divider -- set the master clock divider

***********************************************************************************************/

void okim6258_device::set_divider(int val)
{
<<<<<<< HEAD
	int divider = dividers[val];

	m_divider = dividers[val];
	m_stream->set_sample_rate(m_master_clock / divider);
=======
	m_divider = dividers[val];
	notify_clock_changed();
>>>>>>> upstream/master
}


/**********************************************************************************************

     okim6258::set_clock -- set the master clock

***********************************************************************************************/

<<<<<<< HEAD
void okim6258_device::set_clock(int val)
{
	m_master_clock = val;
	m_stream->set_sample_rate(m_master_clock / m_divider);
=======
void okim6258_device::device_clock_changed()
{
	m_stream->set_sample_rate(clock() / m_divider);
>>>>>>> upstream/master
}


/**********************************************************************************************

     okim6258::get_vclk -- get the VCLK/sampling frequency

***********************************************************************************************/

int okim6258_device::get_vclk()
{
<<<<<<< HEAD
	return (m_master_clock / m_divider);
=======
	return (clock() / m_divider);
>>>>>>> upstream/master
}


/**********************************************************************************************

     okim6258_status_r -- read the status port of an OKIM6258-compatible chip

***********************************************************************************************/

<<<<<<< HEAD
READ8_MEMBER( okim6258_device::okim6258_status_r )
=======
READ8_MEMBER( okim6258_device::status_r )
>>>>>>> upstream/master
{
	m_stream->update();

	return (m_status & STATUS_PLAYING) ? 0x00 : 0x80;
}


/**********************************************************************************************

     okim6258_data_w -- write to the control port of an OKIM6258-compatible chip

***********************************************************************************************/
<<<<<<< HEAD
WRITE8_MEMBER( okim6258_device::okim6258_data_w )
=======
WRITE8_MEMBER( okim6258_device::data_w )
>>>>>>> upstream/master
{
	/* update the stream */
	m_stream->update();

	m_data_in = data;
	m_nibble_shift = 0;
}


/**********************************************************************************************

     okim6258_ctrl_w -- write to the control port of an OKIM6258-compatible chip

***********************************************************************************************/

<<<<<<< HEAD
WRITE8_MEMBER( okim6258_device::okim6258_ctrl_w )
=======
WRITE8_MEMBER( okim6258_device::ctrl_w )
>>>>>>> upstream/master
{
	m_stream->update();

	if (data & COMMAND_STOP)
	{
		m_status &= ~(STATUS_PLAYING | STATUS_RECORDING);
		return;
	}

	if (data & COMMAND_PLAY)
	{
		if (!(m_status & STATUS_PLAYING))
		{
			m_status |= STATUS_PLAYING;

			/* Also reset the ADPCM parameters */
			m_signal = -2;
			m_step = 0;
			m_nibble_shift = 0;
		}
	}
	else
	{
		m_status &= ~STATUS_PLAYING;
	}

	if (data & COMMAND_RECORD)
	{
		logerror("M6258: Record enabled\n");
		m_status |= STATUS_RECORDING;
	}
	else
	{
		m_status &= ~STATUS_RECORDING;
	}
}
