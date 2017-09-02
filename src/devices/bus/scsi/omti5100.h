// license:BSD-3-Clause
// copyright-holders:smf
<<<<<<< HEAD
#ifndef OMTI5100_H_
#define OMTI5100_H_

#include "emu.h"
=======
#ifndef MAME_BUS_SCSI_OMTI5100_H
#define MAME_BUS_SCSI_OMTI5100_H

>>>>>>> upstream/master
#include "scsi.h"
#include "scsihd.h"
#include "imagedev/harddriv.h"

class omti5100_device : public scsihd_device
{
public:
<<<<<<< HEAD
	omti5100_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
	//virtual const rom_entry *device_rom_region() const;

	virtual void ExecCommand();
	virtual void ReadData( UINT8 *data, int dataLength );
	virtual void WriteData( UINT8 *data, int dataLength );
	void device_start();
=======
	omti5100_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void ExecCommand() override;
	virtual void ReadData( uint8_t *data, int dataLength ) override;
	virtual void WriteData( uint8_t *data, int dataLength ) override;

protected:
	void device_start() override;

	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	required_device<harddisk_image_device> m_image0;
	required_device<harddisk_image_device> m_image1;
	hard_disk_info m_param[2];
};

<<<<<<< HEAD
extern const device_type OMTI5100;

#endif /* OMTI5100_H_ */
=======
DECLARE_DEVICE_TYPE(OMTI5100, omti5100_device)

#endif // MAME_BUS_SCSI_OMTI5100_H
>>>>>>> upstream/master
