// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
/***************************************************************************

    Covox Speech Thing

***************************************************************************/

<<<<<<< HEAD
#ifndef __CENTRONICS_COVOX_H__
#define __CENTRONICS_COVOX_H__
=======
#ifndef MAME_BUS_CENTRONICS_COVOX_H
#define MAME_BUS_CENTRONICS_COVOX_H
>>>>>>> upstream/master

#pragma once

#include "ctronics.h"
#include "sound/dac.h"

// ======================> centronics_covox_device

class centronics_covox_device : public device_t,
	public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	centronics_covox_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) { if (state) m_data |= 0x01; else m_data &= ~0x01; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) { if (state) m_data |= 0x02; else m_data &= ~0x02; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) { if (state) m_data |= 0x04; else m_data &= ~0x04; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) { if (state) m_data |= 0x08; else m_data &= ~0x08; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) { if (state) m_data |= 0x10; else m_data &= ~0x10; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) { if (state) m_data |= 0x20; else m_data &= ~0x20; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) { if (state) m_data |= 0x40; else m_data &= ~0x40; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) { if (state) m_data |= 0x80; else m_data &= ~0x80; update_dac(); }

private:
	required_device<dac_device> m_dac;

	void update_dac();

	UINT8 m_data;
};

// device type definition
extern const device_type CENTRONICS_COVOX;
=======
	centronics_covox_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) override { if (state) m_data |= 0x01; else m_data &= ~0x01; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) override { if (state) m_data |= 0x02; else m_data &= ~0x02; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) override { if (state) m_data |= 0x04; else m_data &= ~0x04; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) override { if (state) m_data |= 0x08; else m_data &= ~0x08; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) override { if (state) m_data |= 0x10; else m_data &= ~0x10; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) override { if (state) m_data |= 0x20; else m_data &= ~0x20; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) override { if (state) m_data |= 0x40; else m_data &= ~0x40; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) override { if (state) m_data |= 0x80; else m_data &= ~0x80; update_dac(); }

private:
	required_device<dac_byte_interface> m_dac;

	void update_dac();

	uint8_t m_data;
};

// device type definition
DECLARE_DEVICE_TYPE(CENTRONICS_COVOX, centronics_covox_device)
>>>>>>> upstream/master

// ======================> centronics_covox_stereo_device

class centronics_covox_stereo_device : public device_t,
	public device_centronics_peripheral_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	centronics_covox_stereo_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();

	virtual DECLARE_WRITE_LINE_MEMBER( input_strobe ) { m_strobe = state; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) { if (state) m_data |= 0x01; else m_data &= ~0x01; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) { if (state) m_data |= 0x02; else m_data &= ~0x02; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) { if (state) m_data |= 0x04; else m_data &= ~0x04; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) { if (state) m_data |= 0x08; else m_data &= ~0x08; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) { if (state) m_data |= 0x10; else m_data &= ~0x10; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) { if (state) m_data |= 0x20; else m_data &= ~0x20; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) { if (state) m_data |= 0x40; else m_data &= ~0x40; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) { if (state) m_data |= 0x80; else m_data &= ~0x80; update_dac(); if (started()) output_busy(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_autofd ) { m_autofd = state; update_dac(); }

private:
	required_device<dac_device> m_dac_left;
	required_device<dac_device> m_dac_right;
=======
	centronics_covox_stereo_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	virtual DECLARE_WRITE_LINE_MEMBER( input_strobe ) override { m_strobe = state; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data0 ) override { if (state) m_data |= 0x01; else m_data &= ~0x01; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data1 ) override { if (state) m_data |= 0x02; else m_data &= ~0x02; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data2 ) override { if (state) m_data |= 0x04; else m_data &= ~0x04; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data3 ) override { if (state) m_data |= 0x08; else m_data &= ~0x08; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data4 ) override { if (state) m_data |= 0x10; else m_data &= ~0x10; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data5 ) override { if (state) m_data |= 0x20; else m_data &= ~0x20; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data6 ) override { if (state) m_data |= 0x40; else m_data &= ~0x40; update_dac(); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_data7 ) override { if (state) m_data |= 0x80; else m_data &= ~0x80; update_dac(); if (started()) output_busy(state); }
	virtual DECLARE_WRITE_LINE_MEMBER( input_autofd ) override { m_autofd = state; update_dac(); }

private:
	required_device<dac_byte_interface> m_ldac;
	required_device<dac_byte_interface> m_rdac;
>>>>>>> upstream/master

	void update_dac();

	int m_strobe;
<<<<<<< HEAD
	UINT8 m_data;
=======
	uint8_t m_data;
>>>>>>> upstream/master
	int m_autofd;
};

// device type definition
<<<<<<< HEAD
extern const device_type CENTRONICS_COVOX_STEREO;

#endif /* __CENTRONICS_COVOX_H__ */
=======
DECLARE_DEVICE_TYPE(CENTRONICS_COVOX_STEREO, centronics_covox_stereo_device)

#endif // MAME_BUS_CENTRONICS_COVOX_H
>>>>>>> upstream/master
