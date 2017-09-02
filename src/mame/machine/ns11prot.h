// license:BSD-3-Clause
// copyright-holders:smf
/*
 * Namco System 11 Protection
 *
 */
<<<<<<< HEAD

#include "emu.h"
=======
#ifndef MAME_MACHINE_NS11PROT_H
#define MAME_MACHINE_NS11PROT_H

#pragma once

>>>>>>> upstream/master

class ns11_keycus_device : public device_t
{
protected:
<<<<<<< HEAD
	ns11_keycus_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock,const char *shortname, const char *source);

	virtual void device_start();
	virtual void device_reset();

protected:
	UINT16 m_p1;
	UINT16 m_p2;
	UINT16 m_p3;
=======
	ns11_keycus_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	uint16_t m_p1;
	uint16_t m_p2;
	uint16_t m_p3;
>>>>>>> upstream/master

public:
	virtual DECLARE_READ16_MEMBER( read ) = 0;
	virtual DECLARE_WRITE16_MEMBER( write ) = 0;
};

/* tekken 2 */

class keycus_c406_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c406_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C406;
=======
	keycus_c406_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C406, keycus_c406_device)
>>>>>>> upstream/master

/* soul edge */

class keycus_c409_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c409_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C409;
=======
	keycus_c409_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C409, keycus_c409_device)
>>>>>>> upstream/master

/* dunk mania */

class keycus_c410_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c410_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C410;
=======
	keycus_c410_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C410, keycus_c410_device)
>>>>>>> upstream/master

/* prime goal ex */

class keycus_c411_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c411_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C411;
=======
	keycus_c411_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C411, keycus_c411_device)
>>>>>>> upstream/master

/* xevious 3d/g */

class keycus_c430_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c430_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C430;
=======
	keycus_c430_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C430, keycus_c430_device)
>>>>>>> upstream/master

/* dancing eyes */

class keycus_c431_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c431_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C431;
=======
	keycus_c431_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C431, keycus_c431_device)
>>>>>>> upstream/master

/* pocket racer */

class keycus_c432_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c432_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C432;
=======
	keycus_c432_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C432, keycus_c432_device)
>>>>>>> upstream/master

/* star sweep */

class keycus_c442_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c442_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C442;
=======
	keycus_c442_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C442, keycus_c442_device)
>>>>>>> upstream/master

/* kosodate quiz my angel 3 / point blank 2 */

class keycus_c443_device : public ns11_keycus_device
{
public:
<<<<<<< HEAD
	keycus_c443_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	virtual DECLARE_READ16_MEMBER( read );
	virtual DECLARE_WRITE16_MEMBER( write );
};

extern const device_type KEYCUS_C443;
=======
	keycus_c443_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	virtual DECLARE_READ16_MEMBER( read ) override;
	virtual DECLARE_WRITE16_MEMBER( write ) override;
};

DECLARE_DEVICE_TYPE(KEYCUS_C443, keycus_c443_device)

#endif // MAME_MACHINE_NS11PROT_H
>>>>>>> upstream/master
