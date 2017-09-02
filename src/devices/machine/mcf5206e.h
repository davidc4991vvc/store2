// license:BSD-3-Clause
// copyright-holders:David Haywood
/***************************************************************************

    MCF5206E Peripherals

***************************************************************************/

<<<<<<< HEAD
#pragma once

#ifndef __MCF5206E_PERIPHERAL_H__
#define __MCF5206E_PERIPHERAL_H__

#include "emu.h"
=======
#ifndef MAME_MACHINE_MCF5206E_H
#define MAME_MACHINE_MCF5206E_H

#pragma once

>>>>>>> upstream/master



/***************************************************************************
    DEVICE CONFIGURATION MACROS
***************************************************************************/

#define MCFG_MCF5206E_PERIPHERAL_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MCF5206E_PERIPHERAL, 0)

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

// ======================> mcf5206e_peripheral_device

<<<<<<< HEAD
enum
{
	ICR1 = 0,
	ICR2,
	ICR3,
	ICR4,
	ICR5,
	ICR6,
	ICR7,
	ICR8,
	ICR9,
	ICR10,
	ICR11,
	ICR12,
	ICR13,
	MAX_ICR
};

=======
>>>>>>> upstream/master
class mcf5206e_peripheral_device :  public device_t,
									public device_memory_interface
{
public:
<<<<<<< HEAD
	// construction/destruction
	mcf5206e_peripheral_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	void ICR_info(UINT8 ICR);
=======
	enum
	{
		ICR1 = 0,
		ICR2,
		ICR3,
		ICR4,
		ICR5,
		ICR6,
		ICR7,
		ICR8,
		ICR9,
		ICR10,
		ICR11,
		ICR12,
		ICR13,
		MAX_ICR
	};

	// construction/destruction
	mcf5206e_peripheral_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	void ICR_info(uint8_t ICR);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( dev_r );
	DECLARE_WRITE32_MEMBER( dev_w );
	DECLARE_READ32_MEMBER( seta2_coldfire_regs_r );
	DECLARE_WRITE32_MEMBER( seta2_coldfire_regs_w );

	DECLARE_READ8_MEMBER( ICR1_ICR2_ICR3_ICR4_r );
	DECLARE_WRITE8_MEMBER( ICR1_ICR2_ICR3_ICR4_w );

	DECLARE_READ8_MEMBER( ICR9_ICR10_ICR11_ICR12_r );
	DECLARE_WRITE8_MEMBER( ICR9_ICR10_ICR11_ICR12_w );
	DECLARE_READ8_MEMBER( ICR13_r );
	DECLARE_WRITE8_MEMBER( ICR13_w );

<<<<<<< HEAD
	UINT16 CSAR_r(int which, int offset, UINT16 mem_mask);
	void CSAR_w(int which, int offset, UINT16 data, UINT16 mem_mask);
	UINT32 CSMR_r(int which, UINT32 mem_mask);
	void CSMR_w(int which, UINT32 data, UINT32 mem_mask);
	UINT16 CSCR_r(int which, int offset, UINT16 mem_mask);
	void CSCR_w(int which, int offset, UINT16 data, UINT16 mem_mask);
=======
	uint16_t CSAR_r(int which, int offset, uint16_t mem_mask);
	void CSAR_w(int which, int offset, uint16_t data, uint16_t mem_mask);
	uint32_t CSMR_r(int which, uint32_t mem_mask);
	void CSMR_w(int which, uint32_t data, uint32_t mem_mask);
	uint16_t CSCR_r(int which, int offset, uint16_t mem_mask);
	void CSCR_w(int which, int offset, uint16_t data, uint16_t mem_mask);
>>>>>>> upstream/master

	DECLARE_READ16_MEMBER(  CSAR0_r );
	DECLARE_WRITE16_MEMBER( CSAR0_w );
	DECLARE_READ32_MEMBER(  CSMR0_r );
	DECLARE_WRITE32_MEMBER( CSMR0_w );
	DECLARE_READ16_MEMBER(  CSCR0_r );
	DECLARE_WRITE16_MEMBER( CSCR0_w );
	DECLARE_READ16_MEMBER(  CSAR1_r );
	DECLARE_WRITE16_MEMBER( CSAR1_w );
	DECLARE_READ32_MEMBER(  CSMR1_r );
	DECLARE_WRITE32_MEMBER( CSMR1_w );
	DECLARE_READ16_MEMBER(  CSCR1_r );
	DECLARE_WRITE16_MEMBER( CSCR1_w );
	DECLARE_READ16_MEMBER(  CSAR2_r );
	DECLARE_WRITE16_MEMBER( CSAR2_w );
	DECLARE_READ32_MEMBER(  CSMR2_r );
	DECLARE_WRITE32_MEMBER( CSMR2_w );
	DECLARE_READ16_MEMBER(  CSCR2_r );
	DECLARE_WRITE16_MEMBER( CSCR2_w );
	DECLARE_READ16_MEMBER(  CSAR3_r );
	DECLARE_WRITE16_MEMBER( CSAR3_w );
	DECLARE_READ32_MEMBER(  CSMR3_r );
	DECLARE_WRITE32_MEMBER( CSMR3_w );
	DECLARE_READ16_MEMBER(  CSCR3_r );
	DECLARE_WRITE16_MEMBER( CSCR3_w );
	DECLARE_READ16_MEMBER(  CSAR4_r );
	DECLARE_WRITE16_MEMBER( CSAR4_w );
	DECLARE_READ32_MEMBER(  CSMR4_r );
	DECLARE_WRITE32_MEMBER( CSMR4_w );
	DECLARE_READ16_MEMBER(  CSCR4_r );
	DECLARE_WRITE16_MEMBER( CSCR4_w );
	DECLARE_READ16_MEMBER(  CSAR5_r );
	DECLARE_WRITE16_MEMBER( CSAR5_w );
	DECLARE_READ32_MEMBER(  CSMR5_r );
	DECLARE_WRITE32_MEMBER( CSMR5_w );
	DECLARE_READ16_MEMBER(  CSCR5_r );
	DECLARE_WRITE16_MEMBER( CSCR5_w );
	DECLARE_READ16_MEMBER(  CSAR6_r );
	DECLARE_WRITE16_MEMBER( CSAR6_w );
	DECLARE_READ32_MEMBER(  CSMR6_r );
	DECLARE_WRITE32_MEMBER( CSMR6_w );
	DECLARE_READ16_MEMBER(  CSCR6_r );
	DECLARE_WRITE16_MEMBER( CSCR6_w );
	DECLARE_READ16_MEMBER(  CSAR7_r );
	DECLARE_WRITE16_MEMBER( CSAR7_w );
	DECLARE_READ32_MEMBER(  CSMR7_r );
	DECLARE_WRITE32_MEMBER( CSMR7_w );
	DECLARE_READ16_MEMBER(  CSCR7_r );
	DECLARE_WRITE16_MEMBER( CSCR7_w );

	DECLARE_READ16_MEMBER( DMCR_r );
	DECLARE_WRITE16_MEMBER( DMCR_w );
	DECLARE_READ16_MEMBER( PAR_r );
	DECLARE_WRITE16_MEMBER( PAR_w );

	DECLARE_READ16_MEMBER( TMR1_r );
	DECLARE_WRITE16_MEMBER( TMR1_w );
	DECLARE_READ16_MEMBER( TRR1_r );
	DECLARE_WRITE16_MEMBER( TRR1_w );
	DECLARE_READ8_MEMBER( TER1_r );
	DECLARE_WRITE8_MEMBER(TER1_w );
	DECLARE_READ16_MEMBER( TCN1_r );
	DECLARE_WRITE16_MEMBER( TCN1_w );

	DECLARE_READ8_MEMBER( PPDDR_r );
	DECLARE_WRITE8_MEMBER( PPDDR_w );
	DECLARE_READ8_MEMBER( PPDAT_r );
	DECLARE_WRITE8_MEMBER( PPDAT_w );

	DECLARE_READ16_MEMBER( IMR_r );
	DECLARE_WRITE16_MEMBER( IMR_w );


	DECLARE_READ8_MEMBER( MBCR_r );
	DECLARE_WRITE8_MEMBER( MBCR_w );
	DECLARE_READ8_MEMBER( MBSR_r );
	DECLARE_WRITE8_MEMBER( MBSR_w );
	DECLARE_READ8_MEMBER( MFDR_r );
	DECLARE_WRITE8_MEMBER( MFDR_w );
	DECLARE_READ8_MEMBER( MBDR_r );
	DECLARE_WRITE8_MEMBER( MBDR_w );

<<<<<<< HEAD



	cpu_device* m_cpu;

protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
	virtual void device_post_load() { }
	virtual void device_clock_changed() { }
	virtual const address_space_config *memory_space_config(address_spacenum spacenum = AS_0) const;
	address_space_config        m_space_config;


private:

	void init_regs(bool first_init);

	UINT8 m_ICR[MAX_ICR];

	UINT16 m_CSAR[8];
	UINT32 m_CSMR[8];
	UINT16 m_CSCR[8];

	UINT16 m_DMCR;
	UINT16 m_PAR;

	emu_timer *m_timer1;
	UINT16 m_TMR1;
	UINT16 m_TRR1;
	UINT8 m_TER1;
	UINT16 m_TCN1;
	TIMER_CALLBACK_MEMBER(timer1_callback);


	UINT8 m_PPDDR;
	UINT8 m_PPDAT;

	UINT16 m_IMR;

	UINT8 m_MBCR;
	UINT8 m_MBSR;
	UINT8 m_MFDR;
	UINT8 m_MBDR;

	UINT32 m_coldfire_regs[0x400/4];

private:
=======
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override { }
	virtual void device_clock_changed() override { }
	virtual space_config_vector memory_space_config() const override;

private:
	TIMER_CALLBACK_MEMBER(timer1_callback);

	void init_regs(bool first_init);

	cpu_device* m_cpu;

	address_space_config m_space_config;

	uint8_t m_ICR[MAX_ICR];

	uint16_t m_CSAR[8];
	uint32_t m_CSMR[8];
	uint16_t m_CSCR[8];

	uint16_t m_DMCR;
	uint16_t m_PAR;

	emu_timer *m_timer1;
	uint16_t m_TMR1;
	uint16_t m_TRR1;
	uint8_t m_TER1;
	uint16_t m_TCN1;


	uint8_t m_PPDDR;
	uint8_t m_PPDAT;

	uint16_t m_IMR;

	uint8_t m_MBCR;
	uint8_t m_MBSR;
	uint8_t m_MFDR;
	uint8_t m_MBDR;

	uint32_t m_coldfire_regs[0x400/4];
>>>>>>> upstream/master
};


// device type definition
<<<<<<< HEAD
extern const device_type MCF5206E_PERIPHERAL;

#endif  /* __MCF5206E_PERIPHERAL_H__ */
=======
DECLARE_DEVICE_TYPE(MCF5206E_PERIPHERAL, mcf5206e_peripheral_device)

#endif // MAME_MACHINE_MCF5206E_H
>>>>>>> upstream/master
