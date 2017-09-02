// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
/*********************************************************************

    formats/kc85_dsk.h

    kc85 format

*********************************************************************/

#ifndef KC85_DSK_H_
#define KC85_DSK_H_

#include "upd765_dsk.h"

class kc85_format : public upd765_format {
public:
	kc85_format();

<<<<<<< HEAD
	virtual const char *name() const;
	virtual const char *description() const;
	virtual const char *extensions() const;
=======
	virtual const char *name() const override;
	virtual const char *description() const override;
	virtual const char *extensions() const override;
>>>>>>> upstream/master

private:
	static const format formats[];
};

extern const floppy_format_type FLOPPY_KC85_FORMAT;

#endif
