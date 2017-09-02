// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __VCS_DCP_H
#define __VCS_DCP_H
=======
#ifndef MAME_BUS_VCS_DPC_H
#define MAME_BUS_VCS_DPC_H

#pragma once
>>>>>>> upstream/master

#include "rom.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// TO DO: DPC should be made a separate device!

<<<<<<< HEAD
struct df_t {
	UINT8   top;
	UINT8   bottom;
	UINT8   low;
	UINT8   high;
	UINT8   flag;
	UINT8   music_mode;     /* Only used by data fetchers 5,6, and 7 */
	UINT8   osc_clk;        /* Only used by data fetchers 5,6, and 7 */
};

=======
>>>>>>> upstream/master
//  m_dpc.oscillator = machine().scheduler().timer_alloc(timer_expired_delegate(FUNC(a2600_state::modeDPC_timer_callback),this));

class dpc_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	dpc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	df_t    m_df[8];
	UINT8   m_movamt;
	UINT8   m_latch_62;
	UINT8   m_latch_64;
	UINT8   m_dlc;
	UINT8   m_shift_reg;
	UINT8   *m_displaydata;
	void set_display_data(UINT8 *data) { m_displaydata = data; }

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);

private:

	void decrement_counter(UINT8 data_fetcher);
	void check_flag(UINT8 data_fetcher);

	static const device_timer_id TIMER_OSC = 0;
=======
	dpc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_display_data(uint8_t *data) { m_displaydata = data; }

	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);

protected:
	static constexpr device_timer_id TIMER_OSC = 0;

	struct df_t {
		uint8_t   top;
		uint8_t   bottom;
		uint8_t   low;
		uint8_t   high;
		uint8_t   flag;
		uint8_t   music_mode;     /* Only used by data fetchers 5,6, and 7 */
		uint8_t   osc_clk;        /* Only used by data fetchers 5,6, and 7 */
	};

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;

	df_t    m_df[8];
	uint8_t   m_movamt;
	uint8_t   m_latch_62;
	uint8_t   m_latch_64;
	uint8_t   m_dlc;
	uint8_t   m_shift_reg;
	uint8_t   *m_displaydata;

private:
	void decrement_counter(uint8_t data_fetcher);
	void check_flag(uint8_t data_fetcher);

>>>>>>> upstream/master
	emu_timer *m_oscillator;
};


// device type definition
<<<<<<< HEAD
extern const device_type ATARI_DPC;
=======
DECLARE_DEVICE_TYPE(ATARI_DPC, dpc_device)
>>>>>>> upstream/master



// ======================> a26_rom_dpc_device

class a26_rom_dpc_device : public a26_rom_f8_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	a26_rom_dpc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void device_reset();
=======
	a26_rom_dpc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	required_device<dpc_device> m_dpc;

	// reading and writing
<<<<<<< HEAD
	virtual DECLARE_READ8_MEMBER(read_rom);
	virtual DECLARE_WRITE8_MEMBER(write_bank);
	virtual DECLARE_DIRECT_UPDATE_MEMBER(cart_opbase);

	virtual void setup_addon_ptr(UINT8 *ptr);

protected:
//  int m_reset_bank;
=======
	virtual DECLARE_READ8_MEMBER(read_rom) override;
	virtual DECLARE_WRITE8_MEMBER(write_bank) override;

	virtual void setup_addon_ptr(uint8_t *ptr) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type A26_ROM_DPC;

#endif
=======
DECLARE_DEVICE_TYPE(A26_ROM_DPC, a26_rom_dpc_device)

#endif // MAME_BUS_VCS_DPC_H
>>>>>>> upstream/master
