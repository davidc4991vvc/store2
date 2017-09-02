// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_NTDEC_H
#define __NES_NTDEC_H
=======
#ifndef MAME_BUS_NES_NTDEC_H
#define MAME_BUS_NES_NTDEC_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_ntdec_asder_device

class nes_ntdec_asder_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ntdec_asder_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	UINT8 m_latch;
=======
	nes_ntdec_asder_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_latch;
>>>>>>> upstream/master
};


// ======================> nes_ntdec_fh_device

class nes_ntdec_fh_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_ntdec_fh_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_m);

	virtual void pcb_reset();
};





// device type definition
extern const device_type NES_NTDEC_ASDER;
extern const device_type NES_NTDEC_FH;

#endif
=======
	nes_ntdec_fh_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_m) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_NTDEC_ASDER, nes_ntdec_asder_device)
DECLARE_DEVICE_TYPE(NES_NTDEC_FH,    nes_ntdec_fh_device)

#endif // MAME_BUS_NES_NTDEC_H
>>>>>>> upstream/master
