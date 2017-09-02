// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
/**********************************************************************

    Sega Master System "Sports Pad" (Japanese model) emulation

**********************************************************************/

<<<<<<< HEAD
// The Japanese Sports Pad controller is only required to play the cartridge
// Sports Pad Soccer, released in Japan. It uses a different mode than the
// used by the US model, due to missing output lines on Sega Mark III
// controller ports.

#pragma once

#ifndef __SMS_SPORTS_PAD_JP__
#define __SMS_SPORTS_PAD_JP__


#include "emu.h"
=======
#ifndef MAME_BUS_SMS_CTROL_SPORTSJP_H
#define MAME_BUS_SMS_CTROL_SPORTSJP_H

#pragma once


>>>>>>> upstream/master
#include "smsctrl.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> sms_sports_pad_jp_device

class sms_sports_pad_jp_device : public device_t,
							public device_sms_control_port_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	sms_sports_pad_jp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const;

	CUSTOM_INPUT_MEMBER( dir_pins_r );

protected:
	// device-level overrides
	virtual void device_start();

	// device_sms_control_port_interface overrides
	virtual UINT8 peripheral_r();

private:
	required_ioport m_sports_jp_in;
	required_ioport m_sports_jp_x;
	required_ioport m_sports_jp_y;

	UINT8 m_read_state;
=======
	sms_sports_pad_jp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_CUSTOM_INPUT_MEMBER( rldu_pins_r ); // Right, Left, Down and Up lines.
	DECLARE_READ_LINE_MEMBER( tl_pin_r );
	DECLARE_READ_LINE_MEMBER( tr_pin_r );

protected:
	// device-level overrides
	virtual void device_start() override;

	// device_sms_control_port_interface overrides
	virtual uint8_t peripheral_r() override;

private:
	required_ioport m_sports_jp_in;
	required_ioport m_sports_jp_bt;
	required_ioport m_sports_jp_x;
	required_ioport m_sports_jp_y;

	uint8_t m_rldu_pins_state;
	uint8_t m_tl_pin_state;
	uint8_t m_tr_pin_state;
>>>>>>> upstream/master
	attotime m_start_time;
	const attotime m_interval;
};


// device type definition
<<<<<<< HEAD
extern const device_type SMS_SPORTS_PAD_JP;


#endif
=======
DECLARE_DEVICE_TYPE(SMS_SPORTS_PAD_JP, sms_sports_pad_jp_device)


#endif // MAME_BUS_SMS_CTROL_SPORTSJP_H
>>>>>>> upstream/master
