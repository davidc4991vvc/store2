// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    COMX-35E Expansion Box emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __COMX_EB__
#define __COMX_EB__
=======
#ifndef MAME_BUS_COMX35_EXPBOX_H
#define MAME_BUS_COMX35_EXPBOX_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"



//**************************************************************************
//  CONSTANTS
//**************************************************************************

#define MAX_EB_SLOTS    4



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> comx_eb_device

class comx_eb_device : public device_t,
						public device_comx_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	comx_eb_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_WRITE_LINE_MEMBER( slot1_irq_w ) { m_irq[0] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot2_irq_w ) { m_irq[1] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot3_irq_w ) { m_irq[2] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot4_irq_w ) { m_irq[3] = state; set_irq(); }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r();
	virtual void comx_q_w(int state);
	virtual UINT8 comx_mrd_r(address_space &space, offs_t offset, int *extrom);
	virtual void comx_mwr_w(address_space &space, offs_t offset, UINT8 data);
	virtual UINT8 comx_io_r(address_space &space, offs_t offset);
	virtual void comx_io_w(address_space &space, offs_t offset, UINT8 data);
=======
	comx_eb_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_comx_expansion_card_interface overrides
	virtual int comx_ef4_r() override;
	virtual void comx_q_w(int state) override;
	virtual uint8_t comx_mrd_r(address_space &space, offs_t offset, int *extrom) override;
	virtual void comx_mwr_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual uint8_t comx_io_r(address_space &space, offs_t offset) override;
	virtual void comx_io_w(address_space &space, offs_t offset, uint8_t data) override;
>>>>>>> upstream/master

	void set_irq() { m_slot->irq_w(m_irq[0] || m_irq[1] || m_irq[2] || m_irq[3]); }

private:
<<<<<<< HEAD
=======
	DECLARE_WRITE_LINE_MEMBER( slot1_irq_w ) { m_irq[0] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot2_irq_w ) { m_irq[1] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot3_irq_w ) { m_irq[2] = state; set_irq(); }
	DECLARE_WRITE_LINE_MEMBER( slot4_irq_w ) { m_irq[3] = state; set_irq(); }

>>>>>>> upstream/master
	required_memory_region m_rom;

	comx_expansion_slot_device  *m_expansion_slot[MAX_EB_SLOTS];
	int m_irq[MAX_EB_SLOTS];

<<<<<<< HEAD
	UINT8 m_select;
=======
	uint8_t m_select;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type COMX_EB;


#endif
=======
DECLARE_DEVICE_TYPE(COMX_EB, comx_eb_device)


#endif // MAME_BUS_COMX35_EXPBOX_H
>>>>>>> upstream/master
