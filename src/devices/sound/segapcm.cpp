// license:BSD-3-Clause
// copyright-holders:Hiromitsu Shioya, Olivier Galibert
/*********************************************************/
/*    SEGA 16ch 8bit PCM                                 */
/*********************************************************/

#include "emu.h"
#include "segapcm.h"


// device type definition
<<<<<<< HEAD
const device_type SEGAPCM = &device_creator<segapcm_device>;
=======
DEFINE_DEVICE_TYPE(SEGAPCM, segapcm_device, "segapcm", "Sega PCM")
>>>>>>> upstream/master


//-------------------------------------------------
//  segapcm_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
segapcm_device::segapcm_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, SEGAPCM, "Sega PCM", tag, owner, clock, "segapcm", __FILE__),
		device_sound_interface(mconfig, *this),
		m_rom(*this, DEVICE_SELF),
		m_ram(NULL),
		m_bank(0),
		m_bankshift(0),
		m_bankmask(0),
		m_stream(NULL)
=======
segapcm_device::segapcm_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, SEGAPCM, tag, owner, clock),
		device_sound_interface(mconfig, *this),
		device_rom_interface(mconfig, *this, 21),
		m_ram(nullptr),
		m_bank(0),
		m_bankshift(0),
		m_bankmask(0),
		m_stream(nullptr)
>>>>>>> upstream/master
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void segapcm_device::device_start()
{
<<<<<<< HEAD
	int mask, rom_mask;

	m_ram = auto_alloc_array(machine(), UINT8, 0x800);

	memset(m_ram, 0xff, 0x800);

	m_bankshift = (UINT8) m_bank;
=======
	int mask;

	m_ram = std::make_unique<uint8_t[]>(0x800);

	memset(m_ram.get(), 0xff, 0x800);

	m_bankshift = (uint8_t) m_bank;
>>>>>>> upstream/master
	mask = m_bank >> 16;
	if (!mask)
		mask = BANK_MASK7 >> 16;

<<<<<<< HEAD
	for(rom_mask = 1; rom_mask < m_rom.length(); rom_mask *= 2);
	rom_mask--;

	m_bankmask = mask & (rom_mask >> m_bankshift);
=======
	m_bankmask = mask & (0x1fffff >> m_bankshift);
>>>>>>> upstream/master

	m_stream = stream_alloc(0, 2, clock() / 128);

	save_item(NAME(m_low));
<<<<<<< HEAD
	save_pointer(NAME(m_ram), 0x800);
=======
	save_pointer(NAME(m_ram.get()), 0x800);
}



//-------------------------------------------------
//  rom_bank_updated - the rom bank has changed
//-------------------------------------------------

void segapcm_device::rom_bank_updated()
{
	m_stream->update();
>>>>>>> upstream/master
}


//-------------------------------------------------
//  sound_stream_update - handle a stream update
//-------------------------------------------------

void segapcm_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	/* clear the buffers */
	memset(outputs[0], 0, samples*sizeof(*outputs[0]));
	memset(outputs[1], 0, samples*sizeof(*outputs[1]));

	// reg      function
	// ------------------------------------------------
	// 0x00     ?
	// 0x01     ?
	// 0x02     volume left
	// 0x03     volume right
	// 0x04     loop address (08-15)
	// 0x05     loop address (16-23)
	// 0x06     end address
	// 0x07     address delta
	// 0x80     ?
	// 0x81     ?
	// 0x82     ?
	// 0x83     ?
	// 0x84     current address (08-15), 00-07 is internal?
	// 0x85     current address (16-23)
	// 0x86     bit 0: channel disable?
	//          bit 1: loop disable
	//          other bits: bank
	// 0x87     ?

	/* loop over channels */
	for (int ch = 0; ch < 16; ch++)
	{
<<<<<<< HEAD
		UINT8 *regs = m_ram+8*ch;
=======
		uint8_t *regs = m_ram.get()+8*ch;
>>>>>>> upstream/master

		/* only process active channels */
		if (!(regs[0x86]&1))
		{
<<<<<<< HEAD
			const UINT8 *rom = m_rom + ((regs[0x86] & m_bankmask) << m_bankshift);
			UINT32 addr = (regs[0x85] << 16) | (regs[0x84] << 8) | m_low[ch];
			UINT32 loop = (regs[0x05] << 16) | (regs[0x04] << 8);
			UINT8 end = regs[6] + 1;
=======
			int offset = (regs[0x86] & m_bankmask) << m_bankshift;
			uint32_t addr = (regs[0x85] << 16) | (regs[0x84] << 8) | m_low[ch];
			uint32_t loop = (regs[0x05] << 16) | (regs[0x04] << 8);
			uint8_t end = regs[6] + 1;
>>>>>>> upstream/master
			int i;

			/* loop over samples on this channel */
			for (i = 0; i < samples; i++)
			{
<<<<<<< HEAD
				INT8 v = 0;
=======
				int8_t v;
>>>>>>> upstream/master

				/* handle looping if we've hit the end */
				if ((addr >> 16) == end)
				{
					if (regs[0x86] & 2)
					{
						regs[0x86] |= 1;
						break;
					}
					else addr = loop;
				}

				/* fetch the sample */
<<<<<<< HEAD
				v = rom[(addr >> 8) & m_rom.mask()] - 0x80;
=======
				v = read_byte(offset + (addr >> 8)) - 0x80;
>>>>>>> upstream/master

				/* apply panning and advance */
				outputs[0][i] += v * (regs[2] & 0x7f);
				outputs[1][i] += v * (regs[3] & 0x7f);
				addr = (addr + regs[7]) & 0xffffff;
			}

			/* store back the updated address */
			regs[0x84] = addr >> 8;
			regs[0x85] = addr >> 16;
			m_low[ch] = regs[0x86] & 1 ? 0 : addr;
		}
	}
}


WRITE8_MEMBER( segapcm_device::sega_pcm_w )
{
	m_stream->update();
	m_ram[offset & 0x07ff] = data;
}


READ8_MEMBER( segapcm_device::sega_pcm_r )
{
	m_stream->update();
	return m_ram[offset & 0x07ff];
}
