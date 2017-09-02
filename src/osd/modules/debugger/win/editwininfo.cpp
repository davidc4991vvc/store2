// license:BSD-3-Clause
// copyright-holders:Aaron Giles, Vas Crabb
//============================================================
//
//  editwininfo.c - Win32 debug window handling
//
//============================================================

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#include "editwininfo.h"

#include "debugviewinfo.h"
#include "uimetrics.h"

#include "strconv.h"

#include "winutil.h"


<<<<<<< HEAD
// edit box styles
#define EDIT_BOX_STYLE      WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL
#define EDIT_BOX_STYLE_EX   0
=======
namespace {

constexpr DWORD EDIT_BOX_STYLE      = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
constexpr DWORD EDIT_BOX_STYLE_EX   = 0;

constexpr int   MAX_EDIT_STRING     = 256;
constexpr int   HISTORY_LENGTH      = 20;

} // anonymous namespace
>>>>>>> upstream/master


editwin_info::editwin_info(debugger_windows_interface &debugger, bool is_main_console, LPCSTR title, WNDPROC handler) :
	debugwin_info(debugger, is_main_console, title, handler),
<<<<<<< HEAD
	m_editwnd(NULL),
	m_edit_defstr(),
	m_original_editproc(NULL),
	m_history_count(0),
	m_last_history(0)
{
	if (window() == NULL)
		return;

	// create an edit box and override its key handling
	m_editwnd = CreateWindowEx(EDIT_BOX_STYLE_EX, TEXT("EDIT"), NULL, EDIT_BOX_STYLE,
			0, 0, 100, 100, window(), NULL, GetModuleHandleUni(), NULL);
	m_original_editproc = (WNDPROC)(FPTR)GetWindowLongPtr(m_editwnd, GWLP_WNDPROC);
	SetWindowLongPtr(m_editwnd, GWLP_USERDATA, (LONG_PTR)this);
	SetWindowLongPtr(m_editwnd, GWLP_WNDPROC, (LONG_PTR)&editwin_info::static_edit_proc);
	SendMessage(m_editwnd, WM_SETFONT, (WPARAM)metrics().debug_font(), (LPARAM)FALSE);
	SendMessage(m_editwnd, EM_LIMITTEXT, (WPARAM)MAX_EDIT_STRING, (LPARAM)0);
=======
	m_editwnd(nullptr),
	m_edit_defstr(),
	m_original_editproc(nullptr),
	m_history(),
	m_last_history(0)
{
	if (window() == nullptr)
		return;

	// create an edit box and override its key handling
	m_editwnd = CreateWindowEx(EDIT_BOX_STYLE_EX, TEXT("EDIT"), nullptr, EDIT_BOX_STYLE,
			0, 0, 100, 100, window(), nullptr, GetModuleHandleUni(), nullptr);
	m_original_editproc = WNDPROC(uintptr_t(GetWindowLongPtr(m_editwnd, GWLP_WNDPROC)));
	SetWindowLongPtr(m_editwnd, GWLP_USERDATA, LONG_PTR(this));
	SetWindowLongPtr(m_editwnd, GWLP_WNDPROC, LONG_PTR(&editwin_info::static_edit_proc));
	SendMessage(m_editwnd, WM_SETFONT, WPARAM(metrics().debug_font()), LPARAM(FALSE));
	SendMessage(m_editwnd, EM_LIMITTEXT, WPARAM(MAX_EDIT_STRING), LPARAM(0));
>>>>>>> upstream/master
	set_editwnd_text("");
}


editwin_info::~editwin_info()
{
}


bool editwin_info::restore_field(HWND wnd)
{
	if (wnd == m_editwnd)
	{
		set_editwnd_text(m_edit_defstr.c_str());
		editwnd_select_all();
		return true;
	}
	else
	{
		return false;
	}
}


bool editwin_info::set_default_focus()
{
	SetFocus(m_editwnd);
	return true;
}


void editwin_info::set_editwnd_bounds(RECT const &bounds)
{
	smart_set_window_bounds(m_editwnd, window(), bounds);
}


void editwin_info::set_editwnd_text(char const *text)
{
<<<<<<< HEAD
	TCHAR *tc_buffer = tstring_from_utf8(text);
	if (tc_buffer != NULL)
	{
		SendMessage(m_editwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)tc_buffer);
		osd_free(tc_buffer);
	}
=======
	auto tc_buffer = osd::text::to_tstring(text);
	SendMessage(m_editwnd, WM_SETTEXT, WPARAM(0), LPARAM(tc_buffer.c_str()));
>>>>>>> upstream/master
}


void editwin_info::editwnd_select_all()
{
<<<<<<< HEAD
	SendMessage(m_editwnd, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
=======
	SendMessage(m_editwnd, EM_SETSEL, WPARAM(0), LPARAM(-1));
>>>>>>> upstream/master
}


void editwin_info::draw_contents(HDC dc)
{
	debugwin_info::draw_contents(dc);
	if (m_editwnd)
		draw_border(dc, m_editwnd);
}


LRESULT editwin_info::edit_proc(UINT message, WPARAM wparam, LPARAM lparam)
{
<<<<<<< HEAD
	TCHAR buffer[MAX_EDIT_STRING];

=======
>>>>>>> upstream/master
	// handle a few messages
	switch (message)
	{
	// key down: handle navigation in the attached view
	case WM_SYSKEYDOWN:
		if (wparam != VK_F10)
			return CallWindowProc(m_original_editproc, m_editwnd, message, wparam, lparam);
		// (fall through)
	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_UP:
<<<<<<< HEAD
			if (m_last_history < (m_history_count - 1))
				m_last_history++;
			else
				m_last_history = 0;
			SendMessage(m_editwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)&m_history[m_last_history][0]);
			SendMessage(m_editwnd, EM_SETSEL, (WPARAM)MAX_EDIT_STRING, (LPARAM)MAX_EDIT_STRING);
			break;

		case VK_DOWN:
			if (m_last_history > 0)
				m_last_history--;
			else if (m_history_count > 0)
				m_last_history = m_history_count - 1;
			else
				m_last_history = 0;
			SendMessage(m_editwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)&m_history[m_last_history][0]);
			SendMessage(m_editwnd, EM_SETSEL, (WPARAM)MAX_EDIT_STRING, (LPARAM)MAX_EDIT_STRING);
			break;

		case VK_PRIOR:
			if (m_views[0] != NULL)
=======
			if (!m_history.empty())
			{
				m_last_history++;
				if (m_last_history >= m_history.size())
					m_last_history = 0;
				auto const &entry(m_history[m_last_history]);
				SendMessage(m_editwnd, WM_SETTEXT, WPARAM(0), LPARAM(entry.c_str()));
				SendMessage(m_editwnd, EM_SETSEL, WPARAM(entry.length()), LPARAM(entry.length()));
			}
			break;

		case VK_DOWN:
			if (!m_history.empty())
			{
				if (m_last_history > 0)
					m_last_history--;
				else
					m_last_history = m_history.size() - 1;
				auto const &entry(m_history[m_last_history]);
				SendMessage(m_editwnd, WM_SETTEXT, WPARAM(0), LPARAM(entry.c_str()));
				SendMessage(m_editwnd, EM_SETSEL, WPARAM(entry.length()), LPARAM(entry.length()));
			}
			break;

		case VK_PRIOR:
			if (m_views[0] != nullptr)
>>>>>>> upstream/master
				m_views[0]->send_pageup();
			break;

		case VK_NEXT:
<<<<<<< HEAD
			if (m_views[0] != NULL)
=======
			if (m_views[0] != nullptr)
>>>>>>> upstream/master
				m_views[0]->send_pagedown();
			break;

		case VK_TAB:
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
<<<<<<< HEAD
				prev_view(NULL);
			else
				next_view(NULL);
=======
				prev_view(nullptr);
			else
				next_view(nullptr);
>>>>>>> upstream/master
			set_ignore_char_lparam(lparam);
			break;

		default:
			if (handle_key(wparam, lparam))
				set_ignore_char_lparam(lparam);
			else
				return CallWindowProc(m_original_editproc, m_editwnd, message, wparam, lparam);
			break;
		}
		break;

	// char: handle the return key
	case WM_CHAR:

		// ignore chars associated with keys we've handled
		if (check_ignore_char_lparam(lparam))
		{
			if (waiting_for_debugger() || !seq_pressed())
			{
<<<<<<< HEAD
				switch (wparam)
				{
				case 13:
					{
						// fetch the text
						SendMessage(m_editwnd, WM_GETTEXT, (WPARAM)ARRAY_LENGTH(buffer), (LPARAM)buffer);

						// add to the history if it's not a repeat of the last one
						if (buffer[0] != 0 && _tcscmp(buffer, &m_history[0][0]))
						{
							memmove(&m_history[1][0], &m_history[0][0], (HISTORY_LENGTH - 1) * MAX_EDIT_STRING * sizeof(TCHAR));
							_tcscpy(&m_history[0][0], buffer);
							if (m_history_count < HISTORY_LENGTH)
								m_history_count++;
						}
						m_last_history = m_history_count - 1;

						// process
						char *utf8_buffer = utf8_from_tstring(buffer);
						if (utf8_buffer != NULL)
						{
							process_string(utf8_buffer);
							osd_free(utf8_buffer);
						}
						break;
					}

				case 27:
					{
						// fetch the text
						SendMessage(m_editwnd, WM_GETTEXT, (WPARAM)sizeof(buffer), (LPARAM)buffer);
=======
				TCHAR buffer[MAX_EDIT_STRING];

				switch (wparam)
				{
				case 13: // carriage return
					{
						// fetch the text
						SendMessage(m_editwnd, WM_GETTEXT, WPARAM(ARRAY_LENGTH(buffer)), LPARAM(buffer));

						// add to the history if it's not a repeat of the last one
						if (buffer[0] && (m_history.empty() || _tcscmp(buffer, m_history[0].c_str())))
						{
							while (m_history.size() >= HISTORY_LENGTH)
								m_history.pop_back();
							m_history.emplace_front(buffer);
						}
						m_last_history = m_history.size() - 1;

						// process
						{
							auto utf8_buffer = osd::text::from_tstring(buffer);
							process_string(utf8_buffer.c_str());
						}
					}
					break;

				case 27: // escape
					{
						// fetch the text
						SendMessage(m_editwnd, WM_GETTEXT, WPARAM(sizeof(buffer)), LPARAM(buffer));
>>>>>>> upstream/master

						// if it's not empty, clear the text
						if (_tcslen(buffer) > 0)
						{
							set_ignore_char_lparam(lparam);
							set_editwnd_text(m_edit_defstr.c_str());
							editwnd_select_all();
						}
<<<<<<< HEAD
						break;
					}
=======
					}
					break;
>>>>>>> upstream/master

				default:
					return CallWindowProc(m_original_editproc, m_editwnd, message, wparam, lparam);
				}
			}
		}
		break;

	// everything else: defaults
	default:
		return CallWindowProc(m_original_editproc, m_editwnd, message, wparam, lparam);
	}

	return 0;
}


LRESULT CALLBACK editwin_info::static_edit_proc(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
{
<<<<<<< HEAD
	editwin_info *const info = (editwin_info *)(FPTR)GetWindowLongPtr(wnd, GWLP_USERDATA);
=======
	editwin_info *const info = (editwin_info *)uintptr_t(GetWindowLongPtr(wnd, GWLP_USERDATA));
>>>>>>> upstream/master
	assert(info->m_editwnd == wnd);
	return info->edit_proc(message, wparam, lparam);
}
