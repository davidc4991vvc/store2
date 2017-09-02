// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_RACERMATE_H
#define __NES_RACERMATE_H
=======
#ifndef MAME_BUS_NES_RACERMATE_H
#define MAME_BUS_NES_RACERMATE_H
>>>>>>> upstream/master

#include "nxrom.h"


// ======================> nes_racermate_device

class nes_racermate_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_racermate_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();

private:
	void update_banks();
	UINT8 m_latch;
};





// device type definition
extern const device_type NES_RACERMATE;

#endif
=======
	nes_racermate_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

private:
	void update_banks();
	uint8_t m_latch;
};


// device type definition
DECLARE_DEVICE_TYPE(NES_RACERMATE, nes_racermate_device)

#endif // MAME_BUS_NES_RACERMATE_H
>>>>>>> upstream/master
