// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    CST Q+4 emulation

**********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __CST_Q_PLUS4__
#define __CST_Q_PLUS4__
=======
#ifndef MAME_BUS_QL_CST_Q_PLUS4_H
#define MAME_BUS_QL_CST_Q_PLUS4_H

#pragma once
>>>>>>> upstream/master

#include "exp.h"
#include "machine/6821pia.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// ======================> cst_q_plus4_t

class cst_q_plus4_t : public device_t,
						public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	cst_q_plus4_t(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	cst_q_plus4_t(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source, int ram_size);

	// optional information overrides
	virtual const rom_entry *device_rom_region() const;
	virtual machine_config_constructor device_mconfig_additions() const;

=======
// ======================> cst_q_plus4_device

class cst_q_plus4_device : public device_t, public device_ql_expansion_card_interface
{
public:
	// construction/destruction
	cst_q_plus4_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	// device-level overrides
	virtual void device_start() override;

	// optional information overrides
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual void device_add_mconfig(machine_config &config) override;

	// device_ql_expansion_card_interface overrides
	virtual uint8_t read(address_space &space, offs_t offset, uint8_t data) override;
	virtual void write(address_space &space, offs_t offset, uint8_t data) override;

private:
>>>>>>> upstream/master
	DECLARE_WRITE_LINE_MEMBER( exp1_extintl_w ) { m_exp1_extinl = state; update_extintl(); }
	DECLARE_WRITE_LINE_MEMBER( exp2_extintl_w ) { m_exp2_extinl = state; update_extintl(); }
	DECLARE_WRITE_LINE_MEMBER( exp3_extintl_w ) { m_exp3_extinl = state; update_extintl(); }
	DECLARE_WRITE_LINE_MEMBER( exp4_extintl_w ) { m_exp4_extinl = state; update_extintl(); }

<<<<<<< HEAD
protected:
	// device-level overrides
	virtual void device_start();

	// device_ql_expansion_card_interface overrides
	virtual UINT8 read(address_space &space, offs_t offset, UINT8 data);
	virtual void write(address_space &space, offs_t offset, UINT8 data);

private:
	void update_extintl() { m_slot->extintl_w(m_exp1_extinl || m_exp2_extinl || m_exp3_extinl || m_exp4_extinl); }

	required_device<ql_expansion_slot_t> m_exp1;
	required_device<ql_expansion_slot_t> m_exp2;
	required_device<ql_expansion_slot_t> m_exp3;
	required_device<ql_expansion_slot_t> m_exp4;
=======
	void update_extintl() { m_slot->extintl_w(m_exp1_extinl || m_exp2_extinl || m_exp3_extinl || m_exp4_extinl); }

	required_device<ql_expansion_slot_device> m_exp1;
	required_device<ql_expansion_slot_device> m_exp2;
	required_device<ql_expansion_slot_device> m_exp3;
	required_device<ql_expansion_slot_device> m_exp4;
>>>>>>> upstream/master
	required_memory_region m_rom;

	int m_exp1_extinl;
	int m_exp2_extinl;
	int m_exp3_extinl;
	int m_exp4_extinl;
};


<<<<<<< HEAD

// device type definition
extern const device_type CST_Q_PLUS4;



#endif
=======
// device type definition
DECLARE_DEVICE_TYPE(CST_Q_PLUS4, cst_q_plus4_device)

#endif // MAME_BUS_QL_CST_Q_PLUS4_H
>>>>>>> upstream/master
