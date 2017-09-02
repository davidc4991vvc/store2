// license:BSD-3-Clause
// copyright-holders:Olivier Galibert

#include "emu.h"
#include "naomim1.h"

<<<<<<< HEAD
const device_type NAOMI_M1_BOARD = &device_creator<naomi_m1_board>;
=======
DEFINE_DEVICE_TYPE(NAOMI_M1_BOARD, naomi_m1_board, "naomi_m1_board", "Sega NAOMI M1 Board")
>>>>>>> upstream/master

DEVICE_ADDRESS_MAP_START(submap, 16, naomi_m1_board)
	AM_RANGE(0x0a, 0x0b) AM_READ(actel_id_r)

	AM_INHERIT_FROM(naomi_board::submap)
ADDRESS_MAP_END

<<<<<<< HEAD
naomi_m1_board::naomi_m1_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: naomi_board(mconfig, NAOMI_M1_BOARD, "Sega NAOMI M1 Board", tag, owner, clock, "naomi_m1_board", __FILE__)
=======
naomi_m1_board::naomi_m1_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: naomi_board(mconfig, NAOMI_M1_BOARD, tag, owner, clock)
	, m_region(*this, DEVICE_SELF)
>>>>>>> upstream/master
{
}

READ16_MEMBER(naomi_m1_board::actel_id_r)
{
<<<<<<< HEAD
	if (rombdid_tag && memregion(rombdid_tag) != NULL)
	{
		const UINT8 *bdid = memregion(rombdid_tag)->base();
		return bdid[0] | (bdid[1] << 8);
	}

	return 0x0000;
=======
	return actel_id;
>>>>>>> upstream/master
}

void naomi_m1_board::device_start()
{
	naomi_board::device_start();

	std::string skey = parameter("key");
	if(!skey.empty())
<<<<<<< HEAD
		key = strtoll(skey.c_str(), 0, 16);
=======
		key = strtoll(skey.c_str(), nullptr, 16);
>>>>>>> upstream/master
	else
	{
		logerror("%s: Warning: key not provided\n", tag());
		key = 0;
	}

<<<<<<< HEAD
	buffer = auto_alloc_array(machine(), UINT8, BUFFER_SIZE);

	save_pointer(NAME(buffer), BUFFER_SIZE);
=======
	std::string sid = parameter("id");
	if (!sid.empty())
		actel_id = strtoll(sid.c_str(), nullptr, 16);
	else
	{
		logerror("%s: Warning: Actel ID not provided\n", tag());
		actel_id = 0;
	}

	buffer = std::make_unique<uint8_t[]>(BUFFER_SIZE);

	save_pointer(NAME(buffer.get()), BUFFER_SIZE);
>>>>>>> upstream/master
	save_item(NAME(dict));
	save_item(NAME(hist));
	save_item(NAME(rom_cur_address));
	save_item(NAME(buffer_actual_size));
	save_item(NAME(avail_bits));
	save_item(NAME(encryption));
	save_item(NAME(stream_ended));
	save_item(NAME(has_history));
}

void naomi_m1_board::device_reset()
{
	naomi_board::device_reset();
	encryption = false;
	rom_cur_address = 0;
	buffer_actual_size = 0;
	has_history = false;
	stream_ended = false;

	memset(dict, 0, sizeof(dict));
	memset(hist, 0, sizeof(hist));

	avail_val = 0;
	avail_bits = 0;
}

<<<<<<< HEAD
void naomi_m1_board::board_setup_address(UINT32 address, bool is_dma)
=======
void naomi_m1_board::board_setup_address(uint32_t address, bool is_dma)
>>>>>>> upstream/master
{
	rom_cur_address = address & 0x1fffffff;
	encryption = (!(address & 0x20000000)) && is_dma;

	if(encryption) {
		enc_reset();
		enc_fill();
	}
}

<<<<<<< HEAD
void naomi_m1_board::board_get_buffer(UINT8 *&base, UINT32 &limit)
{
	if(encryption) {
		base = buffer;
=======
void naomi_m1_board::board_get_buffer(uint8_t *&base, uint32_t &limit)
{
	if(encryption) {
		base = buffer.get();
>>>>>>> upstream/master
		limit = BUFFER_SIZE;

	} else {
		base = m_region->base() + rom_cur_address;
		limit = m_region->bytes() - rom_cur_address;
	}
}

<<<<<<< HEAD
void naomi_m1_board::board_advance(UINT32 size)
{
	if(encryption) {
		if(size < buffer_actual_size) {
			memmove(buffer, buffer + size, buffer_actual_size - size);
=======
void naomi_m1_board::board_advance(uint32_t size)
{
	if(encryption) {
		if(size < buffer_actual_size) {
			memmove(buffer.get(), buffer.get() + size, buffer_actual_size - size);
>>>>>>> upstream/master
			buffer_actual_size -= size;
		} else {
			hist[0] = buffer[buffer_actual_size-2];
			hist[1] = buffer[buffer_actual_size-1];
			has_history = true;
			buffer_actual_size = 0;
		}
		enc_fill();

	} else
		rom_cur_address += size;
}

<<<<<<< HEAD
UINT32 naomi_m1_board::get_decrypted_32b()
{
	UINT8 *base = m_region->base() + rom_cur_address;
	UINT8 a = base[0];
	UINT8 b = base[1];
	UINT8 c = base[2];
	UINT8 d = base[3];

	rom_cur_address += 4;

	UINT32 res = key ^ (((b^d) << 24) | ((a^c) << 16) | (b << 8) | a);
=======
uint32_t naomi_m1_board::get_decrypted_32b()
{
	uint8_t *base = m_region->base() + rom_cur_address;
	uint8_t a = base[0];
	uint8_t b = base[1];
	uint8_t c = base[2];
	uint8_t d = base[3];

	rom_cur_address += 4;

	uint32_t res = key ^ (((b^d) << 24) | ((a^c) << 16) | (b << 8) | a);
>>>>>>> upstream/master
	return res;
}

void naomi_m1_board::gb_reset()
{
	avail_val = 0;
	avail_bits = 0;
}

<<<<<<< HEAD
inline UINT32 naomi_m1_board::lookb(int bits)
=======
inline uint32_t naomi_m1_board::lookb(int bits)
>>>>>>> upstream/master
{
	if(bits > avail_bits) {
		avail_val = (avail_val << 32) | get_decrypted_32b();
		avail_bits += 32;
	}
	return (avail_val >> (avail_bits - bits)) & ((1 << bits)-1);
}

inline void naomi_m1_board::skipb(int bits)
{
	avail_bits -= bits;
}

<<<<<<< HEAD
inline UINT32 naomi_m1_board::getb(int bits)
{
	UINT32 res = lookb(bits);
=======
inline uint32_t naomi_m1_board::getb(int bits)
{
	uint32_t res = lookb(bits);
>>>>>>> upstream/master
	skipb(bits);
	return res;
}

void naomi_m1_board::enc_reset()
{
	gb_reset();
	stream_ended = false;
	has_history = false;
	buffer_actual_size = 0;

<<<<<<< HEAD
	for(int i=0; i<111; i++)
		dict[i] = getb(8);
}

void naomi_m1_board::wb(UINT8 byte)
=======
	for(auto & elem : dict)
		elem = getb(8);
}

void naomi_m1_board::wb(uint8_t byte)
>>>>>>> upstream/master
{
	if(dict[0] & 64)
		if(buffer_actual_size < 2)
			if(has_history)
				buffer[buffer_actual_size] = hist[buffer_actual_size] - byte;
			else
				buffer[buffer_actual_size] = byte;
		else
			buffer[buffer_actual_size] = buffer[buffer_actual_size-2] - byte;
	else
		buffer[buffer_actual_size] = byte;

	buffer_actual_size++;
}

void naomi_m1_board::enc_fill()
{
	while(buffer_actual_size < BUFFER_SIZE && !stream_ended) {
		switch(lookb(3)) {
			// 00+2 - 0000+esc
		case 0: case 1: {
			skipb(2);
			int addr = getb(2);
			if(addr)
				wb(dict[addr]);
			else
				wb(getb(8));
			break;
		}

			// 010+2
		case 2:
			skipb(3);
			wb(dict[getb(2)+4]);
			break;

			// 011+3
		case 3:
			skipb(3);
			wb(dict[getb(3)+8]);
			break;

			// 10+5
		case 4: case 5:
			skipb(2);
			wb(dict[getb(5)+16]);
			break;

			// 11+6
		case 6: case 7: {
			skipb(2);
			int addr = getb(6)+48;
			if(addr == 111)
				stream_ended = true;
			else
				wb(dict[addr]);
			break;
		}
		}
	}

	while(buffer_actual_size < BUFFER_SIZE)
		buffer[buffer_actual_size++] = 0;
}
