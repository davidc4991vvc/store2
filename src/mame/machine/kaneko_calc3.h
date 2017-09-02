// license:BSD-3-Clause
// copyright-holders:Luca Elia, David Haywood
/* CALC 3 */
<<<<<<< HEAD

#define VERBOSE_OUTPUT 0

=======
#ifndef MAME_MACHINE_KANEKO_CALC3_H
#define MAME_MACHINE_KANEKO_CALC3_H

#pragma once
>>>>>>> upstream/master


class kaneko_calc3_device : public device_t
{
public:
<<<<<<< HEAD
	kaneko_calc3_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	kaneko_calc3_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_WRITE16_MEMBER(mcu_com0_w);
	DECLARE_WRITE16_MEMBER(mcu_com1_w);
	DECLARE_WRITE16_MEMBER(mcu_com2_w);
	DECLARE_WRITE16_MEMBER(mcu_com3_w);

	void reset_run_timer();
	void mcu_run();

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

private:
	required_shared_ptr<UINT16> m_mcuram;
	int m_mcu_status;
	int m_mcu_command_offset;
	UINT16 m_mcu_crc;
	UINT8 m_decryption_key_byte;
	UINT8 m_alternateswaps;
	UINT8 m_shift;
	UINT8 m_subtracttype;
	UINT8 m_mode;
	UINT8 m_blocksize_offset;
	UINT16 m_dataend;
	UINT16 m_database;
	int m_data_header[2];
	UINT32 m_writeaddress;
	UINT32 m_writeaddress_current;
	UINT16 m_dsw_addr;
	UINT16 m_eeprom_addr;
	UINT16 m_poll_addr;
	UINT16 m_checksumaddress;
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

private:
	required_shared_ptr<uint16_t> m_mcuram;
	int m_mcu_status;
	int m_mcu_command_offset;
	uint16_t m_mcu_crc;
	uint8_t m_decryption_key_byte;
	uint8_t m_alternateswaps;
	uint8_t m_shift;
	uint8_t m_subtracttype;
	uint8_t m_mode;
	uint8_t m_blocksize_offset;
	uint16_t m_dataend;
	uint16_t m_database;
	int m_data_header[2];
	uint32_t m_writeaddress;
	uint32_t m_writeaddress_current;
	uint16_t m_dsw_addr;
	uint16_t m_eeprom_addr;
	uint16_t m_poll_addr;
	uint16_t m_checksumaddress;
>>>>>>> upstream/master
	emu_timer* m_runtimer;

	enum
	{
		MCU_RUN_TIMER
	};

	void mcu_init();
	void initial_scan_tables();
<<<<<<< HEAD
	void mcu_com_w(offs_t offset, UINT16 data, UINT16 mem_mask, int _n_);
	UINT8 shift_bits(UINT8 dat, int bits);
	int decompress_table(int tabnum, UINT8* dstram, int dstoffset);
};


extern const device_type KANEKO_CALC3;
=======
	void mcu_com_w(offs_t offset, uint16_t data, uint16_t mem_mask, int _n_);
	uint8_t shift_bits(uint8_t dat, int bits);
	int decompress_table(int tabnum, uint8_t* dstram, int dstoffset);
};


DECLARE_DEVICE_TYPE(KANEKO_CALC3, kaneko_calc3_device)

#endif // MAME_MACHINE_KANEKO_CALC3_H
>>>>>>> upstream/master
