// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    DMA-driven DAC driver
    by Aaron Giles

***************************************************************************/

#include "emu.h"
#include "dmadac.h"

<<<<<<< HEAD


/*************************************
 *
 *  Debugging
 *
 *************************************/

#define VERBOSE     0

#define LOG(x) do { if (VERBOSE) logerror x; } while (0)

=======
//#define VERBOSE 1
#include "logmacro.h"


>>>>>>> upstream/master

/*************************************
 *
 *  Constants
 *
 *************************************/

#define DEFAULT_SAMPLE_RATE         (44100)

#define BUFFER_SIZE                 32768


/*************************************
 *
 *  Sound hardware init
 *
 *************************************/

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void dmadac_sound_device::device_start()
{
	/* allocate a clear a buffer */
<<<<<<< HEAD
	m_buffer = auto_alloc_array_clear(machine(), INT16, BUFFER_SIZE);
=======
	m_buffer = make_unique_clear<int16_t[]>(BUFFER_SIZE);
>>>>>>> upstream/master

	/* reset the state */
	m_volume = 0x100;

	/* allocate a stream channel */
	m_channel = machine().sound().stream_alloc(*this, 0, 1, DEFAULT_SAMPLE_RATE);

	/* register with the save state system */
	save_item(NAME(m_bufin));
	save_item(NAME(m_bufout));
	save_item(NAME(m_volume));
	save_item(NAME(m_enabled));
	save_item(NAME(m_frequency));
<<<<<<< HEAD
	save_pointer(NAME(m_buffer), BUFFER_SIZE);
=======
	save_pointer(NAME(m_buffer.get()), BUFFER_SIZE);
>>>>>>> upstream/master
}



/*************************************
 *
 *  Primary transfer routine
 *
 *************************************/

<<<<<<< HEAD
void dmadac_transfer(dmadac_sound_device **devlist, UINT8 num_channels, offs_t channel_spacing, offs_t frame_spacing, offs_t total_frames, INT16 *data)
=======
void dmadac_transfer(dmadac_sound_device **devlist, uint8_t num_channels, offs_t channel_spacing, offs_t frame_spacing, offs_t total_frames, int16_t *data)
>>>>>>> upstream/master
{
	int i;

	/* flush out as much data as we can */
	for (i = 0; i < num_channels; i++)
	{
		devlist[i]->flush();
	}

	/* loop over all channels and accumulate the data */
	for (i = 0; i < num_channels; i++)
	{
		devlist[i]->transfer(i, channel_spacing, frame_spacing, total_frames, data);
	}
}

void dmadac_sound_device::flush()
{
	m_channel->update();
}

<<<<<<< HEAD
void dmadac_sound_device::transfer(int channel, offs_t channel_spacing, offs_t frame_spacing, offs_t total_frames, INT16 *data)
=======
void dmadac_sound_device::transfer(int channel, offs_t channel_spacing, offs_t frame_spacing, offs_t total_frames, int16_t *data)
>>>>>>> upstream/master
{
	int j;

	/* loop over all channels and accumulate the data */
	if (m_enabled)
	{
		int maxin = (m_bufout + BUFFER_SIZE - 1) % BUFFER_SIZE;
<<<<<<< HEAD
		INT16 *src = data + channel * channel_spacing;
=======
		int16_t *src = data + channel * channel_spacing;
>>>>>>> upstream/master
		int curin = m_bufin;

		/* copy the data */
		for (j = 0; j < total_frames && curin != maxin; j++)
		{
			m_buffer[curin] = *src;
			curin = (curin + 1) % BUFFER_SIZE;
			src += frame_spacing;
		}
		m_bufin = curin;

		/* log overruns */
		if (j != total_frames)
			logerror("dmadac_transfer: buffer overrun (short %d frames)\n", total_frames - j);
	}

<<<<<<< HEAD
	//LOG(("dmadac_transfer - %d samples, %d effective, %d in buffer\n", total_frames, (int)(total_frames * (double)DEFAULT_SAMPLE_RATE / dmadac[first_channel].frequency), dmadac[first_channel].curinpos - dmadac[first_channel].curoutpos));
=======
	// FIXME: this line has rotted and can no longer compile - it should be fixed and uncommented or removed
	//LOG("dmadac_transfer - %d samples, %d effective, %d in buffer\n", total_frames, int(total_frames * double(DEFAULT_SAMPLE_RATE) / dmadac[first_channel].frequency), dmadac[first_channel].curinpos - dmadac[first_channel].curoutpos);
>>>>>>> upstream/master
}



/*************************************
 *
 *  Enable/disable DMA channel(s)
 *
 *************************************/

<<<<<<< HEAD
void dmadac_enable(dmadac_sound_device **devlist, UINT8 num_channels, UINT8 enable)
=======
void dmadac_enable(dmadac_sound_device **devlist, uint8_t num_channels, uint8_t enable)
>>>>>>> upstream/master
{
	int i;

	/* flush out as much data as we can */
	for (i = 0; i < num_channels; i++)
	{
<<<<<<< HEAD
		devlist[i]->enable(enable);
=======
		if (devlist[i])
			devlist[i]->enable(enable);
>>>>>>> upstream/master
	}
}


<<<<<<< HEAD
void dmadac_sound_device::enable(UINT8 enable)
=======
void dmadac_sound_device::enable(uint8_t enable)
>>>>>>> upstream/master
{
	m_channel->update();
	m_enabled = enable;
	if (!enable)
		m_bufin = m_bufout = 0;
}

/*************************************
 *
 *  Set the frequency on DMA channel(s)
 *
 *************************************/

<<<<<<< HEAD
void dmadac_set_frequency(dmadac_sound_device **devlist, UINT8 num_channels, double frequency)
=======
void dmadac_set_frequency(dmadac_sound_device **devlist, uint8_t num_channels, double frequency)
>>>>>>> upstream/master
{
	int i;

	/* set the sample rate on each channel */
	for (i = 0; i < num_channels; i++)
	{
		devlist[i]->set_frequency(frequency);
	}
}


void dmadac_sound_device::set_frequency(double frequency)
{
	m_channel->set_sample_rate(frequency);
}

/*************************************
 *
 *  Set the volume on DMA channel(s)
 *
 *************************************/

<<<<<<< HEAD
void dmadac_set_volume(dmadac_sound_device **devlist, UINT8 num_channels, UINT16 volume)
=======
void dmadac_set_volume(dmadac_sound_device **devlist, uint8_t num_channels, uint16_t volume)
>>>>>>> upstream/master
{
	int i;

	/* flush out as much data as we can */
	for (i = 0; i < num_channels; i++)
	{
		devlist[i]->set_volume(volume);
	}
}

<<<<<<< HEAD
void dmadac_sound_device::set_volume(UINT16 volume)
=======
void dmadac_sound_device::set_volume(uint16_t volume)
>>>>>>> upstream/master
{
	m_channel->update();
	m_volume = volume;
}

<<<<<<< HEAD
const device_type DMADAC = &device_creator<dmadac_sound_device>;

dmadac_sound_device::dmadac_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, DMADAC, "DMA-driven DAC", tag, owner, clock, "dmadac", __FILE__),
		device_sound_interface(mconfig, *this),
		m_buffer(NULL),
=======
DEFINE_DEVICE_TYPE(DMADAC, dmadac_sound_device, "dmadac", "DMA-driven DAC")

dmadac_sound_device::dmadac_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, DMADAC, tag, owner, clock),
		device_sound_interface(mconfig, *this),
		m_buffer(nullptr),
>>>>>>> upstream/master
		m_bufin(0),
		m_bufout(0),
		m_volume(0),
		m_enabled(0),
		m_frequency(0)
{
}

//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------

void dmadac_sound_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	stream_sample_t *output = outputs[0];
<<<<<<< HEAD
	INT16 *source = m_buffer;
	UINT32 curout = m_bufout;
	UINT32 curin = m_bufin;
=======
	int16_t *source = m_buffer.get();
	uint32_t curout = m_bufout;
	uint32_t curin = m_bufin;
>>>>>>> upstream/master
	int volume = m_volume;

	/* feed as much as we can */
	while (curout != curin && samples-- > 0)
	{
		*output++ = (source[curout] * volume) >> 8;
		curout = (curout + 1) % BUFFER_SIZE;
	}

	/* fill the rest with silence */
	while (samples-- > 0)
		*output++ = 0;

	/* save the new output pointer */
	m_bufout = curout;
}
