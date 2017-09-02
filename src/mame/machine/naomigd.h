// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef _NAOMIGD_H_
#define _NAOMIGD_H_
=======
#ifndef MAME_MACHINE_NAOMIGD_H
#define MAME_MACHINE_NAOMIGD_H

#pragma once
>>>>>>> upstream/master

#include "machine/naomibd.h"

#define MCFG_NAOMI_GDROM_BOARD_ADD(_tag, _image_tag, _pic_tag, _eeprom_tag, _irq_cb) \
<<<<<<< HEAD
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_GDROM_BOARD, _eeprom_tag, NULL, _irq_cb) \
=======
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_GDROM_BOARD, _eeprom_tag, _irq_cb) \
>>>>>>> upstream/master
	naomi_gdrom_board::static_set_tags(*device, _image_tag, _pic_tag);

class naomi_gdrom_board : public naomi_board
{
public:
<<<<<<< HEAD
	naomi_gdrom_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void static_set_tags(device_t &device, const char *_image_tag, const char *_pic_tag);

	UINT8 *memory(UINT32 &size) { size = dimm_data_size; return dimm_data; }

protected:
	virtual void device_start();
	virtual void device_reset();

	virtual void board_setup_address(UINT32 address, bool is_dma);
	virtual void board_get_buffer(UINT8 *&base, UINT32 &limit);
	virtual void board_advance(UINT32 size);
=======
	naomi_gdrom_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void static_set_tags(device_t &device, const char *_image_tag, const char *_pic_tag);

	uint8_t *memory(uint32_t &size) { size = dimm_data_size; return dimm_data; }

	virtual const tiny_rom_entry *device_rom_region() const override;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void board_setup_address(uint32_t address, bool is_dma) override;
	virtual void board_get_buffer(uint8_t *&base, uint32_t &limit) override;
	virtual void board_advance(uint32_t size) override;
>>>>>>> upstream/master

private:
	enum { FILENAME_LENGTH=24 };

	const char *image_tag, *pic_tag;

<<<<<<< HEAD
	UINT32 dimm_cur_address;

	// Note: voluntarily not saved into the state
	UINT8 *dimm_data;
	UINT32 dimm_data_size;

	static const UINT32 DES_LEFTSWAP[];
	static const UINT32 DES_RIGHTSWAP[];
	static const UINT32 DES_SBOX1[];
	static const UINT32 DES_SBOX2[];
	static const UINT32 DES_SBOX3[];
	static const UINT32 DES_SBOX4[];
	static const UINT32 DES_SBOX5[];
	static const UINT32 DES_SBOX6[];
	static const UINT32 DES_SBOX7[];
	static const UINT32 DES_SBOX8[];
	static const UINT32 DES_MASK_TABLE[];
	static const UINT8 DES_ROTATE_TABLE[16];

	void find_file(const char *name, const UINT8 *dir_sector, UINT32 &file_start, UINT32 &file_size);

	inline void permutate(UINT32 &a, UINT32 &b, UINT32 m, int shift);
	void des_generate_subkeys(const UINT64 key, UINT32 *subkeys);
	UINT64 des_encrypt_decrypt(bool decrypt, UINT64 src, const UINT32 *des_subkeys);
	UINT64 rev64(UINT64 src);
	UINT64 read_to_qword(const UINT8 *region);
	void write_from_qword(UINT8 *region, UINT64 qword);
};

extern const device_type NAOMI_GDROM_BOARD;

#endif
=======
	uint32_t dimm_cur_address;

	// Note: voluntarily not saved into the state
	uint8_t *dimm_data;
	uint32_t dimm_data_size;

	static const uint32_t DES_LEFTSWAP[];
	static const uint32_t DES_RIGHTSWAP[];
	static const uint32_t DES_SBOX1[];
	static const uint32_t DES_SBOX2[];
	static const uint32_t DES_SBOX3[];
	static const uint32_t DES_SBOX4[];
	static const uint32_t DES_SBOX5[];
	static const uint32_t DES_SBOX6[];
	static const uint32_t DES_SBOX7[];
	static const uint32_t DES_SBOX8[];
	static const uint32_t DES_MASK_TABLE[];
	static const uint8_t DES_ROTATE_TABLE[16];

	void find_file(const char *name, const uint8_t *dir_sector, uint32_t &file_start, uint32_t &file_size);

	inline void permutate(uint32_t &a, uint32_t &b, uint32_t m, int shift);
	void des_generate_subkeys(const uint64_t key, uint32_t *subkeys);
	uint64_t des_encrypt_decrypt(bool decrypt, uint64_t src, const uint32_t *des_subkeys);
	uint64_t rev64(uint64_t src);
	uint64_t read_to_qword(const uint8_t *region);
	void write_from_qword(uint8_t *region, uint64_t qword);
};

extern const device_type NAOMI_GDROM_BOARD;
DECLARE_DEVICE_TYPE(NAOMI_GDROM_BOARD, naomi_gdrom_board)

#endif // MAME_MACHINE_NAOMIGD_H
>>>>>>> upstream/master
