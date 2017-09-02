// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/***************************************************************************

    m6510t.h

    6510 with the full 8 i/o pins at the expense of the NMI and RDY lines.

***************************************************************************/

<<<<<<< HEAD
#ifndef __M6510T_H__
#define __M6510T_H__
=======
#ifndef MAME_CPU_M6502_M6510T_H
#define MAME_CPU_M6502_M6510T_H
>>>>>>> upstream/master

#include "m6510.h"

#define MCFG_M6510T_PORT_CALLBACKS(_read, _write) \
	downcast<m6510t_device *>(device)->set_callbacks(DEVCB_##_read, DEVCB_##_write);

#define MCFG_M6510T_PORT_PULLS(_up, _down) \
	downcast<m6510t_device *>(device)->set_pulls(_up, _down);

class m6510t_device : public m6510_device {
public:
<<<<<<< HEAD
	m6510t_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
=======
	m6510t_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};

enum {
	M6510T_IRQ_LINE = m6502_device::IRQ_LINE,
	M6510T_SET_OVERFLOW = m6502_device::V_LINE
};

<<<<<<< HEAD
extern const device_type M6510T;

#endif
=======
DECLARE_DEVICE_TYPE(M6510T, m6510t_device)

#endif // MAME_CPU_M6502_M6510T_H
>>>>>>> upstream/master
