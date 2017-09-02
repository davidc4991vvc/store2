// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/*********************************************************************

    dvtext.h

    Debugger simple text-based views.

***************************************************************************/

<<<<<<< HEAD
#ifndef __DVTEXT_H__
#define __DVTEXT_H__
=======
#ifndef MAME_EMU_DEBUG_DVTEXT_H
#define MAME_EMU_DEBUG_DVTEXT_H

#pragma once
>>>>>>> upstream/master

#include "debugvw.h"
#include "textbuf.h"


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// debug_view_textbuf contains data specific to a textbuffer view
class debug_view_textbuf : public debug_view
{
	friend class debug_view_manager;

<<<<<<< HEAD
=======
public:
	void clear();

>>>>>>> upstream/master
protected:
	// construction/destruction
	debug_view_textbuf(running_machine &machine, debug_view_type type, debug_view_osd_update_func osdupdate, void *osdprivate, text_buffer &textbuf);
	virtual ~debug_view_textbuf();

protected:
	// view overrides
<<<<<<< HEAD
	virtual void view_update();
	virtual void view_notify(debug_view_notification type);
=======
	virtual void view_update() override;
	virtual void view_notify(debug_view_notification type) override;
>>>>>>> upstream/master

private:
	// internal state
	text_buffer &       m_textbuf;              /* pointer to the text buffer */
<<<<<<< HEAD
	bool                m_at_bottom;                /* are we tracking new stuff being added? */
	UINT32              m_topseq;                   /* sequence number of the top line */
=======
	bool                m_at_bottom;            /* are we tracking new stuff being added? */
	u32                 m_topseq;               /* sequence number of the top line */
>>>>>>> upstream/master
};


// debug_view_console describes a console view
class debug_view_console : public debug_view_textbuf
{
	friend class debug_view_manager;
	debug_view_console(running_machine &machine, debug_view_osd_update_func osdupdate, void *osdprivate);
};


// debug_view_textbuf describes an error log view
class debug_view_log : public debug_view_textbuf
{
	friend class debug_view_manager;
	debug_view_log(running_machine &machine, debug_view_osd_update_func osdupdate, void *osdprivate);
};

<<<<<<< HEAD

#endif
=======
#endif // MAME_EMU_DEBUG_DVTEXT_H
>>>>>>> upstream/master
