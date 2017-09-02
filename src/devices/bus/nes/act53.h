// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __NES_ACTION53_H
#define __NES_ACTION53_H
=======
#ifndef MAME_BUS_NES_ACT53_H
#define MAME_BUS_NES_ACT53_H
>>>>>>> upstream/master

#include "nxrom.h"


<<<<<<< HEAD
// ======================> nes_racermate_device
=======
// ======================> nes_action53_device
>>>>>>> upstream/master

class nes_action53_device : public nes_nrom_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	nes_action53_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual DECLARE_WRITE8_MEMBER(write_l);
	virtual DECLARE_WRITE8_MEMBER(write_h);

	virtual void pcb_reset();
=======
	nes_action53_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_WRITE8_MEMBER(write_l) override;
	virtual DECLARE_WRITE8_MEMBER(write_h) override;

	virtual void pcb_reset() override;

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

private:
	void update_prg();
	void update_mirr();
<<<<<<< HEAD
	UINT8 m_sel;
	UINT8 m_reg[4];
};





// device type definition
extern const device_type NES_ACTION53;

#endif
=======
	uint8_t m_sel;
	uint8_t m_reg[4];
};

// device type definition
DECLARE_DEVICE_TYPE(NES_ACTION53, nes_action53_device)

#endif // MAME_BUS_NES_ACT53_H
>>>>>>> upstream/master
