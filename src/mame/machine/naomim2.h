// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef _NAOMIM2_H_
#define _NAOMIM2_H_
=======
#ifndef MAME_MACHINE_NAOMIM2_H
#define MAME_MACHINE_NAOMIM2_H

#pragma once
>>>>>>> upstream/master

#include "naomibd.h"
#include "315-5881_crypt.h"


<<<<<<< HEAD
#define MCFG_NAOMI_M2_BOARD_ADD(_tag, _eeprom_tag, _actel_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M2_BOARD, _eeprom_tag, _actel_tag, _irq_cb)
=======
#define MCFG_NAOMI_M2_BOARD_ADD(_tag, _eeprom_tag, _irq_cb) \
	MCFG_NAOMI_BOARD_ADD(_tag, NAOMI_M2_BOARD, _eeprom_tag, _irq_cb)
>>>>>>> upstream/master

class naomi_m2_board : public naomi_board
{
public:
<<<<<<< HEAD
	naomi_m2_board(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	UINT32 rom_cur_address;
	static const int RAM_SIZE = 65536;
	UINT8* ram;

	UINT16 read_callback(UINT32 addr);

protected:
	virtual void device_start();
	virtual void device_reset();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual void board_setup_address(UINT32 address, bool is_dma);
	virtual void board_get_buffer(UINT8 *&base, UINT32 &limit);
	virtual void board_advance(UINT32 size);
	virtual void board_write(offs_t offset, UINT16 data);

private:
	required_device<sega_315_5881_crypt_device> m_cryptdevice;
};

extern const device_type NAOMI_M2_BOARD;

#endif
=======
	naomi_m2_board(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	uint32_t rom_cur_address;
	static const int RAM_SIZE = 65536;
	std::unique_ptr<uint8_t[]> ram;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	virtual void board_setup_address(uint32_t address, bool is_dma) override;
	virtual void board_get_buffer(uint8_t *&base, uint32_t &limit) override;
	virtual void board_advance(uint32_t size) override;
	virtual void board_write(offs_t offset, uint16_t data) override;

private:
	required_device<sega_315_5881_crypt_device> m_cryptdevice;
	required_memory_region m_region;

	uint16_t read_callback(uint32_t addr);
};

DECLARE_DEVICE_TYPE(NAOMI_M2_BOARD, naomi_m2_board)

#endif // MAME_MACHINE_NAOMIM2_H
>>>>>>> upstream/master
