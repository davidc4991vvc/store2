// license:BSD-3-Clause
// copyright-holders:Curt Coder, smf
/**********************************************************************

    geoCable Centronics Cable emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __C64_GEOCABLE__
#define __C64_GEOCABLE__


#include "emu.h"
=======
#ifndef MAME_BUS_C64_GEOCABLE_H
#define MAME_BUS_C64_GEOCABLE_H

#pragma once


>>>>>>> upstream/master
#include "user.h"
#include "bus/centronics/ctronics.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_geocable_device

class c64_geocable_device : public device_t,
	public device_pet_user_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	c64_geocable_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER(input_c) { m_centronics->write_data0(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_d) { m_centronics->write_data1(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_e) { m_centronics->write_data2(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_f) { m_centronics->write_data3(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_h) { m_centronics->write_data4(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_j) { m_centronics->write_data5(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_k) { m_centronics->write_data6(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_l) { m_centronics->write_data7(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_m) { m_centronics->write_strobe(state); }

private:
	required_device<centronics_device> m_centronics;

	void update_output();
=======
	c64_geocable_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER(input_c) override { m_centronics->write_data0(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_d) override { m_centronics->write_data1(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_e) override { m_centronics->write_data2(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_f) override { m_centronics->write_data3(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_h) override { m_centronics->write_data4(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_j) override { m_centronics->write_data5(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_k) override { m_centronics->write_data6(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_l) override { m_centronics->write_data7(state); }
	virtual DECLARE_WRITE_LINE_MEMBER(input_m) override { m_centronics->write_strobe(state); }

private:
	required_device<centronics_device> m_centronics;
>>>>>>> upstream/master
};


// device type definition
extern const device_type C64_GEOCABLE;
<<<<<<< HEAD


#endif
=======
DECLARE_DEVICE_TYPE(C64_GEOCABLE, c64_geocable_device)


#endif // MAME_BUS_C64_GEOCABLE_H
>>>>>>> upstream/master
