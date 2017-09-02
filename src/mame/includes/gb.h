// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
/*****************************************************************************
 *
 * includes/gb.h
 *
 ****************************************************************************/

#ifndef GB_H_
#define GB_H_

<<<<<<< HEAD
#include "audio/gb.h"
=======
#include "sound/gb.h"
>>>>>>> upstream/master
#include "cpu/lr35902/lr35902.h"
#include "bus/gameboy/gb_slot.h"
#include "machine/ram.h"
#include "video/gb_lcd.h"

<<<<<<< HEAD
/* Interrupts */
#define VBL_INT               0       /* V-Blank    */
#define LCD_INT               1       /* LCD Status */
#define TIM_INT               2       /* Timer      */
#define SIO_INT               3       /* Serial I/O */
#define EXT_INT               4       /* Joypad     */

#ifdef TIMER
#undef TIMER
#endif

/* Cartridge types */
#define CART_RAM    0x01    /* Cartridge has RAM                             */
#define BATTERY     0x02    /* Cartridge has a battery to save RAM           */
#define TIMER       0x04    /* Cartridge has a real-time-clock (MBC3 only)   */
#define RUMBLE      0x08    /* Cartridge has a rumble motor (MBC5 only)      */
#define SRAM        0x10    /* Cartridge has SRAM                            */
#define UNKNOWN     0x80    /* Cartridge is of an unknown type               */

#define DMG_FRAMES_PER_SECOND   59.732155
#define SGB_FRAMES_PER_SECOND   61.17


#define MAX_ROMBANK 512
#define MAX_RAMBANK 256


=======
>>>>>>> upstream/master

class gb_state : public driver_device
{
public:
	gb_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_cartslot(*this, "gbslot"),
		m_maincpu(*this, "maincpu"),
<<<<<<< HEAD
		m_custom(*this, "custom"),
=======
		m_apu(*this, "apu"),
>>>>>>> upstream/master
		m_region_maincpu(*this, "maincpu"),
		m_rambank(*this, "cgb_ram"),
		m_inputs(*this, "INPUTS"),
		m_bios_hack(*this, "SKIP_CHECK"),
		m_ram(*this, RAM_TAG),
<<<<<<< HEAD
		m_lcd(*this, "lcd") { }

	//gb_state driver_data;
	UINT8       m_gb_io[0x10];

	/* Timer related */
	UINT16      m_divcount;
	UINT8       m_shift;
	UINT16      m_shift_cycles;
	UINT8       m_triggering_irq;
	UINT8       m_reloading;

	/* Serial I/O related */
	UINT32      m_sio_count;             /* Serial I/O counter */
	emu_timer   *m_gb_serial_timer;

	/* SGB variables */
	INT8 m_sgb_packets;
	UINT8 m_sgb_bitcount;
	UINT8 m_sgb_bytecount;
	UINT8 m_sgb_start;
	UINT8 m_sgb_rest;
	UINT8 m_sgb_controller_no;
	UINT8 m_sgb_controller_mode;
	UINT8 m_sgb_data[0x100];

	/* CGB variables */
	UINT8       *m_gbc_rammap[8];           /* (CGB) Addresses of internal RAM banks */
	UINT8       m_gbc_rambank;          /* (CGB) Current CGB RAM bank */

	int m_bios_disable;
=======
		m_ppu(*this, "ppu") { }

	uint8_t       m_gb_io[0x10];

	/* Timer related */
	uint16_t      m_divcount;
	uint8_t       m_shift;
	uint16_t      m_shift_cycles;
	uint8_t       m_triggering_irq;
	uint8_t       m_reloading;

	/* Serial I/O related */
	uint16_t      m_internal_serial_clock;
	uint16_t      m_internal_serial_frequency;
	uint32_t      m_sio_count;             /* Serial I/O counter */

	/* SGB variables */
	int8_t m_sgb_packets;
	uint8_t m_sgb_bitcount;
	uint8_t m_sgb_bytecount;
	uint8_t m_sgb_start;
	uint8_t m_sgb_rest;
	uint8_t m_sgb_controller_no;
	uint8_t m_sgb_controller_mode;
	uint8_t m_sgb_data[0x100];

	/* CGB variables */
	uint8_t       *m_gbc_rammap[8];           /* (CGB) Addresses of internal RAM banks */
	uint8_t       m_gbc_rambank;          /* (CGB) Current CGB RAM bank */

	bool m_bios_disable;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(gb_io_w);
	DECLARE_WRITE8_MEMBER(gb_io2_w);
	DECLARE_WRITE8_MEMBER(sgb_io_w);
	DECLARE_READ8_MEMBER(gb_ie_r);
	DECLARE_WRITE8_MEMBER(gb_ie_w);
	DECLARE_READ8_MEMBER(gb_io_r);
<<<<<<< HEAD
=======
	DECLARE_WRITE8_MEMBER(gbc_io_w);
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(gbc_io2_w);
	DECLARE_READ8_MEMBER(gbc_io2_r);
	DECLARE_PALETTE_INIT(gb);
	DECLARE_MACHINE_START(sgb);
	DECLARE_MACHINE_RESET(sgb);
	DECLARE_PALETTE_INIT(sgb);
	DECLARE_PALETTE_INIT(gbp);
	DECLARE_MACHINE_START(gbc);
	DECLARE_MACHINE_RESET(gbc);
	DECLARE_PALETTE_INIT(gbc);
<<<<<<< HEAD
	TIMER_CALLBACK_MEMBER(gb_serial_timer_proc);
=======
>>>>>>> upstream/master
	DECLARE_WRITE8_MEMBER(gb_timer_callback);

	DECLARE_READ8_MEMBER(gb_cart_r);
	DECLARE_READ8_MEMBER(gbc_cart_r);
	DECLARE_WRITE8_MEMBER(gb_bank_w);
	DECLARE_READ8_MEMBER(gb_ram_r);
	DECLARE_WRITE8_MEMBER(gb_ram_w);
	DECLARE_READ8_MEMBER(gb_echo_r);
	DECLARE_WRITE8_MEMBER(gb_echo_w);
	optional_device<gb_cart_slot_device> m_cartslot;

protected:
<<<<<<< HEAD
	required_device<lr35902_cpu_device> m_maincpu;
	required_device<gameboy_sound_device> m_custom;
=======
	enum {
		SIO_ENABLED = 0x80,
		SIO_FAST_CLOCK = 0x02,
		SIO_INTERNAL_CLOCK = 0x01
	};

	required_device<lr35902_cpu_device> m_maincpu;
	required_device<gameboy_sound_device> m_apu;
>>>>>>> upstream/master
	required_memory_region m_region_maincpu;
	optional_memory_bank m_rambank;   // cgb
	required_ioport m_inputs;
	required_ioport m_bios_hack;
	optional_device<ram_device> m_ram;
<<<<<<< HEAD
	required_device<gb_lcd_device> m_lcd;
=======
	required_device<dmg_ppu_device> m_ppu;
>>>>>>> upstream/master

	void gb_timer_increment();
	void gb_timer_check_irq();
	void gb_init();
	void gb_init_regs();
<<<<<<< HEAD
	void gb_video_reset(int mode);
	void gb_video_start(int mode);
=======
	void gb_serial_timer_tick();
>>>>>>> upstream/master

	void save_gb_base();
	void save_gbc_only();
	void save_sgb_only();

<<<<<<< HEAD
	virtual void machine_start();
	virtual void machine_reset();
=======
	virtual void machine_start() override;
	virtual void machine_reset() override;
>>>>>>> upstream/master
};


class megaduck_state : public gb_state
{
public:
	megaduck_state(const machine_config &mconfig, device_type type, const char *tag)
		: gb_state(mconfig, type, tag)
		, m_cartslot(*this, "duckslot")
	{ }

	DECLARE_READ8_MEMBER(megaduck_video_r);
	DECLARE_WRITE8_MEMBER(megaduck_video_w);
	DECLARE_WRITE8_MEMBER(megaduck_sound_w1);
	DECLARE_READ8_MEMBER(megaduck_sound_r1);
	DECLARE_WRITE8_MEMBER(megaduck_sound_w2);
	DECLARE_READ8_MEMBER(megaduck_sound_r2);
	DECLARE_MACHINE_START(megaduck);
	DECLARE_MACHINE_RESET(megaduck);
	DECLARE_PALETTE_INIT(megaduck);

	DECLARE_READ8_MEMBER(cart_r);
	DECLARE_WRITE8_MEMBER(bank1_w);
	DECLARE_WRITE8_MEMBER(bank2_w);
	optional_device<megaduck_cart_slot_device> m_cartslot;
};



#endif /* GB_H_ */
