// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
<<<<<<< HEAD
#ifndef __SCP1000_SLOT_H
#define __SCP1000_SLOT_H
=======
#ifndef MAME_BUS_SPC1000_EXP_H
#define MAME_BUS_SPC1000_EXP_H

#pragma once
>>>>>>> upstream/master

// ======================> device_spc1000_card_interface

class device_spc1000_card_interface : public device_slot_card_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	device_spc1000_card_interface(const machine_config &mconfig, device_t &device);
=======
>>>>>>> upstream/master
	virtual ~device_spc1000_card_interface();

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read) { return 0xff; }
<<<<<<< HEAD
	virtual DECLARE_WRITE8_MEMBER(write) {}

protected:
=======
	virtual DECLARE_WRITE8_MEMBER(write) { }

protected:
	device_spc1000_card_interface(const machine_config &mconfig, device_t &device);
>>>>>>> upstream/master
};


// ======================> spc1000_exp_device

<<<<<<< HEAD
class spc1000_exp_device : public device_t,
								public device_slot_interface
{
public:
	// construction/destruction
	spc1000_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~spc1000_exp_device();

	// device-level overrides
	virtual void device_start();

=======
class spc1000_exp_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	spc1000_exp_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	virtual ~spc1000_exp_device();

>>>>>>> upstream/master
	// reading and writing
	virtual DECLARE_READ8_MEMBER(read);
	virtual DECLARE_WRITE8_MEMBER(write);

protected:
<<<<<<< HEAD

	device_spc1000_card_interface*       m_card;
};



// device type definition
extern const device_type SPC1000_EXP_SLOT;

#endif
=======
	// device-level overrides
	virtual void device_start() override;

	device_spc1000_card_interface* m_card;
};


// device type definition
DECLARE_DEVICE_TYPE(SPC1000_EXP_SLOT, spc1000_exp_device)

#endif // MAME_BUS_SPC1000_EXP_H
>>>>>>> upstream/master
