// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Wilbert Pol
/***************************************************************************

Template for skeleton device

***************************************************************************/

#pragma once

#ifndef __huc6272DEV_H__
#define __huc6272DEV_H__

=======
// copyright-holders:Wilbert Pol, Angelo Salese
/***************************************************************************

    Hudson/NEC HuC6272 "King" device

***************************************************************************/

#ifndef MAME_VIDEO_HUC6272_H
#define MAME_VIDEO_HUC6272_H

#pragma once

#include "bus/scsi/scsi.h"
#include "bus/scsi/scsicd.h"
#include "video/huc6271.h"
>>>>>>> upstream/master


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_HUC6272_ADD(_tag,_freq) \
	MCFG_DEVICE_ADD(_tag, huc6272, _freq)
=======
#define MCFG_HUC6272_ADD(tag, freq) \
		MCFG_DEVICE_ADD((tag), HUC6272, (freq))

#define MCFG_HUC6272_IRQ_CHANGED_CB(cb) \
		devcb = &huc6272_device::set_irq_changed_callback(*device, (DEVCB_##cb));

#define MCFG_HUC6272_RAINBOW(tag) \
		huc6272_device::set_rainbow_tag(*device, (tag));
>>>>>>> upstream/master


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> huc6272_device

class huc6272_device :  public device_t,
						public device_memory_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	huc6272_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	huc6272_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_irq_changed_callback(device_t &device, Object &&cb) { return downcast<huc6272_device &>(device).m_irq_changed_cb.set_callback(std::forward<Object>(cb)); }
	static void set_rainbow_tag(device_t &device, const char *tag) { downcast<huc6272_device &>(device).m_huc6271_tag = tag; }
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE32_MEMBER( write );
	DECLARE_READ32_MEMBER( read );

<<<<<<< HEAD

protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;

private:
	inline UINT32 read_dword(offs_t address);
	inline void write_dword(offs_t address, UINT32 data);
	UINT8 m_register;
	UINT32 m_kram_addr_r, m_kram_addr_w;
	UINT16 m_kram_inc_r,m_kram_inc_w;
	UINT8 m_kram_page_r,m_kram_page_w;
	UINT32 m_page_setting;
	UINT8 m_bgmode[4];

	struct{
		UINT8 addr;
		UINT8 ctrl;
		UINT16 data[16];
	}m_micro_prg;

	const address_space_config      m_space_config;
};


// device type definition
extern const device_type huc6272;



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************



#endif
=======
protected:
	// device-level overrides
	virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual space_config_vector memory_space_config() const override;

private:
	const char *m_huc6271_tag;

	huc6271_device *m_huc6271;

	uint8_t m_register;
	uint32_t m_kram_addr_r, m_kram_addr_w;
	uint16_t m_kram_inc_r,m_kram_inc_w;
	uint8_t m_kram_page_r,m_kram_page_w;
	uint32_t m_page_setting;

	struct{
		uint32_t bat_address;
		uint32_t cg_address;
		uint8_t mode;
		uint16_t height;
		uint16_t width;
		uint16_t xscroll;
		uint16_t yscroll;
		uint8_t priority;
	}m_bg[4];

	struct{
		uint32_t bat_address;
		uint32_t cg_address;
		uint16_t height;
		uint16_t width;
	}m_bg0sub;

	struct{
		uint8_t index;
		uint8_t ctrl;
	}m_micro_prg;

	const address_space_config      m_program_space_config;
	const address_space_config      m_data_space_config;
	required_shared_ptr<uint16_t>   m_microprg_ram;
	required_shared_ptr<uint32_t>   m_kram_page0;
	required_shared_ptr<uint32_t>   m_kram_page1;
	required_device<scsi_port_device> m_scsibus;
	required_device<input_buffer_device> m_scsi_data_in;
	required_device<output_latch_device> m_scsi_data_out;
	required_device<input_buffer_device> m_scsi_ctrl_in;

	/* Callback for when the irq line may have changed (mandatory) */
	devcb_write_line    m_irq_changed_cb;

	uint32_t read_dword(offs_t address);
	void write_dword(offs_t address, uint32_t data);
	void write_microprg_data(offs_t address, uint16_t data);
};

// device type definition
DECLARE_DEVICE_TYPE(HUC6272, huc6272_device)

#endif // MAME_VIDEO_HUC6272_H
>>>>>>> upstream/master
