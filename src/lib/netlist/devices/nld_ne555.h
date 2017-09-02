// license:GPL-2.0+
// copyright-holders:Couriersud
<<<<<<< HEAD
/*
 * nld_NE555.h
 *
 *  NE555: PRECISION TIMERS
 *
 *          +--------+
 *      GND |1  ++  8| VCC
 *     TRIG |2      7| DISCH
 *      OUT |3      6| THRES
 *    RESET |4      5| CONT
 *          +--------+
 *
 *  Naming conventions follow Texas Instruments datasheet
 *
 */
=======
>>>>>>> upstream/master

#ifndef NLD_NE555_H_
#define NLD_NE555_H_

<<<<<<< HEAD
#include "nl_base.h"
#include "analog/nld_twoterm.h"

#define NE555(_name)                                                        \
		NET_REGISTER_DEV(NE555, _name)

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_DEVICE(NE555,
	NETLIB_NAME(R) m_R1;
	NETLIB_NAME(R) m_R2;
	NETLIB_NAME(R) m_R3;
	NETLIB_NAME(R) m_RDIS;

	logic_input_t m_RESET;
	analog_input_t m_THRES;
	analog_input_t m_TRIG;
	analog_output_t m_OUT;

	bool m_last_out;
	bool m_ff;

	inline nl_double clamp(const nl_double v, const nl_double a, const nl_double b);

);

#define NE555_DIP(_name)                                                         \
		NET_REGISTER_DEV(NE555_DIP, _name)

NETLIB_DEVICE_DERIVED_PURE(NE555_dip, NE555);

NETLIB_NAMESPACE_DEVICES_END()
=======
#include "../nl_setup.h"

#define NE555(name)                                                             \
		NET_REGISTER_DEV(NE555, name)

#define NE555_DIP(name)                                                         \
		NET_REGISTER_DEV(NE555_DIP, name)
>>>>>>> upstream/master

#endif /* NLD_NE555_H_ */
