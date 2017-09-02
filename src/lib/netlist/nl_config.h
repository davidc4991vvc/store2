// license:GPL-2.0+
// copyright-holders:Couriersud
<<<<<<< HEAD
/*
 * nlconfig.h
=======
/*!
 *
 * \file nl_config.h
>>>>>>> upstream/master
 *
 */

#ifndef NLCONFIG_H_
#define NLCONFIG_H_

#include "plib/pconfig.h"

//============================================================
//  SETUP
//============================================================

<<<<<<< HEAD
/*
 * The following options determine how object::update is called.
 * NL_PMF_TYPE_VIRTUAL
 *      Use stock virtual call
 *
 * NL_PMF_TYPE_GNUC_PMF
 *      Use standard pointer to member function syntax
 *
 *  NL_PMF_TYPE_GNUC_PMF_CONV
 *      Use gnu extension and convert the pmf to a function pointer.
 *      This is not standard compliant and needs
 *      -Wno-pmf-conversions to compile.
 *
 *  NL_PMF_TYPE_INTERNAL
 *      Use the same approach as MAME for deriving the function pointer.
 *      This is compiler-dependant as well
 *
 *  Benchmarks for ./nltool -c run -f src/mame/drivers/nl_pong.c -t 10 -n pong_fast
 *
 *  NL_PMF_TYPE_INTERNAL:       215%
 *  NL_PMF_TYPE_GNUC_PMF:       163%
 *  NL_PMF_TYPE_GNUC_PMF_CONV:  215%
 *  NL_PMF_TYPE_VIRTUAL:        213%
 *
 *  The whole exercise was done to avoid virtual calls. In prior versions of
 *  netlist, the INTERNAL and GNUC_PMF_CONV approach provided significant improvement.
 *  Since than, ATTR_COLD was removed from functions declared as virtual.
 *  This may explain that the recent benchmarks show no difference at all.
 *
 *  Disappointing is the GNUC_PMF performance.
 */

// This will be autodetected
// #define NL_PMF_TYPE 2

#define NL_PMF_TYPE_VIRTUAL         0
#define NL_PMF_TYPE_GNUC_PMF        1
#define NL_PMF_TYPE_GNUC_PMF_CONV   2
#define NL_PMF_TYPE_INTERNAL        3

#ifndef NL_PMF_TYPE
	#if PHAS_PMF_INTERNAL
		#define NL_PMF_TYPE NL_PMF_TYPE_INTERNAL
	#else
		#define NL_PMF_TYPE NL_PMF_TYPE_VIRTUAL
	#endif
#endif

#if (NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF_CONV)
#pragma GCC diagnostic ignored "-Wpmf-conversions"
#endif

#define USE_TRUTHTABLE          (1)

// The following adds about 10% performance ...

#if !defined(USE_OPENMP)
#define USE_OPENMP              (0)
#endif // !defined(USE_OPENMP)

// Use nano-second resolution - Sufficient for now
#define NETLIST_INTERNAL_RES        (U64(1000000000))
//#define NETLIST_INTERNAL_RES      (U64(1000000000000))

#define NETLIST_CLOCK               (NETLIST_INTERNAL_RES)

#define NETLIST_GMIN_DEFAULT    (1e-9)

//#define nl_double float
//#define NL_FCONST(x) (x ## f)

#define nl_double double
#define NL_FCONST(x) x

=======

//============================================================
//  GENERAL
//============================================================

/*! Make use of a memory pool for performance related objects.
 *
 * Set to 1 to compile netlist with memory allocations from a
 * linear memory pool. This is based of the assumption that
 * due to enhanced locality there will be less cache misses.
 * Your mileage may vary.
 * This will cause crashes on OSX and thus is ignored on OSX.
 *
 */
#define USE_MEMPOOL                 (0)

/*
 * FIXME: Using truthtable is a lot slower than the explicit device
 *        in breakout. Performance drops by 20%. This can be fixed by
 *        setting param USE_DEACTIVATE for the device.
 */

#define USE_TRUTHTABLE_7448 (0)

// How many times do we try to resolve links (connections)
#define NL_MAX_LINK_RESOLVE_LOOPS   (100)
>>>>>>> upstream/master

//============================================================
//  Solver defines
//============================================================

<<<<<<< HEAD
#define USE_MATRIX_GS (0)
#define USE_GABS (1)
// savings are eaten up by effort
// FIXME: Convert into solver parameter
#define USE_LINEAR_PREDICTION (0)
=======
#define USE_GABS                    (1)
// savings are eaten up by effort
// FIXME: Convert into solver parameter
#define USE_LINEAR_PREDICTION       (0)
#define NETLIST_GMIN_DEFAULT     (1e-9)

>>>>>>> upstream/master


//============================================================
//  DEBUGGING
//============================================================

#define NL_DEBUG                    (false)
#define NL_KEEP_STATISTICS          (0)

//============================================================
//  General Macros
//============================================================

<<<<<<< HEAD
#if defined(_OPENMP)
=======
#if defined(OPENMP)
#define HAS_OPENMP ( OPENMP >= 200805 )
#elif defined(_OPENMP)
>>>>>>> upstream/master
#define HAS_OPENMP ( _OPENMP >= 200805 )
#else
#define HAS_OPENMP (0)
#endif

//============================================================
<<<<<<< HEAD
//  Performance tracking
//============================================================

#if NL_KEEP_STATISTICS
#include "eminline.h"
#define add_to_stat(v,x)        do { v += (x); } while (0)
#define inc_stat(v)             add_to_stat(v, 1)
#define begin_timing(v)         do { v -= get_profile_ticks(); } while (0)
#define end_timing(v)           do { v += get_profile_ticks(); } while (0)
#else
#define add_to_stat(v,x)        do { } while (0)
#define inc_stat(v)             add_to_stat(v, 1)
#define begin_timing(v)         do { } while (0)
#define end_timing(v)           do { } while (0)
#endif

// this macro passes an item followed by a string version of itself as two consecutive parameters
#define NLNAME(x) x, #x
=======
//  General
//============================================================

/* The following adds about 10% to 20% performance for analog
 * netlists like kidniki.
 */

#if !defined(USE_OPENMP)
#define USE_OPENMP              (0)
#endif // !defined(USE_OPENMP)

// Use nano-second resolution - Sufficient for now
#define NETLIST_INTERNAL_RES        (UINT64_C(1000000000))
#define NETLIST_CLOCK               (NETLIST_INTERNAL_RES)
//#define NETLIST_INTERNAL_RES      (UINT64_C(1000000000000))
//#define NETLIST_CLOCK               (UINT64_C(1000000000))


//#define nl_double float
//#define NL_FCONST(x) (x ## f)

//#define nl_double double
#define NL_FCONST(x) x
using nl_double = double;

/* The following option determines how object::update is called.
 * If set to 1, a virtual call is used. If it is left undefined, the best
 * approach will be automatically selected.
 */
>>>>>>> upstream/master

//============================================================
//  WARNINGS
//============================================================

#if (USE_OPENMP)
#if (!(HAS_OPENMP))
#error To use openmp compile and link with "-fopenmp"
#endif
#endif

<<<<<<< HEAD

=======
>>>>>>> upstream/master
#endif /* NLCONFIG_H_ */
