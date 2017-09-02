// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Commodore VIC-1011A/B RS-232C Adapter emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VIC1011__
#define __VIC1011__
=======
#ifndef MAME_BUS_VIC20_VIC1011_H
#define MAME_BUS_VIC20_VIC1011_H

#pragma once
>>>>>>> upstream/master

#include "user.h"
#include "bus/rs232/rs232.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> vic1011_device

class vic1011_device : public device_t,
	public device_pet_user_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	vic1011_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( input_d );
	virtual DECLARE_WRITE_LINE_MEMBER( input_e );
	virtual DECLARE_WRITE_LINE_MEMBER( input_j );
	virtual DECLARE_WRITE_LINE_MEMBER( input_m );

	DECLARE_WRITE_LINE_MEMBER( output_rxd );

protected:
	// device-level overrides
	virtual void device_start();

private:
=======
	vic1011_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( input_d ) override;
	virtual DECLARE_WRITE_LINE_MEMBER( input_e ) override;
	virtual DECLARE_WRITE_LINE_MEMBER( input_j ) override;
	virtual DECLARE_WRITE_LINE_MEMBER( input_m ) override;

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

private:
	DECLARE_WRITE_LINE_MEMBER( output_rxd );

>>>>>>> upstream/master
	required_device<rs232_port_device> m_rs232;
};


// device type definition
extern const device_type VIC1011;



<<<<<<< HEAD
#endif
=======
#endif // MAME_BUS_VIC20_VIC1011_H
>>>>>>> upstream/master
