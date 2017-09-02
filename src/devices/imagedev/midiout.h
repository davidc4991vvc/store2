// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    midiout.h

    MIDI Out image device

*********************************************************************/

<<<<<<< HEAD
#ifndef __MIDIOUT_H__
#define __MIDIOUT_H__
=======
#ifndef MAME_DEVICES_IMAGEDEV_MIDIOUT_H
#define MAME_DEVICES_IMAGEDEV_MIDIOUT_H
>>>>>>> upstream/master


/***************************************************************************
    CONSTANTS
***************************************************************************/


#define MCFG_MIDIOUT_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MIDIOUT, 0)


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class midiout_device :    public device_t,
						public device_image_interface,
						public device_serial_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	midiout_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload();

	// image device
	virtual iodevice_t image_type() const { return IO_MIDIOUT; }
	virtual bool is_readable()  const { return 0; }
	virtual bool is_writeable() const { return 1; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 0; }
	virtual const char *file_extensions() const { return "mid"; }
	virtual bool core_opens_image_file() const { return FALSE; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	virtual void tx(UINT8 state) { rx_w(state); }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	virtual void device_config_complete();

	// serial overrides
	virtual void rcv_complete();    // Rx completed receiving byte
=======
	midiout_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// image-level overrides
	virtual image_init_result call_load() override;
	virtual void call_unload() override;

	// image device
	virtual iodevice_t image_type() const override { return IO_MIDIOUT; }
	virtual bool is_readable()  const override { return 0; }
	virtual bool is_writeable() const override { return 1; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 0; }
	virtual const char *file_extensions() const override { return "mid"; }
	virtual bool core_opens_image_file() const override { return false; }

	virtual void tx(uint8_t state) { rx_w(state); }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// serial overrides
	virtual void rcv_complete() override;    // Rx completed receiving byte
>>>>>>> upstream/master

private:
	osd_midi_device *m_midi;
};

// device type definition
<<<<<<< HEAD
extern const device_type MIDIOUT;

// device iterator
typedef device_type_iterator<&device_creator<midiout_device>, midiout_device> midiout_device_iterator;

#endif /* __MIDIOUT_H__ */
=======
DECLARE_DEVICE_TYPE(MIDIOUT, midiout_device)

// device iterator
typedef device_type_iterator<midiout_device> midiout_device_iterator;

#endif // MAME_DEVICES_IMAGEDEV_MIDIOUT_H
>>>>>>> upstream/master
