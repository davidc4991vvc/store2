// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_7490.h
 *
 *  DM7490: Decade Counters
 *
 *          +--------------+
 *        B |1     ++    14| A
 *      R01 |2           13| NC
 *      R02 |3           12| QA
 *       NC |4    7490   11| QD
 *      VCC |5           10| GND
 *      R91 |6            9| QB
 *      R92 |7            8| QC
 *          +--------------+
 *
 *          Counter Sequence
 *
 *          +-------++----+----+----+----+
 *          | COUNT || QD | QC | QB | QA |
 *          +=======++====+====+====+====+
 *          |    0  ||  0 |  0 |  0 |  0 |
 *          |    1  ||  0 |  0 |  0 |  1 |
 *          |    2  ||  0 |  0 |  1 |  0 |
 *          |    3  ||  0 |  0 |  1 |  1 |
 *          |    4  ||  0 |  1 |  0 |  0 |
 *          |    5  ||  0 |  1 |  0 |  1 |
 *          |    6  ||  0 |  1 |  1 |  0 |
 *          |    7  ||  0 |  1 |  1 |  1 |
 *          |    8  ||  1 |  0 |  0 |  0 |
 *          |    9  ||  1 |  0 |  0 |  1 |
 *          +-------++----+----+----+----+
 *
 *          Note A Output QA is connected to input B for BCD count
 *
 *          Reset Count Function table
 *
 *          +-----+-----+-----+-----++----+----+----+----+
 *          | R01 | R02 | R91 | R92 || QD | QC | QB | QA |
 *          +=====+=====+=====+=====++====+====+====+====+
 *          |  1  |  1  |  0  |  X  ||  0 |  0 |  0 |  0 |
 *          |  1  |  1  |  X  |  0  ||  0 |  0 |  0 |  0 |
 *          |  X  |  X  |  1  |  1  ||  1 |  0 |  0 |  1 |
 *          |  X  |  0  |  X  |  0  ||       COUNT       |
 *          |  0  |  X  |  0  |  X  ||       COUNT       |
 *          |  0  |  X  |  X  |  0  ||       COUNT       |
 *          |  X  |  0  |  0  |  X  ||       COUNT       |
 *          +-----+-----+-----+-----++----+----+----+----+
 *
 *  Naming conventions follow National Semiconductor datasheet
 *
 */

#ifndef NLD_7490_H_
#define NLD_7490_H_

<<<<<<< HEAD
#include "nl_base.h"

#define TTL_7490(_name, _A, _B, _R1, _R2, _R91, _R92)                               \
		NET_REGISTER_DEV(TTL_7490, _name)                                               \
		NET_CONNECT(_name, A, _A)                                                   \
		NET_CONNECT(_name, B, _B)                                                   \
		NET_CONNECT(_name, R1,  _R1)                                                \
		NET_CONNECT(_name, R2,  _R2)                                                \
		NET_CONNECT(_name, R91, _R91)                                               \
		NET_CONNECT(_name, R92, _R92)

#define TTL_7490_DIP(_name)                                                         \
		NET_REGISTER_DEV(TTL_7490_DIP, _name)

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_DEVICE(7490,
	ATTR_HOT void update_outputs();

	logic_input_t m_R1;
	logic_input_t m_R2;
	logic_input_t m_R91;
	logic_input_t m_R92;
	logic_input_t m_A;
	logic_input_t m_B;

	UINT8 m_cnt;
	UINT8 m_last_A;
	UINT8 m_last_B;

	logic_output_t m_Q[4];
);

NETLIB_DEVICE_DERIVED_PURE(7490_dip, 7490);

NETLIB_NAMESPACE_DEVICES_END()
=======
#include "../nl_setup.h"

#define TTL_7490(name, cA, cB, cR1, cR2, cR91, cR92)                               \
		NET_REGISTER_DEV(TTL_7490, name)                                               \
		NET_CONNECT(name, A, cA)                                                   \
		NET_CONNECT(name, B, cB)                                                   \
		NET_CONNECT(name, R1,  cR1)                                                \
		NET_CONNECT(name, R2,  cR2)                                                \
		NET_CONNECT(name, R91, cR91)                                               \
		NET_CONNECT(name, R92, cR92)

#define TTL_7490_DIP(name)                                                         \
		NET_REGISTER_DEV(TTL_7490_DIP, name)
>>>>>>> upstream/master

#endif /* NLD_7490_H_ */
