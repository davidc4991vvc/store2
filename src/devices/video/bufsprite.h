// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************************

    bufsprite.h

    Buffered Sprite RAM device.

*********************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __BUFSPRITE_H__
#define __BUFSPRITE_H__
=======
#ifndef MAME_VIDEO_BUFSPRITE_H
#define MAME_VIDEO_BUFSPRITE_H

#pragma once
>>>>>>> upstream/master



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
<<<<<<< HEAD
extern const device_type BUFFERED_SPRITERAM8;
extern const device_type BUFFERED_SPRITERAM16;
extern const device_type BUFFERED_SPRITERAM32;
extern const device_type BUFFERED_SPRITERAM64;
=======
DECLARE_DEVICE_TYPE(BUFFERED_SPRITERAM8,  buffered_spriteram8_device)
DECLARE_DEVICE_TYPE(BUFFERED_SPRITERAM16, buffered_spriteram16_device)
DECLARE_DEVICE_TYPE(BUFFERED_SPRITERAM32, buffered_spriteram32_device)
DECLARE_DEVICE_TYPE(BUFFERED_SPRITERAM64, buffered_spriteram64_device)
>>>>>>> upstream/master



//**************************************************************************
//  DEVICE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_BUFFERED_SPRITERAM8_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, BUFFERED_SPRITERAM8, 0)
#define MCFG_BUFFERED_SPRITERAM16_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, BUFFERED_SPRITERAM16, 0)
#define MCFG_BUFFERED_SPRITERAM32_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, BUFFERED_SPRITERAM32, 0)
#define MCFG_BUFFERED_SPRITERAM64_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, BUFFERED_SPRITERAM64, 0)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> buffered_spriteram_device

// base class to manage buffered spriteram
<<<<<<< HEAD
template<typename _Type>
class buffered_spriteram_device : public device_t
{
public:
	// construction
	buffered_spriteram_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, UINT32 clock)
		: device_t(mconfig, type, "Buffered Sprite RAM", tag, owner, clock, "buffered_spriteram", __FILE__),
			m_spriteram(*owner, tag) { }

	// getters
	_Type *live() const { return m_spriteram; }
	_Type *buffer() { return &m_buffered[0]; }
	UINT32 bytes() const { return m_spriteram.bytes(); }

	// operations
	_Type *copy(UINT32 srcoffset = 0, UINT32 srclength = 0x7fffffff)
	{
		assert(m_spriteram != NULL);
		if (m_spriteram != NULL)
			memcpy(&m_buffered[0], m_spriteram + srcoffset, MIN(srclength, m_spriteram.bytes() / sizeof(_Type) - srcoffset) * sizeof(_Type));
=======
template <typename Type>
class buffered_spriteram_device : public device_t
{
public:
	// getters
	Type *live() const { return m_spriteram; }
	Type *buffer() { return &m_buffered[0]; }
	uint32_t bytes() const { return m_spriteram.bytes(); }

	// operations
	Type *copy(uint32_t srcoffset = 0, uint32_t srclength = 0x7fffffff)
	{
		assert(m_spriteram != nullptr);
		if (m_spriteram != nullptr)
			memcpy(&m_buffered[0], m_spriteram + srcoffset, (std::min<size_t>)(srclength, m_spriteram.bytes() / sizeof(Type) - srcoffset) * sizeof(Type));
>>>>>>> upstream/master
		return &m_buffered[0];
	}

	// read/write handlers
<<<<<<< HEAD
	void write(address_space &space, offs_t offset, _Type data, _Type mem_mask = ~_Type(0)) { copy(); }

	// VBLANK handlers
	void vblank_copy_rising(screen_device &screen, bool state) { if (state) copy(); }
	void vblank_copy_falling(screen_device &screen, bool state) { if (!state) copy(); }

protected:
	// first-time setup
	virtual void device_start()
	{
		if (m_spriteram != NULL)
		{
			m_buffered.resize(m_spriteram.bytes() / sizeof(_Type));
			save_item(NAME(m_buffered));
		}
	}

private:
	// internal state
	required_shared_ptr<_Type>  m_spriteram;
	std::vector<_Type>        m_buffered;
=======
	void write(address_space &space, offs_t offset, Type data, Type mem_mask = ~Type(0)) { copy(); }

	// VBLANK handlers
	DECLARE_WRITE_LINE_MEMBER(vblank_copy_rising) { if (state) copy(); }
	DECLARE_WRITE_LINE_MEMBER(vblank_copy_falling) { if (!state) copy(); }

protected:
	// construction
	buffered_spriteram_device(
			const machine_config &mconfig,
			device_type type,
			const char *tag,
			device_t *owner,
			uint32_t clock);

	// first-time setup
	virtual void device_start() override;

private:
	// internal state
	required_shared_ptr<Type>   m_spriteram;
	std::vector<Type>           m_buffered;
>>>>>>> upstream/master
};


// ======================> buffered_spriteram8_device

<<<<<<< HEAD
class buffered_spriteram8_device : public buffered_spriteram_device<UINT8>
{
public:
	// construction
	buffered_spriteram8_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: buffered_spriteram_device<UINT8>(mconfig, BUFFERED_SPRITERAM8, tag, owner, clock) { }
=======
class buffered_spriteram8_device : public buffered_spriteram_device<uint8_t>
{
public:
	// construction
	buffered_spriteram8_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> buffered_spriteram16_device

<<<<<<< HEAD
class buffered_spriteram16_device : public buffered_spriteram_device<UINT16>
{
public:
	// construction
	buffered_spriteram16_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: buffered_spriteram_device<UINT16>(mconfig, BUFFERED_SPRITERAM16, tag, owner, clock) { }
=======
class buffered_spriteram16_device : public buffered_spriteram_device<uint16_t>
{
public:
	// construction
	buffered_spriteram16_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> buffered_spriteram32_device

<<<<<<< HEAD
class buffered_spriteram32_device : public buffered_spriteram_device<UINT32>
{
public:
	// construction
	buffered_spriteram32_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: buffered_spriteram_device<UINT32>(mconfig, BUFFERED_SPRITERAM32, tag, owner, clock) { }
=======
class buffered_spriteram32_device : public buffered_spriteram_device<uint32_t>
{
public:
	// construction
	buffered_spriteram32_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
>>>>>>> upstream/master
};


// ======================> buffered_spriteram64_device

<<<<<<< HEAD
class buffered_spriteram64_device : public buffered_spriteram_device<UINT64>
{
public:
	// construction
	buffered_spriteram64_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
		: buffered_spriteram_device<UINT64>(mconfig, BUFFERED_SPRITERAM64, tag, owner, clock) { }
};


#endif  /* __BUFSPRITE_H__ */
=======
class buffered_spriteram64_device : public buffered_spriteram_device<uint64_t>
{
public:
	// construction
	buffered_spriteram64_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};


#endif  // MAME_VIDEO_BUFSPRITE_H
>>>>>>> upstream/master
