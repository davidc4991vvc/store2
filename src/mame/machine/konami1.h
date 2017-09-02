// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
<<<<<<< HEAD
=======
#ifndef MAME_MACHINE_KONAMI1_H
#define MAME_MACHINE_KONAMI1_H

#pragma once

>>>>>>> upstream/master

#include "cpu/m6809/m6809.h"

class konami1_device : public m6809_base_device {
public:
<<<<<<< HEAD
	konami1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void set_encryption_boundary(UINT16 adr);
=======
	konami1_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void set_encryption_boundary(uint16_t adr);
>>>>>>> upstream/master

protected:
	class mi_konami1 : public mi_default {
	public:
<<<<<<< HEAD
		UINT16 m_boundary;
		mi_konami1(UINT16 boundary);
		virtual ~mi_konami1() {}
		virtual UINT8 read_opcode(UINT16 adr);
	};

	UINT16 m_boundary;

	virtual void device_start();
};

extern const device_type KONAMI1;
=======
		uint16_t m_boundary;
		mi_konami1(uint16_t boundary);
		virtual ~mi_konami1() {}
		virtual uint8_t read_opcode(uint16_t adr) override;
	};

	uint16_t m_boundary;

	virtual void device_start() override;
};

DECLARE_DEVICE_TYPE(KONAMI1, konami1_device)

#endif // MAME_MACHINE_KONAMI1_H
>>>>>>> upstream/master
