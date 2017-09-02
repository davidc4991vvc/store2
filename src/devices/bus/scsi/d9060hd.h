// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#pragma once

#ifndef __D9060HD__
#define __D9060HD__
=======
#ifndef MAME_BUS_SCSI_D9060HD_H
#define MAME_BUS_SCSI_D9060HD_H

#pragma once
>>>>>>> upstream/master

#include "scsihd.h"

class d9060hd_device : public scsihd_device
{
public:
	// construction/destruction
<<<<<<< HEAD
	d9060hd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void ExecCommand();
};

// device type definition
extern const device_type D9060HD;

#endif
=======
	d9060hd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
};

// device type definition
DECLARE_DEVICE_TYPE(D9060HD, d9060hd_device)

#endif // MAME_BUS_SCSI_D9060HD_H
>>>>>>> upstream/master
