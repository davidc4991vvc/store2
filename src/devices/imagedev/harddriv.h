// license:BSD-3-Clause
// copyright-holders:Nathan Woods, Raphael Nabet, Miodrag Milanovic
/*********************************************************************

    harddriv.h

    Interface to the CHD code

*********************************************************************/

<<<<<<< HEAD
#ifndef HARDDRIV_H
#define HARDDRIV_H

#include "harddisk.h"
=======
#ifndef MAME_DEVICES_IMAGEDEV_HARDDRIV_H
#define MAME_DEVICES_IMAGEDEV_HARDDRIV_H

#include "harddisk.h"
#include "softlist_dev.h"
>>>>>>> upstream/master

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

// ======================> harddisk_image_device

class harddisk_image_device :   public device_t,
								public device_image_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	harddisk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	harddisk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
	virtual ~harddisk_image_device();

	static void static_set_device_load(device_t &device, device_image_load_delegate callback) { downcast<harddisk_image_device &>(device).m_device_image_load = callback; }
	static void static_set_device_unload(device_t &device, device_image_func_delegate callback) { downcast<harddisk_image_device &>(device).m_device_image_unload = callback; }
	static void static_set_interface(device_t &device, const char *_interface) { downcast<harddisk_image_device &>(device).m_interface = _interface; }

	// image-level overrides
<<<<<<< HEAD
	virtual bool call_load();
	virtual bool call_create(int create_format, option_resolution *create_args);
	virtual void call_unload();
	virtual bool call_softlist_load(software_list_device &swlist, const char *swname, const rom_entry *start_entry) { load_software_part_region(*this, swlist, swname, start_entry ); return TRUE; }

	virtual iodevice_t image_type() const { return IO_HARDDISK; }

	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 1; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 0; }
	virtual const char *image_interface() const { return m_interface; }
	virtual const char *file_extensions() const { return "chd,hd"; }
	virtual const option_guide *create_option_guide() const;
=======
	virtual image_init_result call_load() override;
	virtual image_init_result call_create(int create_format, util::option_resolution *create_args) override;
	virtual void call_unload() override;
	virtual const software_list_loader &get_software_list_loader() const override { return rom_software_list_loader::instance(); }

	virtual iodevice_t image_type() const override { return IO_HARDDISK; }

	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 1; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 0; }
	virtual const char *image_interface() const override { return m_interface; }
	virtual const char *file_extensions() const override { return "chd,hd"; }
	virtual const util::option_guide &create_option_guide() const override;
>>>>>>> upstream/master

	// specific implementation
	hard_disk_file *get_hard_disk_file() { return m_hard_disk_handle; }
	chd_file *get_chd_file();

protected:
<<<<<<< HEAD
	harddisk_image_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_stop();

	int internal_load_hd();
=======
	harddisk_image_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_config_complete() override;
	virtual void device_start() override;
	virtual void device_stop() override;

	image_init_result internal_load_hd();
>>>>>>> upstream/master

	chd_file        *m_chd;
	chd_file        m_origchd;              /* handle to the original CHD */
	chd_file        m_diffchd;              /* handle to the diff CHD */
	hard_disk_file  *m_hard_disk_handle;

	device_image_load_delegate      m_device_image_load;
	device_image_func_delegate      m_device_image_unload;
	const char *                    m_interface;
};

// device type definition
<<<<<<< HEAD
extern const device_type HARDDISK;
=======
DECLARE_DEVICE_TYPE(HARDDISK, harddisk_image_device)
>>>>>>> upstream/master

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_HARDDISK_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, HARDDISK, 0)

#define MCFG_HARDDISK_LOAD(_class,_method)                                \
<<<<<<< HEAD
	harddisk_image_device::static_set_device_load(*device, device_image_load_delegate(&DEVICE_IMAGE_LOAD_NAME(_class,_method), #_class "::device_image_load_" #_method, downcast<_class *>(owner)));

#define MCFG_HARDDISK_UNLOAD(_class,_method)                            \
	harddisk_image_device::static_set_device_unload(*device, device_image_func_delegate(&DEVICE_IMAGE_UNLOAD_NAME(_class,_method), #_class "::device_image_unload_" #_method, downcast<_class *>(owner)));
=======
	harddisk_image_device::static_set_device_load(*device, device_image_load_delegate(&DEVICE_IMAGE_LOAD_NAME(_class,_method), downcast<_class *>(owner)));

#define MCFG_HARDDISK_UNLOAD(_class,_method)                            \
	harddisk_image_device::static_set_device_unload(*device, device_image_func_delegate(&DEVICE_IMAGE_UNLOAD_NAME(_class,_method), downcast<_class *>(owner)));
>>>>>>> upstream/master

#define MCFG_HARDDISK_INTERFACE(_interface)                         \
	harddisk_image_device::static_set_interface(*device, _interface);

<<<<<<< HEAD
#endif /* HARDDRIV_H */
=======
#endif // MAME_DEVICES_IMAGEDEV_HARDDRIV_H
>>>>>>> upstream/master
