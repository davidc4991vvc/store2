// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/*********************************************************************

    ng_memcard.h

    NEOGEO Memory card functions.

*********************************************************************/
<<<<<<< HEAD

#pragma once

#ifndef __NG_MEMCARD_H__
#define __NG_MEMCARD_H__
=======
#ifndef MAME_MACHINE_NG_MEMCARD_H
#define MAME_MACHINE_NG_MEMCARD_H

#pragma once

>>>>>>> upstream/master

//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_NEOGEO_MEMCARD_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, NG_MEMCARD, 0)

/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

// ======================> ng_memcard_device

class ng_memcard_device :  public device_t,
							public device_image_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	ng_memcard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual iodevice_t image_type() const { return IO_MEMCARD; }

	virtual bool is_readable()  const { return true; }
	virtual bool is_writeable() const { return true; }
	virtual bool is_creatable() const { return true; }
	virtual bool must_be_loaded() const { return false; }
	virtual bool is_reset_on_load() const { return false; }
	virtual const char *file_extensions() const { return "neo"; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	virtual bool call_load();
	virtual void call_unload();
	virtual bool call_create(int format_type, option_resolution *format_options);

	// device-level overrides
	virtual void device_start();
	virtual void device_config_complete();
=======
	ng_memcard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual iodevice_t image_type() const override { return IO_MEMCARD; }

	virtual bool is_readable()  const override { return true; }
	virtual bool is_writeable() const override { return true; }
	virtual bool is_creatable() const override { return true; }
	virtual bool must_be_loaded() const override { return false; }
	virtual bool is_reset_on_load() const override { return false; }
	virtual const char *file_extensions() const override { return "neo"; }

	virtual image_init_result call_load() override;
	virtual void call_unload() override;
	virtual image_init_result call_create(int format_type, util::option_resolution *format_options) override;

	// device-level overrides
	virtual void device_start() override;
>>>>>>> upstream/master

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

	/* returns the index of the current memory card, or -1 if none */
	int present() { return is_loaded() ? 0 : -1; }
private:
<<<<<<< HEAD
	UINT8 m_memcard_data[0x800];
=======
	uint8_t m_memcard_data[0x800];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type NG_MEMCARD;


#endif  /* __NG_MEMCARD_H__ */
=======
DECLARE_DEVICE_TYPE(NG_MEMCARD, ng_memcard_device)


#endif // MAME_MACHINE_NG_MEMCARD_H
>>>>>>> upstream/master
