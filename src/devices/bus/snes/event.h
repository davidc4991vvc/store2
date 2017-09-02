// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SNS_EVENT_H
#define __SNS_EVENT_H
=======
#ifndef MAME_BUS_SNES_EVENT_H
#define MAME_BUS_SNES_EVENT_H

#pragma once
>>>>>>> upstream/master

#include "snes_slot.h"
#include "cpu/upd7725/upd7725.h"


// ======================> sns_pfest94_device

class sns_pfest94_device : public device_t,
						public device_sns_cart_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sns_pfest94_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	required_device<upd7725_device> m_upd7725;
	required_ioport m_dsw;

	virtual void speedup_addon_bios_access();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l);
	virtual DECLARE_READ8_MEMBER(read_h);
	virtual DECLARE_READ8_MEMBER(chip_read);
	virtual DECLARE_WRITE8_MEMBER(chip_write);
=======
	sns_pfest94_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void speedup_addon_bios_access() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_READ8_MEMBER(chip_read) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;
>>>>>>> upstream/master

	virtual DECLARE_READ32_MEMBER(necdsp_prg_r);
	virtual DECLARE_READ16_MEMBER(necdsp_data_r);

<<<<<<< HEAD
private:
	UINT8 m_base_bank;
	UINT8 m_mask;
	UINT8 m_status;
	UINT32 m_count;

	std::vector<UINT32> m_dsp_prg;
	std::vector<UINT16> m_dsp_data;

	static const device_timer_id TIMER_EVENT = 0;
=======
protected:
	static constexpr device_timer_id TIMER_EVENT = 0;

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	required_device<upd7725_device> m_upd7725;
	required_ioport m_dsw;

private:
	uint8_t m_base_bank;
	uint8_t m_mask;
	uint8_t m_status;
	uint32_t m_count;

	std::vector<uint32_t> m_dsp_prg;
	std::vector<uint16_t> m_dsp_data;

>>>>>>> upstream/master
	emu_timer *pfest94_timer;
};


// device type definition
<<<<<<< HEAD
extern const device_type SNS_PFEST94;

#endif
=======
DECLARE_DEVICE_TYPE(SNS_PFEST94, sns_pfest94_device)

#endif // MAME_BUS_SNES_EVENT_H
>>>>>>> upstream/master
