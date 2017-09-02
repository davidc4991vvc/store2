// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_log.h
 *
 *  Devices supporting analysis and logging
 *
 *  nld_log:
 *
 *          +---------+
 *          |    ++   |
 *        I |         | ==> Log to file "netlist_" + name() + ".log"
 *          |         |
 *          +---------+
 *
 */

#ifndef NLD_LOG_H_
#define NLD_LOG_H_

<<<<<<< HEAD
#include "nl_base.h"
#include "plib/pstream.h"

#define LOG(_name, _I)                                                        \
		NET_REGISTER_DEV(??PG, _name)                                         \
		NET_CONNECT(_name, I, _I)

NETLIB_NAMESPACE_DEVICES_START()

NETLIB_DEVICE(log,
	~NETLIB_NAME(log)();
	analog_input_t m_I;
protected:
	pofilestream *m_strm;
);

#define LOGD(_name, _I, _I2)                                                 \
		NET_REGISTER_DEV(LOGD, _name)                                        \
		NET_CONNECT(_name, I, _I)                                            \
		NET_CONNECT(_name, I2, _I2)

NETLIB_DEVICE_DERIVED(logD, log,
	analog_input_t m_I2;
);

#if 0
NETLIB_DEVICE(wav,
	~NETLIB_NAME(wav)();
	analog_input_t m_I;
private:
	// FIXME: rewrite sound/wavwrite.h to be an object ...
	void *m_file;
);
#endif

NETLIB_NAMESPACE_DEVICES_END()
=======
#include "../nl_setup.h"

#define LOG(name, cI)                                                        \
		NET_REGISTER_DEV(??PG, name)                                         \
		NET_CONNECT(name, I, cI)

#define LOGD(name, cI, cI2)                                                 \
		NET_REGISTER_DEV(LOGD, name)                                        \
		NET_CONNECT(name, I, cI)                                            \
		NET_CONNECT(name, I2, cI2)
>>>>>>> upstream/master

#endif /* NLD_LOG_H_ */
