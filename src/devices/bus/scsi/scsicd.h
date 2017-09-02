// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

 scsicd.h

***************************************************************************/

<<<<<<< HEAD
#ifndef _SCSICD_H_
#define _SCSICD_H_
=======
#ifndef MAME_BUS_SCSI_SCSICD_H
#define MAME_BUS_SCSI_SCSICD_H
>>>>>>> upstream/master

#include "scsihle.h"
#include "machine/t10mmc.h"

<<<<<<< HEAD
class scsicd_device : public scsihle_device,
	public t10mmc
{
public:
	// construction/destruction
	scsicd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	scsicd_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	virtual void device_start();
};

// device type definition
extern const device_type SCSICD;

#endif
=======
class scsicd_device : public scsihle_device, public t10mmc
{
public:
	// construction/destruction
	scsicd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	scsicd_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);
	virtual void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
};

// device type definition
DECLARE_DEVICE_TYPE(SCSICD, scsicd_device)

#endif // MAME_BUS_SCSI_SCSICD_H
>>>>>>> upstream/master
