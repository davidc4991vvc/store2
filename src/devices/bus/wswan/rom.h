// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __WS_ROM_H
#define __WS_ROM_H
=======
#ifndef MAME_BUS_WSWAN_ROM_H
#define MAME_BUS_WSWAN_ROM_H
>>>>>>> upstream/master

#include "slot.h"


// ======================> ws_rom_device

class ws_rom_device : public device_t,
						public device_ws_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ws_rom_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	ws_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom20);
	virtual DECLARE_READ8_MEMBER(read_rom30);
	virtual DECLARE_READ8_MEMBER(read_rom40);
	virtual DECLARE_READ8_MEMBER(read_io);
	virtual DECLARE_WRITE8_MEMBER(write_io);

protected:
	UINT8 m_io_regs[0x10];
	UINT32 m_base20, m_base30, m_base40;

	// RTC
	UINT8   m_rtc_setting;    /* Timer setting byte */
	UINT8   m_rtc_year;       /* Year */
	UINT8   m_rtc_month;      /* Month */
	UINT8   m_rtc_day;        /* Day */
	UINT8   m_rtc_day_of_week;    /* Day of the week */
	UINT8   m_rtc_hour;       /* Hour, high bit = 0 => AM, high bit = 1 => PM */
	UINT8   m_rtc_minute;     /* Minute */
	UINT8   m_rtc_second;     /* Second */
	UINT8   m_rtc_index;      /* index for reading/writing of current of alarm time */

	static const device_timer_id TIMER_RTC = 0;
=======
	ws_rom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom20) override;
	virtual DECLARE_READ8_MEMBER(read_rom30) override;
	virtual DECLARE_READ8_MEMBER(read_rom40) override;
	virtual DECLARE_READ8_MEMBER(read_io) override;
	virtual DECLARE_WRITE8_MEMBER(write_io) override;

protected:
	static constexpr device_timer_id TIMER_RTC = 0;

	ws_rom_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	uint8_t m_io_regs[0x10];
	uint32_t m_base20, m_base30, m_base40;

	// RTC
	uint8_t   m_rtc_setting;    /* Timer setting byte */
	uint8_t   m_rtc_year;       /* Year */
	uint8_t   m_rtc_month;      /* Month */
	uint8_t   m_rtc_day;        /* Day */
	uint8_t   m_rtc_day_of_week;    /* Day of the week */
	uint8_t   m_rtc_hour;       /* Hour, high bit = 0 => AM, high bit = 1 => PM */
	uint8_t   m_rtc_minute;     /* Minute */
	uint8_t   m_rtc_second;     /* Second */
	uint8_t   m_rtc_index;      /* index for reading/writing of current of alarm time */

>>>>>>> upstream/master
	emu_timer *rtc_timer;
};


// ======================> ws_rom_sram_device

class ws_rom_sram_device : public ws_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	ws_rom_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_ram);
	virtual DECLARE_WRITE8_MEMBER(write_ram);
	virtual DECLARE_WRITE8_MEMBER(write_io);

private:
	UINT32 m_nvram_base;
=======
	ws_rom_sram_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_ram) override;
	virtual DECLARE_WRITE8_MEMBER(write_io) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint32_t m_nvram_base;
>>>>>>> upstream/master
};


// ======================> ws_rom_eeprom_device

class ws_rom_eeprom_device : public ws_rom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	ws_rom_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_io);
	virtual DECLARE_WRITE8_MEMBER(write_io);

private:
	UINT8   m_eeprom_mode;       /* eeprom mode */
	UINT16  m_eeprom_address;    /* Read/write address */
	UINT8   m_eeprom_command;    /* Commands: 00, 01, 02, 03, 04, 08, 0C */
	UINT8   m_eeprom_start;      /* start bit */
	UINT8   m_eeprom_write_enabled;  /* write enabled yes/no */
=======
	ws_rom_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_io) override;
	virtual DECLARE_WRITE8_MEMBER(write_io) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t   m_eeprom_mode;       /* eeprom mode */
	uint16_t  m_eeprom_address;    /* Read/write address */
	uint8_t   m_eeprom_command;    /* Commands: 00, 01, 02, 03, 04, 08, 0C */
	uint8_t   m_eeprom_start;      /* start bit */
	uint8_t   m_eeprom_write_enabled;  /* write enabled yes/no */
>>>>>>> upstream/master
};



// device type definition
<<<<<<< HEAD
extern const device_type WS_ROM_STD;
extern const device_type WS_ROM_SRAM;
extern const device_type WS_ROM_EEPROM;


#endif
=======
DECLARE_DEVICE_TYPE(WS_ROM_STD,    ws_rom_device)
DECLARE_DEVICE_TYPE(WS_ROM_SRAM,   ws_rom_sram_device)
DECLARE_DEVICE_TYPE(WS_ROM_EEPROM, ws_rom_eeprom_device)

#endif // MAME_BUS_WSWAN_ROM_H
>>>>>>> upstream/master
