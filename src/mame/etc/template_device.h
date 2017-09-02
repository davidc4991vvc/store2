// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Angelo Salese
/***************************************************************************

Template for skeleton device

***************************************************************************/

#pragma once

#ifndef __XXXDEV_H__
#define __XXXDEV_H__
=======
// copyright-holders:<author_name>
/***************************************************************************

Template for squeleton device

***************************************************************************/

#ifndef MAME_MACHINE_XXX_H
#define MAME_MACHINE_XXX_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

<<<<<<< HEAD
#define MCFG_XXX_ADD(_tag,_freq) \
	MCFG_DEVICE_ADD(_tag, XXX, _freq)
=======
#define MCFG_XXX_ADD(tag, freq) \
		MCFG_DEVICE_ADD((tag), XXX, (freq))

>>>>>>> upstream/master

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> xxx_device

class xxx_device : public device_t
{
public:
	// construction/destruction
<<<<<<< HEAD
	xxx_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	xxx_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

	// I/O operations
	DECLARE_WRITE8_MEMBER( write );
	DECLARE_READ8_MEMBER( read );

protected:
	// device-level overrides
<<<<<<< HEAD
	virtual void device_validity_check(validity_checker &valid) const;
	virtual void device_start();
	virtual void device_reset();
=======
	//virtual void device_validity_check(validity_checker &valid) const override;
	virtual void device_add_mconfig() override;
	virtual void device_start() override;
	virtual void device_reset() override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type XXX;
=======
DECLARE_DEVICE_TYPE(XXX, xxx_device)
>>>>>>> upstream/master



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************


<<<<<<< HEAD

#endif
=======
#endif // MAME_MACHINE_XXX_H
>>>>>>> upstream/master
