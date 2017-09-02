// license:BSD-3-Clause
// copyright-holders:Wilbert Pol
<<<<<<< HEAD
#ifndef __MSX_MATSUSHITA_H
#define __MSX_MATSUSHITA_H


#include "msx_switched.h"
#include "machine/nvram.h"


extern const device_type MSX_MATSUSHITA;
=======
#ifndef MAME_MACHINE_MSX_MATSUSHITA_H
#define MAME_MACHINE_MSX_MATSUSHITA_H


#include "msx_switched.h"


DECLARE_DEVICE_TYPE(MSX_MATSUSHITA, msx_matsushita_device)
>>>>>>> upstream/master


#define MCFG_MSX_MATSUSHITA_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MSX_MATSUSHITA, 0)

#define MCFG_MSX_MATSUSHITA_TURBO_CB(_devcb) \
	devcb = &msx_matsushita_device::set_turbo_callback(*device, DEVCB_##_devcb);


<<<<<<< HEAD
class msx_matsushita_device : public msx_switched_device
{
public:
	msx_matsushita_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_turbo_callback(device_t &device, _Object object) { return downcast<msx_matsushita_device &>(device).m_turbo_out_cb.set_callback(object); }

	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual ioport_constructor device_input_ports() const;

	virtual UINT8 get_id();

	virtual DECLARE_READ8_MEMBER(io_read);
	virtual DECLARE_WRITE8_MEMBER(io_write);

private:
	required_ioport m_io_config;
	required_device<nvram_device> m_nvram;
	devcb_write_line m_turbo_out_cb;
	UINT16 m_address;
	dynamic_buffer m_sram;
	UINT8 m_nibble1;
	UINT8 m_nibble2;
	UINT8 m_pattern;
};

#endif
=======
class msx_matsushita_device : public device_t,
	public msx_switched_interface,
	public device_nvram_interface
{
public:
	msx_matsushita_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <class Object> static devcb_base &set_turbo_callback(device_t &device, Object &&cb)
	{ return downcast<msx_matsushita_device &>(device).m_turbo_out_cb.set_callback(std::forward<Object>(cb)); }

	virtual DECLARE_READ8_MEMBER(switched_read) override;
	virtual DECLARE_WRITE8_MEMBER(switched_write) override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual ioport_constructor device_input_ports() const override;

	// device_nvram_interface overrides
	virtual void nvram_default() override;
	virtual void nvram_read(emu_file &file) override;
	virtual void nvram_write(emu_file &file) override;

private:
	required_ioport m_io_config;
	devcb_write_line m_turbo_out_cb;
	bool m_selected;
	uint16_t m_address;
	std::vector<uint8_t> m_sram;
	uint8_t m_nibble1;
	uint8_t m_nibble2;
	uint8_t m_pattern;
};

#endif // MAME_MACHINE_MSX_MATSUSHITA_H
>>>>>>> upstream/master
