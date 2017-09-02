// license:BSD-3-Clause
// copyright-holders:Juergen Buchmueller
/*****************************************************************************
 *
 *   Xerox AltoII memory block (MEM)
 *
 *****************************************************************************/
#ifdef  ALTO2_DEFINE_CONSTANTS

#define ALTO2_RAM_SIZE          0200000                     //!< size of main memory in words
#define ALTO2_IO_PAGE_BASE      0177000                     //!< base address of the memory mapped io range
#define ALTO2_IO_PAGE_SIZE      0001000                     //!< size of the memory mapped io range

#else   // ALTO2_DEFINE_CONSTANTS
#ifndef _A2MEM_H_
#define _A2MEM_H_
//! memory access mode
enum {
	ALTO2_MEM_NONE,
	ALTO2_MEM_ODD       = (1 << 0),
	ALTO2_MEM_RAM       = (1 << 1),
<<<<<<< HEAD
	ALTO2_MEM_REFRESH   = (1 << 2),
	ALTO2_MEM_INVALID   = (1 << 3)
};

struct {
	UINT32 size;                        //!< main memory size (64K or 128K)
	UINT32* ram;                        //!< main memory organized as double-words
	UINT8* hpb;                         //!< Hamming Code bits (6) and Parity bits (1) per double word
	UINT32 mar;                         //!< memory address register
	UINT32 rmdd;                        //!< read memory data double-word
	UINT32 wmdd;                        //!< write memory data double-word
	UINT16 md;                          //!< memory data register
	UINT64 cycle;                       //!< cycle when the memory address register was loaded
=======
	ALTO2_MEM_LATCHED   = (1 << 2),
	ALTO2_MEM_REFRESH   = (1 << 3),
	ALTO2_MEM_INVALID   = (1 << 4)
};

struct {
	uint32_t size;                        //!< main memory size (64K or 128K)
	std::unique_ptr<uint32_t[]> ram;      //!< main memory organized as double-words
	std::unique_ptr<uint8_t[]> hpb;       //!< Hamming Code bits (6) and Parity bits (1) per double word
	uint32_t mar;                         //!< memory address register
	uint32_t rmdd;                        //!< read memory data double-word
	uint32_t wmdd;                        //!< write memory data double-word
	uint32_t md;                          //!< memory data register
	uint64_t cycle;                       //!< cycle when the memory address register was loaded
>>>>>>> upstream/master

	/**
	 * @brief memory access under the way if non-zero
	 * 0: no memory access (MEM_NONE)
	 * 1: invalid
	 * 2: memory access even word (MEM_RAM)
	 * 3: memory access odd word (MEM_RAM | MEM_ODD)
	 */
	int access;
	bool error;                         //!< non-zero after a memory error was detected
<<<<<<< HEAD
	UINT32 mear;                        //!< memory error address register
	UINT16 mesr;                        //!< memory error status register
	UINT16 mecr;                        //!< memory error control register
}   m_mem;

/**
 * @brief check if memory address register load is yet possible
 * suspend if accessing RAM and previous MAR<- was less than 5 cycles ago
=======
	uint32_t mear;                        //!< memory error address register
	uint32_t mesr;                        //!< memory error status register
	uint32_t mecr;                        //!< memory error control register
}   m_mem;

/**
 * @brief Check if memory address register load is yet possible.
 * Suspend if accessing RAM and previous MAR<- was less than 5 cycles ago.
>>>>>>> upstream/master
 *
 * 1.  MAR<- ANY
 * 2.  REQUIRED
 * 3.  MD<- whatever
 * 4.  SUSPEND
 * 5.  SUSPEND
 * 6.  MAR<- ANY
 *
 * @return false, if memory address can be loaded
 */
<<<<<<< HEAD
inline bool check_mem_load_mar_stall(UINT8 rsel) {
	if (ALTO2_MEM_NONE == m_mem.access)
=======
inline bool check_mem_load_mar_stall(uint8_t rsel) {
	if (ALTO2_MEM_NONE == m_mem.access || ALTO2_MEM_REFRESH == m_mem.access)
>>>>>>> upstream/master
		return false;
	return cycle() < m_mem.cycle+5;
}

/**
<<<<<<< HEAD
 * @brief check if memory read is yet possible
=======
 * @brief Check if memory read is yet possible.
>>>>>>> upstream/master
 * MAR<- = cycle #1, earliest read at cycle #5, i.e. + 4
 *
 * 1.  MAR<- ANY
 * 2.  REQUIRED
 * 3.  SUSPEND
 * 4.  SUSPEND
<<<<<<< HEAD
 * 5.  whereever <-MD
=======
 * 5.  wherever <-MD
>>>>>>> upstream/master
 *
 * @return false, if memory can be read without wait cycle
 */
inline bool check_mem_read_stall() {
<<<<<<< HEAD
	if (ALTO2_MEM_NONE == m_mem.access)
=======
	if (ALTO2_MEM_NONE == m_mem.access || ALTO2_MEM_REFRESH == m_mem.access)
>>>>>>> upstream/master
		return false;
	return cycle() < m_mem.cycle+4;
}

/**
<<<<<<< HEAD
 * @brief check if memory write is yet possible
=======
 * @brief Check if memory write is yet possible.
>>>>>>> upstream/master
 * MAR<- = cycle #1, earliest write at cycle #3, i.e. + 2
 *
 * 1.  MAR<- ANY
 * 2.  REQUIRED
 * 3.  OPTIONAL
 * 4.  MD<- whatever
 *
 * @return false, if memory can be written without wait cycle
 */
inline bool check_mem_write_stall() {
<<<<<<< HEAD
	if (ALTO2_MEM_NONE == m_mem.access)
=======
	if (ALTO2_MEM_NONE == m_mem.access || ALTO2_MEM_REFRESH == m_mem.access)
>>>>>>> upstream/master
		return false;
	return cycle() < m_mem.cycle+2;
}


DECLARE_READ16_MEMBER ( mear_r );       //!< memory error address register read
DECLARE_READ16_MEMBER ( mesr_r );       //!< memory error status register read
DECLARE_WRITE16_MEMBER( mesr_w );       //!< memory error status register write (clear)
DECLARE_READ16_MEMBER ( mecr_r );       //!< memory error control register read
DECLARE_WRITE16_MEMBER( mecr_w );       //!< memory error control register write

<<<<<<< HEAD
//! read or write a memory double-word and caluclate its Hamming code
UINT32 hamming_code(int write, UINT32 dw_addr, UINT32 dw_data);

//! load the memory address register with some value
void load_mar(UINT8 rsel, UINT32 addr);

//! read memory or memory mapped I/O from the address in mar to md
UINT16 read_mem();

//! write memory or memory mapped I/O from md to the address in mar
void write_mem(UINT16 data);

//! debugger interface to read memory
UINT16 debug_read_mem(UINT32 addr);

//! debugger interface to write memory
void debug_write_mem(UINT32 addr, UINT16 data);

#if ALTO2_DEBUG
void watch_write(UINT32 addr, UINT32 data);
void watch_read(UINT32 addr, UINT32 data);
=======
//! Read or write a memory double-word and calculate or compare its Hamming code.
uint32_t hamming_code(bool write, uint32_t dw_addr, uint32_t dw_data);

//! Load the memory address register with some value.
void load_mar(uint8_t rsel, uint32_t addr);

//! Read memory or memory mapped I/O from the address in mar to md.
uint16_t read_mem();

//! Write memory or memory mapped I/O from md to the address in mar.
void write_mem(uint16_t data);

//! Debugger interface to read memory.
uint16_t debug_read_mem(uint32_t addr);

//! Debugger interface to write memory.
void debug_write_mem(uint32_t addr, uint16_t data);

#if ALTO2_DEBUG
void watch_write(uint32_t addr, uint32_t data);
void watch_read(uint32_t addr, uint32_t data);
>>>>>>> upstream/master
#endif

void init_memory();                             //!< initialize the memory system
void exit_memory();                             //!< deinitialize the memory system
void reset_memory();                            //!< reset the memory system
#endif // _A2MEM_H_
#endif  // ALTO2_DEFINE_CONSTANTS
