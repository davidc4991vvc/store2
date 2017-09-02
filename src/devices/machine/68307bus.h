// license:BSD-3-Clause
// copyright-holders:David Haywood
<<<<<<< HEAD
#include "cpu/m68000/m68000.h"

#define m68307BUS_MADR (0x01)
#define m68307BUS_MFDR (0x03)
#define m68307BUS_MBCR (0x05)
#define m68307BUS_MBSR (0x07)
#define m68307BUS_MBDR (0x09)


class m68307_mbus
{
	public:

	UINT16 m_MFCR;
=======
#ifndef MAME_MACHINE_68307_BUS_H
#define MAME_MACHINE_68307_BUS_H

#pragma once

#include "68307.h"


class m68307_cpu_device::m68307_mbus
{
public:
	uint16_t m_MFCR;
>>>>>>> upstream/master

	bool m_busy;
	bool m_intpend;

<<<<<<< HEAD
	void reset(void);
};
=======
	void reset();
};

#endif // MAME_MACHINE_68307_BUS_H
>>>>>>> upstream/master
