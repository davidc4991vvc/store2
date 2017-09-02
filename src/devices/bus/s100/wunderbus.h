// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Morrow Designs Wunderbus I/O card emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __S100_WUNDERBUS__
#define __S100_WUNDERBUS__
=======
#ifndef MAME_BUS_S100_WUNDERBUS_H
#define MAME_BUS_S100_WUNDERBUS_H

#pragma once
>>>>>>> upstream/master

#include "s100.h"
#include "machine/ins8250.h"
#include "machine/pic8259.h"
#include "machine/upd1990a.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> s100_wunderbus_device

class s100_wunderbus_device : public device_t,
								public device_s100_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	s100_wunderbus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	// not really public
	DECLARE_WRITE_LINE_MEMBER( pic_int_w );
	DECLARE_WRITE_LINE_MEMBER( rtc_tp_w );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_s100_card_interface overrides
	virtual void s100_vi0_w(int state);
	virtual void s100_vi1_w(int state);
	virtual void s100_vi2_w(int state);
	virtual UINT8 s100_sinp_r(address_space &space, offs_t offset);
	virtual void s100_sout_w(address_space &space, offs_t offset, UINT8 data);

private:
=======
	s100_wunderbus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;

	// device_s100_card_interface overrides
	virtual void s100_vi0_w(int state) override;
	virtual void s100_vi1_w(int state) override;
	virtual void s100_vi2_w(int state) override;
	virtual uint8_t s100_sinp_r(address_space &space, offs_t offset) override;
	virtual void s100_sout_w(address_space &space, offs_t offset, uint8_t data) override;

private:
	DECLARE_WRITE_LINE_MEMBER( pic_int_w );
	DECLARE_WRITE_LINE_MEMBER( rtc_tp_w );

>>>>>>> upstream/master
	required_device<pic8259_device> m_pic;
	required_device<ins8250_device> m_ace1;
	required_device<ins8250_device> m_ace2;
	required_device<ins8250_device> m_ace3;
	required_device<upd1990a_device> m_rtc;
	required_ioport m_7c;
	required_ioport m_10a;

<<<<<<< HEAD
	UINT8 m_group;
=======
	uint8_t m_group;
>>>>>>> upstream/master
	int m_rtc_tp;
};


// device type definition
<<<<<<< HEAD
extern const device_type S100_WUNDERBUS;


#endif
=======
DECLARE_DEVICE_TYPE(S100_WUNDERBUS, s100_wunderbus_device)

#endif // MAME_BUS_S100_WUNDERBUS_H
>>>>>>> upstream/master
