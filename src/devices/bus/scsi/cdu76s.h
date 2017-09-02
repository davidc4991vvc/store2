// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    cdu76s.h

    Sony CDU-76S

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CDU76S_H__
#define __CDU76S_H__
=======
#ifndef MAME_BUS_SCSI_CDU76S_H
#define MAME_BUS_SCSI_CDU76S_H

#pragma once
>>>>>>> upstream/master

#include "scsicd.h"
#include "machine/t10mmc.h"

class sony_cdu76s_device : public scsicd_device
{
public:
<<<<<<< HEAD
	sony_cdu76s_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual void ExecCommand();
	virtual void ReadData( UINT8 *data, int dataLength );
};

// device type definition
extern const device_type CDU76S;

#endif
=======
	sony_cdu76s_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;
};

// device type definition
DECLARE_DEVICE_TYPE(CDU76S, sony_cdu76s_device)

#endif // MAME_BUS_SCSI_CDU76S_H
>>>>>>> upstream/master
