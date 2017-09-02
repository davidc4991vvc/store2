<<<<<<< HEAD
#ifndef NLM_OTHER_H_
#define NLM_OTHER_H_

#include "nl_setup.h"
=======
// license:GPL-2.0+
// copyright-holders:Couriersud
#ifndef NLM_OTHER_H_
#define NLM_OTHER_H_

#include "../nl_setup.h"
>>>>>>> upstream/master

#ifndef __PLIB_PREPROCESSOR__

/* ----------------------------------------------------------------------------
 *  Netlist Macros
 * ---------------------------------------------------------------------------*/

<<<<<<< HEAD
#define MC14584B_GATE(_name)                                                   \
		NET_REGISTER_DEV(MC14584B_GATE, _name)

#define MC14584B_DIP(_name)                                                    \
		NET_REGISTER_DEV(MC14584B_DIP, _name)

=======
#ifndef NL_AUTO_DEVICES

#define MC14584B_GATE(name)                                                   \
		NET_REGISTER_DEV(MC14584B_GATE, name)

#define MC14584B_DIP(name)                                                    \
		NET_REGISTER_DEV(MC14584B_DIP, name)

#endif
>>>>>>> upstream/master

/* ----------------------------------------------------------------------------
 *  External declarations
 * ---------------------------------------------------------------------------*/

NETLIST_EXTERNAL(otheric_lib)

#endif

#endif
