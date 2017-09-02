// license:BSD-3-Clause
// copyright-holders:David Haywood,Alex Marshall
/***************************************************************************

 NMK004 emulation

***************************************************************************/

<<<<<<< HEAD
#ifndef NMK004_H
#define NMK004_H

#include "cpu/tlcs90/tlcs90.h"
#include "sound/2203intf.h"
#include "sound/okim6295.h"

#define MCFG_NMK004_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, NMK004, _clock)


/* device get info callback */
class nmk004_device : public device_t
{
public:
	nmk004_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	WRITE8_MEMBER( write );
	READ8_MEMBER( read );
=======
#ifndef MAME_MACHINE_NMK004_H
#define MAME_MACHINE_NMK004_H

#include "cpu/tlcs90/tlcs90.h"

#pragma once


#define MCFG_NMK004_ADD(tag, clock) \
	MCFG_DEVICE_ADD(tag, NMK004, clock)

#define MCFG_NMK004_RESET_CB(cb) \
	nmk004_device::set_reset_cb(*device, DEVCB_##cb);

class nmk004_device : public device_t
{
public:
	template <typename Obj> static devcb_base &set_reset_cb(device_t &device, Obj &&object)
	{ return downcast<nmk004_device &>(device).m_reset_cb.set_callback(std::forward<Obj>(object)); }

	nmk004_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// host interface
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );
	DECLARE_WRITE_LINE_MEMBER( nmi_w ) { m_cpu->set_input_line(INPUT_LINE_NMI, state); }

>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(nmk004_port4_w);
	DECLARE_WRITE8_MEMBER(nmk004_oki0_bankswitch_w);
	DECLARE_WRITE8_MEMBER(nmk004_oki1_bankswitch_w);
	DECLARE_READ8_MEMBER(nmk004_tonmk004_r);
	DECLARE_WRITE8_MEMBER(nmk004_tomain_w);
	void ym2203_irq_handler(int irq);
<<<<<<< HEAD
	required_device<tlcs90_device> m_cpu;

protected:
	// device-level overrides
	virtual void device_start();
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;


private:
	// internal state
	required_device<cpu_device> m_systemcpu;
	UINT8 to_nmk004;
	UINT8 to_main;

};

extern const device_type NMK004;

#endif  /* NMK004_H */
=======

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// internal state
	required_device<tlcs90_device>  m_cpu;
	devcb_write_line                m_reset_cb;

	uint8_t to_nmk004;
	uint8_t to_main;
};

DECLARE_DEVICE_TYPE(NMK004, nmk004_device)

#endif // MAME_MACHINE_NMK004_H
>>>>>>> upstream/master
