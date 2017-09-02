// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
#ifndef __MICRODISC_H__
#define __MICRODISC_H__
=======
#ifndef MAME_BUS_ORICEXT_MICRODISC_H
#define MAME_BUS_ORICEXT_MICRODISC_H
>>>>>>> upstream/master

#include "oricext.h"
#include "imagedev/floppy.h"
#include "machine/wd_fdc.h"

<<<<<<< HEAD
extern const device_type MICRODISC;
=======
DECLARE_DEVICE_TYPE(MICRODISC, microdisc_device)
>>>>>>> upstream/master

class microdisc_device : public oricext_device
{
public:
<<<<<<< HEAD
	microdisc_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~microdisc_device();

	DECLARE_FLOPPY_FORMATS(floppy_formats);
=======
	microdisc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~microdisc_device();

>>>>>>> upstream/master
	DECLARE_ADDRESS_MAP(map, 8);
	DECLARE_WRITE8_MEMBER(port_314_w);
	DECLARE_READ8_MEMBER(port_314_r);
	DECLARE_READ8_MEMBER(port_318_r);

<<<<<<< HEAD
	DECLARE_WRITE_LINE_MEMBER(fdc_irq_w);
	DECLARE_WRITE_LINE_MEMBER(fdc_drq_w);
	DECLARE_WRITE_LINE_MEMBER(fdc_hld_w);

=======
>>>>>>> upstream/master
protected:
	enum {
		P_IRQEN  = 0x01,
		P_ROMDIS = 0x02,
		P_DDS    = 0x04,
		P_DDEN   = 0x08,
		P_SS     = 0x10,
		P_DRIVE  = 0x60,
		P_EPROM  = 0x80
	};

<<<<<<< HEAD
	required_device<fd1793_t> fdc;

	UINT8 *microdisc_rom;
	floppy_image_device *floppies[4];
	UINT8 port_314;
	bool intrq_state, drq_state, hld_state;

	virtual void device_start();
	virtual void device_reset();
	const rom_entry *device_rom_region() const;
	machine_config_constructor device_mconfig_additions() const;

	void remap();
};

#endif
=======
	required_device<fd1793_device> fdc;

	uint8_t *microdisc_rom;
	floppy_image_device *floppies[4];
	uint8_t port_314;
	bool intrq_state, drq_state, hld_state;

	virtual void device_start() override;
	virtual void device_reset() override;
	const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	void remap();

private:
	DECLARE_WRITE_LINE_MEMBER(fdc_irq_w);
	DECLARE_WRITE_LINE_MEMBER(fdc_drq_w);
	DECLARE_WRITE_LINE_MEMBER(fdc_hld_w);

	DECLARE_FLOPPY_FORMATS(floppy_formats);
};

#endif // MAME_BUS_ORICEXT_MICRODISC_H
>>>>>>> upstream/master
