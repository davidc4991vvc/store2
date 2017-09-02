// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_CART_MSX_AUDIO_H
#define __MSX_CART_MSX_AUDIO_H
=======
#ifndef MAME_BUS_MSX_CART_MSX_AUDIO_H
#define MAME_BUS_MSX_CART_MSX_AUDIO_H

#pragma once
>>>>>>> upstream/master

#include "bus/msx_cart/cartridge.h"
#include "sound/8950intf.h"
#include "machine/6850acia.h"
#include "bus/midi/midi.h"


<<<<<<< HEAD
extern const device_type MSX_CART_MSX_AUDIO_NMS1205;
extern const device_type MSX_CART_MSX_AUDIO_HXMU900;
extern const device_type MSX_CART_MSX_AUDIO_FSCA1;


class msx_cart_msx_audio_hxmu900 : public device_t
								, public msx_cart_interface
{
public:
	msx_cart_msx_audio_hxmu900(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
=======
DECLARE_DEVICE_TYPE(MSX_CART_MSX_AUDIO_HXMU900, msx_cart_msx_audio_hxmu900_device)
DECLARE_DEVICE_TYPE(MSX_CART_MSX_AUDIO_NMS1205, msx_cart_msx_audio_nms1205_device)
DECLARE_DEVICE_TYPE(MSX_CART_MSX_AUDIO_FSCA1,   msx_cart_msx_audio_fsca1_device)


class msx_cart_msx_audio_hxmu900_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_msx_audio_hxmu900_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;

protected:
	virtual void device_start() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

private:
	required_device<y8950_device> m_y8950;
};


<<<<<<< HEAD
class msx_cart_msx_audio_nms1205 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_msx_audio_nms1205(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);

	DECLARE_WRITE_LINE_MEMBER(midi_in);
	DECLARE_WRITE_LINE_MEMBER(irq_write);

private:
=======
class msx_cart_msx_audio_nms1205_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_msx_audio_nms1205_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;

protected:
	virtual void device_start() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual const tiny_rom_entry *device_rom_region() const override;

private:
	DECLARE_WRITE_LINE_MEMBER(midi_in);
	DECLARE_WRITE_LINE_MEMBER(irq_write);

>>>>>>> upstream/master
	required_device<y8950_device> m_y8950;
	required_device<acia6850_device> m_acia6850;
	required_device<midi_port_device> m_mdout;
	required_device<midi_port_device> m_mdthru;
};


<<<<<<< HEAD
class msx_cart_msx_audio_fsca1 : public device_t
						, public msx_cart_interface
{
public:
	msx_cart_msx_audio_fsca1(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;
	virtual const rom_entry *device_rom_region() const;

	virtual void initialize_cartridge();

	virtual DECLARE_READ8_MEMBER(read_cart);
	virtual DECLARE_WRITE8_MEMBER(write_cart);
=======
class msx_cart_msx_audio_fsca1_device : public device_t, public msx_cart_interface
{
public:
	msx_cart_msx_audio_fsca1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual void initialize_cartridge() override;

	virtual DECLARE_READ8_MEMBER(read_cart) override;
	virtual DECLARE_WRITE8_MEMBER(write_cart) override;

protected:
	virtual void device_start() override;

	// device-level overrides
	virtual void device_add_mconfig(machine_config &config) override;
	virtual ioport_constructor device_input_ports() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER(write_y8950);
	DECLARE_READ8_MEMBER(read_y8950);

<<<<<<< HEAD
	DECLARE_WRITE8_MEMBER(y8950_io_w);
	DECLARE_READ8_MEMBER(y8950_io_r);

private:
	required_device<y8950_device> m_y8950;
	required_ioport m_io_config;
	required_memory_region m_region_y8950;
	UINT8 m_7ffe;
	UINT8 m_7fff;
};

#endif
=======
private:
	DECLARE_WRITE8_MEMBER(y8950_io_w);
	DECLARE_READ8_MEMBER(y8950_io_r);

	required_device<y8950_device> m_y8950;
	required_ioport m_io_config;
	required_memory_region m_region_y8950;
	uint8_t m_7ffe;
	uint8_t m_7fff;
};

#endif // MAME_BUS_MSX_CART_MSX_AUDIO_H
>>>>>>> upstream/master
