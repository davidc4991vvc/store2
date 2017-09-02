// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    a2mockingboard.h

    Sweet Micro Systems Mockingboard and compatibles

*********************************************************************/

<<<<<<< HEAD
#ifndef __A2BUS_MOCKINGBOARD__
#define __A2BUS_MOCKINGBOARD__

#include "emu.h"
=======
#ifndef MAME_BUS_A2BUS_A2MOCKINGBOARD_H
#define MAME_BUS_A2BUS_A2MOCKINGBOARD_H

>>>>>>> upstream/master
#include "a2bus.h"
#include "machine/6522via.h"
#include "sound/ay8910.h"
#include "sound/tms5220.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_ayboard_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	a2bus_ayboard_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;

=======
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( via1_irq_w );
	DECLARE_WRITE_LINE_MEMBER( via2_irq_w );
	DECLARE_WRITE8_MEMBER(via1_out_a);
	DECLARE_WRITE8_MEMBER(via1_out_b);
	DECLARE_WRITE8_MEMBER(via2_out_a);
	DECLARE_WRITE8_MEMBER(via2_out_b);

protected:
<<<<<<< HEAD
	virtual void device_start();
	virtual void device_reset();

	// overrides of standard a2bus slot functions
	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);
	virtual UINT8 read_cnxx(address_space &space, UINT8 offset);
	virtual void write_cnxx(address_space &space, UINT8 offset, UINT8 data);
=======
	// construction/destruction
	a2bus_ayboard_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual void write_cnxx(address_space &space, uint8_t offset, uint8_t data) override;
>>>>>>> upstream/master

	required_device<via6522_device> m_via1;
	required_device<via6522_device> m_via2;
	required_device<ay8913_device> m_ay1;
	required_device<ay8913_device> m_ay2;
	optional_device<ay8913_device> m_ay3;
	optional_device<ay8913_device> m_ay4;

	bool m_isPhasor, m_PhasorNative;

private:
<<<<<<< HEAD
	UINT8 m_porta1, m_porta2;
=======
	uint8_t m_porta1, m_porta2;
>>>>>>> upstream/master
};

class a2bus_mockingboard_device : public a2bus_ayboard_device
{
public:
<<<<<<< HEAD
	a2bus_mockingboard_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	a2bus_mockingboard_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

class a2bus_phasor_device : public a2bus_ayboard_device
{
public:
<<<<<<< HEAD
	a2bus_phasor_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual machine_config_constructor device_mconfig_additions() const;
=======
	a2bus_phasor_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master
};

class a2bus_echoplus_device : public a2bus_ayboard_device
{
public:
<<<<<<< HEAD
	a2bus_echoplus_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual UINT8 read_c0nx(address_space &space, UINT8 offset);
	virtual void write_c0nx(address_space &space, UINT8 offset, UINT8 data);

	required_device<tms5220_device> m_tms;

	virtual machine_config_constructor device_mconfig_additions() const;
};

// device type definition
extern const device_type A2BUS_MOCKINGBOARD;
extern const device_type A2BUS_PHASOR;
extern const device_type A2BUS_ECHOPLUS;

#endif  /* __A2BUS_MOCKINGBOARD__ */
=======
	a2bus_echoplus_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_add_mconfig(machine_config &config) override;

	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;

	required_device<tms5220_device> m_tms;
};

// device type definition
DECLARE_DEVICE_TYPE(A2BUS_MOCKINGBOARD, a2bus_mockingboard_device)
DECLARE_DEVICE_TYPE(A2BUS_PHASOR,       a2bus_phasor_device)
DECLARE_DEVICE_TYPE(A2BUS_ECHOPLUS,     a2bus_echoplus_device)

#endif  // MAME_BUS_A2BUS_A2MOCKINGBOARD_H
>>>>>>> upstream/master
