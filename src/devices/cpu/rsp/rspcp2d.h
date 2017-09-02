// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
/***************************************************************************

    rspcp2d.h

    Interface file for Reality Signal Processor (RSP) vector extensions
    using Universal Machine Language (UML) dynamic recompilation.

***************************************************************************/

#pragma once

#ifndef __RSPCP2D_H__
#define __RSPCP2D_H__

#include "cpu/drcuml.h"
#include "rsp.h"
#include "rspcp2.h"

class rsp_cop2_drc : public rsp_cop2
{
	friend class rsp_device;
<<<<<<< HEAD

	rsp_cop2_drc(rsp_device &rsp, running_machine &machine) : rsp_cop2(rsp, machine) { }

	virtual int generate_cop2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc);
	virtual int generate_lwc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc);
	virtual int generate_swc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc);

	virtual void state_string_export(const int index, std::string &str);

	void cfunc_unimplemented_opcode();

public:
	virtual void lbv();
	virtual void lsv();
	virtual void llv();
	virtual void ldv();
	virtual void lqv();
	virtual void lrv();
	virtual void lpv();
	virtual void luv();
	virtual void lhv();
	virtual void lfv();
	virtual void lwv();
	virtual void ltv();
	virtual void sbv();
	virtual void ssv();
	virtual void slv();
	virtual void sdv();
	virtual void sqv();
	virtual void srv();
	virtual void spv();
	virtual void suv();
	virtual void shv();
	virtual void sfv();
	virtual void swv();
	virtual void stv();
	virtual void vmulf();
	virtual void vmulu();
	virtual void vmudl();
	virtual void vmudm();
	virtual void vmudn();
	virtual void vmudh();
	virtual void vmacf();
	virtual void vmacu();
	virtual void vmadl();
	virtual void vmadm();
	virtual void vmadn();
	virtual void vmadh();
	virtual void vadd();
	virtual void vsub();
	virtual void vabs();
	virtual void vaddc();
	virtual void vsubc();
	virtual void vaddb();
	virtual void vsaw();
	virtual void vlt();
	virtual void veq();
	virtual void vne();
	virtual void vge();
	virtual void vcl();
	virtual void vch();
	virtual void vcr();
	virtual void vmrg();
	virtual void vand();
	virtual void vnand();
	virtual void vor();
	virtual void vnor();
	virtual void vxor();
	virtual void vnxor();
	virtual void vrcp();
	virtual void vrcpl();
	virtual void vrcph();
	virtual void vmov();
	virtual void vrsql();
	virtual void vrsqh();
	virtual void vrsq();
	virtual void mfc2();
	virtual void cfc2();
	virtual void mtc2();
	virtual void ctc2();

private:
	virtual int     generate_vector_opcode(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc);
=======
public:
	rsp_cop2_drc(rsp_device &rsp, running_machine &machine) : rsp_cop2(rsp, machine) { }
private:
	virtual bool generate_cop2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc) override;
	virtual bool generate_lwc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc) override;
	virtual bool generate_swc2(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc) override;

	virtual void state_string_export(const int index, std::string &str) const override;

	void cfunc_unimplemented_opcode() override;

public:
	virtual void lbv() override;
	virtual void lsv() override;
	virtual void llv() override;
	virtual void ldv() override;
	virtual void lqv() override;
	virtual void lrv() override;
	virtual void lpv() override;
	virtual void luv() override;
	virtual void lhv() override;
	virtual void lfv() override;
	virtual void lwv() override;
	virtual void ltv() override;
	virtual void sbv() override;
	virtual void ssv() override;
	virtual void slv() override;
	virtual void sdv() override;
	virtual void sqv() override;
	virtual void srv() override;
	virtual void spv() override;
	virtual void suv() override;
	virtual void shv() override;
	virtual void sfv() override;
	virtual void swv() override;
	virtual void stv() override;
	virtual void vmulf() override;
	virtual void vmulu() override;
	virtual void vmudl() override;
	virtual void vmudm() override;
	virtual void vmudn() override;
	virtual void vmudh() override;
	virtual void vmacf() override;
	virtual void vmacu() override;
	virtual void vmadl() override;
	virtual void vmadm() override;
	virtual void vmadn() override;
	virtual void vmadh() override;
	virtual void vadd() override;
	virtual void vsub() override;
	virtual void vabs() override;
	virtual void vaddc() override;
	virtual void vsubc() override;
	virtual void vaddb() override;
	virtual void vsaw() override;
	virtual void vlt() override;
	virtual void veq() override;
	virtual void vne() override;
	virtual void vge() override;
	virtual void vcl() override;
	virtual void vch() override;
	virtual void vcr() override;
	virtual void vmrg() override;
	virtual void vand() override;
	virtual void vnand() override;
	virtual void vor() override;
	virtual void vnor() override;
	virtual void vxor() override;
	virtual void vnxor() override;
	virtual void vrcp() override;
	virtual void vrcpl() override;
	virtual void vrcph() override;
	virtual void vmov() override;
	virtual void vrsql() override;
	virtual void vrsqh() override;
	virtual void vrsq() override;
	virtual void mfc2() override;
	virtual void cfc2() override;
	virtual void mtc2() override;
	virtual void ctc2() override;

private:
	virtual bool generate_vector_opcode(drcuml_block *block, rsp_device::compiler_state *compiler, const opcode_desc *desc) override;
>>>>>>> upstream/master
};

#endif /* __RSPCP2D_H__ */
