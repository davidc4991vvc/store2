// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Diag264 Cassette Loop Back Connector emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __DIAG264_CASSETTE_LOOPBACK__
#define __DIAG264_CASSETTE_LOOPBACK__

#include "emu.h"
=======
#ifndef MAME_BUS_PET_DIAG264_LB_TAPE_H
#define MAME_BUS_PET_DIAG264_LB_TAPE_H

#pragma once

>>>>>>> upstream/master
#include "cass.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> diag264_cassette_loopback_device

class diag264_cassette_loopback_device :  public device_t,
											public device_pet_datassette_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	diag264_cassette_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start();

	// device_pet_datassette_port_interface overrides
	virtual int datassette_read();
	virtual void datassette_write(int state);
	virtual int datassette_sense();
	virtual void datassette_motor(int state);
=======
	diag264_cassette_loopback_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_pet_datassette_port_interface overrides
	virtual int datassette_read() override;
	virtual void datassette_write(int state) override;
	virtual int datassette_sense() override;
	virtual void datassette_motor(int state) override;
>>>>>>> upstream/master

private:
	int m_read;
	int m_sense;
};


// device type definition
extern const device_type DIAG264_CASSETTE_LOOPBACK;
<<<<<<< HEAD



#endif
=======
DECLARE_DEVICE_TYPE(DIAG264_CASSETTE_LOOPBACK, diag264_cassette_loopback_device)

#endif // MAME_BUS_PET_DIAG264_LB_TAPE_H
>>>>>>> upstream/master
