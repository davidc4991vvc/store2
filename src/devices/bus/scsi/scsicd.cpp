// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

 scsicd.c - Implementation of a SCSI CD-ROM device

***************************************************************************/

<<<<<<< HEAD
#include "scsicd.h"

// device type definition
const device_type SCSICD = &device_creator<scsicd_device>;

scsicd_device::scsicd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	scsihle_device(mconfig, SCSICD, "SCSI CD", tag, owner, clock, "scsicd", __FILE__)
{
}

scsicd_device::scsicd_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	scsihle_device(mconfig, type, name, tag, owner, clock, shortname, source)
=======
#include "emu.h"
#include "scsicd.h"

// device type definition
DEFINE_DEVICE_TYPE(SCSICD, scsicd_device, "scsicd", "SCSI CD")

scsicd_device::scsicd_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	scsicd_device(mconfig, SCSICD, tag, owner, clock)
{
}

scsicd_device::scsicd_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	scsihle_device(mconfig, type, tag, owner, clock)
>>>>>>> upstream/master
{
}

void scsicd_device::device_start()
{
	m_image = subdevice<cdrom_image_device>("image");
	m_cdda = subdevice<cdda_device>("cdda");

	scsihle_device::device_start();
}

<<<<<<< HEAD
static MACHINE_CONFIG_FRAGMENT(scsi_cdrom)
=======
MACHINE_CONFIG_MEMBER(scsicd_device::device_add_mconfig)
>>>>>>> upstream/master
	MCFG_CDROM_ADD("image")
	MCFG_CDROM_INTERFACE("cdrom")
	MCFG_SOUND_ADD("cdda", CDDA, 0)
MACHINE_CONFIG_END
<<<<<<< HEAD

machine_config_constructor scsicd_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME(scsi_cdrom);
}
=======
>>>>>>> upstream/master
