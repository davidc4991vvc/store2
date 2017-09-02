// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    drcuml.h

    Universal machine language for dynamic recompiling CPU cores.

***************************************************************************/

#pragma once

<<<<<<< HEAD
#ifndef __DRCUML_H__
#define __DRCUML_H__
=======
#ifndef MAME_DEVICES_CPU_DRCUML_H
#define MAME_DEVICES_CPU_DRCUML_H
>>>>>>> upstream/master

#include "drccache.h"
#include "uml.h"


//**************************************************************************
//  CONSTANTS
//**************************************************************************

// these options are passed into drcuml_alloc() and control global behaviors



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

<<<<<<< HEAD
// determine the type of the native DRC, falling back to C
#ifndef NATIVE_DRC
class drcbe_c;
typedef drcbe_c drcbe_native;
#else
class NATIVE_DRC;
typedef NATIVE_DRC drcbe_native;
#endif


=======
>>>>>>> upstream/master
// opaque structure describing UML generation state
class drcuml_state;


// an integer register, with low/high parts
union drcuml_ireg
{
#ifdef LSB_FIRST
<<<<<<< HEAD
	struct { UINT32 l,h; } w;               // 32-bit low, high parts of the register
#else
	struct { UINT32 h,l; } w;               // 32-bit low, high parts of the register
#endif
	UINT64              d;                  // 64-bit full register
=======
	struct { uint32_t l,h; } w;               // 32-bit low, high parts of the register
#else
	struct { uint32_t h,l; } w;               // 32-bit low, high parts of the register
#endif
	uint64_t              d;                  // 64-bit full register
>>>>>>> upstream/master
};


// a floating-point register, with low/high parts
union drcuml_freg
{
#ifdef LSB_FIRST
	struct { float l,h; } s;                // 32-bit low, high parts of the register
#else
	struct { float h,l; } s;                // 32-bit low, high parts of the register
#endif
	double              d;                  // 64-bit full register
};


// the collected machine state of a system
struct drcuml_machine_state
{
	drcuml_ireg         r[uml::REG_I_COUNT];    // integer registers
	drcuml_freg         f[uml::REG_F_COUNT];    // floating-point registers
<<<<<<< HEAD
	UINT32              exp;                // exception parameter register
	UINT8               fmod;               // fmod (floating-point mode) register
	UINT8               flags;              // flags state
=======
	uint32_t              exp;                // exception parameter register
	uint8_t               fmod;               // fmod (floating-point mode) register
	uint8_t               flags;              // flags state
>>>>>>> upstream/master
};


// hints and information about the back-end
struct drcbe_info
{
<<<<<<< HEAD
	UINT8               direct_iregs;       // number of direct-mapped integer registers
	UINT8               direct_fregs;       // number of direct-mapped floating point registers
=======
	uint8_t               direct_iregs;       // number of direct-mapped integer registers
	uint8_t               direct_fregs;       // number of direct-mapped floating point registers
>>>>>>> upstream/master
};


// a drcuml_block describes a basic block of instructions
class drcuml_block
{
	friend class simple_list<drcuml_block>;

public:
	// construction/destruction
<<<<<<< HEAD
	drcuml_block(drcuml_state &drcuml, UINT32 maxinst);
=======
	drcuml_block(drcuml_state &drcuml, uint32_t maxinst);
>>>>>>> upstream/master
	~drcuml_block();

	// getters
	drcuml_block *next() const { return m_next; }
	bool inuse() const { return m_inuse; }
<<<<<<< HEAD
	UINT32 maxinst() const { return m_maxinst; }
=======
	uint32_t maxinst() const { return m_maxinst; }
>>>>>>> upstream/master

	// code generation
	void begin();
	void end();
	void abort();

	// instruction appending
	uml::instruction &append();
<<<<<<< HEAD
	void append_comment(const char *format, ...) ATTR_PRINTF(2,3);
=======
	template <typename Format, typename... Params> void append_comment(Format &&fmt, Params &&... args);
>>>>>>> upstream/master

	// this class is thrown if abort() is called
	class abort_compilation : public emu_exception
	{
		friend class drcuml_block;
		abort_compilation() { }
	};

private:
	// internal helpers
	void optimize();
	void disassemble();
	const char *get_comment_text(const uml::instruction &inst, std::string &comment);

	// internal state
	drcuml_state &          m_drcuml;           // pointer back to the owning UML
	drcuml_block *          m_next;             // pointer to next block
<<<<<<< HEAD
	UINT32                  m_nextinst;         // next instruction to fill in the cache
	UINT32                  m_maxinst;          // maximum number of instructions
=======
	uint32_t                  m_nextinst;         // next instruction to fill in the cache
	uint32_t                  m_maxinst;          // maximum number of instructions
>>>>>>> upstream/master
	std::vector<uml::instruction> m_inst;     // pointer to the instruction list
	bool                    m_inuse;            // this block is in use
};


// interface structure for a back-end
class drcbe_interface
{
public:
	// construction/destruction
	drcbe_interface(drcuml_state &drcuml, drc_cache &cache, device_t &device);
	virtual ~drcbe_interface();

	// required overrides
	virtual void reset() = 0;
	virtual int execute(uml::code_handle &entry) = 0;
<<<<<<< HEAD
	virtual void generate(drcuml_block &block, const uml::instruction *instlist, UINT32 numinst) = 0;
	virtual bool hash_exists(UINT32 mode, UINT32 pc) = 0;
=======
	virtual void generate(drcuml_block &block, const uml::instruction *instlist, uint32_t numinst) = 0;
	virtual bool hash_exists(uint32_t mode, uint32_t pc) = 0;
>>>>>>> upstream/master
	virtual void get_info(drcbe_info &info) = 0;
	virtual bool logging() const { return false; }

protected:
	// internal state
<<<<<<< HEAD
	drcuml_state &          m_drcuml;           // pointer back to our owner
	drc_cache &             m_cache;            // pointer to the cache
	device_t &              m_device;           // CPU device we are associated with
	address_space *         m_space[ADDRESS_SPACES];// pointers to CPU's address space
	drcuml_machine_state &  m_state;            // state of the machine (in near cache)
	data_accessors *        m_accessors;        // memory accessors (in near cache)
=======
	drcuml_state &               m_drcuml;      // pointer back to our owner
	drc_cache &                  m_cache;       // pointer to the cache
	device_t &                   m_device;      // CPU device we are associated with
	std::vector<address_space *> m_space;       // pointers to CPU's address space
	drcuml_machine_state &       m_state;       // state of the machine (in near cache)
	data_accessors *             m_accessors;   // memory accessors (in near cache)
>>>>>>> upstream/master
};


// structure describing UML generation state
class drcuml_state
{
public:
	// construction/destruction
<<<<<<< HEAD
	drcuml_state(device_t &device, drc_cache &cache, UINT32 flags, int modes, int addrbits, int ignorebits);
=======
	drcuml_state(device_t &device, drc_cache &cache, uint32_t flags, int modes, int addrbits, int ignorebits);
>>>>>>> upstream/master
	~drcuml_state();

	// getters
	device_t &device() const { return m_device; }
	drc_cache &cache() const { return m_cache; }

	// reset the state
	void reset();
	int execute(uml::code_handle &entry) { return m_beintf.execute(entry); }

	// code generation
<<<<<<< HEAD
	drcuml_block *begin_block(UINT32 maxinst);

	// back-end interface
	void get_backend_info(drcbe_info &info) { m_beintf.get_info(info); }
	bool hash_exists(UINT32 mode, UINT32 pc) { return m_beintf.hash_exists(mode, pc); }
	void generate(drcuml_block &block, uml::instruction *instructions, UINT32 count) { m_beintf.generate(block, instructions, count); }
=======
	drcuml_block *begin_block(uint32_t maxinst);

	// back-end interface
	void get_backend_info(drcbe_info &info) { m_beintf.get_info(info); }
	bool hash_exists(uint32_t mode, uint32_t pc) { return m_beintf.hash_exists(mode, pc); }
	void generate(drcuml_block &block, uml::instruction *instructions, uint32_t count) { m_beintf.generate(block, instructions, count); }
>>>>>>> upstream/master

	// handle management
	uml::code_handle *handle_alloc(const char *name);

	// symbol management
<<<<<<< HEAD
	void symbol_add(void *base, UINT32 length, const char *name);
	const char *symbol_find(void *base, UINT32 *offset = NULL);

	// logging
	bool logging() const { return (m_umllog != NULL); }
=======
	void symbol_add(void *base, uint32_t length, const char *name);
	const char *symbol_find(void *base, uint32_t *offset = nullptr);

	// logging
	bool logging() const { return (m_umllog != nullptr); }
>>>>>>> upstream/master
	void log_printf(const char *format, ...) ATTR_PRINTF(2,3);
	void log_flush() { if (logging()) fflush(m_umllog); }
	bool logging_native() const { return m_beintf.logging(); }

private:
	// symbol class
	class symbol
	{
		friend class drcuml_state;
		friend class simple_list<symbol>;

		// construction/destruction
<<<<<<< HEAD
		symbol(void *base, UINT32 length, const char *name)
			: m_next(NULL),
=======
		symbol(void *base, uint32_t length, const char *name)
			: m_next(nullptr),
>>>>>>> upstream/master
				m_base(drccodeptr(base)),
				m_length(length),
				m_name(name) { }

	public:
		// getters
		symbol *next() const { return m_next; }

	private:
		// internal state
		symbol *                m_next;             // link to the next symbol
		drccodeptr              m_base;             // base of the symbol
<<<<<<< HEAD
		UINT32                  m_length;           // length of the region covered
=======
		uint32_t                  m_length;           // length of the region covered
>>>>>>> upstream/master
		std::string             m_name;             // name of the symbol
	};

	// internal state
	device_t &                  m_device;           // CPU device we are associated with
	drc_cache &                 m_cache;            // pointer to the codegen cache
<<<<<<< HEAD
=======
	std::unique_ptr<drcbe_interface> m_drcbe_interface;
>>>>>>> upstream/master
	drcbe_interface &           m_beintf;           // backend interface pointer
	FILE *                      m_umllog;           // handle to the UML logfile
	simple_list<drcuml_block>   m_blocklist;        // list of active blocks
	simple_list<uml::code_handle> m_handlelist;     // list of active handles
	simple_list<symbol>         m_symlist;          // list of symbols
};



<<<<<<< HEAD
#endif /* __DRCUML_H__ */
=======
//**************************************************************************
//  MEMBER TEMPLATES
//**************************************************************************

//-------------------------------------------------
//  comment - attach a comment to the current
//  output location in the specified block
//-------------------------------------------------

template <typename Format, typename... Params>
inline void drcuml_block::append_comment(Format &&fmt, Params &&... args)
{
	// do the printf
	std::string temp(util::string_format(std::forward<Format>(fmt), std::forward<Params>(args)...));

	// allocate space in the cache to hold the comment
	char *comment = (char *)m_drcuml.cache().alloc_temporary(temp.length() + 1);
	if (comment != nullptr)
	{
		strcpy(comment, temp.c_str());

		// add an instruction with a pointer
		append().comment(comment);
	}
}


#endif /* MAME_DEVICES_CPU_DRCUML_H */
>>>>>>> upstream/master
