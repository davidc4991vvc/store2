<<<<<<< HEAD
=======
// license:BSD-3-Clause
// copyright-holders:Angelo Salese
>>>>>>> upstream/master
/* Sega 315-5641 / D77591 / 9442CA010 */

#include "emu.h"
#include "315-5641.h"

<<<<<<< HEAD
const device_type SEGA_315_5641_PCM = &device_creator<sega_315_5641_pcm_device>;

sega_315_5641_pcm_device::sega_315_5641_pcm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: upd7759_device(mconfig, SEGA_315_5641_PCM, "315-5641 PCM", tag, owner, clock, "315-5641_pcm", __FILE__), m_fifo_read(0), m_fifo_write(0)
=======
DEFINE_DEVICE_TYPE(SEGA_315_5641_PCM, sega_315_5641_pcm_device, "315_5641_pcm", "Sega 315-5641 PCM")

sega_315_5641_pcm_device::sega_315_5641_pcm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: upd7759_device(mconfig, SEGA_315_5641_PCM, tag, owner, clock), m_fifo_read(0), m_fifo_write(0)
>>>>>>> upstream/master
{
}

void sega_315_5641_pcm_device::device_start()
{
	save_item(NAME(m_fifo_data), 0x40);
	save_item(NAME(m_fifo_read));
	save_item(NAME(m_fifo_write));

	upd7759_device::device_start();
}

void sega_315_5641_pcm_device::advance_state()
{
	switch (m_state)
	{
		case STATE_DROP_DRQ:
<<<<<<< HEAD
			if (m_rombase == NULL)
			{
				// Slave Mode: get data from FIFO buffer
				UINT8 fiforead = (m_fifo_read + 1) & 0x3F;
=======
			if (m_rombase == nullptr)
			{
				// Slave Mode: get data from FIFO buffer
				uint8_t fiforead = (m_fifo_read + 1) & 0x3F;
>>>>>>> upstream/master
				if (fiforead != m_fifo_write)
				{
					m_fifo_in = m_fifo_data[fiforead];
					m_fifo_read = fiforead;
				}
			}
			break;
	}

	upd775x_device::advance_state();
}


WRITE8_MEMBER( sega_315_5641_pcm_device::port_w )
{
<<<<<<< HEAD
	if (m_rombase != NULL)
=======
	if (m_rombase != nullptr)
>>>>>>> upstream/master
	{
		/* update the FIFO value */
		m_fifo_in = data;
	}
	else
	{
		m_fifo_data[m_fifo_write++] = data;
		m_fifo_write &= 0x3F;
	}
}


<<<<<<< HEAD
UINT8 sega_315_5641_pcm_device::get_fifo_space()
=======
uint8_t sega_315_5641_pcm_device::get_fifo_space()
>>>>>>> upstream/master
{
	return (m_fifo_read - m_fifo_write) & 0x3F;
}

void sega_315_5641_pcm_device::device_reset()
{
	m_fifo_read          = 0x3F;
	m_fifo_write         = 0x00;

	upd775x_device::device_reset();
}
