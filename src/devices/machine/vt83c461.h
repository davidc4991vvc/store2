// license:BSD-3-Clause
// copyright-holders:smf
/***************************************************************************

    vt83c461.h

    VIA VT83C461 (IDE Hard Drive controller).

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __VT83C461_H__
#define __VT83C461_H__
=======
#ifndef MAME_MACHINE_VT83C461_H
#define MAME_MACHINE_VT83C461_H

#pragma once
>>>>>>> upstream/master

#include "idectrl.h"

/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_VT83C461_ADD(_tag, _slot_intf, _master, _slave, _fixed) \
	MCFG_DEVICE_ADD(_tag, VT83C461, 0) \
	MCFG_DEVICE_MODIFY(_tag ":0") \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _master, _fixed) \
	MCFG_DEVICE_MODIFY(_tag ":1") \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _slave, _fixed) \
	MCFG_DEVICE_MODIFY(_tag)

<<<<<<< HEAD
#define IDE_CONFIG_REGISTERS                0x10

class vt83c461_device : public ide_controller_32_device
{
public:
	vt83c461_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
class vt83c461_device : public ide_controller_32_device
{
public:
	vt83c461_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER(read_config);
	DECLARE_WRITE32_MEMBER(write_config);

protected:
<<<<<<< HEAD
	virtual void device_start();

private:
	UINT8           m_config_unknown;
	UINT8           m_config_register[IDE_CONFIG_REGISTERS];
	UINT8           m_config_register_num;
};

extern const device_type VT83C461;

#endif
=======
	virtual void device_start() override;

private:
	static constexpr unsigned  IDE_CONFIG_REGISTERS= 0x10;

	uint8_t           m_config_unknown;
	uint8_t           m_config_register[IDE_CONFIG_REGISTERS];
	uint8_t           m_config_register_num;
};

DECLARE_DEVICE_TYPE(VT83C461, vt83c461_device)

#endif // MAME_MACHINE_VT83C461_H
>>>>>>> upstream/master
