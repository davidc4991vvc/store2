// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#include "legscsi.h"

legacy_scsi_host_adapter::legacy_scsi_host_adapter(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	m_selected(0),
	m_scsi_port(*this)
=======
#include "emu.h"
#include "legscsi.h"

legacy_scsi_host_adapter::legacy_scsi_host_adapter(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, type, tag, owner, clock)
	, m_selected(0)
	, m_scsi_port(*this, finder_base::DUMMY_TAG)
>>>>>>> upstream/master
{
}

void legacy_scsi_host_adapter::device_start()
{
}

void legacy_scsi_host_adapter::reset_bus()
{
	for (int i = 0; i <= 7; i++)
	{
		scsihle_device *scsidev = get_device(i);
<<<<<<< HEAD
		if (scsidev != NULL)
=======
		if (scsidev != nullptr)
>>>>>>> upstream/master
		{
			scsidev->reset();
		}
	}
}

bool legacy_scsi_host_adapter::select(int id)
{
	m_selected = id;

	scsihle_device *scsidev = get_device(m_selected);
<<<<<<< HEAD
	if (scsidev != NULL)
=======
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		return true;
	}

	return false;
}

<<<<<<< HEAD
void legacy_scsi_host_adapter::send_command(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != NULL)
=======
void legacy_scsi_host_adapter::send_command(uint8_t *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		scsidev->SetCommand(data, bytes);
		scsidev->ExecCommand();
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: send_command unknown SCSI id %d\n", tag(), m_selected);
=======
		logerror("send_command unknown SCSI id %d\n", m_selected);
>>>>>>> upstream/master
	}
}

int legacy_scsi_host_adapter::get_length(void)
{
	scsihle_device *scsidev = get_device(m_selected);
<<<<<<< HEAD
	if (scsidev != NULL)
=======
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		int length;
		scsidev->GetLength(&length);
		return length;
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: get_length unknown SCSI id %d\n", tag(), m_selected);
=======
		logerror("get_length unknown SCSI id %d\n", m_selected);
>>>>>>> upstream/master
		return 0;
	}
}

int legacy_scsi_host_adapter::get_phase(void)
{
	scsihle_device *scsidev = get_device(m_selected);
<<<<<<< HEAD
	if (scsidev != NULL)
=======
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		int phase;
		scsidev->GetPhase(&phase);
		return phase;
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: get_phase unknown SCSI id %d\n", tag(), m_selected);
=======
		logerror("get_phase unknown SCSI id %d\n", m_selected);
>>>>>>> upstream/master
		return 0;
	}
}

<<<<<<< HEAD
void legacy_scsi_host_adapter::read_data(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != NULL)
=======
void legacy_scsi_host_adapter::read_data(uint8_t *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		scsidev->ReadData(data, bytes);
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: read_data unknown SCSI id %d\n", tag(), m_selected);
	}
}

void legacy_scsi_host_adapter::write_data(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != NULL)
=======
		logerror("read_data unknown SCSI id %d\n", m_selected);
	}
}

void legacy_scsi_host_adapter::write_data(uint8_t *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		scsidev->WriteData(data, bytes);
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: write_data unknown SCSI id %d\n", tag(), m_selected);
	}
}

UINT8 legacy_scsi_host_adapter::get_status()
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != NULL)
=======
		logerror("write_data unknown SCSI id %d\n", m_selected);
	}
}

uint8_t legacy_scsi_host_adapter::get_status()
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
>>>>>>> upstream/master
	{
		void *image;

		scsidev->GetDevice(&image);
<<<<<<< HEAD
		if (image != NULL)
=======
		if (image != nullptr)
>>>>>>> upstream/master
			return 0x00;

		return 0x02;
	}
	else
	{
<<<<<<< HEAD
		logerror("%s: get_status unknown SCSI id %d\n", tag(), m_selected);
=======
		logerror("get_status unknown SCSI id %d\n", m_selected);
>>>>>>> upstream/master
		return 0;
	}
}

scsihle_device *legacy_scsi_host_adapter::get_device(int id)
{
<<<<<<< HEAD
	// steal scsi devices from bus
	for (device_t *device = m_scsi_port->first_subdevice(); device != NULL; device = device->next())
	{
		SCSI_PORT_SLOT_device *slot = dynamic_cast<SCSI_PORT_SLOT_device *>(device);
		if (slot != NULL)
		{
			scsihle_device *scsidev = dynamic_cast<scsihle_device *>(slot->dev());
			if (scsidev != NULL)
=======
	// steal SCSI devices from bus
	for (device_t &device : m_scsi_port->subdevices())
	{
		scsi_port_slot_device *slot = dynamic_cast<scsi_port_slot_device *>(&device);
		if (slot != nullptr)
		{
			scsihle_device *scsidev = dynamic_cast<scsihle_device *>(slot->dev());
			if (scsidev != nullptr)
>>>>>>> upstream/master
			{
				if (scsidev->GetDeviceID() == id)
				{
					return scsidev;
				}
			}
		}
	}

<<<<<<< HEAD
	return NULL;
=======
	return nullptr;
>>>>>>> upstream/master
}
