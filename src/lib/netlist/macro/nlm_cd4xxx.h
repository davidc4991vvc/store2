<<<<<<< HEAD
#ifndef NLD_CD4XXX_H_
#define NLD_CD4XXX_H_

#include "nl_setup.h"
=======
// license:GPL-2.0+
// copyright-holders:Couriersud
#ifndef NLD_CD4XXX_H_
#define NLD_CD4XXX_H_

#include "../nl_setup.h"
>>>>>>> upstream/master

/*
 * Devices:
 *
 * CD4001_NOR : single gate
 * CD4001_DIP : dip package
 * CD4020_DIP : dip package (device model in core)
 * CD4016_DIP : dip package (device model in core)
 * CD4066_DIP : dip package (device model in core)
 *
 */

#ifndef __PLIB_PREPROCESSOR__

/* ----------------------------------------------------------------------------
 *  Netlist Macros
 * ---------------------------------------------------------------------------*/

<<<<<<< HEAD
#define CD4001_NOR(_name)                                                      \
		NET_REGISTER_DEV(CD4001_NOR, _name)

#define CD4001_DIP(_name)                                                      \
		NET_REGISTER_DEV(CD4001_DIP, _name)
=======
#ifndef NL_AUTO_DEVICES

#define CD4001_NOR(name)                                                      \
		NET_REGISTER_DEV(CD4001_NOR, name)

#define CD4001_DIP(name)                                                      \
		NET_REGISTER_DEV(CD4001_DIP, name)
>>>>>>> upstream/master

/* ----------------------------------------------------------------------------
 *  DIP only macros
 * ---------------------------------------------------------------------------*/

<<<<<<< HEAD
#define CD4020_DIP(_name)                                                      \
		NET_REGISTER_DEV(CD4020_DIP, _name)

#define CD4066_DIP(_name)                                                      \
		NET_REGISTER_DEV(CD4066_DIP, _name)

#define CD4016_DIP(_name)                                                      \
		NET_REGISTER_DEV(CD4016_DIP, _name)

=======
#define CD4020_DIP(name)                                                      \
		NET_REGISTER_DEV(CD4020_DIP, name)

#define CD4066_DIP(name)                                                      \
		NET_REGISTER_DEV(CD4066_DIP, name)

#define CD4016_DIP(name)                                                      \
		NET_REGISTER_DEV(CD4016_DIP, name)

#define CD4316_DIP(name)                                                      \
		NET_REGISTER_DEV(CD4016_DIP, name)

#endif
>>>>>>> upstream/master
/* ----------------------------------------------------------------------------
 *  External declarations
 * ---------------------------------------------------------------------------*/

NETLIST_EXTERNAL(CD4XXX_lib)

#endif

#endif
