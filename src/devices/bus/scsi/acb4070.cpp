// license:BSD-3-Clause
// copyright-holders:smf
/*
 * ACB4070 + RLL drive
 *
 */

<<<<<<< HEAD
#include "acb4070.h"

// device type definition
const device_type ACB4070 = &device_creator<acb4070_device>;

acb4070_device::acb4070_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: scsihd_device(mconfig, ACB4070, "ACB4070", tag, owner, clock, "acb4070", __FILE__)
=======
#include "emu.h"
#include "acb4070.h"

// device type definition
DEFINE_DEVICE_TYPE(ACB4070, acb4070_device, "acb4070", "ACB4070")

acb4070_device::acb4070_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: scsihd_device(mconfig, ACB4070, tag, owner, clock)
>>>>>>> upstream/master
{
}

#define ACB4070_CMD_WRITE_DATA_BUFFER ( 0x13 )
#define ACB4070_CMD_READ_DATA_BUFFER ( 0x14 )

#define TRANSFERLENGTH_DATA_BUFFER  0x0400

void acb4070_device::ExecCommand()
{
	switch( command[ 0 ] )
	{
	case ACB4070_CMD_WRITE_DATA_BUFFER:
		m_phase = SCSI_PHASE_DATAOUT;
		m_status_code = SCSI_STATUS_CODE_GOOD;
		m_transfer_length = TRANSFERLENGTH_DATA_BUFFER;
		break;

	case ACB4070_CMD_READ_DATA_BUFFER:
		m_phase = SCSI_PHASE_DATAIN;
		m_status_code = SCSI_STATUS_CODE_GOOD;
		m_transfer_length = TRANSFERLENGTH_DATA_BUFFER;
		break;

	case T10SPC_CMD_MODE_SELECT_6:
		m_phase = SCSI_PHASE_DATAOUT;
		m_status_code = SCSI_STATUS_CODE_GOOD;
		m_transfer_length = SCSILengthFromUINT8( &command[ 4 ] );
		break;

	default:
		scsihd_device::ExecCommand();
		break;
	}
}

<<<<<<< HEAD
void acb4070_device::WriteData( UINT8 *data, int dataLength )
=======
void acb4070_device::WriteData( uint8_t *data, int dataLength )
>>>>>>> upstream/master
{
	switch( command[ 0 ] )
	{
	case T10SPC_CMD_MODE_SELECT_6:
		adaptec_sense_t *sense=(adaptec_sense_t *) data;
		int tracks=(sense->cylinder_count[0]<<8)+sense->cylinder_count[1];
		int capacity=(tracks * sense->head_count * 17);
		logerror("Tracks=%d, Heads=%d sec/track=%d\n",tracks,sense->head_count,sense->sectors_per_track);
		logerror("Setting disk capacity to %d blocks\n",capacity);
		break;
	}
}
