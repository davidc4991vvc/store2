// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD

#include "emu.h"
=======
#ifndef MAME_MACHINE_DECO222
#define MAME_MACHINE_DECO222

#pragma once

>>>>>>> upstream/master
#include "cpu/m6502/m6502.h"

class deco_222_device : public m6502_device {
public:
<<<<<<< HEAD
	deco_222_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	deco_222_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

protected:
	class mi_decrypt : public mi_default_normal {
	public:
		bool had_written;

		virtual ~mi_decrypt() {}
<<<<<<< HEAD
		virtual UINT8 read_sync(UINT16 adr);
	};

	virtual void device_start();
	virtual void device_reset();

};

static const device_type DECO_222 = &device_creator<deco_222_device>;

=======
		virtual uint8_t read_sync(uint16_t adr) override;
	};

	virtual void device_start() override;
	virtual void device_reset() override;

};

>>>>>>> upstream/master


class deco_c10707_device : public m6502_device {
public:
<<<<<<< HEAD
	deco_c10707_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	deco_c10707_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master

protected:
	class mi_decrypt : public mi_default_normal {
	public:
		bool had_written;

		virtual ~mi_decrypt() {}
<<<<<<< HEAD
		virtual UINT8 read_sync(UINT16 adr);
	};

	virtual void device_start();
	virtual void device_reset();

};

static const device_type DECO_C10707 = &device_creator<deco_c10707_device>;
=======
		virtual uint8_t read_sync(uint16_t adr) override;
	};

	virtual void device_start() override;
	virtual void device_reset() override;

};


DECLARE_DEVICE_TYPE(DECO_222, deco_222_device)
DECLARE_DEVICE_TYPE(DECO_C10707, deco_c10707_device)

#endif // MAME_MACHINE_DECO222
>>>>>>> upstream/master
