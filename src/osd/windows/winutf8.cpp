// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  winutf8.c - Win32 OSD core utility functions
//
//============================================================

// standard windows headers
<<<<<<< HEAD
#define WIN32_LEAN_AND_MEAN
=======
>>>>>>> upstream/master
#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>

// MAMEOS headers
#include "winutf8.h"
#include "strconv.h"


//============================================================
//  win_output_debug_string_utf8
//============================================================

void win_output_debug_string_utf8(const char *string)
{
<<<<<<< HEAD
	TCHAR *t_string = tstring_from_utf8(string);
	if (t_string != NULL)
	{
		OutputDebugString(t_string);
		osd_free(t_string);
	}
}



//============================================================
//  win_get_module_file_name_utf8
//============================================================

DWORD win_get_module_file_name_utf8(HMODULE module, char *filename, DWORD size)
{
	TCHAR t_filename[MAX_PATH];
	char *utf8_filename;

	if (GetModuleFileName(module, t_filename, ARRAY_LENGTH(t_filename)) == 0)
		return 0;

	utf8_filename = utf8_from_tstring(t_filename);
	if (!utf8_filename)
		return 0;

	size = (DWORD) snprintf(filename, size, "%s", utf8_filename);
	osd_free(utf8_filename);
	return size;
}



//============================================================
//  win_set_file_attributes_utf8
//============================================================

BOOL win_set_file_attributes_utf8(const char* filename, DWORD fileattributes)
{
	BOOL result = FALSE;
	TCHAR* t_filename = tstring_from_utf8(filename);
	if( !t_filename )
		return result;

	result = SetFileAttributes(t_filename, fileattributes);

	osd_free(t_filename);

	return result;
}



//============================================================
//  win_copy_file_utf8
//============================================================

BOOL win_copy_file_utf8(const char* existingfilename, const char* newfilename, BOOL failifexists)
{
	TCHAR* t_existingfilename;
	TCHAR* t_newfilename;
	BOOL result = FALSE;

	t_existingfilename = tstring_from_utf8(existingfilename);
	if( !t_existingfilename )
		return result;

	t_newfilename = tstring_from_utf8(newfilename);
	if( !t_newfilename ) {
		osd_free(t_existingfilename);
		return result;
	}

	result = CopyFile(t_existingfilename, t_newfilename, failifexists);

	osd_free(t_newfilename);
	osd_free(t_existingfilename);

	return result;
}



//============================================================
//  win_move_file_utf8
//============================================================

BOOL win_move_file_utf8(const char* existingfilename, const char* newfilename)
{
	TCHAR* t_existingfilename;
	TCHAR* t_newfilename;
	BOOL result = FALSE;

	t_existingfilename = tstring_from_utf8(existingfilename);
	if( !t_existingfilename )
		return result;

	t_newfilename = tstring_from_utf8(newfilename);
	if( !t_newfilename ) {
		free(t_existingfilename);
		return result;
	}

	result = MoveFile(t_existingfilename, t_newfilename);

	osd_free(t_newfilename);
	osd_free(t_existingfilename);

	return result;
}


=======
	auto t_string = osd::text::to_tstring(string);
	OutputDebugString(t_string.c_str());
}


#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
>>>>>>> upstream/master

//============================================================
//  win_message_box_utf8
//============================================================

int win_message_box_utf8(HWND window, const char *text, const char *caption, UINT type)
{
<<<<<<< HEAD
	int result = IDNO;
	TCHAR *t_text = NULL;
	TCHAR *t_caption = NULL;

	if (text)
	{
		t_text = tstring_from_utf8(text);
		if (!t_text)
			goto done;
=======
	LPCTSTR t_text = nullptr;
	LPCTSTR t_caption = nullptr;
	std::basic_string<TCHAR> ts_text;
	std::basic_string<TCHAR> ts_caption;

	if (text)
	{
		ts_text = osd::text::to_tstring(text);
		t_text = ts_text.c_str();
>>>>>>> upstream/master
	}

	if (caption)
	{
<<<<<<< HEAD
		t_caption = tstring_from_utf8(caption);
		if (!t_caption)
			goto done;
	}

	result = MessageBox(window, t_text, t_caption, type);

done:
	if (t_text)
		osd_free(t_text);
	if (t_caption)
		osd_free(t_caption);
	return result;
}

=======
		ts_caption = osd::text::to_tstring(caption);
		t_caption = ts_caption.c_str();
	}

	return MessageBox(window, t_text, t_caption, type);
}

#endif

>>>>>>> upstream/master


//============================================================
//  win_set_window_text_utf8
//============================================================

BOOL win_set_window_text_utf8(HWND window, const char *text)
{
	BOOL result = FALSE;
<<<<<<< HEAD
	TCHAR *t_text = NULL;

	if (text)
	{
		t_text = tstring_from_utf8(text);
		if (!t_text)
			goto done;
	}

	result = SetWindowText(window, t_text);

done:
	if (t_text)
		osd_free(t_text);
=======
	LPCTSTR t_text = nullptr;
	std::basic_string<TCHAR> ts_text;

	if (text)
	{
		ts_text = osd::text::to_tstring(text);
		t_text = ts_text.c_str();
	}

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	result = SetWindowText(window, t_text);
#else
	Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->Title = ref new Platform::String(t_text);
	result = TRUE;
#endif

>>>>>>> upstream/master
	return result;
}



//============================================================
//  win_get_window_text_utf8
//============================================================

<<<<<<< HEAD
int win_get_window_text_utf8(HWND window, char *buffer, size_t buffer_size)
{
	int result = 0;
	char *utf8_buffer = NULL;
	TCHAR t_buffer[256];

	t_buffer[0] = '\0';

	// invoke the core Win32 API
	GetWindowText(window, t_buffer, ARRAY_LENGTH(t_buffer));

	utf8_buffer = utf8_from_tstring(t_buffer);
	if (!utf8_buffer)
		goto done;

	result = snprintf(buffer, buffer_size, "%s", utf8_buffer);

done:
	if (utf8_buffer)
		osd_free(utf8_buffer);
	return result;
}


=======
std::string win_get_window_text_utf8(HWND window)
{
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	{
		// invoke the core Win32 API
		int length = GetWindowTextLength(window);
		if (length <= 0)
			return std::string();

		TCHAR *buffer = (TCHAR *) alloca((length + 1) * sizeof(TCHAR));
		GetWindowText(window, buffer, length + 1);
		return osd::text::from_tstring(buffer);
	}
#else
	{
		TCHAR t_buffer[256];
		auto title = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->Title;
		wcsncpy(t_buffer, title->Data(), ARRAY_LENGTH(t_buffer));
		return osd::text::from_tstring(t_buffer);
	}
#endif
}


#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
>>>>>>> upstream/master

//============================================================
//  win_create_window_ex_utf8
//============================================================

HWND win_create_window_ex_utf8(DWORD exstyle, const char* classname, const char* windowname, DWORD style,
								int x, int y, int width, int height, HWND parent, HMENU menu,
								HINSTANCE instance, void* param)
{
<<<<<<< HEAD
	TCHAR* t_classname;
	TCHAR* t_windowname = NULL;
	HWND result = 0;

	t_classname = tstring_from_utf8(classname);
	if( !t_classname )
		return result;

	if( windowname ) {
		t_windowname = tstring_from_utf8(windowname);
		if( !t_windowname ) {
			osd_free(t_classname);
			return result;
		}
	}

	result = CreateWindowEx(exstyle, t_classname, t_windowname, style, x, y, width, height, parent,
							menu, instance, param);

	if( t_windowname )
		osd_free(t_windowname);
	osd_free(t_classname);

	return result;
}
=======
	std::basic_string<TCHAR> ts_classname = osd::text::to_tstring(classname);

	LPCTSTR t_windowname = nullptr;
	std::basic_string<TCHAR> ts_windowname;
	if (windowname != nullptr)
	{
		ts_windowname = osd::text::to_tstring(windowname);
		t_windowname = ts_windowname.c_str();
	}

	return CreateWindowEx(exstyle, ts_classname.c_str(), t_windowname, style, x, y, width, height, parent,
		menu, instance, param);
}

#endif
>>>>>>> upstream/master
