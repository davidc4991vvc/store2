// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Luxor ABC 890 bus expander emulation

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __ABC890__
#define __ABC890__

#include "emu.h"
=======
#ifndef MAME_BUS_ABCBUS_ABC890_H
#define MAME_BUS_ABCBUS_ABC890_H

#pragma once

>>>>>>> upstream/master
#include "abcbus.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> abc890_t

class abc890_t :  public device_t,
=======
// ======================> abc890_device

class abc890_device :  public device_t,
>>>>>>> upstream/master
					public device_abcbus_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	abc890_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);
	abc890_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	// device_abcbus_interface overrides
	virtual void abcbus_cs(UINT8 data);
	virtual UINT8 abcbus_inp();
	virtual void abcbus_out(UINT8 data);
	virtual UINT8 abcbus_stat();
	virtual void abcbus_c1(UINT8 data);
	virtual void abcbus_c2(UINT8 data);
	virtual void abcbus_c3(UINT8 data);
	virtual void abcbus_c4(UINT8 data);
	virtual UINT8 abcbus_xmemfl(offs_t offset);
	virtual void abcbus_xmemw(offs_t offset, UINT8 data);
};


// ======================> abc_expansion_unit_t

class abc_expansion_unit_t :  public abc890_t
{
public:
	// construction/destruction
	abc_expansion_unit_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
};


// ======================> abc894_t

class abc894_t :  public abc890_t
{
public:
	// construction/destruction
	abc894_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
};


// ======================> abc850_t

class abc850_t :  public abc890_t
{
public:
	// construction/destruction
	abc850_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
};


// ======================> abc852_t

class abc852_t :  public abc890_t
{
public:
	// construction/destruction
	abc852_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
};


// ======================> abc856_t

class abc856_t :  public abc890_t
{
public:
	// construction/destruction
	abc856_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
=======
	abc890_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	abc890_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;

	// device_abcbus_interface overrides
	virtual void abcbus_cs(uint8_t data) override;
	virtual uint8_t abcbus_inp() override;
	virtual void abcbus_out(uint8_t data) override;
	virtual uint8_t abcbus_stat() override;
	virtual void abcbus_c1(uint8_t data) override;
	virtual void abcbus_c2(uint8_t data) override;
	virtual void abcbus_c3(uint8_t data) override;
	virtual void abcbus_c4(uint8_t data) override;
	virtual uint8_t abcbus_xmemfl(offs_t offset) override;
	virtual void abcbus_xmemw(offs_t offset, uint8_t data) override;
};


// ======================> abc_expansion_unit_device

class abc_expansion_unit_device :  public abc890_device
{
public:
	// construction/destruction
	abc_expansion_unit_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
};


// ======================> abc894_device

class abc894_device :  public abc890_device
{
public:
	// construction/destruction
	abc894_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
};


// ======================> abc850_device

class abc850_device :  public abc890_device
{
public:
	// construction/destruction
	abc850_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
};


// ======================> abc852_device

class abc852_device :  public abc890_device
{
public:
	// construction/destruction
	abc852_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
};


// ======================> abc856_device

class abc856_device :  public abc890_device
{
public:
	// construction/destruction
	abc856_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// optional information overrides
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type ABC_EXPANSION_UNIT;
extern const device_type ABC890;
extern const device_type ABC894;
extern const device_type ABC850;
extern const device_type ABC852;
extern const device_type ABC856;



#endif
=======
DECLARE_DEVICE_TYPE(ABC_EXPANSION_UNIT, abc_expansion_unit_device)
DECLARE_DEVICE_TYPE(ABC890,             abc890_device)
DECLARE_DEVICE_TYPE(ABC894,             abc894_device)
DECLARE_DEVICE_TYPE(ABC850,             abc850_device)
DECLARE_DEVICE_TYPE(ABC852,             abc852_device)
DECLARE_DEVICE_TYPE(ABC856,             abc856_device)



#endif // MAME_BUS_ABCBUS_ABC890_H
>>>>>>> upstream/master
