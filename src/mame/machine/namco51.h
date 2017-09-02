// license:BSD-3-Clause
// copyright-holders:Aaron Giles
<<<<<<< HEAD
#ifndef NAMCO51_H
#define NAMCO51_H
=======
#ifndef MAME_MACHINE_NAMCO51_H
#define MAME_MACHINE_NAMCO51_H

#pragma once
>>>>>>> upstream/master

#include "cpu/mb88xx/mb88xx.h"


#define MCFG_NAMCO_51XX_ADD(_tag, _clock) \
	MCFG_DEVICE_ADD(_tag, NAMCO_51XX, _clock)

#define MCFG_NAMCO_51XX_INPUT_0_CB(_devcb) \
<<<<<<< HEAD
	devcb = &namco_51xx_device::set_input_0_callback(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_1_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_1_callback(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_2_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_2_callback(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_3_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_3_callback(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_OUTPUT_0_CB(_devcb) \
	devcb = &namco_51xx_device::set_output_0_callback(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_OUTPUT_1_CB(_devcb) \
	devcb = &namco_51xx_device::set_output_1_callback(*device, DEVCB_##_devcb);
=======
	devcb = &namco_51xx_device::set_input_callback<0>(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_1_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_callback<1>(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_2_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_callback<2>(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_INPUT_3_CB(_devcb) \
	devcb = &namco_51xx_device::set_input_callback<3>(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_OUTPUT_0_CB(_devcb) \
	devcb = &namco_51xx_device::set_output_callback<0>(*device, DEVCB_##_devcb);

#define MCFG_NAMCO_51XX_OUTPUT_1_CB(_devcb) \
	devcb = &namco_51xx_device::set_output_callback<1>(*device, DEVCB_##_devcb);
>>>>>>> upstream/master

class namco_51xx_device : public device_t
{
public:
<<<<<<< HEAD
	namco_51xx_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _Object> static devcb_base &set_input_0_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_in_0.set_callback(object); }
	template<class _Object> static devcb_base &set_input_1_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_in_1.set_callback(object); }
	template<class _Object> static devcb_base &set_input_2_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_in_2.set_callback(object); }
	template<class _Object> static devcb_base &set_input_3_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_in_3.set_callback(object); }

	template<class _Object> static devcb_base &set_output_0_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_out_0.set_callback(object); }
	template<class _Object> static devcb_base &set_output_1_callback(device_t &device, _Object object) { return downcast<namco_51xx_device &>(device).m_out_1.set_callback(object); }
=======
	namco_51xx_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	template <unsigned N, class Object> static devcb_base &set_input_callback(device_t &device, Object &&cb) { return downcast<namco_51xx_device &>(device).m_in[N].set_callback(std::forward<Object>(cb)); }

	template <unsigned N, class Object> static devcb_base &set_output_callback(device_t &device, Object &&cb) { return downcast<namco_51xx_device &>(device).m_out[N].set_callback(std::forward<Object>(cb)); }
>>>>>>> upstream/master

	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;
private:
	// internal state
	required_device<mb88_cpu_device> m_cpu;
	devcb_read8 m_in_0;
	devcb_read8 m_in_1;
	devcb_read8 m_in_2;
	devcb_read8 m_in_3;
	devcb_write8 m_out_0;
	devcb_write8 m_out_1;

	INT32 m_lastcoins;
	INT32 m_lastbuttons;
	INT32 m_credits;
	INT32 m_coins[2];
	INT32 m_coins_per_cred[2];
	INT32 m_creds_per_coin[2];
	INT32 m_in_count;
	INT32 m_mode;
	INT32 m_coincred_mode;
	INT32 m_remap_joy;
};

extern const device_type NAMCO_51XX;



#endif  /* NAMCO51_H */
=======
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	// internal state
	required_device<mb88_cpu_device> m_cpu;
	devcb_read8 m_in[4];
	devcb_write8 m_out[2];

	int32_t m_lastcoins;
	int32_t m_lastbuttons;
	int32_t m_credits;
	int32_t m_coins[2];
	int32_t m_coins_per_cred[2];
	int32_t m_creds_per_coin[2];
	int32_t m_in_count;
	int32_t m_mode;
	int32_t m_coincred_mode;
	int32_t m_remap_joy;
};

DECLARE_DEVICE_TYPE(NAMCO_51XX, namco_51xx_device)


#endif // NAMCO_51XX
>>>>>>> upstream/master
