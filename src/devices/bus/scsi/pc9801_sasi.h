// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef PC9801_SASI_H_
#define PC9801_SASI_H_

#include "scsihd.h"

class pc9801_sasi_device  : public scsihd_device
{
public:
	// construction/destruction
	pc9801_sasi_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void ExecCommand();
};

// device type definition
extern const device_type PC9801_SASI;

#endif /* PC9801_SASI_H_ */
=======
#ifndef MAME_BUS_SCSI_PC9801_SASI_H
#define MAME_BUS_SCSI_PC9801_SASI_H

#include "scsihd.h"

class pc9801_sasi_device : public scsihd_device
{
public:
	// construction/destruction
	pc9801_sasi_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
};

// device type definition
DECLARE_DEVICE_TYPE(PC9801_SASI, pc9801_sasi_device)

#endif // MAME_BUS_SCSI_PC9801_SASI_H
>>>>>>> upstream/master
