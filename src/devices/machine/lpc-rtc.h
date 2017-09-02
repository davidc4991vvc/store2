// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef LPC_RTC_H
#define LPC_RTC_H
=======
#ifndef MAME_MACHINE_LPC_RTC_H
#define MAME_MACHINE_LPC_RTC_H

#pragma once
>>>>>>> upstream/master

#include "lpc.h"

#define MCFG_LPC_RTC_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, LPC_RTC, 0)

class lpc_rtc_device : public lpc_device {
public:
<<<<<<< HEAD
	lpc_rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void map_device(UINT64 memory_window_start, UINT64 memory_window_end, UINT64 memory_offset, address_space *memory_space,
							UINT64 io_window_start, UINT64 io_window_end, UINT64 io_offset, address_space *io_space);

	virtual void map_extdevice(UINT64 memory_window_start, UINT64 memory_window_end, UINT64 memory_offset, address_space *memory_space,
									UINT64 io_window_start, UINT64 io_window_end, UINT64 io_offset, address_space *io_space);
=======
	lpc_rtc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void map_device(uint64_t memory_window_start, uint64_t memory_window_end, uint64_t memory_offset, address_space *memory_space,
							uint64_t io_window_start, uint64_t io_window_end, uint64_t io_offset, address_space *io_space) override;

	virtual void map_extdevice(uint64_t memory_window_start, uint64_t memory_window_end, uint64_t memory_offset, address_space *memory_space,
									uint64_t io_window_start, uint64_t io_window_end, uint64_t io_offset, address_space *io_space);
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(  index_r);
	DECLARE_WRITE8_MEMBER( index_w);
	DECLARE_READ8_MEMBER(  target_r);
	DECLARE_WRITE8_MEMBER( target_w);
	DECLARE_READ8_MEMBER(  extindex_r);
	DECLARE_WRITE8_MEMBER( extindex_w);
	DECLARE_READ8_MEMBER(  exttarget_r);
	DECLARE_WRITE8_MEMBER( exttarget_w);

protected:
<<<<<<< HEAD
	void device_start();
	void device_reset();
=======
	void device_start() override;
	void device_reset() override;
>>>>>>> upstream/master

private:
	DECLARE_ADDRESS_MAP(map, 32);
	DECLARE_ADDRESS_MAP(extmap, 32);

<<<<<<< HEAD
	UINT8 cur_index, cur_extindex;
	UINT8 ram[256];
};

extern const device_type LPC_RTC;

#endif
=======
	uint8_t cur_index, cur_extindex;
	uint8_t ram[256];
};

DECLARE_DEVICE_TYPE(LPC_RTC, lpc_rtc_device)

#endif // MAME_MACHINE_LPC_RTC_H
>>>>>>> upstream/master
