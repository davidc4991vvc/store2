// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m6504.h

    Mostek 6502, NMOS variant with reduced address bus

***************************************************************************/

<<<<<<< HEAD
#ifndef __M6504_H__
#define __M6504_H__
=======
#ifndef MAME_CPU_M6502_M6504_H
#define MAME_CPU_M6502_M6504_H
>>>>>>> upstream/master

#include "m6502.h"

class m6504_device : public m6502_device {
public:
<<<<<<< HEAD
	m6504_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m6504_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

protected:
	class mi_6504_normal : public memory_interface {
	public:
		virtual ~mi_6504_normal() {}
<<<<<<< HEAD
		virtual UINT8 read(UINT16 adr);
		virtual UINT8 read_sync(UINT16 adr);
		virtual UINT8 read_arg(UINT16 adr);
		virtual void write(UINT16 adr, UINT8 val);
=======
		virtual uint8_t read(uint16_t adr) override;
		virtual uint8_t read_sync(uint16_t adr) override;
		virtual uint8_t read_arg(uint16_t adr) override;
		virtual void write(uint16_t adr, uint8_t val) override;
>>>>>>> upstream/master
	};

	class mi_6504_nd : public mi_6504_normal {
	public:
		virtual ~mi_6504_nd() {}
<<<<<<< HEAD
		virtual UINT8 read_sync(UINT16 adr);
		virtual UINT8 read_arg(UINT16 adr);
	};

	virtual void device_start();
=======
		virtual uint8_t read_sync(uint16_t adr) override;
		virtual uint8_t read_arg(uint16_t adr) override;
	};

	virtual void device_start() override;
>>>>>>> upstream/master
};


enum {
	M6504_IRQ_LINE = m6502_device::IRQ_LINE,
	M6504_NMI_LINE = m6502_device::NMI_LINE,
	M6504_SET_OVERFLOW = m6502_device::V_LINE
};

extern const device_type M6504;

<<<<<<< HEAD
#endif
=======
#endif // MAME_CPU_M6502_M6504_H
>>>>>>> upstream/master
