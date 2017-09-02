// license:BSD-3-Clause
// copyright-holders:smf
/**********************************************************************

    Commodore PET User Port Diagnostic Connector emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __PET_USER_DIAG__
#define __PET_USER_DIAG__

#include "emu.h"
=======
#ifndef MAME_BUS_PET_DIAG_H
#define MAME_BUS_PET_DIAG_H

#pragma once

>>>>>>> upstream/master
#include "user.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> pet_userport_diagnostic_connector_t

class pet_userport_diagnostic_connector_t : public device_t,
											public device_pet_user_port_interface
{
public:
	// construction/destruction
	pet_userport_diagnostic_connector_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( input_2 ) { output_b(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_3 ) { output_c(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_4 ) { output_d(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_6 ) { output_7(state); output_8(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_7 ) { output_6(state); output_8(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_8 ) { output_6(state); output_7(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_9 ) { output_k(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_10 ) { output_l(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_b ) { output_2(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_c ) { output_3(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_d ) { output_4(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_k ) { output_9(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_l ) { output_10(state); }

protected:
	// device-level overrides
	virtual void device_start();
=======
// ======================> pet_userport_diagnostic_connector_device

class pet_userport_diagnostic_connector_device : public device_t, public device_pet_user_port_interface
{
public:
	// construction/destruction
	pet_userport_diagnostic_connector_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// device_pet_user_port_interface overrides
	virtual DECLARE_WRITE_LINE_MEMBER( input_2 ) override { output_b(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_3 ) override { output_c(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_4 ) override { output_d(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_6 ) override { output_7(state); output_8(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_7 ) override { output_6(state); output_8(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_8 ) override { output_6(state); output_7(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_9 ) override { output_k(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_10 ) override { output_l(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_b ) override { output_2(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_c ) override { output_3(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_d ) override { output_4(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_k ) override { output_9(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_l ) override { output_10(state); }

protected:
	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type PET_USERPORT_DIAGNOSTIC_CONNECTOR;


#endif
=======
DECLARE_DEVICE_TYPE(PET_USERPORT_DIAGNOSTIC_CONNECTOR, pet_userport_diagnostic_connector_device)

#endif // MAME_BUS_PET_DIAG_H
>>>>>>> upstream/master
