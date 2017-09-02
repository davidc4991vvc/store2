// license:BSD-3-Clause
// copyright-holders:Andrew Gardner,Aaron Giles
/***************************************************************************

    okiadpcm.h

    OKI ADCPM emulation.

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __OKIADPCM_H__
#define __OKIADPCM_H__
=======
#ifndef MAME_SOUND_OKIADPCM_H
#define MAME_SOUND_OKIADPCM_H

#pragma once
>>>>>>> upstream/master


// ======================> oki_adpcm_state

// Internal ADPCM state, used by external ADPCM generators with compatible specs to the OKIM 6295.
class oki_adpcm_state
{
public:
	oki_adpcm_state() { compute_tables(); reset(); }

	void reset();
<<<<<<< HEAD
	INT16 clock(UINT8 nibble);

	INT32   m_signal;
	INT32   m_step;

private:
	static const INT8 s_index_shift[8];
=======
	int16_t clock(uint8_t nibble);

	int32_t   m_signal;
	int32_t   m_step;

private:
	static const int8_t s_index_shift[8];
>>>>>>> upstream/master
	static int s_diff_lookup[49*16];

	static void compute_tables();
	static bool s_tables_computed;
};


// ======================> oki_adpcm2_state

// Internal ADPCM2 state, used by external ADPCM generators with compatible specs to the OKI MSM9810.
// TODO: not thoroughly tested: is the output 15 bit?
class oki_adpcm2_state
{
public:
	oki_adpcm2_state() { compute_tables(); reset(); }

	void reset();
<<<<<<< HEAD
	INT16 clock(UINT8 nibble);

	INT32   m_signal;
	INT32   m_step;

private:
	static const INT8 s_index_shift[8];
=======
	int16_t clock(uint8_t nibble);

	int32_t   m_signal;
	int32_t   m_step;

private:
	static const int8_t s_index_shift[8];
>>>>>>> upstream/master
	static int s_diff_lookup[49*16];

	static void compute_tables();
	static bool s_tables_computed;
};


<<<<<<< HEAD
#endif // __OKIADPCM_H__
=======
#endif // MAME_SOUND_OKIADPCM_H
>>>>>>> upstream/master
