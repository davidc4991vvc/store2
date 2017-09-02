// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_2A03PUR_H
#define __NES_2A03PUR_H
=======
#ifndef MAME_BUS_NES_2A03PUR_H
#define MAME_BUS_NES_2A03PUR_H

#pragma once
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_racermate_device

class nes_2a03pur_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_2a03pur_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_WRITE8_MEMBER(write_l);

	virtual void pcb_reset();

private:
	UINT8 m_reg[8];
=======
	nes_2a03pur_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_WRITE8_MEMBER(write_l) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;

private:
	uint8_t m_reg[8];
>>>>>>> upstream/master
};



// device type definition
extern const device_type NES_2A03PURITANS;

<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_NES_2A03PUR_H
>>>>>>> upstream/master
