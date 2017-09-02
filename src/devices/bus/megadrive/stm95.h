// license:BSD-3-Clause
// copyright-holders:Fabio Priuli, MetalliC
<<<<<<< HEAD
#ifndef __MD_STM95_H
#define __MD_STM95_H
=======
#ifndef MAME_BUS_MEGADRIVE_STM95_H
#define MAME_BUS_MEGADRIVE_STM95_H

#pragma once
>>>>>>> upstream/master

#include "md_slot.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

/* ST M95320 32Kbit serial EEPROM implementation */
// TO DO: STM95 should be made a separate EEPROM device and this should be merged with md_eeprom.c!

<<<<<<< HEAD
#define M95320_SIZE 0x1000

enum STMSTATE
{
	IDLE = 0,
	CMD_WRSR,
	CMD_RDSR,
	M95320_CMD_READ,
	CMD_WRITE,
	READING,
	WRITING
};

class stm95_eeprom_device
{
public:
	stm95_eeprom_device(running_machine &machine, UINT8 *eeprom);
	running_machine &machine() const { return m_machine; }

	UINT8   *eeprom_data;
=======
class stm95_eeprom_device
{
public:
	static constexpr unsigned M95320_SIZE = 0x1000;

	stm95_eeprom_device(running_machine &machine, uint8_t *eeprom);
	running_machine &machine() const { return m_machine; }

	uint8_t   *eeprom_data;
>>>>>>> upstream/master
	void    set_cs_line(int);
	void    set_halt_line(int state) {}; // not implemented
	void    set_si_line(int);
	void    set_sck_line(int state);
	int     get_so_line(void);

protected:
<<<<<<< HEAD
=======
	enum STMSTATE
	{
		IDLE = 0,
		CMD_WRSR,
		CMD_RDSR,
		M95320_CMD_READ,
		CMD_WRITE,
		READING,
		WRITING
	};

>>>>>>> upstream/master
	int     latch;
	int     reset_line;
	int     sck_line;
	int     WEL;

	STMSTATE    stm_state;
	int     stream_pos;
	int     stream_data;
	int     eeprom_addr;

	running_machine& m_machine;
};


// ======================> md_eeprom_stm95_device

<<<<<<< HEAD
class md_eeprom_stm95_device : public device_t,
						public device_md_cart_interface
{
public:
	// construction/destruction
	md_eeprom_stm95_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	md_eeprom_stm95_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read);
	virtual DECLARE_READ16_MEMBER(read_a13);
	virtual DECLARE_WRITE16_MEMBER(write_a13);

private:
	UINT8 m_bank[3];
	int m_rdcnt;

	auto_pointer<stm95_eeprom_device> m_stm95;
=======
class md_eeprom_stm95_device : public device_t, public device_md_cart_interface
{
public:
	// construction/destruction
	md_eeprom_stm95_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read) override;
	virtual DECLARE_READ16_MEMBER(read_a13) override;
	virtual DECLARE_WRITE16_MEMBER(write_a13) override;

protected:
	md_eeprom_stm95_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

private:
	uint8_t m_bank[3];
	int m_rdcnt;

	std::unique_ptr<stm95_eeprom_device> m_stm95;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MD_EEPROM_STM95;

#endif
=======
DECLARE_DEVICE_TYPE(MD_EEPROM_STM95, md_eeprom_stm95_device)

#endif // MAME_BUS_MEGADRIVE_STM95_H
>>>>>>> upstream/master
