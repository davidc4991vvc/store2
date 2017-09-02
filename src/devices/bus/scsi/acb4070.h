// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#pragma once

#ifndef __ACB4070__
#define __ACB4070__
=======
#ifndef MAME_BUS_SCSI_ACB4070_H
#define MAME_BUS_SCSI_ACB4070_H

#pragma once
>>>>>>> upstream/master

#include "scsihd.h"

class acb4070_device : public scsihd_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	acb4070_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void ExecCommand();
	virtual void WriteData( UINT8 *data, int dataLength );
=======
	acb4070_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;
>>>>>>> upstream/master

private:
	struct adaptec_sense_t
	{
		// parameter list
<<<<<<< HEAD
		UINT8       reserved1[3];
		UINT8       length;

		// descriptor list
		UINT8       density;
		UINT8       reserved2[4];
		UINT8       block_size[3];

		// drive parameter list
		UINT8       format_code;
		UINT8       cylinder_count[2];
		UINT8       head_count;
		UINT8       reduced_write[2];
		UINT8       write_precomp[2];
		UINT8       landing_zone;
		UINT8       step_pulse_code;
		UINT8       bit_flags;
		UINT8       sectors_per_track;
=======
		uint8_t       reserved1[3];
		uint8_t       length;

		// descriptor list
		uint8_t       density;
		uint8_t       reserved2[4];
		uint8_t       block_size[3];

		// drive parameter list
		uint8_t       format_code;
		uint8_t       cylinder_count[2];
		uint8_t       head_count;
		uint8_t       reduced_write[2];
		uint8_t       write_precomp[2];
		uint8_t       landing_zone;
		uint8_t       step_pulse_code;
		uint8_t       bit_flags;
		uint8_t       sectors_per_track;
>>>>>>> upstream/master
	};
};

// device type definition
<<<<<<< HEAD
extern const device_type ACB4070;

#endif
=======
DECLARE_DEVICE_TYPE(ACB4070, acb4070_device)

#endif // MAME_BUS_SCSI_ACB4070_H
>>>>>>> upstream/master
