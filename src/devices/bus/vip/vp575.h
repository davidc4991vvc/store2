// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    RCA VIP Expansion Board VP-575 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VP575__
#define __VP575__

#include "emu.h"
=======
#ifndef MAME_BUS_VIP_VP575_H
#define MAME_BUS_VIP_VP575_H

#pragma once

>>>>>>> upstream/master
#include "exp.h"



//**************************************************************************
<<<<<<< HEAD
//  MACROS/CONSTANTS
//**************************************************************************

#define MAX_SLOTS 5



//**************************************************************************
=======
>>>>>>> upstream/master
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vp575_device

class vp575_device : public device_t,
						public device_vip_expansion_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vp575_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// not really public
=======
	vp575_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_vip_expansion_card_interface overrides
	virtual uint8_t vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh) override;
	virtual void vip_program_w(address_space &space, offs_t offset, uint8_t data, int cdef, int *minh) override;
	virtual uint8_t vip_io_r(address_space &space, offs_t offset) override;
	virtual void vip_io_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual uint8_t vip_dma_r(address_space &space, offs_t offset) override;
	virtual void vip_dma_w(address_space &space, offs_t offset, uint8_t data) override;
	virtual uint32_t vip_screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect) override;
	virtual int vip_ef1_r() override;
	virtual int vip_ef3_r() override;
	virtual int vip_ef4_r() override;
	virtual void vip_sc_w(int data) override;
	virtual void vip_q_w(int state) override;
	virtual void vip_run_w(int state) override;

private:
	static constexpr unsigned MAX_SLOTS = 5;

>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( exp1_int_w ) { m_int[0] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp2_int_w ) { m_int[1] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp3_int_w ) { m_int[2] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp4_int_w ) { m_int[3] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp5_int_w ) { m_int[4] = state; update_interrupts(); }

	DECLARE_WRITE_LINE_MEMBER( exp1_dma_out_w ) { m_dma_out[0] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp2_dma_out_w ) { m_dma_out[1] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp3_dma_out_w ) { m_dma_out[2] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp4_dma_out_w ) { m_dma_out[3] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp5_dma_out_w ) { m_dma_out[4] = state; update_interrupts(); }

	DECLARE_WRITE_LINE_MEMBER( exp1_dma_in_w ) { m_dma_in[0] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp2_dma_in_w ) { m_dma_in[1] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp3_dma_in_w ) { m_dma_in[2] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp4_dma_in_w ) { m_dma_in[3] = state; update_interrupts(); }
	DECLARE_WRITE_LINE_MEMBER( exp5_dma_in_w ) { m_dma_in[4] = state; update_interrupts(); }

	void update_interrupts();

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();

	// device_vip_expansion_card_interface overrides
	virtual UINT8 vip_program_r(address_space &space, offs_t offset, int cs, int cdef, int *minh);
	virtual void vip_program_w(address_space &space, offs_t offset, UINT8 data, int cdef, int *minh);
	virtual UINT8 vip_io_r(address_space &space, offs_t offset);
	virtual void vip_io_w(address_space &space, offs_t offset, UINT8 data);
	virtual UINT8 vip_dma_r(address_space &space, offs_t offset);
	virtual void vip_dma_w(address_space &space, offs_t offset, UINT8 data);
	virtual UINT32 vip_screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	virtual int vip_ef1_r();
	virtual int vip_ef3_r();
	virtual int vip_ef4_r();
	virtual void vip_sc_w(int data);
	virtual void vip_q_w(int state);
	virtual void vip_run_w(int state);

private:
	vip_expansion_slot_device *m_expansion_slot[MAX_SLOTS];
=======
	required_device_array<vip_expansion_slot_device, MAX_SLOTS> m_expansion_slot;
>>>>>>> upstream/master

	int m_int[MAX_SLOTS];
	int m_dma_out[MAX_SLOTS];
	int m_dma_in[MAX_SLOTS];
};


// device type definition
<<<<<<< HEAD
extern const device_type VP575;


#endif
=======
DECLARE_DEVICE_TYPE(VP575, vp575_device)

#endif // MAME_BUS_VIP_VP575_H
>>>>>>> upstream/master
