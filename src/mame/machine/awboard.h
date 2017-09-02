// license:BSD-3-Clause
// copyright-holders:Olivier Galibert,Andreas Naive
<<<<<<< HEAD
#ifndef _AWBOARD_H_
#define _AWBOARD_H_
=======
#ifndef MAME_MACHINE_AWBOARD_H
#define MAME_MACHINE_AWBOARD_H

#pragma once
>>>>>>> upstream/master

#include "naomig1.h"

#define MCFG_AW_ROM_BOARD_ADD(_tag, _keyregion, _irq_cb)  \
	MCFG_NAOMI_G1_ADD(_tag, AW_ROM_BOARD, _irq_cb)        \
<<<<<<< HEAD
	aw_rom_board::static_set_keyregion(*device, _keyregion);
=======
	aw_rom_board::static_set_keyregion(*device, "^" _keyregion);
>>>>>>> upstream/master

class aw_rom_board : public naomi_g1_device
{
public:
<<<<<<< HEAD
	aw_rom_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void static_set_keyregion(device_t &device, const char *_keyregion);
=======
	aw_rom_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void static_set_keyregion(device_t &device, const char *keyregion);
>>>>>>> upstream/master

	DECLARE_ADDRESS_MAP(submap, 16);

	DECLARE_WRITE16_MEMBER(epr_offsetl_w);          // 5f7000
	DECLARE_WRITE16_MEMBER(epr_offseth_w);          // 5f7004
	DECLARE_WRITE16_MEMBER(mpr_record_index_w);     // 5f700c
	DECLARE_WRITE16_MEMBER(mpr_first_file_index_w); // 5f7010
	DECLARE_WRITE16_MEMBER(mpr_file_offsetl_w);     // 5f7014
	DECLARE_WRITE16_MEMBER(mpr_file_offseth_w);     // 5f7018
	DECLARE_READ16_MEMBER(pio_r);                   // 5f7080
	DECLARE_WRITE16_MEMBER(pio_w);                  // 5f7080

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	virtual void dma_get_position(UINT8 *&base, UINT32 &limit, bool to_mainram);
	virtual void dma_advance(UINT32 size);
=======
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void dma_get_position(uint8_t *&base, uint32_t &limit, bool to_mainram) override;
	virtual void dma_advance(uint32_t size) override;
>>>>>>> upstream/master

private:
	enum { EPR, MPR_RECORD, MPR_FILE };

<<<<<<< HEAD
	const char *keyregion;
	UINT32 rombd_key;
	UINT32 mpr_offset, mpr_bank;
	UINT32 epr_offset, mpr_file_offset;
	UINT16 mpr_record_index, mpr_first_file_index;
	UINT16 decrypted_buf[16];

	UINT32 dma_offset, dma_limit;

	struct sbox_set {
		UINT8 S0[32];
		UINT8 S1[16];
		UINT8 S2[16];
		UINT8 S3[8];
=======
	required_memory_region m_region;
	optional_memory_region m_keyregion;
	uint32_t rombd_key;
	uint32_t mpr_offset, mpr_bank;
	uint32_t epr_offset, mpr_file_offset;
	uint16_t mpr_record_index, mpr_first_file_index;
	uint16_t decrypted_buf[16];

	uint32_t dma_offset, dma_limit;

	struct sbox_set {
		uint8_t S0[32];
		uint8_t S1[16];
		uint8_t S2[16];
		uint8_t S3[8];
>>>>>>> upstream/master
	};

	static const int permutation_table[4][16];
	static const sbox_set sboxes_table[4];
<<<<<<< HEAD
	static UINT16 decrypt(UINT16 cipherText, UINT32 address, const UINT32 key);
	UINT16 decrypt16(UINT32 address) { return decrypt(m_region->u16(address), address, rombd_key); }
=======
	static uint16_t decrypt(uint16_t cipherText, uint32_t address, const uint32_t key);
	uint16_t decrypt16(uint32_t address) { return decrypt(m_region->as_u16(address), address, rombd_key); }
>>>>>>> upstream/master

	void set_key();
	void recalc_dma_offset(int mode);
};

<<<<<<< HEAD
extern const device_type AW_ROM_BOARD;

#endif
=======
DECLARE_DEVICE_TYPE(AW_ROM_BOARD, aw_rom_board)

#endif // MAME_MACHINE_AWBOARD_H
>>>>>>> upstream/master
