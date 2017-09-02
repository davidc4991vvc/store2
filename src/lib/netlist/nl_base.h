// license:GPL-2.0+
// copyright-holders:Couriersud
<<<<<<< HEAD
/*
 * nlbase.h
 *
 *  A mixed signal circuit simulation
 *
 *  D: Device
 *  O: Rail output (output)
 *  I: Infinite impedance input (input)
 *  T: Terminal (finite impedance)
 *
 *  +---+     +---+     +---+     +---+     +---+
 *  |   |     |   |     |   |     |   |     |   |
 *  | D |     | D |     | D |     | D |     | D |
 *  |   |     |   |     |   |     |   |     |   |
 *  +-O-+     +-I-+     +-I-+     +-T-+     +-T-+
 *    |         |         |         |         |
 *  +-+---------+---------+---------+---------+-+
 *  | rail net                                  |
 *  +-------------------------------------------+
 *
 *  A rail net is a net which is driven by exactly one output with an
 *  (idealized) internal resistance of zero.
 *  Ideally, it can deliver infinite current.
 *
 *  A infinite resistance input does not source or sink current.
 *
 *  Terminals source or sink finite (but never zero) current.
 *
 *  The system differentiates between analog and logic input and outputs and
 *  analog terminals. Analog and logic devices can not be connected to the
 *  same net. Instead, proxy devices are inserted automatically:
 *
 *  +---+     +---+
 *  |   |     |   |
 *  | D1|     | D2|
 *  | A |     | L |
 *  +-O-+     +-I-+
 *    |         |
 *  +-+---------+---+
 *  | rail net      |
 *  +---------------+
 *
 *  is converted into
 *              +----------+
 *              |          |
 *  +---+     +-+-+        |   +---+
 *  |   |     | L |  A-L   |   |   |
 *  | D1|     | D | Proxy  |   | D2|
 *  | A |     | A |        |   |   |
 *  +-O-+     +-I-+        |   +-I-+
 *    |         |          |     |
 *  +-+---------+--+     +-+-----+-------+
 *  | rail net (A) |     | rail net (L)  |
 *  +--------------|     +---------------+
 *
 *  This works both analog to logic as well as logic to analog.
 *
 *  The above is an advanced implementation of the existing discrete
 *  subsystem in MAME. Instead of relying on a fixed time-step, analog devices
 *  could either connect to fixed time-step clock or use an internal clock
 *  to update them. This would however introduce macro devices for RC, diodes
 *  and transistors again.
 *
 *  ============================================================================
 *
 *  Instead, the following approach in case of a pure terminal/input network
 *  is taken:
 *
 *  +---+     +---+     +---+     +---+     +---+
 *  |   |     |   |     |   |     |   |     |   |
 *  | D |     | D |     | D |     | D |     | D |
 *  |   |     |   |     |   |     |   |     |   |
 *  +-T-+     +-I-+     +-I-+     +-T-+     +-T-+
 *    |         |         |         |         |
 *   '+'        |         |        '-'       '-'
 *  +-+---------+---------+---------+---------+-+
 *  | Calculated net                            |
 *  +-------------------------------------------+
 *
 *  SPICE uses the following basic two terminal device:
 *
 *       (k)
 *  +-----T-----+
 *  |     |     |
 *  |  +--+--+  |
 *  |  |     |  |
 *  |  R     |  |
 *  |  R     |  |
 *  |  R     I  |
 *  |  |     I  |  Device n
 *  |  V+    I  |
 *  |  V     |  |
 *  |  V-    |  |
 *  |  |     |  |
 *  |  +--+--+  |
 *  |     |     |
 *  +-----T-----+
 *       (l)
 *
 *  This is a resistance in series to a voltage source and paralleled by a
 *  current source. This is suitable to model voltage sources, current sources,
 *  resistors, capacitors, inductances and diodes.
 *
 *  I(n,l) = - I(n,k) = ( V(k) - V - V(l) ) * (1/R(n)) + I(n)
 *
 *  Now, the sum of all currents for a given net must be 0:
 *
 *  Sum(n,I(n,l)) = 0 = sum(n, ( V(k) - V(n) - V(l) ) * (1/R(n)) + I(n) )
 *
 *  With G(n) = 1 / R(n) and sum(n, G(n)) = Gtot and k=k(n)
 *
 *  0 = - V(l) * Gtot + sum(n, (V(k(n)) - V(n)) * G(n) + I(n))
 *
 *  and with l=l(n) and fixed k
 *
 *  0 =  -V(k) * Gtot + sum(n, ( V(l(n) + V(n) ) * G(n) - I(n))
 *
 *  These equations represent a linear Matrix equation (with more math).
 *
 *  In the end the solution of the analog subsystem boils down to
 *
 *  (G - D) * V = I
 *
 *  with G being the conductance matrix, D a diagonal matrix with the total
 *  conductance on the diagonal elements, V the net voltage vector and I the
 *  current vector.
 *
 *  By using solely two terminal devices, we can simplify the whole calculation
 *  significantly. A BJT now is a four terminal device with two terminals being
 *  connected internally.
 *
 *  The system is solved using an iterative approach:
 *
 *  G * V - D * V = I
 *
 *  assuming V=Vn=Vo
 *
 *  Vn = D-1 * (I - G * Vo)
 *
 *  Each terminal thus has three properties:
 *
 *  a) Resistance
 *  b) Voltage source
 *  c) Current source/sink
 *
 *  Going forward, the approach can be extended e.g. to use a linear
 *  equation solver.
 *
 *  The formal representation of the circuit will stay the same, thus scales.
=======
/*!
 *
 * \file nl_base.h
>>>>>>> upstream/master
 *
 */

#ifndef NLBASE_H_
#define NLBASE_H_

#include "nl_lists.h"
#include "nl_time.h"
<<<<<<< HEAD
#include "nl_util.h"
#include "plib/pstate.h"
#include "plib/pfmtlog.h"
=======
#include "plib/palloc.h" // owned_ptr
#include "plib/pdynlib.h"
#include "plib/pstate.h"
#include "plib/pfmtlog.h"
#include "plib/pstream.h"
#include "plib/ppmf.h"

#include <unordered_map>

#ifdef NL_PROHIBIT_BASEH_INCLUDE
#error "nl_base.h included. Please correct."
#endif
>>>>>>> upstream/master

// ----------------------------------------------------------------------------------------
// Type definitions
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
typedef UINT8 netlist_sig_t;

//============================================================
//  MACROS / netlist devices
//============================================================

#define NETLIB_NAMESPACE_DEVICES_START()    namespace netlist { namespace devices {
#define NETLIB_NAMESPACE_DEVICES_END()  }}

#define NETLIB_NAME(_chip) nld_ ## _chip

#define NETLIB_NAME_STR_S(_s) # _s
#define NETLIB_NAME_STR(_chip) NETLIB_NAME_STR_S(nld_ ## _chip)

#define NETLIB_UPDATE(_chip) ATTR_HOT void NETLIB_NAME(_chip) :: update(void)
#define NETLIB_START(_chip) ATTR_COLD void NETLIB_NAME(_chip) :: start(void)

#define NETLIB_RESET(_chip) ATTR_COLD void NETLIB_NAME(_chip) :: reset(void)

#define NETLIB_STOP(_chip) ATTR_COLD void NETLIB_NAME(_chip) :: stop(void)

#define NETLIB_UPDATE_PARAM(_chip) ATTR_HOT void NETLIB_NAME(_chip) :: update_param(void)
#define NETLIB_FUNC_VOID(_chip, _name, _params) ATTR_HOT void NETLIB_NAME(_chip) :: _name _params

#define NETLIB_UPDATE_TERMINALS(_chip) ATTR_HOT void NETLIB_NAME(_chip) :: update_terminals(void)
#define NETLIB_UPDATE_TERMINALSI() ATTR_HOT void update_terminals(void)
#define NETLIB_UPDATEI() ATTR_HOT void update(void)

#define NETLIB_DEVICE_BASE(_name, _pclass, _extra, _priv)                       \
	class _name : public _pclass                                                \
	{                                                                           \
	public:                                                                     \
		_name()                                                                 \
		: _pclass()    { }                                                      \
	protected:                                                                  \
		_extra                                                                  \
		ATTR_HOT void update();                                                 \
		ATTR_HOT void start();                                                  \
		ATTR_HOT void reset();                                                  \
		_priv                                                                   \
	}

#define NETLIB_DEVICE_DERIVED_PURE(_name, _pclass)                            \
		NETLIB_DEVICE_BASE(NETLIB_NAME(_name), NETLIB_NAME(_pclass), protected:, private:)

#define NETLIB_DEVICE_DERIVED(_name, _pclass, _priv)                            \
		NETLIB_DEVICE_BASE(NETLIB_NAME(_name), NETLIB_NAME(_pclass), protected:, _priv)

#define NETLIB_DEVICE(_name, _priv)                                             \
		NETLIB_DEVICE_BASE(NETLIB_NAME(_name), device_t, protected:, _priv)

#define NETLIB_SUBDEVICE(_name, _priv)                                          \
	class NETLIB_NAME(_name) : public device_t                                  \
	{                                                                           \
	public:                                                                     \
		NETLIB_NAME(_name) ()                                                   \
		: device_t()                                                            \
			{ }                                                                 \
	/*protected:*/                                                              \
		ATTR_HOT void update();                                                 \
		ATTR_HOT void start();                                                  \
		ATTR_HOT void reset();                                                  \
	public:                                                                     \
		_priv                                                                   \
	}

#define NETLIB_DEVICE_WITH_PARAMS(_name, _priv)                                 \
		NETLIB_DEVICE_BASE(NETLIB_NAME(_name), device_t,                        \
			ATTR_HOT void update_param();                                       \
		, _priv)

#define NETLIB_DEVICE_WITH_PARAMS_DERIVED(_name, _pclass, _priv)                \
		NETLIB_DEVICE_BASE(NETLIB_NAME(_name), NETLIB_NAME(_pclass),            \
			ATTR_HOT void update_param();                                       \
		, _priv)

#define NETLIB_LOGIC_FAMILY(_fam)                                               \
virtual logic_family_desc_t *default_logic_family()                             \
{                                                                               \
	return netlist_family_ ## _fam;                                             \
}

=======
/*! netlist_sig_t is the type used for logic signals. */
using netlist_sig_t = std::uint32_t;

//============================================================
//  MACROS / New Syntax
//============================================================

/*! Construct a netlist device name */
#define NETLIB_NAME(chip) nld_ ## chip

#define NETLIB_OBJECT_DERIVED(name, pclass)                                   \
class NETLIB_NAME(name) : public NETLIB_NAME(pclass)

/*! Start a netlist device class.
 *  Used to start defining a netlist device class.
 *  The simplest device without inputs or outputs would look like this:
 *
 *      NETLIB_OBJECT(base_dummy)
 *      {
 *      public:
 *          NETLIB_CONSTRUCTOR(base_dummy) { }
 *      };
 *
 *  Also refer to #NETLIB_CONSTRUCTOR.
 */
#define NETLIB_OBJECT(name)                                                    \
class NETLIB_NAME(name) : public device_t

#define NETLIB_CONSTRUCTOR_DERIVED(cname, pclass)                              \
	private: detail::family_setter_t m_famsetter;                              \
	public: template <class CLASS> NETLIB_NAME(cname)(CLASS &owner, const pstring &name) \
	: NETLIB_NAME(pclass)(owner, name)

/*! Used to define the constructor of a netlist device.
 *  Use this to define the constructor of a netlist device. Please refer to
 *  #NETLIB_OBJECT for an example.
 */
#define NETLIB_CONSTRUCTOR(cname)                                              \
	private: detail::family_setter_t m_famsetter;                              \
	public: template <class CLASS> NETLIB_NAME(cname)(CLASS &owner, const pstring &name) \
		: device_t(owner, name)

	/*! Used to define the destructor of a netlist device.
	*  The use of a destructor for netlist device should normally not be necessary.
	*/
#define NETLIB_DESTRUCTOR(name) public: virtual ~NETLIB_NAME(name)()

	/*! Define an extended constructor and add further parameters to it.
	*  The macro allows to add further parameters to a device constructor. This is
	*  normally used for sub-devices and system devices only.
	*/
#define NETLIB_CONSTRUCTOR_EX(cname, ...)                                      \
	private: detail::family_setter_t m_famsetter;                              \
	public: template <class CLASS> NETLIB_NAME(cname)(CLASS &owner, const pstring &name, __VA_ARGS__) \
		: device_t(owner, name)

	/*! Add this to a device definition to mark the device as dynamic.
	*  If NETLIB_IS_DYNAMIC(true) is added to the device definition the device
	*  is treated as an analog dynamic device, i.e. #NETLIB_UPDATE_TERMINALSI
	*  is called on a each step of the Newton-Raphson step
	*  of solving the linear equations.
	*
	*  You may also use e.g. NETLIB_IS_DYNAMIC(m_func() != "") to only make the
	*  device a dynamic device if parameter m_func is set.
	*/
#define NETLIB_IS_DYNAMIC(expr)                                                \
	public: virtual bool is_dynamic() const override { return expr; }

	/*! Add this to a device definition to mark the device as a time-stepping device.
	 *
	 *  You have to implement NETLIB_TIMESTEP in this case as well. Currently, only
	 *  the capacitor and inductor devices uses this.
	 *
	 *  You may also use e.g. NETLIB_IS_TIMESTEP(m_func() != "") to only make the
	 *  device a dynamic device if parameter m_func is set. This is used by the
	 *  Voltage Source element.
	 *
	 *  Example:
	 *
	 *   NETLIB_TIMESTEP_IS_TIMESTEP()
	 *   NETLIB_TIMESTEPI()
	 *       {
	 *           // Gpar should support convergence
	 *           const nl_double G = m_C.Value() / step +  m_GParallel;
	 *           const nl_double I = -G * deltaV();
	 *           set(G, 0.0, I);
	 *       }
	 *
	 */
#define NETLIB_IS_TIMESTEP(expr)                                               \
	public: virtual bool is_timestep() const override { return expr; }

	/*! Used to implement the time stepping code.
	 *
	 * Please see NETLIB_IS_TIMESTEP for an example.
	 */
#define NETLIB_TIMESTEPI()                                                     \
	public: virtual void timestep(const nl_double step) override

#define NETLIB_UPDATE_AFTER_PARAM_CHANGE()                                     \
	public: virtual bool needs_update_after_param_change() const override { return true; }

#define NETLIB_FAMILY(family) , m_famsetter(*this, family)

#define NETLIB_DELEGATE(chip, name) nldelegate(&NETLIB_NAME(chip) :: name, this)

#define NETLIB_UPDATE_TERMINALSI() public: virtual void update_terminals() override
#define NETLIB_HANDLERI(name) private: virtual void name() NL_NOEXCEPT
#define NETLIB_UPDATEI() protected: virtual void update() NL_NOEXCEPT override
#define NETLIB_UPDATE_PARAMI() public: virtual void update_param() override
#define NETLIB_RESETI() protected: virtual void reset() override

#define NETLIB_TIMESTEP(chip) void NETLIB_NAME(chip) :: timestep(const nl_double step)

#define NETLIB_SUB(chip) nld_ ## chip
#define NETLIB_SUBXX(ns, chip) std::unique_ptr< ns :: nld_ ## chip >

#define NETLIB_HANDLER(chip, name) void NETLIB_NAME(chip) :: name(void) NL_NOEXCEPT
#define NETLIB_UPDATE(chip) NETLIB_HANDLER(chip, update)

// FIXME: NETLIB_PARENT_UPDATE should disappear
#define NETLIB_PARENT_UPDATE(chip) NETLIB_NAME(chip) :: update();

#define NETLIB_RESET(chip) void NETLIB_NAME(chip) :: reset(void)

#define NETLIB_UPDATE_PARAM(chip) void NETLIB_NAME(chip) :: update_param(void)
#define NETLIB_FUNC_VOID(chip, name, params) void NETLIB_NAME(chip) :: name params

#define NETLIB_UPDATE_TERMINALS(chip) void NETLIB_NAME(chip) :: update_terminals(void)
>>>>>>> upstream/master

//============================================================
//  Asserts
//============================================================

#if defined(MAME_DEBUG)
<<<<<<< HEAD
#define nl_assert(x)               do { if (1) if (!(x)) throw fatalerror_e(pfmt("assert: {1}:{2}: {3}")(__FILE__)(__LINE__)(#x) ); } while (0)
#else
#define nl_assert(x)               do { if (0) if (!(x)) throw fatalerror_e(pfmt("assert: {1}:{2}: {3}")(__FILE__)(__LINE__)(#x) ); } while (0)
#endif
#define nl_assert_always(x, msg)    do { if (!(x)) throw fatalerror_e(pfmt("Fatal error: {1}\nCaused by assert: {2}:{3}: {4}")(msg)(__FILE__)(__LINE__)(#x)); } while (0)


// -----------------------------------------------------------------------------
// forward definitions
// -----------------------------------------------------------------------------
=======
#define nl_assert(x)    do { if (1) if (!(x)) throw nl_exception(plib::pfmt("assert: {1}:{2}: {3}")(__FILE__)(__LINE__)(#x) ); } while (0)
#define NL_NOEXCEPT
#else
#define nl_assert(x)    do { if (0) if (!(x)) { /*throw nl_exception(plib::pfmt("assert: {1}:{2}: {3}")(__FILE__)(__LINE__)(#x) ); */} } while (0)
#define NL_NOEXCEPT     noexcept
#endif
#define nl_assert_always(x, msg)    do { if (!(x)) throw nl_exception(plib::pfmt("Fatal error: {1}\nCaused by assert: {2}:{3}: {4}")(msg)(__FILE__)(__LINE__)(#x)); } while (0)
>>>>>>> upstream/master

//============================================================
// Namespace starts
//============================================================

namespace netlist
{
<<<<<<< HEAD
=======
	// -----------------------------------------------------------------------------
	// forward definitions
	// -----------------------------------------------------------------------------

>>>>>>> upstream/master
	namespace devices
	{
		class matrix_solver_t;
		class NETLIB_NAME(gnd);
		class NETLIB_NAME(solver);
		class NETLIB_NAME(mainclock);
		class NETLIB_NAME(netlistparams);
		class NETLIB_NAME(base_proxy);
<<<<<<< HEAD
		class nld_base_d_to_a_proxy;
	}

	//============================================================
	//  Exceptions
	//============================================================

	class fatalerror_e : public pexception
	{
	public:
		fatalerror_e(const pstring &text) : pexception(text) { }
		virtual ~fatalerror_e() throw() {}
	};

	class logic_output_t;
=======
		class NETLIB_NAME(base_d_to_a_proxy);
		class NETLIB_NAME(base_a_to_d_proxy);
	}

	namespace detail {
		class object_t;
		class device_object_t;
		struct netlist_ref;
		class core_terminal_t;
		struct family_setter_t;
		class queue_t;
		class net_t;
	}

	class logic_output_t;
	class logic_input_t;
>>>>>>> upstream/master
	class analog_net_t;
	class logic_net_t;
	class net_t;
	class setup_t;
	class netlist_t;
	class core_device_t;
<<<<<<< HEAD
	class param_model_t;

	// -----------------------------------------------------------------------------
	// model_map_t
	// -----------------------------------------------------------------------------

	typedef phashmap_t<pstring, pstring> model_map_t;

	// -----------------------------------------------------------------------------
	// netlist_output_family_t
	// -----------------------------------------------------------------------------

	class logic_family_desc_t
	{
	public:
		logic_family_desc_t() : m_is_static(false) {}
		virtual ~logic_family_desc_t() {}
		virtual devices::nld_base_d_to_a_proxy *create_d_a_proxy(logic_output_t *proxied) const = 0;

		nl_double m_low_thresh_V;
		nl_double m_high_thresh_V;
		nl_double m_low_V;
		nl_double m_high_V;
		nl_double m_R_low;
		nl_double m_R_high;

		bool m_is_static;
	};

=======
	class device_t;

	//============================================================
	//  Exceptions
	//============================================================

	/*! Generic netlist exception.
	 *  The exception is used in all events which are considered fatal.
	 */
	class nl_exception : public plib::pexception
	{
	public:
		/*! Constructor.
		 *  Allows a descriptive text to be assed to the exception
		 */
		explicit nl_exception(const pstring &text //!< text to be passed
				)
		: plib::pexception(text) { }
		/*! Copy constructor. */
		nl_exception(const nl_exception &e) : plib::pexception(e) { }
		virtual ~nl_exception();
	};

	/*! Logic families descriptors are used to create proxy devices.
	 *  The logic family describes the analog capabilities of logic devices,
	 *  inputs and outputs.
	 */
	class logic_family_desc_t
	{
	public:
		logic_family_desc_t();
		virtual ~logic_family_desc_t();

		virtual plib::owned_ptr<devices::nld_base_d_to_a_proxy> create_d_a_proxy(netlist_t &anetlist, const pstring &name,
				logic_output_t *proxied) const = 0;
		virtual plib::owned_ptr<devices::nld_base_a_to_d_proxy> create_a_d_proxy(netlist_t &anetlist, const pstring &name,
				logic_input_t *proxied) const = 0;

		double fixed_V() const { return m_fixed_V; }
		double low_thresh_V(const double VN, const double VP) const { return VN + (VP - VN) * m_low_thresh_PCNT; }
		double high_thresh_V(const double VN, const double VP) const { return VN + (VP - VN) * m_high_thresh_PCNT; }
		double low_V(const double VN, const double VP) const { return VN + m_low_VO; }
		double high_V(const double VN, const double VP) const { return VP - m_high_VO; }
		double R_low() const { return m_R_low; }
		double R_high() const { return m_R_high; }

		double m_fixed_V;           //!< For variable voltage families, specify 0. For TTL this would be 5. */
		double m_low_thresh_PCNT;   //!< low input threshhold offset. If the input voltage is below this value times supply voltage, a "0" input is signalled
		double m_high_thresh_PCNT;  //!< high input threshhold offset. If the input voltage is above the value times supply voltage, a "0" input is signalled
		double m_low_VO;            //!< low output voltage offset. This voltage is output if the ouput is "0"
		double m_high_VO;           //!< high output voltage offset. The supply voltage minus this offset is output if the ouput is "1"
		double m_R_low;             //!< low output resistance. Value of series resistor used for low output
		double m_R_high;            //!< high output resistance. Value of series resistor used for high output
	};

	/*! Base class for devices, terminals, outputs and inputs which support
	 *  logic families.
	 *  This class is a storage container to store the logic family for a
	 *  netlist object. You will not directly use it. Please refer to
	 *  #NETLIB_FAMILY to learn how to define a logic family for a device.
	 *
	 * All terminals inherit the family description from the device
	 * The default is the ttl family, but any device can override the family.
	 * For individual terminals, the family can be overwritten as well.
	 *
	 */
>>>>>>> upstream/master
	class logic_family_t
	{
	public:

<<<<<<< HEAD
		logic_family_t() : m_logic_family(NULL) {}
		~logic_family_t() { }

		ATTR_HOT  logic_family_desc_t *logic_family() const { return m_logic_family; }
		ATTR_COLD void set_logic_family(logic_family_desc_t *fam) { m_logic_family = fam; }

	protected:
		logic_family_desc_t *m_logic_family;
	};

	/* Terminals inherit the family description from the netlist_device
	 * The default is the ttl family, but any device can override the family.
	 * For individual terminals, these can be overwritten as well.
	 *
	 * Only devices of type GENERIC should have a family description entry
	 */


	extern logic_family_desc_t *netlist_family_TTL;
	extern logic_family_desc_t *netlist_family_CD4XXX;


	// -----------------------------------------------------------------------------
	// netlist_object_t
	// -----------------------------------------------------------------------------

	class object_t
	{
		P_PREVENT_COPYING(object_t)
	public:
		enum type_t {
			TERMINAL = 0,
			INPUT    = 1,
			OUTPUT   = 2,
			PARAM    = 3,
			NET      = 4,
			DEVICE   = 5,
			NETLIST   = 6,
			QUEUE   = 7
		};
		enum family_t {
			// Terminal families
			LOGIC,
			ANALOG,
			// Device families
			GENERIC,    // <== devices usually fall into this category
			TWOTERM,    // Generic twoterm ...
			RESISTOR,   // Resistor
			CAPACITOR,  // Capacitor
			DIODE,      // Diode
			DUMMY,      // DUMMY device without function
			FRONTIER,   // Net frontier
			BJT_EB,     // BJT(Ebers-Moll)
			BJT_SWITCH, // BJT(Switch)
			VCVS,       // Voltage controlled voltage source
			VCCS,       // Voltage controlled current source
			LVCCS,      // Voltage controlled current source (Current limited)
			CCCS,       // Current controlled current source
			VS,         // Voltage Source
			CS,         // Current Source
			GND         // GND device
		};

		ATTR_COLD object_t(const type_t atype, const family_t afamily);

		virtual ~object_t();

		ATTR_COLD void init_object(netlist_t &nl, const pstring &aname);
		ATTR_COLD bool isInitialized() { return (m_netlist != NULL); }

		ATTR_COLD const pstring &name() const;

		PSTATE_INTERFACE_DECL()

		ATTR_HOT  type_t type() const { return m_objtype; }
		ATTR_HOT  family_t family() const { return m_family; }

		ATTR_HOT  bool isType(const type_t atype) const { return (m_objtype == atype); }
		ATTR_HOT  bool isFamily(const family_t afamily) const { return (m_family == afamily); }

		ATTR_HOT  netlist_t & netlist() { return *m_netlist; }
		ATTR_HOT  const netlist_t & netlist() const { return *m_netlist; }

		ATTR_COLD void  do_reset()
		{
			reset();
		}

	protected:

		virtual void reset() = 0;
		// must call parent save_register !
		virtual void save_register() { };

	private:
		pstring m_name;
		const type_t m_objtype;
		const family_t m_family;
		netlist_t * m_netlist;
	};

	// -----------------------------------------------------------------------------
	// netlist_owned_object_t
	// -----------------------------------------------------------------------------

	class device_object_t : public object_t
	{
		P_PREVENT_COPYING(device_object_t)
	public:
		ATTR_COLD device_object_t(const type_t atype, const family_t afamily);

		ATTR_COLD void init_object(core_device_t &dev, const pstring &aname);

		ATTR_HOT core_device_t &device() const { return *m_device; }
	private:
		core_device_t * m_device;
	};


	// -----------------------------------------------------------------------------
	// netlist_core_terminal_t
	// -----------------------------------------------------------------------------

	class core_terminal_t : public device_object_t, public plinkedlist_element_t<core_terminal_t>
	{
		P_PREVENT_COPYING(core_terminal_t)
	public:

		typedef plist_t<core_terminal_t *> list_t;

		/* needed here ... */

		enum state_e {
			STATE_INP_PASSIVE = 0,
			STATE_INP_ACTIVE = 1,
			STATE_INP_HL = 2,
			STATE_INP_LH = 4,
			STATE_OUT = 128,
			STATE_NONEX = 256
		};


		ATTR_COLD core_terminal_t(const type_t atype, const family_t afamily);

		//ATTR_COLD void init_object(netlist_core_device_t &dev, const pstring &aname);

		ATTR_COLD void set_net(net_t &anet);
		ATTR_COLD  void clear_net() { m_net = NULL; }
		ATTR_HOT  bool has_net() const { return (m_net != NULL); }

		ATTR_HOT  const net_t & net() const { return *m_net;}
		ATTR_HOT  net_t & net() { return *m_net;}

		ATTR_HOT  bool is_state(const state_e astate) const { return (m_state == astate); }
		ATTR_HOT  state_e state() const { return m_state; }
		ATTR_HOT  void set_state(const state_e astate)
		{
			nl_assert(astate != STATE_NONEX);
			m_state = astate;
		}


		ATTR_HOT /* inline */ void update_dev(const UINT32 mask);

	protected:
		virtual void save_register()
		{
			save(NLNAME(m_state));
			device_object_t::save_register();
		}

	private:
		net_t *  m_net;
		state_e m_state;
	};

	class terminal_t : public core_terminal_t
	{
		P_PREVENT_COPYING(terminal_t)
	public:

		typedef plist_t<terminal_t *> list_t;

		ATTR_COLD terminal_t();

		nl_double *m_Idr1; // drive current
		nl_double *m_go1;  // conductance for Voltage from other term
		nl_double *m_gt1;  // conductance for total conductance

		ATTR_HOT  void set(const nl_double G)
		{
			set_ptr(m_Idr1, 0);
			set_ptr(m_go1, G);
			set_ptr(m_gt1, G);
		}

		ATTR_HOT  void set(const nl_double GO, const nl_double GT)
		{
			set_ptr(m_Idr1, 0);
			set_ptr(m_go1, GO);
			set_ptr(m_gt1, GT);
		}

		ATTR_HOT  void set(const nl_double GO, const nl_double GT, const nl_double I)
=======
		logic_family_t() : m_logic_family(nullptr) {}

		const logic_family_desc_t *logic_family() const { return m_logic_family; }
		void set_logic_family(const logic_family_desc_t *fam) { m_logic_family = fam; }

	protected:
		~logic_family_t() { } // prohibit polymorphic destruction
		const logic_family_desc_t *m_logic_family;
	};

	const logic_family_desc_t *family_TTL();        //*!< logic family for TTL devices.
	const logic_family_desc_t *family_CD4XXX();     //*!< logic family for CD4XXX CMOS devices.

	/*! A persistent variable template.
	 *  Use the state_var template to define a variable whose value is saved.
	 *  Within a device definition use
	 *
	 *      NETLIB_OBJECT(abc)
	 *      {
	 *          NETLIB_CONSTRUCTOR(abc)
	 *          , m_var(*this, "myvar", 0)
	 *          ...
	 *          state_var<unsigned> m_var;
	 *      }
	 */

	template <typename T>
	struct state_var
	{
	public:
		template <typename O>
		//! Constructor.
		state_var(O &owner,             //!< owner must have a netlist() method.
				const pstring &name,     //!< identifier/name for this state variable
				const T &value          //!< Initial value after construction
				);
		//! Copy Constructor.
		constexpr state_var(const state_var &rhs) noexcept = default;
		//! Move Constructor.
		constexpr state_var(state_var &&rhs) noexcept = default;
		//! Assignment operator to assign value of a state var.
		C14CONSTEXPR state_var &operator=(const state_var &rhs) noexcept = default;
		//! Assignment move operator to assign value of a state var.
		C14CONSTEXPR state_var &operator=(state_var &&rhs) noexcept = default;
		//! Assignment operator to assign value of type T.
		C14CONSTEXPR state_var &operator=(const T &rhs) noexcept { m_value = rhs; return *this; }
		//! Assignment move operator to assign value of type T.
		C14CONSTEXPR state_var &operator=(T &&rhs) noexcept { std::swap(m_value, rhs); return *this; }
		//! Return value of state variable.
		C14CONSTEXPR operator T & () noexcept { return m_value; }
		//! Return const value of state variable.
		constexpr operator const T & () const noexcept { return m_value; }
		C14CONSTEXPR T * ptr() noexcept { return &m_value; }
		constexpr const T * ptr() const noexcept{ return &m_value; }

	private:
		T m_value;
	};

	/*! A persistent array template.
	 *  Use this state_var template to define an array whose contents are saved.
	 *  Please refer to \ref state_var.
	 */
	template <typename T, std::size_t N>
	struct state_var<T[N]>
	{
	public:
		//! Constructor.
		template <typename O>
		state_var(O &owner,             //!< owner must have a netlist() method.
				const pstring &name,     //!< identifier/name for this state variable
				const T &value          //!< Initial value after construction
				);
		//! Copy Constructor.
		state_var(const state_var &rhs) NL_NOEXCEPT = default;
		//! Move Constructor.
		state_var(state_var &&rhs) NL_NOEXCEPT = default;
		state_var &operator=(const state_var &rhs) NL_NOEXCEPT = default;
		state_var &operator=(const T &rhs) NL_NOEXCEPT { m_value = rhs; return *this; }
		T & operator[](const std::size_t i) NL_NOEXCEPT { return m_value[i]; }
		constexpr T & operator[](const std::size_t i) const NL_NOEXCEPT { return m_value[i]; }
	private:
		T m_value[N];
	};

	// -----------------------------------------------------------------------------
	// State variables - predefined and c++11 non-optional
	// -----------------------------------------------------------------------------

	/*! predefined state variable type for uint8_t */
	using state_var_u8 = state_var<std::uint8_t>;
	/*! predefined state variable type for int8_t */
	using state_var_s8 = state_var<std::int8_t>;

	/*! predefined state variable type for uint32_t */
	using state_var_u32 = state_var<std::uint32_t>;
	/*! predefined state variable type for int32_t */
	using state_var_s32 = state_var<std::int32_t>;
	/*! predefined state variable type for sig_t */
	using state_var_sig = state_var<netlist_sig_t>;

	// -----------------------------------------------------------------------------
	// object_t
	// -----------------------------------------------------------------------------

	/*! The base class for netlist devices, terminals and parameters.
	 *
	 *  This class serves as the base class for all device, terminal and
	 *  objects. It provides new and delete operators to support e.g. pooled
	 *  memory allocation to enhance locality. Please refer to \ref USE_MEMPOOL as
	 *  well.
	 */
	class detail::object_t
	{
	public:

		/*! Constructor.
		 *
		 *  Every class derived from the object_t class must have a name.
		 */
		explicit object_t(const pstring &aname /*!< string containing name of the object */);

		/*! return name of the object
		 *
		 *  \returns name of the object.
		 */
		const pstring &name() const;

		void * operator new (size_t size, void *ptr) { return ptr; }
		void operator delete (void *ptr, void *) {  }
		void * operator new (size_t size);
		void operator delete (void * mem);
	protected:
		~object_t(); // only childs should be destructible

	private:
		std::unique_ptr<pstring> m_name;
	};

	struct detail::netlist_ref
	{
		explicit constexpr netlist_ref(netlist_t &nl) : m_netlist(nl) { }

		C14CONSTEXPR netlist_t & netlist() NL_NOEXCEPT { return m_netlist; }
		constexpr const netlist_t & netlist() const NL_NOEXCEPT { return m_netlist; }

	protected:
		~netlist_ref() = default; // prohibit polymorphic destruction

	private:
		netlist_t & m_netlist;

	};

	// -----------------------------------------------------------------------------
	// device_object_t
	// -----------------------------------------------------------------------------

	/*! Base class for all objects being owned by a device.
	 *
	 * Serves as the base class of all objects being owned by a device.
	 *
	 */
	class detail::device_object_t : public detail::object_t
	{
	public:
		/*! Constructor.
		 *
		 * \param dev  device owning the object.
		 * \param name string holding the name of the device
		 */
		device_object_t(core_device_t &dev, const pstring &name);

		/*! returns reference to owning device.
		 * \returns reference to owning device.
		 */
		core_device_t &device() NL_NOEXCEPT { return m_device; }
		const core_device_t &device() const NL_NOEXCEPT { return m_device; }

		/*! The netlist owning the owner of this object.
		 * \returns reference to netlist object.
		 */
		netlist_t &netlist() NL_NOEXCEPT;
		const netlist_t &netlist() const NL_NOEXCEPT;

	private:
		core_device_t & m_device;
};

	/*! Delegate type for device notification.
	 *
	 */
	typedef plib::pmfp<void> nldelegate;

	// -----------------------------------------------------------------------------
	// core_terminal_t
	// -----------------------------------------------------------------------------

	/*! Base class for all terminals.
	 *
	 * All terminals are derived from this class.
	 *
	 */
	class detail::core_terminal_t : public device_object_t,
									public plib::linkedlist_t<core_terminal_t>::element_t
	{
	public:

		using list_t = std::vector<core_terminal_t *>;

		static constexpr const unsigned INP_HL_SHIFT = 0;
		static constexpr const unsigned INP_LH_SHIFT = 1;
		static constexpr const unsigned INP_ACTIVE_SHIFT = 2;

		enum state_e {
			STATE_INP_PASSIVE = 0,
			STATE_INP_HL      = (1 << INP_HL_SHIFT),
			STATE_INP_LH      = (1 << INP_LH_SHIFT),
			STATE_INP_ACTIVE  = (1 << INP_ACTIVE_SHIFT),
			STATE_OUT = 128,
			STATE_BIDIR = 256
		};

		core_terminal_t(core_device_t &dev, const pstring &aname,
				const state_e state, nldelegate delegate = nldelegate());
		virtual ~core_terminal_t();

		/*! The object type.
		 * \returns type of the object
		 */
		terminal_type type() const;
		/*! Checks if object is of specified type.
		 * \param atype type to check object against.
		 * \returns true if object is of specified type else false.
		 */
		bool is_type(const terminal_type atype) const { return (type() == atype); }

		void set_net(net_t *anet);
		void clear_net();
		bool has_net() const NL_NOEXCEPT { return (m_net != nullptr); }

		const net_t & net() const NL_NOEXCEPT { return *m_net;}
		net_t & net() NL_NOEXCEPT { return *m_net;}

		bool is_logic() const NL_NOEXCEPT;
		bool is_analog() const NL_NOEXCEPT;

		bool is_state(const state_e &astate) const NL_NOEXCEPT { return (m_state == astate); }
		const state_e &state() const NL_NOEXCEPT { return m_state; }
		void set_state(const state_e &astate) NL_NOEXCEPT { m_state = astate; }

		void reset();

		nldelegate m_delegate;

	private:
		net_t * m_net;
		state_var<state_e> m_state;
	};

	// -----------------------------------------------------------------------------
	// analog_t
	// -----------------------------------------------------------------------------

	class analog_t : public detail::core_terminal_t
	{
	public:

		analog_t(core_device_t &dev, const pstring &aname, const state_e state);
		virtual ~analog_t();

		const analog_net_t & net() const NL_NOEXCEPT;
		analog_net_t & net() NL_NOEXCEPT;
	};

	// -----------------------------------------------------------------------------
	// terminal_t
	// -----------------------------------------------------------------------------

	class terminal_t : public analog_t
	{
	public:

		terminal_t(core_device_t &dev, const pstring &aname);
		virtual ~terminal_t();

		nl_double operator ()() const  NL_NOEXCEPT;

		void set(const nl_double &G) NL_NOEXCEPT
		{
			set(G,G, 0.0);
		}

		void set(const nl_double &GO, const nl_double &GT) NL_NOEXCEPT
		{
			set(GO, GT, 0.0);
		}

		void set(const nl_double &GO, const nl_double &GT, const nl_double &I) NL_NOEXCEPT
>>>>>>> upstream/master
		{
			set_ptr(m_Idr1, I);
			set_ptr(m_go1, GO);
			set_ptr(m_gt1, GT);
		}

<<<<<<< HEAD
		ATTR_HOT void schedule_solve();
		ATTR_HOT void schedule_after(const netlist_time &after);

		terminal_t *m_otherterm;

	protected:
		virtual void save_register();

		virtual void reset();
	private:
		ATTR_HOT  void set_ptr(nl_double *ptr, const nl_double val)
		{
			if (ptr != NULL && *ptr != val)
=======
		void solve_now();
		void schedule_solve_after(const netlist_time &after);

		void set_ptrs(nl_double *gt, nl_double *go, nl_double *Idr) NL_NOEXCEPT
		{
			m_gt1 = gt;
			m_go1 = go;
			m_Idr1 = Idr;
		}

		terminal_t *m_otherterm;

	private:
		void set_ptr(nl_double *ptr, const nl_double &val) NL_NOEXCEPT
		{
			if (ptr != nullptr && *ptr != val)
>>>>>>> upstream/master
			{
				*ptr = val;
			}
		}
<<<<<<< HEAD
=======

		nl_double *m_Idr1; // drive current
		nl_double *m_go1;  // conductance for Voltage from other term
		nl_double *m_gt1;  // conductance for total conductance

>>>>>>> upstream/master
	};


	// -----------------------------------------------------------------------------
<<<<<<< HEAD
	// netlist_input_t
	// -----------------------------------------------------------------------------

	class logic_t : public core_terminal_t, public logic_family_t
	{
	public:


		ATTR_COLD logic_t(const type_t atype)
			: core_terminal_t(atype, LOGIC), logic_family_t(),
				m_proxy(NULL)
		{
		}

		ATTR_COLD bool has_proxy() const { return (m_proxy != NULL); }
		ATTR_COLD devices::nld_base_proxy *get_proxy() const  { return m_proxy; }
		ATTR_COLD void set_proxy(devices::nld_base_proxy *proxy) { m_proxy = proxy; }
=======
	// logic_t
	// -----------------------------------------------------------------------------

	class logic_t : public detail::core_terminal_t, public logic_family_t
	{
	public:
		logic_t(core_device_t &dev, const pstring &aname,
				const state_e state, nldelegate delegate = nldelegate());
		virtual ~logic_t();

		bool has_proxy() const { return (m_proxy != nullptr); }
		devices::nld_base_proxy *get_proxy() const  { return m_proxy; }
		void set_proxy(devices::nld_base_proxy *proxy) { m_proxy = proxy; }

		logic_net_t & net() NL_NOEXCEPT;
		const logic_net_t &  net() const NL_NOEXCEPT;
>>>>>>> upstream/master

	protected:

	private:
		devices::nld_base_proxy *m_proxy;
	};

<<<<<<< HEAD
	class netlist_analog_t : public core_terminal_t
	{
	public:


		ATTR_COLD netlist_analog_t(const type_t atype)
			: core_terminal_t(atype, ANALOG)
		{
		}

	protected:

	private:
	};

	// -----------------------------------------------------------------------------
	// netlist_logic_input_t
=======
	// -----------------------------------------------------------------------------
	// logic_input_t
>>>>>>> upstream/master
	// -----------------------------------------------------------------------------

	class logic_input_t : public logic_t
	{
	public:
<<<<<<< HEAD
		ATTR_COLD logic_input_t()
			: logic_t(INPUT)
		{
			set_state(STATE_INP_ACTIVE);
		}

		ATTR_HOT  netlist_sig_t Q() const;
		ATTR_HOT  netlist_sig_t last_Q() const;

		ATTR_HOT  void inactivate();
		ATTR_HOT  void activate();
		ATTR_HOT  void activate_hl();
		ATTR_HOT  void activate_lh();

	protected:
		virtual void reset()
		{
			//netlist_core_terminal_t::reset();
			set_state(STATE_INP_ACTIVE);
		}

	};

	// -----------------------------------------------------------------------------
	// netlist_analog_input_t
	// -----------------------------------------------------------------------------

	class analog_input_t : public netlist_analog_t
	{
	public:
		ATTR_COLD analog_input_t()
			: netlist_analog_t(INPUT)
		{
			set_state(STATE_INP_ACTIVE);
		}

		ATTR_HOT  nl_double Q_Analog() const;

	protected:
		virtual void reset()
		{
			//netlist_core_terminal_t::reset();
			set_state(STATE_INP_ACTIVE);
		}
	};

	// -----------------------------------------------------------------------------
	// net_net_t
	// -----------------------------------------------------------------------------

	class net_t : public object_t
	{
		P_PREVENT_COPYING(net_t)
	public:

		typedef plist_t<net_t *> list_t;

		ATTR_COLD net_t(const family_t afamily);
		virtual ~net_t();

		ATTR_COLD void init_object(netlist_t &nl, const pstring &aname);

		ATTR_COLD void register_con(core_terminal_t &terminal);
		ATTR_COLD void merge_net(net_t *othernet);
		ATTR_COLD void register_railterminal(core_terminal_t &mr);

		ATTR_HOT  logic_net_t & as_logic();
		ATTR_HOT  const logic_net_t &  as_logic() const;

		ATTR_HOT  analog_net_t & as_analog();
		ATTR_HOT  const analog_net_t & as_analog() const;

		ATTR_HOT void update_devs();

		ATTR_HOT  const netlist_time &time() const { return m_time; }
		ATTR_HOT  void set_time(const netlist_time &ntime) { m_time = ntime; }

		ATTR_HOT  bool isRailNet() const { return !(m_railterminal == NULL); }
		ATTR_HOT  core_terminal_t & railterminal() const { return *m_railterminal; }

		ATTR_HOT  void push_to_queue(const netlist_time &delay);
		ATTR_HOT  void reschedule_in_queue(const netlist_time &delay);
		ATTR_HOT bool  is_queued() const { return m_in_queue == 1; }

		ATTR_HOT  int num_cons() const { return m_core_terms.size(); }

		ATTR_HOT void inc_active(core_terminal_t &term);
		ATTR_HOT void dec_active(core_terminal_t &term);

		ATTR_COLD void rebuild_list();     /* rebuild m_list after a load */

		ATTR_COLD void move_connections(net_t *new_net);

		plist_t<core_terminal_t *> m_core_terms; // save post-start m_list ...

		ATTR_HOT  void set_Q_time(const netlist_sig_t &newQ, const netlist_time &at)
		{
			if (newQ != m_new_Q)
			{
				m_in_queue = 0;
				m_time = at;
			}
			m_cur_Q = m_new_Q = newQ;
		}

	protected:  //FIXME: needed by current solver code

		virtual void save_register();
		virtual void reset();

		netlist_sig_t m_new_Q;
		netlist_sig_t m_cur_Q;

	private:

		core_terminal_t * m_railterminal;
		plinkedlist_t<core_terminal_t> m_list_active;

		netlist_time m_time;
		INT32        m_active;
		UINT8        m_in_queue;    /* 0: not in queue, 1: in queue, 2: last was taken */

	public:
		// We have to have those on one object. Dividing those does lead
		// to a significant performance hit
		// FIXME: Have to fix the public at some time
		nl_double m_cur_Analog;

	};

	class logic_net_t : public net_t
	{
		P_PREVENT_COPYING(logic_net_t)
	public:

		typedef plist_t<logic_net_t *> list_t;

		ATTR_COLD logic_net_t();
		virtual ~logic_net_t() { };

		ATTR_HOT  netlist_sig_t Q() const
		{
			return m_cur_Q;
		}

		ATTR_HOT  netlist_sig_t new_Q() const
		{
			return m_new_Q;
		}

		ATTR_HOT  void set_Q(const netlist_sig_t &newQ, const netlist_time &delay)
		{
			if (newQ !=  m_new_Q)
=======
		logic_input_t(core_device_t &dev, const pstring &aname,
				nldelegate delegate = nldelegate());
		virtual ~logic_input_t();

		netlist_sig_t operator()() const NL_NOEXCEPT
		{
			return Q();
		}

		void inactivate() NL_NOEXCEPT;
		void activate() NL_NOEXCEPT;
		void activate_hl() NL_NOEXCEPT;
		void activate_lh() NL_NOEXCEPT;
	private:
		netlist_sig_t Q() const NL_NOEXCEPT;
	};

	// -----------------------------------------------------------------------------
	// analog_input_t
	// -----------------------------------------------------------------------------

	/*! terminal providing analog input voltage.
	 *
	 * This terminal class provides a voltage measurement. The conductance against
	 * ground is infinite.
	 */
	class analog_input_t : public analog_t
	{
	public:
		/*! Constructor */
		analog_input_t(core_device_t &dev, /*!< owning device */
				const pstring &aname       /*!< name of terminal */
		);

		/*! Destructor */
		virtual ~analog_input_t();

		/*! returns voltage at terminal.
		 *  \returns voltage at terminal.
		 */
		nl_double operator()() const NL_NOEXCEPT { return Q_Analog(); }

		/*! returns voltage at terminal.
		 *  \returns voltage at terminal.
		 */
		nl_double Q_Analog() const NL_NOEXCEPT;

	};

	// -----------------------------------------------------------------------------
	// net_t
	// -----------------------------------------------------------------------------

	class detail::net_t :
			public detail::object_t,
			public detail::netlist_ref
	{
	public:

		enum queue_status
		{
			QS_DELAYED_DUE_TO_INACTIVE = 0,
			QS_QUEUED,
			QS_DELIVERED
		};

		net_t(netlist_t &nl, const pstring &aname, core_terminal_t *mr = nullptr);
		virtual ~net_t();

		void reset();

		void toggle_new_Q() NL_NOEXCEPT { m_new_Q = (m_cur_Q ^ 1);   }

		void toggle_and_push_to_queue(const netlist_time &delay) NL_NOEXCEPT
		{
			toggle_new_Q();
			push_to_queue(delay);
		}

		void push_to_queue(const netlist_time &delay) NL_NOEXCEPT;
		bool is_queued() const NL_NOEXCEPT { return m_in_queue == QS_QUEUED; }

		void update_devs() NL_NOEXCEPT;

		const netlist_time &time() const NL_NOEXCEPT { return m_time; }
		void set_time(const netlist_time &ntime) NL_NOEXCEPT { m_time = ntime; }

		bool isRailNet() const NL_NOEXCEPT { return !(m_railterminal == nullptr); }
		core_terminal_t & railterminal() const NL_NOEXCEPT { return *m_railterminal; }

		std::size_t num_cons() const NL_NOEXCEPT { return m_core_terms.size(); }

		void inc_active(core_terminal_t &term) NL_NOEXCEPT;
		void dec_active(core_terminal_t &term) NL_NOEXCEPT;

		/* setup stuff */

		void add_terminal(core_terminal_t &terminal);
		void remove_terminal(core_terminal_t &terminal);

		bool is_logic() const NL_NOEXCEPT;
		bool is_analog() const NL_NOEXCEPT;

		void rebuild_list();     /* rebuild m_list after a load */
		void move_connections(net_t &dest_net);

		std::vector<core_terminal_t *> m_core_terms; // save post-start m_list ...

	protected:
		state_var<netlist_sig_t> m_new_Q;
		state_var<netlist_sig_t> m_cur_Q;
		state_var<queue_status>  m_in_queue;    /* 0: not in queue, 1: in queue, 2: last was taken */
		state_var_s32            m_active;

		state_var<netlist_time>  m_time;

	private:
		plib::linkedlist_t<core_terminal_t> m_list_active;
		core_terminal_t * m_railterminal;

		void process(unsigned Mask);
	};

	class logic_net_t : public detail::net_t
	{
	public:

		logic_net_t(netlist_t &nl, const pstring &aname, detail::core_terminal_t *mr = nullptr);
		virtual ~logic_net_t();

		netlist_sig_t Q() const NL_NOEXCEPT { return m_cur_Q; }
		void initial(const netlist_sig_t val) NL_NOEXCEPT { m_cur_Q = m_new_Q = val; }

		void set_Q_and_push(const netlist_sig_t newQ, const netlist_time &delay) NL_NOEXCEPT
		{
			if (newQ != m_new_Q )
>>>>>>> upstream/master
			{
				m_new_Q = newQ;
				push_to_queue(delay);
			}
		}
<<<<<<< HEAD

		ATTR_HOT  void toggle_new_Q()
		{
			m_new_Q ^= 1;
		}

		ATTR_COLD void initial(const netlist_sig_t val)
		{
			m_cur_Q = val;
			m_new_Q = val;
=======
		void set_Q_and_push_force(const netlist_sig_t newQ, const netlist_time &delay) NL_NOEXCEPT
		{
			if (newQ != m_new_Q || is_queued())
			{
				m_new_Q = newQ;
				push_to_queue(delay);
			}
		}

		void set_Q_time(const netlist_sig_t newQ, const netlist_time &at) NL_NOEXCEPT
		{
			if (newQ != m_new_Q)
			{
				m_in_queue = QS_DELAYED_DUE_TO_INACTIVE;
				m_time = at;
			}
			m_cur_Q = m_new_Q = newQ;
>>>>>>> upstream/master
		}

		/* internal state support
		 * FIXME: get rid of this and implement export/import in MAME
		 */
<<<<<<< HEAD
		ATTR_COLD  netlist_sig_t &Q_state_ptr()
		{
			return m_cur_Q;
		}

	protected:  //FIXME: needed by current solver code

		virtual void save_register();
		virtual void reset();


	private:

	public:

	};

	class analog_net_t : public net_t
	{
		P_PREVENT_COPYING(analog_net_t)
	public:

		typedef plist_t<analog_net_t *> list_t;

		ATTR_COLD analog_net_t();
		virtual ~analog_net_t() { };

		ATTR_HOT  nl_double Q_Analog() const
		{
			return m_cur_Analog;
		}

		ATTR_COLD  nl_double &Q_Analog_state_ptr()
		{
			return m_cur_Analog;
		}

		ATTR_HOT devices::matrix_solver_t *solver() { return m_solver; }

		ATTR_COLD bool already_processed(list_t *groups, int cur_group);
		ATTR_COLD void process_net(list_t *groups, int &cur_group);

	protected:

		virtual void save_register();
		virtual void reset();


	private:

	public:
		nl_double m_DD_n_m_1;
		nl_double m_h_n_m_1;

		//FIXME: needed by current solver code
=======
		netlist_sig_t *Q_state_ptr() { return m_cur_Q.ptr(); }

	protected:
	private:

	};

	class analog_net_t : public detail::net_t
	{
	public:

		using list_t =  std::vector<analog_net_t *>;

		friend class detail::net_t;

		analog_net_t(netlist_t &nl, const pstring &aname, detail::core_terminal_t *mr = nullptr);

		virtual ~analog_net_t();

		nl_double Q_Analog() const NL_NOEXCEPT { return m_cur_Analog; }
		void set_Q_Analog(const nl_double v) NL_NOEXCEPT { m_cur_Analog = v; }
		nl_double *Q_Analog_state_ptr() NL_NOEXCEPT { return m_cur_Analog.ptr(); }

		//FIXME: needed by current solver code
		devices::matrix_solver_t *solver() const NL_NOEXCEPT { return m_solver; }
		void set_solver(devices::matrix_solver_t *solver) NL_NOEXCEPT { m_solver = solver; }

	private:
		state_var<nl_double>     m_cur_Analog;
>>>>>>> upstream/master
		devices::matrix_solver_t *m_solver;
	};

	// -----------------------------------------------------------------------------
<<<<<<< HEAD
	// net_output_t
=======
	// logic_output_t
>>>>>>> upstream/master
	// -----------------------------------------------------------------------------

	class logic_output_t : public logic_t
	{
<<<<<<< HEAD
		P_PREVENT_COPYING(logic_output_t)
	public:

		ATTR_COLD logic_output_t();

		ATTR_COLD void init_object(core_device_t &dev, const pstring &aname);
		virtual void reset()
		{
			set_state(STATE_OUT);
		}

		ATTR_COLD void initial(const netlist_sig_t val);

		ATTR_HOT  void set_Q(const netlist_sig_t newQ, const netlist_time &delay)
		{
			net().as_logic().set_Q(newQ, delay);
=======
	public:

		logic_output_t(core_device_t &dev, const pstring &aname);
		virtual ~logic_output_t();

		void initial(const netlist_sig_t val);

		void push(const netlist_sig_t newQ, const netlist_time &delay) NL_NOEXCEPT
		{
			m_my_net.set_Q_and_push(newQ, delay); // take the shortcut
		}

		void push_force(const netlist_sig_t newQ, const netlist_time &delay) NL_NOEXCEPT
		{
			m_my_net.set_Q_and_push_force(newQ, delay); // take the shortcut
		}

		void set_Q_time(const netlist_sig_t newQ, const netlist_time &at) NL_NOEXCEPT
		{
			m_my_net.set_Q_time(newQ, at); // take the shortcut
>>>>>>> upstream/master
		}

	private:
		logic_net_t m_my_net;
	};

<<<<<<< HEAD
	class analog_output_t : public netlist_analog_t
	{
		P_PREVENT_COPYING(analog_output_t)
	public:

		ATTR_COLD analog_output_t();

		ATTR_COLD void init_object(core_device_t &dev, const pstring &aname);
		virtual void reset()
		{
			set_state(STATE_OUT);
		}

		ATTR_COLD void initial(const nl_double val);

		ATTR_HOT  void set_Q(const nl_double newQ);

		analog_net_t *m_proxied_net; // only for proxy nets in analog input logic

	private:
=======
	class analog_output_t : public analog_t
	{
	public:
		analog_output_t(core_device_t &dev, const pstring &aname);
		virtual ~analog_output_t();

		void push(const nl_double val) NL_NOEXCEPT { set_Q(val); }
		void initial(const nl_double val);

	private:
		void set_Q(const nl_double newQ) NL_NOEXCEPT;
>>>>>>> upstream/master
		analog_net_t m_my_net;
	};

	// -----------------------------------------------------------------------------
<<<<<<< HEAD
	// net_param_t
	// -----------------------------------------------------------------------------

	class param_t : public device_object_t
	{
		P_PREVENT_COPYING(param_t)
	public:

		enum param_type_t {
			MODEL,
			STRING,
			DOUBLE,
			INTEGER,
			LOGIC
		};

		ATTR_COLD param_t(const param_type_t atype);

		ATTR_HOT  param_type_t param_type() const { return m_param_type; }

	protected:

		virtual void reset() { }

	private:
		const param_type_t m_param_type;
	};

	template <class C, param_t::param_type_t T>
	class param_template_t : public param_t
	{
		P_PREVENT_COPYING(param_template_t)
	public:
		ATTR_COLD param_template_t()
		: param_t(T)
		, m_param(C(0))
		{
		}

		operator const C() const { return Value(); }

		ATTR_HOT  void setTo(const C &param);
		ATTR_COLD  void initial(const C &val) { m_param = val; }
		ATTR_HOT  C Value() const { return m_param;   }

	protected:
		virtual void save_register()
		{
			/* pstrings not yet supported, these need special logic */
			if (T != param_t::STRING && T != param_t::MODEL)
				save(NLNAME(m_param));
			param_t::save_register();
		}

		virtual void changed() { }
		C m_param;
	private:
	};

	typedef param_template_t<nl_double, param_t::DOUBLE> param_double_t;
	typedef param_template_t<int, param_t::INTEGER> param_int_t;
	typedef param_template_t<pstring, param_t::STRING> param_str_t;

	class param_logic_t : public param_int_t
	{
		P_PREVENT_COPYING(param_logic_t)
	public:
		ATTR_COLD param_logic_t() : param_int_t() { };
	};

	class param_model_t : public param_template_t<pstring, param_t::MODEL>
	{
		P_PREVENT_COPYING(param_model_t)
	public:
		ATTR_COLD param_model_t() : param_template_t<pstring, param_t::MODEL>() { }

		/* these should be cached! */
		ATTR_COLD nl_double model_value(const pstring &entity);
		ATTR_COLD const pstring model_value_str(const pstring &entity);
		ATTR_COLD const pstring model_type();
	protected:
		void changed()
		{
			m_map.clear();
		}
	private:
		model_map_t m_map;
=======
	// param_t
	// -----------------------------------------------------------------------------

	class param_t : public detail::device_object_t
	{
	public:

		enum param_type_t {
			STRING,
			DOUBLE,
			INTEGER,
			LOGIC,
			POINTER // Special-case which is always initialized at MAME startup time
		};

		param_t(device_t &device, const pstring &name);

		param_type_t param_type() const;

	protected:
		virtual ~param_t(); /* not intended to be destroyed */

		void update_param();

		template<typename C>
		void set(C &p, const C v)
		{
			if (p != v)
			{
				p = v;
				update_param();
			}
		}

	};

	class param_ptr_t final: public param_t
	{
	public:
		param_ptr_t(device_t &device, const pstring &name, std::uint8_t* val);
		std::uint8_t * operator()() const NL_NOEXCEPT { return m_param; }
		void setTo(std::uint8_t *param) { set(m_param, param); }
	private:
		std::uint8_t* m_param;
	};

	class param_logic_t final: public param_t
	{
	public:
		param_logic_t(device_t &device, const pstring &name, const bool val);
		const bool &operator()() const NL_NOEXCEPT { return m_param; }
		void setTo(const bool &param) { set(m_param, param); }
	private:
		bool m_param;
	};

	class param_int_t final: public param_t
	{
	public:
		param_int_t(device_t &device, const pstring &name, const int val);
		const int &operator()() const NL_NOEXCEPT { return m_param; }
		void setTo(const int &param) { set(m_param, param); }
	private:
		int m_param;
	};

	class param_double_t final: public param_t
	{
	public:
		param_double_t(device_t &device, const pstring &name, const double val);
		const double &operator()() const NL_NOEXCEPT { return m_param; }
		void setTo(const double &param) { set(m_param, param); }
	private:
		double m_param;
	};

	class param_str_t : public param_t
	{
	public:
		param_str_t(device_t &device, const pstring &name, const pstring &val);
		virtual ~param_str_t();

		const pstring &operator()() const NL_NOEXCEPT { return Value(); }
		void setTo(const pstring &param) NL_NOEXCEPT
		{
			if (m_param != param)
			{
				m_param = param;
				changed();
				update_param();
			}
		}
	protected:
		virtual void changed();
		const pstring &Value() const NL_NOEXCEPT { return m_param; }
	private:
		pstring m_param;
	};

	class param_model_t : public param_str_t
	{
	public:

		class value_t
		{
		public:
			value_t(param_model_t &param, const pstring &name)
			: m_value(param.model_value(name))
			{
			}
			const double &operator()() const NL_NOEXCEPT { return m_value; }
			operator const double&() const NL_NOEXCEPT { return m_value; }
		private:
			const double m_value;
		};

		friend class value_t;

		param_model_t(device_t &device, const pstring &name, const pstring &val)
		: param_str_t(device, name, val) { }

		const pstring model_value_str(const pstring &entity) /*const*/;
		const pstring model_type() /*const*/;
	protected:
		virtual void changed() override;
		nl_double model_value(const pstring &entity) /*const*/;
	private:
		/* hide this */
		void setTo(const pstring &param) = delete;
		detail::model_map_t m_map;
};


	class param_data_t : public param_str_t
	{
	public:
		param_data_t(device_t &device, const pstring &name);

		std::unique_ptr<plib::pistream> stream();
	protected:
		virtual void changed() override;
	};

	// -----------------------------------------------------------------------------
	// rom parameter
	// -----------------------------------------------------------------------------

	template <typename ST, std::size_t AW, std::size_t DW>
	class param_rom_t final: public param_data_t
	{
	public:

		param_rom_t(device_t &device, const pstring &name);

		const ST & operator[] (std::size_t n) NL_NOEXCEPT { return m_data[n]; }
	protected:
		virtual void changed() override
		{
			stream()->read(&m_data[0],1<<AW);
		}

	private:
		ST m_data[1 << AW];
>>>>>>> upstream/master
	};

	// -----------------------------------------------------------------------------
	// core_device_t
	// -----------------------------------------------------------------------------

<<<<<<< HEAD
	class core_device_t : public object_t, public logic_family_t
	{
		P_PREVENT_COPYING(core_device_t)
	public:

		typedef plist_t<core_device_t *> list_t;

		ATTR_COLD core_device_t(const family_t afamily);

		virtual ~core_device_t();

		virtual void init(netlist_t &anetlist, const pstring &name);
		ATTR_HOT virtual void update_param() {}

		ATTR_HOT  void update_dev()
		{
			begin_timing(stat_total_time);
			inc_stat(stat_update_count);

	#if (NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF)
			(this->*m_static_update)();
	#elif ((NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF_CONV) || (NL_PMF_TYPE == NL_PMF_TYPE_INTERNAL))
			m_static_update(this);
	#else
			update();
	#endif
			end_timing(stat_total_time);
		}
		ATTR_COLD void start_dev();
		ATTR_COLD void stop_dev();

		ATTR_HOT netlist_sig_t INPLOGIC_PASSIVE(logic_input_t &inp);

		ATTR_HOT  netlist_sig_t INPLOGIC(const logic_input_t &inp) const
		{
			nl_assert(inp.state() != logic_t::STATE_INP_PASSIVE);
			return inp.Q();
		}

		ATTR_HOT  void OUTLOGIC(logic_output_t &out, const netlist_sig_t val, const netlist_time &delay)
		{
			out.set_Q(val, delay);
		}

		ATTR_HOT  nl_double INPANALOG(const analog_input_t &inp) const { return inp.Q_Analog(); }

		ATTR_HOT  nl_double TERMANALOG(const terminal_t &term) const { return term.net().as_analog().Q_Analog(); }

		ATTR_HOT  void OUTANALOG(analog_output_t &out, const nl_double val)
		{
			out.set_Q(val);
		}

		ATTR_HOT virtual void inc_active() {  }

		ATTR_HOT virtual void dec_active() {  }

		ATTR_HOT virtual void step_time(ATTR_UNUSED const nl_double st) { }
		ATTR_HOT virtual void update_terminals() { }

	#if (NL_KEEP_STATISTICS)
		/* stats */
		osd_ticks_t stat_total_time;
		INT32 stat_update_count;
		INT32 stat_call_count;
	#endif

	protected:

		ATTR_HOT virtual void update() { }
		virtual void start() { }
		virtual void stop() { }                                                  \
		virtual logic_family_desc_t *default_logic_family()
		{
			return netlist_family_TTL;
		}

	private:

		#if (NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF)
		typedef void (core_device_t::*net_update_delegate)();
		#elif ((NL_PMF_TYPE == NL_PMF_TYPE_GNUC_PMF_CONV) || (NL_PMF_TYPE == NL_PMF_TYPE_INTERNAL))
		typedef MEMBER_ABI void (*net_update_delegate)(core_device_t *);
		#endif

	#if (NL_PMF_TYPE > NL_PMF_TYPE_VIRTUAL)
		net_update_delegate m_static_update;
	#endif
=======
	class core_device_t :
			public detail::object_t,
			public logic_family_t,
			public detail::netlist_ref
	{
	public:
		core_device_t(netlist_t &owner, const pstring &name);
		core_device_t(core_device_t &owner, const pstring &name);

		virtual ~core_device_t();

		void update_dev() NL_NOEXCEPT
		{
			do_update();
		}

		void do_inc_active() NL_NOEXCEPT
		{
			if (m_hint_deactivate)
			{
				m_stat_inc_active.inc();
				inc_active();
			}
		}

		void do_dec_active() NL_NOEXCEPT
		{
			if (m_hint_deactivate)
				dec_active();
		}

		void do_reset() { reset(); }
		void set_hint_deactivate(bool v) { m_hint_deactivate = v; }
		bool get_hint_deactivate() { return m_hint_deactivate; }

		void set_default_delegate(detail::core_terminal_t &term);

		/* stats */
		nperftime_t  m_stat_total_time;
		nperfcount_t m_stat_call_count;
		nperfcount_t m_stat_inc_active;


	protected:

		virtual void update() NL_NOEXCEPT { }
		virtual void inc_active() NL_NOEXCEPT {  }
		virtual void dec_active() NL_NOEXCEPT {  }
		virtual void reset() { }

		void do_update() NL_NOEXCEPT
		{
			update();
		}

		plib::plog_base<netlist_t, NL_DEBUG> &log();

	public:
		virtual void timestep(ATTR_UNUSED const nl_double st) { }
		virtual void update_terminals() { }

		virtual void update_param() {}
		virtual bool is_dynamic() const { return false; }
		virtual bool is_timestep() const { return false; }
		virtual bool needs_update_after_param_change() const { return false; }

	private:
		bool m_hint_deactivate;
>>>>>>> upstream/master
	};

	// -----------------------------------------------------------------------------
	// device_t
	// -----------------------------------------------------------------------------

	class device_t : public core_device_t
	{
<<<<<<< HEAD
		P_PREVENT_COPYING(device_t)
	public:

		ATTR_COLD device_t();
		ATTR_COLD device_t(const family_t afamily);

		virtual ~device_t();

		virtual void init(netlist_t &anetlist, const pstring &name);

		ATTR_COLD setup_t &setup();

		ATTR_COLD void register_sub(const pstring &name, device_t &dev);
		ATTR_COLD void register_subalias(const pstring &name, core_terminal_t &term);
		ATTR_COLD void register_subalias(const pstring &name, const pstring &aliased);
		ATTR_COLD void register_terminal(const pstring &name, terminal_t &port);
		ATTR_COLD void register_output(const pstring &name, analog_output_t &out);
		ATTR_COLD void register_output(const pstring &name, logic_output_t &out);
		ATTR_COLD void register_input(const pstring &name, analog_input_t &in);
		ATTR_COLD void register_input(const pstring &name, logic_input_t &in);

		ATTR_COLD void connect_late(const pstring &t1, const pstring &t2);
		ATTR_COLD void connect_late(core_terminal_t &t1, core_terminal_t &t2);
		ATTR_COLD void connect_direct(core_terminal_t &t1, core_terminal_t &t2);

		plist_t<pstring> m_terminals;

	protected:

		ATTR_HOT virtual void update() { }
		ATTR_HOT virtual void start() { }
		ATTR_HOT virtual void update_terminals() { }

		template <class C, class T>
		ATTR_COLD void register_param(const pstring &sname, C &param, const T initialVal);
=======
	public:

		device_t(netlist_t &owner, const pstring &name);
		device_t(core_device_t &owner, const pstring &name);

		virtual ~device_t() override;

		setup_t &setup();

		template<class C, typename... Args>
		void register_sub(const pstring &name, std::unique_ptr<C> &dev, const Args&... args)
		{
			dev.reset(plib::palloc<C>(*this, name, args...));
		}

		void register_subalias(const pstring &name, detail::core_terminal_t &term);
		void register_subalias(const pstring &name, const pstring &aliased);

		void connect(const pstring &t1, const pstring &t2);
		void connect(detail::core_terminal_t &t1, detail::core_terminal_t &t2);
		void connect_post_start(detail::core_terminal_t &t1, detail::core_terminal_t &t2);
	protected:

		NETLIB_UPDATEI() { }
		NETLIB_UPDATE_TERMINALSI() { }
>>>>>>> upstream/master

	private:
	};

<<<<<<< HEAD

	// -----------------------------------------------------------------------------
	// netlist_queue_t
	// -----------------------------------------------------------------------------

	class queue_t : public timed_queue<net_t *, netlist_time>,
							public object_t,
							public pstate_callback_t
	{
	public:
		queue_t(netlist_t &nl);

	protected:

		void reset() {}

		void register_state(pstate_manager_t &manager, const pstring &module);
		void on_pre_save();
		void on_post_load();

	private:
		struct names_t { char m_buf[64]; };
		int m_qsize;
		parray_t<netlist_time::INTERNALTYPE> m_times;
		parray_t<names_t> m_names;
	};

	// -----------------------------------------------------------------------------
	// netlist_base_t
	// -----------------------------------------------------------------------------


	class netlist_t : public object_t, public pstate_manager_t, public plog_dispatch_intf
	{
		P_PREVENT_COPYING(netlist_t)
	public:

		netlist_t();
		virtual ~netlist_t();

		ATTR_COLD void start();
		ATTR_COLD void stop();

		ATTR_HOT  const queue_t &queue() const { return m_queue; }
		ATTR_HOT  queue_t &queue() { return m_queue; }
		ATTR_HOT  const netlist_time &time() const { return m_time; }
		ATTR_HOT  devices::NETLIB_NAME(solver) *solver() const { return m_solver; }
		ATTR_HOT  devices::NETLIB_NAME(gnd) *gnd() const { return m_gnd; }
		ATTR_HOT nl_double gmin() const;

		ATTR_HOT void push_to_queue(net_t &out, const netlist_time &attime);
		ATTR_HOT void remove_from_queue(net_t &out);

		ATTR_HOT void process_queue(const netlist_time &delta);
		ATTR_HOT  void abort_current_queue_slice() { m_stop = netlist_time::zero; }

		ATTR_HOT  const bool &use_deactivate() const { return m_use_deactivate; }

		ATTR_COLD void rebuild_lists(); /* must be called after post_load ! */

		ATTR_COLD void set_setup(setup_t *asetup) { m_setup = asetup;  }
		ATTR_COLD setup_t &setup() { return *m_setup; }

		ATTR_COLD net_t *find_net(const pstring &name);

		template<class _C>
		ATTR_COLD plist_t<_C *> get_device_list()
		{
			plist_t<_C *> tmp;
			for (std::size_t i = 0; i < m_devices.size(); i++)
			{
				_C *dev = dynamic_cast<_C *>(m_devices[i]);
				if (dev != NULL)
					tmp.add(dev);
=======
	// -----------------------------------------------------------------------------
	// family_setter_t
	// -----------------------------------------------------------------------------

	struct detail::family_setter_t
	{
		family_setter_t() { }
		family_setter_t(core_device_t &dev, const pstring &desc);
		family_setter_t(core_device_t &dev, const logic_family_desc_t *desc);
	};

	// -----------------------------------------------------------------------------
	// nld_base_dummy : basis for dummy devices
	// -----------------------------------------------------------------------------

	NETLIB_OBJECT(base_dummy)
	{
	public:
		NETLIB_CONSTRUCTOR(base_dummy) { }
	};

	// -----------------------------------------------------------------------------
	// queue_t
	// -----------------------------------------------------------------------------

	/* We don't need a thread-safe queue currently. Parallel processing of
	 * solvers will update inputs after parallel processing.
	 */
	class detail::queue_t :
			public timed_queue<pqentry_t<net_t *, netlist_time>, false>,
			public detail::netlist_ref,
			public plib::state_manager_t::callback_t
	{
	public:
		typedef pqentry_t<net_t *, netlist_time> entry_t;
		explicit queue_t(netlist_t &nl);

	protected:

		void register_state(plib::state_manager_t &manager, const pstring &module) override;
		void on_pre_save() override;
		void on_post_load() override;

	private:
		std::size_t m_qsize;
		std::vector<netlist_time::internal_type> m_times;
		std::vector<std::size_t> m_net_ids;
	};

	// -----------------------------------------------------------------------------
	// netlist_t
	// -----------------------------------------------------------------------------


	class netlist_t : private plib::nocopyassignmove
	{
	public:

		explicit netlist_t(const pstring &aname);
		virtual ~netlist_t();

		/* run functions */

		const netlist_time &time() const NL_NOEXCEPT { return m_time; }
		devices::NETLIB_NAME(solver) *solver() const NL_NOEXCEPT { return m_solver; }

		/* never use this in constructors! */
		nl_double gmin() const NL_NOEXCEPT;

		void process_queue(const netlist_time &delta) NL_NOEXCEPT;
		void abort_current_queue_slice() NL_NOEXCEPT { m_queue.retime(detail::queue_t::entry_t(m_time, nullptr)); }

		/* Control functions */

		void start();
		void stop();
		void reset();

		const detail::queue_t &queue() const NL_NOEXCEPT { return m_queue; }
		detail::queue_t &queue() NL_NOEXCEPT { return m_queue; }

		/* netlist build functions */

		setup_t &setup() NL_NOEXCEPT { return *m_setup; }

		void register_dev(plib::owned_ptr<core_device_t> dev);
		void remove_dev(core_device_t *dev);

		detail::net_t *find_net(const pstring &name) const;
		std::size_t find_net_id(const detail::net_t *net) const;

		template<class device_class>
		std::vector<device_class *> get_device_list() const
		{
			std::vector<device_class *> tmp;
			for (auto &d : m_devices)
			{
				device_class *dev = dynamic_cast<device_class *>(d.get());
				if (dev != nullptr)
					tmp.push_back(dev);
>>>>>>> upstream/master
			}
			return tmp;
		}

<<<<<<< HEAD
		template<class _C>
		ATTR_COLD _C *get_first_device()
		{
			for (std::size_t i = 0; i < m_devices.size(); i++)
			{
				_C *dev = dynamic_cast<_C *>(m_devices[i]);
				if (dev != NULL)
					return dev;
			}
			return NULL;
		}

		template<class _C>
		ATTR_COLD _C *get_single_device(const char *classname)
		{
			_C *ret = NULL;
			for (std::size_t i = 0; i < m_devices.size(); i++)
			{
				_C *dev = dynamic_cast<_C *>(m_devices[i]);
				if (dev != NULL)
				{
					if (ret != NULL)
						this->log().fatal("more than one {1} device found", classname);
					else
						ret = dev;
				}
			}
			return ret;
		}

		pnamedlist_t<device_t *> m_devices;
		net_t::list_t m_nets;
	#if (NL_KEEP_STATISTICS)
		pnamedlist_t<core_device_t *> m_started_devices;
	#endif

	ATTR_COLD plog_base<NL_DEBUG> &log() { return m_log; }
	ATTR_COLD const plog_base<NL_DEBUG> &log() const { return m_log; }

	protected:

		// any derived netlist must override vlog inherited from plog_base
		//  virtual void vlog(const plog_level &l, const pstring &ls) = 0;

		/* from netlist_object */
		virtual void reset();
		virtual void save_register();

	#if (NL_KEEP_STATISTICS)
		// performance
		int m_perf_out_processed;
		int m_perf_inp_processed;
		int m_perf_inp_active;
	#endif

	private:
		netlist_time                m_stop;     // target time for current queue processing

		netlist_time                m_time;
		bool                        m_use_deactivate;
		queue_t                     m_queue;


		devices::NETLIB_NAME(mainclock) *    m_mainclock;
		devices::NETLIB_NAME(solver) *       m_solver;
		devices::NETLIB_NAME(gnd) *          m_gnd;


		devices::NETLIB_NAME(netlistparams) *m_params;
		setup_t *m_setup;
		plog_base<NL_DEBUG> m_log;
	};

	// -----------------------------------------------------------------------------
	// inline implementations
	// -----------------------------------------------------------------------------

	PSTATE_INTERFACE(object_t, m_netlist, name())

	template <class C, param_t::param_type_t T>
	ATTR_HOT inline void param_template_t<C, T>::setTo(const C &param)
	{
		if (m_param != param)
		{
			m_param = param;
			changed();
			device().update_param();
		}
	}

	ATTR_HOT inline logic_net_t & net_t::as_logic()
	{
		nl_assert(family() == LOGIC);
		return static_cast<logic_net_t &>(*this);
	}

	ATTR_HOT inline const logic_net_t & net_t::as_logic() const
	{
		nl_assert(family() == LOGIC);
		return static_cast<const logic_net_t &>(*this);
	}

	ATTR_HOT inline analog_net_t & net_t::as_analog()
	{
		nl_assert(family() == ANALOG);
		return static_cast<analog_net_t &>(*this);
	}

	ATTR_HOT inline const analog_net_t & net_t::as_analog() const
	{
		nl_assert(family() == ANALOG);
		return static_cast<const analog_net_t &>(*this);
	}


	ATTR_HOT inline void logic_input_t::inactivate()
	{
		if (EXPECTED(!is_state(STATE_INP_PASSIVE)))
		{
			set_state(STATE_INP_PASSIVE);
			net().as_logic().dec_active(*this);
		}
	}

	ATTR_HOT inline void logic_input_t::activate()
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().as_logic().inc_active(*this);
=======
		template<class C>
		static bool check_class(core_device_t *p)
		{
			return dynamic_cast<C *>(p) != nullptr;
		}

		template<class C>
		C *get_single_device(const pstring &classname) const
		{
			return dynamic_cast<C *>(get_single_device(classname, check_class<C>));
		}

		/* logging and name */

		pstring name() const { return m_name; }
		plib::plog_base<netlist_t, NL_DEBUG> &log() { return m_log; }
		const plib::plog_base<netlist_t, NL_DEBUG> &log() const { return m_log; }

		/* state related */

		plib::state_manager_t &state() { return m_state; }

		template<typename O, typename C> void save(O &owner, C &state, const pstring &stname)
		{
			this->state().save_item(static_cast<void *>(&owner), state, from_utf8(owner.name()) + pstring(".") + stname);
		}
		template<typename O, typename C> void save(O &owner, C *state, const pstring &stname, const std::size_t count)
		{
			this->state().save_state_ptr(static_cast<void *>(&owner), from_utf8(owner.name()) + pstring(".") + stname, plib::state_manager_t::datatype_f<C>::f(), count, state);
		}

		plib::dynlib &lib() { return *m_lib; }

		// FIXME: find something better
		/* sole use is to manage lifetime of net objects */
		std::vector<plib::owned_ptr<detail::net_t>> m_nets;
		/* sole use is to manage lifetime of family objects */
		std::vector<std::pair<pstring, std::unique_ptr<logic_family_desc_t>>> m_family_cache;

		// FIXME: sort rebuild_lists out
		void rebuild_lists(); /* must be called after post_load ! */

		/* logging callback */
		virtual void vlog(const plib::plog_level &l, const pstring &ls) const = 0;

	protected:

		void print_stats() const;

	private:

		/* helper for save above */
		static pstring from_utf8(const char *c) { return pstring(c, pstring::UTF8); }
		static pstring from_utf8(const pstring &c) { return c; }

		core_device_t *get_single_device(const pstring &classname, bool (*cc)(core_device_t *)) const;

		/* mostly rw */
		netlist_time                        m_time;
		detail::queue_t                     m_queue;

		/* mostly ro */

		devices::NETLIB_NAME(mainclock) *    m_mainclock;
		devices::NETLIB_NAME(solver) *       m_solver;
		devices::NETLIB_NAME(netlistparams) *m_params;

		pstring                             m_name;
		std::unique_ptr<setup_t>            m_setup;
		plib::plog_base<netlist_t, NL_DEBUG>           m_log;
		std::unique_ptr<plib::dynlib>       m_lib; // external lib needs to be loaded as long as netlist exists

		plib::state_manager_t               m_state;

		// performance
		nperftime_t     m_stat_mainloop;
		nperfcount_t    m_perf_out_processed;

		std::vector<plib::owned_ptr<core_device_t>> m_devices;
};

	// -----------------------------------------------------------------------------
	// Support classes for devices
	// -----------------------------------------------------------------------------

	template<class C, int N>
	class object_array_t : public plib::uninitialised_array_t<C, N>
	{
	public:
		struct init
		{
			const char *p[N];
		};
		object_array_t(core_device_t &dev, init names)
		{
			for (std::size_t i = 0; i<N; i++)
				this->emplace(i, dev, pstring(names.p[i], pstring::UTF8));
		}
	};

	// -----------------------------------------------------------------------------
	// inline implementations
	// -----------------------------------------------------------------------------

	template <typename ST, std::size_t AW, std::size_t DW>
	inline param_rom_t<ST, AW, DW>::param_rom_t(device_t &device, const pstring &name)
	: param_data_t(device, name)
	{
		auto f = stream();
		if (f != nullptr)
			f->read(&m_data[0],1<<AW);
		else
			device.netlist().log().warning("Rom {1} not found", Value());
	}

	inline void logic_input_t::inactivate() NL_NOEXCEPT
	{
		if (!is_state(STATE_INP_PASSIVE))
		{
			set_state(STATE_INP_PASSIVE);
			net().dec_active(*this);
		}
	}

	inline void logic_input_t::activate() NL_NOEXCEPT
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().inc_active(*this);
>>>>>>> upstream/master
			set_state(STATE_INP_ACTIVE);
		}
	}

<<<<<<< HEAD
	ATTR_HOT inline void logic_input_t::activate_hl()
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().as_logic().inc_active(*this);
=======
	inline void logic_input_t::activate_hl() NL_NOEXCEPT
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().inc_active(*this);
>>>>>>> upstream/master
			set_state(STATE_INP_HL);
		}
	}

<<<<<<< HEAD
	ATTR_HOT inline void logic_input_t::activate_lh()
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().as_logic().inc_active(*this);
=======
	inline void logic_input_t::activate_lh() NL_NOEXCEPT
	{
		if (is_state(STATE_INP_PASSIVE))
		{
			net().inc_active(*this);
>>>>>>> upstream/master
			set_state(STATE_INP_LH);
		}
	}

<<<<<<< HEAD

	ATTR_HOT inline void net_t::push_to_queue(const netlist_time &delay)
	{
		if (!is_queued() && (num_cons() > 0))
		{
			m_time = netlist().time() + delay;
			m_in_queue = (m_active > 0);     /* queued ? */
			if (m_in_queue)
			{
				netlist().push_to_queue(*this, m_time);
			}
		}
	}

	ATTR_HOT inline void net_t::reschedule_in_queue(const netlist_time &delay)
	{
		if (is_queued())
			netlist().remove_from_queue(*this);

		m_time = netlist().time() + delay;
		m_in_queue = (m_active > 0);     /* queued ? */
		if (EXPECTED(m_in_queue))
		{
			netlist().push_to_queue(*this, m_time);
		}
	}


	ATTR_HOT inline netlist_sig_t logic_input_t::Q() const
	{
		return net().as_logic().Q();
	}

	ATTR_HOT inline nl_double analog_input_t::Q_Analog() const
	{
		return net().as_analog().Q_Analog();
	}

	ATTR_HOT inline void analog_output_t::set_Q(const nl_double newQ)
	{
		if (newQ != net().as_analog().m_cur_Analog)
		{
			net().as_analog().m_cur_Analog = newQ;
			net().push_to_queue(NLTIME_FROM_NS(1));
		}
	}

	ATTR_HOT inline void netlist_t::push_to_queue(net_t &out, const netlist_time &attime)
	{
		m_queue.push(queue_t::entry_t(attime, &out));
	}

	ATTR_HOT inline void netlist_t::remove_from_queue(net_t &out)
	{
		m_queue.remove(&out);
	}

}

NETLIST_SAVE_TYPE(netlist::core_terminal_t::state_e, DT_INT);
=======
	inline void detail::net_t::push_to_queue(const netlist_time &delay) NL_NOEXCEPT
	{
		if ((num_cons() != 0))
		{
			if (is_queued())
				netlist().queue().remove(this);
			m_time = netlist().time() + delay;
			m_in_queue = (m_active > 0) ? QS_QUEUED : QS_DELAYED_DUE_TO_INACTIVE;    /* queued ? */
			if (m_in_queue == QS_QUEUED)
				netlist().queue().push(queue_t::entry_t(m_time, this));
		}
	}

	inline const analog_net_t & analog_t::net() const NL_NOEXCEPT
	{
		return static_cast<const analog_net_t &>(core_terminal_t::net());
	}

	inline analog_net_t & analog_t::net() NL_NOEXCEPT
	{
		return static_cast<analog_net_t &>(core_terminal_t::net());
	}

	inline nl_double terminal_t::operator ()() const NL_NOEXCEPT { return net().Q_Analog(); }

	inline logic_net_t & logic_t::net() NL_NOEXCEPT
	{
		return static_cast<logic_net_t &>(core_terminal_t::net());
	}

	inline const logic_net_t & logic_t::net() const NL_NOEXCEPT
	{
		return static_cast<const logic_net_t &>(core_terminal_t::net());
	}

	inline netlist_sig_t logic_input_t::Q() const NL_NOEXCEPT
	{
		nl_assert(state() != STATE_INP_PASSIVE);
		return net().Q();
	}

	inline nl_double analog_input_t::Q_Analog() const NL_NOEXCEPT
	{
		return net().Q_Analog();
	}

	inline void analog_output_t::set_Q(const nl_double newQ) NL_NOEXCEPT
	{
		if (newQ != m_my_net.Q_Analog())
		{
			m_my_net.set_Q_Analog(newQ);
			m_my_net.toggle_and_push_to_queue(NLTIME_FROM_NS(1));
		}
	}

	inline netlist_t &detail::device_object_t::netlist() NL_NOEXCEPT
	{
		return m_device.netlist();
	}

	inline const netlist_t &detail::device_object_t::netlist() const NL_NOEXCEPT
	{
		return m_device.netlist();
	}

	template <typename T>
	template <typename O>
	state_var<T>::state_var(O &owner, const pstring &name, const T &value)
	: m_value(value)
	{
		owner.netlist().save(owner, m_value, name);
	}

	template <typename T, std::size_t N>
	template <typename O>
	state_var<T[N]>::state_var(O &owner, const pstring &name, const T & value)
	{
		owner.netlist().save(owner, m_value, name);
		for (std::size_t i=0; i<N; i++)
			m_value[i] = value;
	}
}

namespace plib
{
	template<typename X>
	struct ptype_traits<netlist::state_var<X>> : ptype_traits<X>
	{
	};
}

>>>>>>> upstream/master


#endif /* NLBASE_H_ */
