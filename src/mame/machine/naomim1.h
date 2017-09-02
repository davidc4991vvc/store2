// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef _NAOMIM1_H_
#define _NAOMIM1_H_

#include "naomibd.h"

#define MCFG_NAOMI_M1_BOARD_ADD(_tag, _eeprom_tag, _actel_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M1_BOARD, _eeprom_tag, _actel_tag, _irq_cb)
=======
#ifndef MAME_MACHINE_NAOMIM1_H
#define MAME_MACHINE_NAOMIM1_H

#pragma once

#include "naomibd.h"

#define MCFG_NAOMI_M1_BOARD_ADD(_tag, _eeprom_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M1_BOARD, _eeprom_tag, _irq_cb)
>>>>>>> upstream/master

class naomi_m1_board : public naomi_board
{
public:
<<<<<<< HEAD
	naomi_m1_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_ADDRESS_MAP(submap, 16);
=======
	naomi_m1_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_ADDRESS_MAP(submap, 16) override;
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(actel_id_r);

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	virtual void board_setup_address(UINT32 address, bool is_dma);
	virtual void board_get_buffer(UINT8 *&base, UINT32 &limit);
	virtual void board_advance(UINT32 size);

private:
	enum { BUFFER_SIZE = 32768 };
	UINT32 key;

	UINT8 *buffer;
	UINT8 dict[111], hist[2];
	UINT64 avail_val;
	UINT32 rom_cur_address, buffer_actual_size, avail_bits;
	bool encryption, stream_ended, has_history;

	void gb_reset();
	UINT32 lookb(int bits);
	void skipb(int bits);
	UINT32 getb(int bits);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void board_setup_address(uint32_t address, bool is_dma) override;
	virtual void board_get_buffer(uint8_t *&base, uint32_t &limit) override;
	virtual void board_advance(uint32_t size) override;

private:
	enum { BUFFER_SIZE = 32768 };
	uint32_t key;
	uint16_t actel_id;

	std::unique_ptr<uint8_t[]> buffer;
	uint8_t dict[111], hist[2];
	uint64_t avail_val;
	uint32_t rom_cur_address, buffer_actual_size, avail_bits;
	bool encryption, stream_ended, has_history;

	required_memory_region m_region;

	void gb_reset();
	uint32_t lookb(int bits);
	void skipb(int bits);
	uint32_t getb(int bits);
>>>>>>> upstream/master

	void enc_reset();
	void enc_fill();

<<<<<<< HEAD
	UINT32 get_decrypted_32b();

	void wb(UINT8 byte);
};

extern const device_type NAOMI_M1_BOARD;

#endif
=======
	uint32_t get_decrypted_32b();

	void wb(uint8_t byte);
};

DECLARE_DEVICE_TYPE(NAOMI_M1_BOARD, naomi_m1_board)

#endif // MAME_MACHINE_NAOMIM1_H
>>>>>>> upstream/master
