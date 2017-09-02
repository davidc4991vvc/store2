// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:R. Belmont
/*
    c352.c - Namco C352 custom PCM chip emulation
    v1.2
    By R. Belmont
=======
// copyright-holders:R. Belmont, superctr
/*
    c352.c - Namco C352 custom PCM chip emulation
    v2.0
    By R. Belmont
    Rewritten and improved by superctr
>>>>>>> upstream/master
    Additional code by cync and the hoot development team

    Thanks to Cap of VivaNonno for info and The_Author for preliminary reverse-engineering

    Chip specs:
    32 voices
    Supports 8-bit linear and 8-bit muLaw samples
    Output: digital, 16 bit, 4 channels
    Output sample rate is the input clock / (288 * 2).
<<<<<<< HEAD

    superctr: The clock divider appears to be configurable for each system.
    Below is a list of the divider values followed by the systems that use it.

    * 228: System 11.
    * 288: System 22, Super 22, NB-1/2, ND-1, FL.
    * 296: System 23, Super 23.
    * 332: System 12.
=======
>>>>>>> upstream/master
 */

#include "emu.h"
#include "c352.h"

<<<<<<< HEAD
#define VERBOSE (0)
#define LOG(x) do { if (VERBOSE) logerror x; } while (0)

// device type definition
const device_type C352 = &device_creator<c352_device>;

// default address map
static ADDRESS_MAP_START( c352, AS_0, 8, c352_device )
	AM_RANGE(0x000000, 0xffffff) AM_ROM
ADDRESS_MAP_END
=======
//#define VERBOSE 1
#include "logmacro.h"


// device type definition
DEFINE_DEVICE_TYPE(C352, c352_device, "c352", "Namco C352")
>>>>>>> upstream/master

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c352_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
c352_device::c352_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, C352, "C352", tag, owner, clock, "c352", __FILE__),
		device_sound_interface(mconfig, *this),
		device_memory_interface(mconfig, *this),
		m_space_config("samples", ENDIANNESS_LITTLE, 8, 24, 0, NULL, *ADDRESS_MAP_NAME(c352))
{
}

//-------------------------------------------------
//  static_set_dividder - configuration helper to
//  set the divider setting
//-------------------------------------------------

void c352_device::static_set_divider(device_t &device, int setting)
{
	c352_device &c352 = downcast<c352_device &>(device);
	c352.m_divider = setting;
}

//-------------------------------------------------
//  memory_space_config - return a description of
//  any address spaces owned by this device
//-------------------------------------------------

const address_space_config *c352_device::memory_space_config(address_spacenum spacenum) const
{
	return (spacenum == 0) ? &m_space_config : NULL;
}

// noise generator
int c352_device::get_mseq_bit()
{
	unsigned int mask = (1 << (7 - 1));
	unsigned int reg = m_mseq_reg;
	unsigned int bit = reg & (1 << (17 - 1));

	if (bit)
	{
		reg = ((reg ^ mask) << 1) | 1;
	}
	else
	{
		reg = reg << 1;
	}

	m_mseq_reg = reg;

	return (reg & 1);
}

void c352_device::mix_one_channel(unsigned long ch, long sample_count)
{
	int i;

	signed short sample, nextsample;
	signed short noisebuf;
	UINT16 noisecnt;
	INT32 frequency, delta, offset, cnt, flag;
	UINT32 bank;
	UINT32 pos;

	frequency = m_c352_ch[ch].pitch;
	delta=frequency;

	pos = m_c352_ch[ch].current_addr;   // sample pointer
	offset = m_c352_ch[ch].pos; // 16.16 fixed-point offset into the sample
	flag = m_c352_ch[ch].flag;
	bank = m_c352_ch[ch].bank << 16;

	noisecnt = m_c352_ch[ch].noisecnt;
	noisebuf = m_c352_ch[ch].noisebuf;

	for(i = 0 ; (i < sample_count) && (flag & C352_FLG_BUSY) ; i++)
	{
		offset += delta;
		cnt = (offset>>16)&0x7fff;
		if (cnt)            // if there is a whole sample part, chop it off now that it's been applied
		{
			offset &= 0xffff;
		}

		if (pos > 0x1000000)
		{
			m_c352_ch[ch].flag &= ~C352_FLG_BUSY;
			return;
		}

		sample = (char)m_direct->read_byte(pos);
		nextsample = (char)m_direct->read_byte(pos+cnt);

		// sample is muLaw, not 8-bit linear (Fighting Layer uses this extensively)
		if (flag & C352_FLG_MULAW)
		{
			sample = m_mulaw_table[(unsigned char)sample];
			nextsample = m_mulaw_table[(unsigned char)nextsample];
		}
		else
		{
			sample <<= 8;
			nextsample <<= 8;
		}

		// play noise instead of sample data
		if (flag & C352_FLG_NOISE)
		{
			int noise_level = 0x8000;
			sample = m_c352_ch[ch].noise = (m_c352_ch[ch].noise << 1) | get_mseq_bit();
			sample = (sample & (noise_level - 1)) - (noise_level >> 1);
			if (sample > 0x7f)
			{
				sample = 0x7f;
			}
			else if (sample < 0)
			{
				sample = 0xff;
			}
			sample = m_mulaw_table[(unsigned char)sample];

			if ( (pos+cnt) == pos )
			{
				noisebuf += sample;
				noisecnt++;
				sample = noisebuf / noisecnt;
			}
			else
			{
				if ( noisecnt )
				{
					sample = noisebuf / noisecnt;
				}
				else
				{
					sample = m_mulaw_table[0x7f];       // Nearest sound(s) is here.
				}
				noisebuf = 0;
				noisecnt = ( flag & C352_FLG_FILTER ) ? 0 : 1;
			}
		}

		// apply linear interpolation
		if ( (flag & (C352_FLG_FILTER | C352_FLG_NOISE)) == 0 )
		{
			sample = (short)(sample + ((nextsample-sample) * (((double)(0x0000ffff&offset) )/0x10000)));
		}

		if ( flag & C352_FLG_PHASEFL )
		{
			m_channel_l[i]  += ((-sample * m_c352_ch[ch].vol_l)>>8);
		}
		else
		{
			m_channel_l[i] += ((sample * m_c352_ch[ch].vol_l)>>8);
		}

		if ( flag & C352_FLG_PHASEFR )
		{
			m_channel_r[i]  += ((-sample * m_c352_ch[ch].vol_r)>>8);
		}
		else
		{
			m_channel_r[i] += ((sample * m_c352_ch[ch].vol_r)>>8);
		}

		if ( flag & C352_FLG_PHASERL )
		{
			m_channel_l2[i] += ((-sample * m_c352_ch[ch].vol_l2)>>8);
		}
		else
		{
			m_channel_l2[i] += ((sample * m_c352_ch[ch].vol_l2)>>8);
		}
		m_channel_r2[i] += ((sample * m_c352_ch[ch].vol_r2)>>8);

		if ( (flag & C352_FLG_REVERSE) && (flag & C352_FLG_LOOP) )
		{
			if ( !(flag & C352_FLG_LDIR) )
			{
				pos += cnt;
				if (
					(((pos&0xFFFF) > m_c352_ch[ch].end_addr) && ((pos&0xFFFF) < m_c352_ch[ch].start) && (m_c352_ch[ch].start > m_c352_ch[ch].end_addr) ) ||
					(((pos&0xFFFF) > m_c352_ch[ch].end_addr) && ((pos&0xFFFF) > m_c352_ch[ch].start) && (m_c352_ch[ch].start < m_c352_ch[ch].end_addr) ) ||
					((pos > (bank|0xFFFF)) && (m_c352_ch[ch].end_addr == 0xFFFF))
					)
				{
					m_c352_ch[ch].flag |= C352_FLG_LDIR;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
			}
			else
			{
				pos -= cnt;
				if (
					(((pos&0xFFFF) < m_c352_ch[ch].repeat) && ((pos&0xFFFF) < m_c352_ch[ch].end_addr) && (m_c352_ch[ch].end_addr > m_c352_ch[ch].start) ) ||
					(((pos&0xFFFF) < m_c352_ch[ch].repeat) && ((pos&0xFFFF) > m_c352_ch[ch].end_addr) && (m_c352_ch[ch].end_addr < m_c352_ch[ch].start) ) ||
					((pos < bank) && (m_c352_ch[ch].repeat == 0x0000))
					)
				{
					m_c352_ch[ch].flag &= ~C352_FLG_LDIR;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
			}
		}
		else if ( flag & C352_FLG_REVERSE )
		{
			pos -= cnt;
			if (
				(((pos&0xFFFF) < m_c352_ch[ch].end_addr) && ((pos&0xFFFF) < m_c352_ch[ch].start) && (m_c352_ch[ch].start > m_c352_ch[ch].end_addr) ) ||
				(((pos&0xFFFF) < m_c352_ch[ch].end_addr) && ((pos&0xFFFF) > m_c352_ch[ch].start) && (m_c352_ch[ch].start < m_c352_ch[ch].end_addr) ) ||
				((pos < bank) && (m_c352_ch[ch].end_addr == 0x0000))
				)
			{
				if ( (flag & C352_FLG_LINK) && (flag & C352_FLG_LOOP) )
				{
					m_c352_ch[ch].bank = m_c352_ch[ch].start_addr & 0xFF;
					m_c352_ch[ch].start_addr = m_c352_ch[ch].repeat_addr;
					m_c352_ch[ch].start = m_c352_ch[ch].start_addr;
					m_c352_ch[ch].repeat = m_c352_ch[ch].repeat_addr;
					pos = (m_c352_ch[ch].bank<<16) + m_c352_ch[ch].start_addr;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
				else if (flag & C352_FLG_LOOP)
				{
					pos = (pos & 0xFF0000) + m_c352_ch[ch].repeat;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
				else
				{
					m_c352_ch[ch].flag |= C352_FLG_KEYOFF;
					m_c352_ch[ch].flag &= ~C352_FLG_BUSY;
					return;
				}
			}
		} else {
			pos += cnt;
			if (
				(((pos&0xFFFF) > m_c352_ch[ch].end_addr) && ((pos&0xFFFF) < m_c352_ch[ch].start) && (m_c352_ch[ch].start > m_c352_ch[ch].end_addr) ) ||
				(((pos&0xFFFF) > m_c352_ch[ch].end_addr) && ((pos&0xFFFF) > m_c352_ch[ch].start) && (m_c352_ch[ch].start < m_c352_ch[ch].end_addr) ) ||
				((pos > (bank|0xFFFF)) && (m_c352_ch[ch].end_addr == 0xFFFF))
				)
			{
				if ( (flag & C352_FLG_LINK) && (flag & C352_FLG_LOOP) )
				{
					m_c352_ch[ch].bank = m_c352_ch[ch].start_addr & 0xFF;
					m_c352_ch[ch].start_addr = m_c352_ch[ch].repeat_addr;
					m_c352_ch[ch].start = m_c352_ch[ch].start_addr;
					m_c352_ch[ch].repeat = m_c352_ch[ch].repeat_addr;
					pos = (m_c352_ch[ch].bank<<16) + m_c352_ch[ch].start_addr;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
				else if (flag & C352_FLG_LOOP)
				{
					pos = (pos & 0xFF0000) + m_c352_ch[ch].repeat;
					m_c352_ch[ch].flag |= C352_FLG_LOOPHIST;
				}
				else
				{
					m_c352_ch[ch].flag |= C352_FLG_KEYOFF;
					m_c352_ch[ch].flag &= ~C352_FLG_BUSY;
					return;
				}
			}
		}
	}

	m_c352_ch[ch].noisecnt = noisecnt;
	m_c352_ch[ch].noisebuf = noisebuf;
	m_c352_ch[ch].pos = offset;
	m_c352_ch[ch].current_addr = pos;
}


void c352_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	int i, j;
	stream_sample_t *bufferl = outputs[0];
	stream_sample_t *bufferr = outputs[1];
	stream_sample_t *bufferl2 = outputs[2];
	stream_sample_t *bufferr2 = outputs[3];

	for(i = 0 ; i < samples ; i++)
	{
			m_channel_l[i] = m_channel_r[i] = m_channel_l2[i] = m_channel_r2[i] = 0;
	}

	for (j = 0 ; j < 32 ; j++)
	{
		mix_one_channel(j, samples);
	}

	for(i = 0 ; i < samples ; i++)
	{
		*bufferl++ = (short) (m_channel_l[i] >>3);
		*bufferr++ = (short) (m_channel_r[i] >>3);
		*bufferl2++ = (short) (m_channel_l2[i] >>3);
		*bufferr2++ = (short) (m_channel_r2[i] >>3);
	}
}

unsigned short c352_device::read_reg16(unsigned long address)
{
	unsigned long   chan;
	unsigned short  val;

	m_stream->update();

	chan = (address >> 4) & 0xfff;
	if (chan > 31)
	{
		val = 0;
	}
	else
	{
		if ((address & 0xf) == 6)
		{
			val = m_c352_ch[chan].flag;
		}
		else
		{
			val = 0;
		}
	}
	return val;
=======
c352_device::c352_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, C352, tag, owner, clock)
	, device_sound_interface(mconfig, *this)
	, device_rom_interface(mconfig, *this, 24)
	, m_stream(nullptr)
{
}


//-------------------------------------------------
//  rom_bank_updated - the rom bank has changed
//-------------------------------------------------

void c352_device::rom_bank_updated()
{
	m_stream->update();
}

//-------------------------------------------------
//  static_set_dividder - configuration helper to
//  set the divider setting
//-------------------------------------------------

void c352_device::static_set_divider(device_t &device, int setting)
{
	c352_device &c352 = downcast<c352_device &>(device);
	c352.m_divider = setting;
}

void c352_device::fetch_sample(c352_voice_t* v)
{
	v->last_sample = v->sample;

	if(v->flags & C352_FLG_NOISE)
	{
		m_random = (m_random>>1) ^ ((-(m_random&1)) & 0xfff6);
		v->sample = m_random;
	}
	else
	{
		int8_t s, s2;

		s = (int8_t)read_byte(v->pos);

		v->sample = s<<8;
		if(v->flags & C352_FLG_MULAW)
		{
			s2 = (s&0x7f)>>4;

			v->sample = ((s2*s2)<<4) - (~(s2<<1)) * (s&0x0f);
			v->sample = (s&0x80) ? (~v->sample)<<5 : v->sample<<5;
		}

		uint16_t pos = v->pos&0xffff;

		if((v->flags & C352_FLG_LOOP) && v->flags & C352_FLG_REVERSE)
		{
			// backwards>forwards
			if((v->flags & C352_FLG_LDIR) && pos == v->wave_loop)
				v->flags &= ~C352_FLG_LDIR;
			// forwards>backwards
			else if(!(v->flags & C352_FLG_LDIR) && pos == v->wave_end)
				v->flags |= C352_FLG_LDIR;

			v->pos += (v->flags&C352_FLG_LDIR) ? -1 : 1;
		}
		else if(pos == v->wave_end)
		{
			if((v->flags & C352_FLG_LINK) && (v->flags & C352_FLG_LOOP))
			{
				v->pos = (v->wave_start<<16) | v->wave_loop;
				v->flags |= C352_FLG_LOOPHIST;
			}
			else if(v->flags & C352_FLG_LOOP)
			{
				v->pos = (v->pos&0xff0000) | v->wave_loop;
				v->flags |= C352_FLG_LOOPHIST;
			}
			else
			{
				v->flags |= C352_FLG_KEYOFF;
				v->flags &= ~C352_FLG_BUSY;
				v->sample=0;
			}
		}
		else
		{
			v->pos += (v->flags&C352_FLG_REVERSE) ? -1 : 1;
		}
	}
}

void c352_device::ramp_volume(c352_voice_t* v,int ch,uint8_t val)
{
	int16_t vol_delta = v->curr_vol[ch] - val;
	if(vol_delta != 0)
		v->curr_vol[ch] += (vol_delta>0) ? -1 : 1;
}

void c352_device::sound_stream_update(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples)
{
	int i,j;
	int16_t s;
	int32_t next_counter;
	stream_sample_t *buffer_fl = outputs[0];
	stream_sample_t *buffer_fr = outputs[1];
	stream_sample_t *buffer_rl = outputs[2];
	stream_sample_t *buffer_rr = outputs[3];
	c352_voice_t* v;

	long out[4];

	for(i=0;i<samples;i++)
	{
		out[0]=out[1]=out[2]=out[3]=0;

		for(j=0;j<32;j++)
		{

			v = &m_c352_v[j];
			s = 0;

			if(v->flags & C352_FLG_BUSY)
			{
				next_counter = v->counter+v->freq;

				if(next_counter & 0x10000)
				{
					fetch_sample(v);
				}

				if((next_counter^v->counter) & 0x18000)
				{
					ramp_volume(v,0,v->vol_f>>8);
					ramp_volume(v,1,v->vol_f&0xff);
					ramp_volume(v,2,v->vol_r>>8);
					ramp_volume(v,3,v->vol_r&0xff);
				}

				v->counter = next_counter&0xffff;

				s = v->sample;

				// Interpolate samples
				if((v->flags & C352_FLG_FILTER) == 0)
					s = v->last_sample + (v->counter*(v->sample-v->last_sample)>>16);
			}

			// Left
			out[0] += (((v->flags & C352_FLG_PHASEFL) ? -s : s) * v->curr_vol[0])>>8;
			out[2] += (((v->flags & C352_FLG_PHASEFR) ? -s : s) * v->curr_vol[2])>>8;

			// Right
			out[1] += (((v->flags & C352_FLG_PHASERL) ? -s : s) * v->curr_vol[1])>>8;
			out[3] += (((v->flags & C352_FLG_PHASERL) ? -s : s) * v->curr_vol[3])>>8;
		}

		*buffer_fl++ = (int16_t) (out[0]>>3);
		*buffer_fr++ = (int16_t) (out[1]>>3);
		*buffer_rl++ = (int16_t) (out[2]>>3);
		*buffer_rr++ = (int16_t) (out[3]>>3);
	}
}

uint16_t c352_device::read_reg16(unsigned long address)
{
	m_stream->update();

	const int reg_map[8] =
	{
		offsetof(c352_voice_t,vol_f) / sizeof(uint16_t),
		offsetof(c352_voice_t,vol_r) / sizeof(uint16_t),
		offsetof(c352_voice_t,freq) / sizeof(uint16_t),
		offsetof(c352_voice_t,flags) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_bank) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_start) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_end) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_loop) / sizeof(uint16_t),
	};

	if(address < 0x100)
		return *((uint16_t*)&m_c352_v[address/8]+reg_map[address%8]);
	else if(address == 0x200)
		return m_control;
	else
		return 0;

	return 0;
>>>>>>> upstream/master
}

void c352_device::write_reg16(unsigned long address, unsigned short val)
{
<<<<<<< HEAD
	unsigned long   chan;
	int i;

	m_stream->update();

	chan = (address >> 4) & 0xfff;

	if ( address >= 0x400 )
	{
		switch(address)
		{
			case 0x404: // execute key-ons/offs
				for ( i = 0 ; i <= 31 ; i++ )
				{
					if ( m_c352_ch[i].flag & C352_FLG_KEYON )
					{
						if (m_c352_ch[i].start_addr != m_c352_ch[i].end_addr)
						{
							m_c352_ch[i].current_addr = (m_c352_ch[i].bank << 16) + m_c352_ch[i].start_addr;
							m_c352_ch[i].start = m_c352_ch[i].start_addr;
							m_c352_ch[i].repeat = m_c352_ch[i].repeat_addr;
							m_c352_ch[i].noisebuf = 0;
							m_c352_ch[i].noisecnt = 0;
							m_c352_ch[i].flag &= ~(C352_FLG_KEYON | C352_FLG_LOOPHIST);
							m_c352_ch[i].flag |= C352_FLG_BUSY;
						}
					}
					else if ( m_c352_ch[i].flag & C352_FLG_KEYOFF )
					{
						m_c352_ch[i].flag &= ~C352_FLG_BUSY;
						m_c352_ch[i].flag &= ~(C352_FLG_KEYOFF);
					}
				}
				break;
			default:
				break;
		}
		return;
	}

	if (chan > 31)
	{
		LOG(("C352 CTRL %08lx %04x\n", address, val));
		return;
	}
	switch(address & 0xf)
	{
	case 0x0:
		// volumes (output 1)
		LOG(("CH %02ld LVOL %02x RVOL %02x\n", chan, val & 0xff, val >> 8));
		m_c352_ch[chan].vol_l = val & 0xff;
		m_c352_ch[chan].vol_r = val >> 8;
		break;

	case 0x2:
		// volumes (output 2)
		LOG(("CH %02ld RLVOL %02x RRVOL %02x\n", chan, val & 0xff, val >> 8));
		m_c352_ch[chan].vol_l2 = val & 0xff;
		m_c352_ch[chan].vol_r2 = val >> 8;
		break;

	case 0x4:
		// pitch
		LOG(("CH %02ld PITCH %04x\n", chan, val));
		m_c352_ch[chan].pitch = val;
		break;

	case 0x6:
		// flags
		LOG(("CH %02ld FLAG %02x\n", chan, val));
		m_c352_ch[chan].flag = val;
		break;

	case 0x8:
		// bank (bits 16-31 of address);
		m_c352_ch[chan].bank = val & 0xff;
		LOG(("CH %02ld BANK %02x", chan, m_c352_ch[chan].bank));
		break;

	case 0xa:
		// start address
		LOG(("CH %02ld SADDR %04x\n", chan, val));
		m_c352_ch[chan].start_addr = val;
		break;

	case 0xc:
		// end address
		LOG(("CH %02ld EADDR %04x\n", chan, val));
		m_c352_ch[chan].end_addr = val;
		break;

	case 0xe:
		// loop address
		LOG(("CH %02ld LADDR %04x\n", chan, val));
		m_c352_ch[chan].repeat_addr = val;
		break;

	default:
		LOG(("CH %02ld UNKN %01lx %04x", chan, address & 0xf, val));
		break;
	}
}

void c352_device::device_start()
{
	int i;
	double x_max = 32752.0;
	double y_max = 127.0;
	double u = 10.0;

	// find our direct access
	m_direct = &space().direct();
=======
	m_stream->update();

	const int reg_map[8] =
	{
		offsetof(c352_voice_t,vol_f) / sizeof(uint16_t),
		offsetof(c352_voice_t,vol_r) / sizeof(uint16_t),
		offsetof(c352_voice_t,freq) / sizeof(uint16_t),
		offsetof(c352_voice_t,flags) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_bank) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_start) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_end) / sizeof(uint16_t),
		offsetof(c352_voice_t,wave_loop) / sizeof(uint16_t),
	};

	int i;

	if(address < 0x100)
	{
		*((uint16_t*)&m_c352_v[address/8]+reg_map[address%8]) = val;
	}
	else if(address == 0x200)
	{
		m_control = val;
		logerror("C352 control register write: %04x\n",val);
	}
	else if(address == 0x202) // execute keyons/keyoffs
	{
		for(i=0;i<32;i++)
		{
			if((m_c352_v[i].flags & C352_FLG_KEYON))
			{
				m_c352_v[i].pos = (m_c352_v[i].wave_bank<<16) | m_c352_v[i].wave_start;

				m_c352_v[i].sample = 0;
				m_c352_v[i].last_sample = 0;
				m_c352_v[i].counter = 0xffff;

				m_c352_v[i].flags |= C352_FLG_BUSY;
				m_c352_v[i].flags &= ~(C352_FLG_KEYON|C352_FLG_LOOPHIST);

				m_c352_v[i].curr_vol[0] = m_c352_v[i].curr_vol[1] = 0;
				m_c352_v[i].curr_vol[2] = m_c352_v[i].curr_vol[3] = 0;
			}
			else if(m_c352_v[i].flags & C352_FLG_KEYOFF)
			{
				m_c352_v[i].flags &= ~(C352_FLG_BUSY|C352_FLG_KEYOFF);
				m_c352_v[i].counter = 0xffff;
			}
		}
	}
}

void c352_device::device_clock_changed()
{
	m_sample_rate_base = clock() / m_divider;
	if (m_stream != nullptr)
		m_stream->set_sample_rate(m_sample_rate_base);
	else
		m_stream = machine().sound().stream_alloc(*this, 0, 4, m_sample_rate_base);
}

void c352_device::device_start()
{
	int i;
>>>>>>> upstream/master

	m_sample_rate_base = clock() / m_divider;

	m_stream = machine().sound().stream_alloc(*this, 0, 4, m_sample_rate_base);

<<<<<<< HEAD
	// generate mulaw table for mulaw format samples
	for (i = 0; i < 256; i++)
	{
			double y = (double) (i & 0x7f);
			double x = (exp (y / y_max * log (1.0 + u)) - 1.0) * x_max / u;

			if (i & 0x80)
			{
			x = -x;
			}
			m_mulaw_table[i] = (short)x;
	}

	// register save state info
	for (i = 0; i < 32; i++)
	{
		save_item(NAME(m_c352_ch[i].vol_l), i);
		save_item(NAME(m_c352_ch[i].vol_r), i);
		save_item(NAME(m_c352_ch[i].vol_l2), i);
		save_item(NAME(m_c352_ch[i].vol_r2), i);
		save_item(NAME(m_c352_ch[i].bank), i);
		save_item(NAME(m_c352_ch[i].noise), i);
		save_item(NAME(m_c352_ch[i].noisebuf), i);
		save_item(NAME(m_c352_ch[i].noisecnt), i);
		save_item(NAME(m_c352_ch[i].pitch), i);
		save_item(NAME(m_c352_ch[i].start_addr), i);
		save_item(NAME(m_c352_ch[i].end_addr), i);
		save_item(NAME(m_c352_ch[i].repeat_addr), i);
		save_item(NAME(m_c352_ch[i].flag), i);
		save_item(NAME(m_c352_ch[i].start), i);
		save_item(NAME(m_c352_ch[i].repeat), i);
		save_item(NAME(m_c352_ch[i].current_addr), i);
		save_item(NAME(m_c352_ch[i].pos), i);
	}
=======
	// register save state info
	for (i = 0; i < 32; i++)
	{
		save_item(NAME(m_c352_v[i].pos), i);
		save_item(NAME(m_c352_v[i].counter), i);
		save_item(NAME(m_c352_v[i].sample), i);
		save_item(NAME(m_c352_v[i].last_sample), i);
		save_item(NAME(m_c352_v[i].vol_f), i);
		save_item(NAME(m_c352_v[i].vol_r), i);
		save_item(NAME(m_c352_v[i].curr_vol), i);
		save_item(NAME(m_c352_v[i].freq), i);
		save_item(NAME(m_c352_v[i].flags), i);
		save_item(NAME(m_c352_v[i].wave_bank), i);
		save_item(NAME(m_c352_v[i].wave_start), i);
		save_item(NAME(m_c352_v[i].wave_end), i);
		save_item(NAME(m_c352_v[i].wave_loop), i);
	}
	save_item(NAME(m_random));
	save_item(NAME(m_control));
>>>>>>> upstream/master
}

void c352_device::device_reset()
{
	// clear all channels states
<<<<<<< HEAD
	memset(m_c352_ch, 0, sizeof(c352_ch_t)*32);

	// init noise generator
	m_mseq_reg = 0x12345678;
=======
	memset(m_c352_v, 0, sizeof(c352_voice_t)*32);

	// init noise generator
	m_random = 0x1234;
	m_control = 0;
>>>>>>> upstream/master
}

READ16_MEMBER( c352_device::read )
{
<<<<<<< HEAD
	return(read_reg16(offset*2));
=======
	return(read_reg16(offset));
>>>>>>> upstream/master
}

WRITE16_MEMBER( c352_device::write )
{
	if (mem_mask == 0xffff)
	{
<<<<<<< HEAD
		write_reg16(offset*2, data);
=======
		write_reg16(offset, data);
>>>>>>> upstream/master
	}
	else
	{
		logerror("C352: byte-wide write unsupported at this time!\n");
	}
}
