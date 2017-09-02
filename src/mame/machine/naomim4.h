// license:BSD-3-Clause
// copyright-holders:Olivier Galibert,Andreas Naive
<<<<<<< HEAD
#ifndef _NAOMIM4_H_
#define _NAOMIM4_H_

#include "naomibd.h"

#define MCFG_NAOMI_M4_BOARD_ADD(_tag, _key_tag, _eeprom_tag, _actel_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M4_BOARD, _eeprom_tag, _actel_tag, _irq_cb) \
	naomi_m4_board::static_set_tags(*device, _key_tag);
=======
#ifndef MAME_MACHINE_NAOMIM4_H
#define MAME_MACHINE_NAOMIM4_H

#include "naomibd.h"

#define MCFG_NAOMI_M4_BOARD_ADD(_tag, _key_tag, _eeprom_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M4_BOARD, _eeprom_tag, _irq_cb) \
	naomi_m4_board::static_set_tags(*device, "^" _key_tag);
>>>>>>> upstream/master

class naomi_m4_board : public naomi_board
{
public:
<<<<<<< HEAD
	naomi_m4_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	static void static_set_tags(device_t &device, const char *_key_tag);

	virtual DECLARE_ADDRESS_MAP(submap, 16);

	DECLARE_READ16_MEMBER(m4_id_r);
protected:
	virtual void device_start();
	virtual void device_reset();

	virtual void board_setup_address(UINT32 address, bool is_dma);
	virtual void board_get_buffer(UINT8 *&base, UINT32 &limit);
	virtual void board_advance(UINT32 size);
	virtual void board_write(offs_t offset, UINT16 data);
=======
	naomi_m4_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	static void static_set_tags(device_t &device, const char *key_tag);

	virtual DECLARE_ADDRESS_MAP(submap, 16) override;

	DECLARE_READ16_MEMBER(m4_id_r);
protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void board_setup_address(uint32_t address, bool is_dma) override;
	virtual void board_get_buffer(uint8_t *&base, uint32_t &limit) override;
	virtual void board_advance(uint32_t size) override;
	virtual void board_write(offs_t offset, uint16_t data) override;
>>>>>>> upstream/master

private:
	enum { BUFFER_SIZE = 32768 };

<<<<<<< HEAD
	static const UINT8 k_sboxes[4][16];

	const char *key_tag;
	UINT16 subkey1, subkey2;
	UINT16 *one_round;

	UINT8 *buffer;
	UINT32 rom_cur_address, buffer_actual_size;
	UINT16 iv;
	UINT8 counter;
=======
	static const uint8_t k_sboxes[4][16];

	uint16_t m4id;
	required_memory_region m_region;
	required_region_ptr<uint8_t> m_key_data;
	uint16_t subkey1, subkey2;
	std::unique_ptr<uint16_t[]> one_round;

	std::unique_ptr<uint8_t[]> buffer;
	uint32_t rom_cur_address, buffer_actual_size;
	uint16_t iv;
	uint8_t counter;
>>>>>>> upstream/master
	bool encryption;
	bool cfi_mode;

	void enc_init();
	void enc_reset();
	void enc_fill();
<<<<<<< HEAD
	UINT16 decrypt_one_round(UINT16 word, UINT16 subkey);
};

extern const device_type NAOMI_M4_BOARD;

#endif
=======
	uint16_t decrypt_one_round(uint16_t word, uint16_t subkey);
};

DECLARE_DEVICE_TYPE(NAOMI_M4_BOARD, naomi_m4_board)

#endif // MAME_MACHINE_NAOMIM4_H
>>>>>>> upstream/master
