// license:BSD-3-Clause
<<<<<<< HEAD
// copyright-holders:Nicola Salmoria, Aaron Giles
=======
// copyright-holders:Nicola Salmoria, Aaron Giles, Vas Crabb
>>>>>>> upstream/master
/***************************************************************************

    output.h

    General purpose output routines.
***************************************************************************/

#pragma once

#ifndef __EMU_H__
#error Dont include this file directly; include emu.h instead.
#endif

<<<<<<< HEAD
#ifndef __OUTPUT_H__
#define __OUTPUT_H__
=======
#ifndef MAME_EMU_OUTPUT_H
#define MAME_EMU_OUTPUT_H
>>>>>>> upstream/master


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

<<<<<<< HEAD
typedef void (*output_notifier_func)(const char *outname, INT32 value, void *param);



/***************************************************************************
    FUNCTION PROTOTYPES
***************************************************************************/

/* core initialization */
void output_init(running_machine &machine);

/* set the value for a given output */
void output_set_value(const char *outname, INT32 value);

/* set an indexed value for an output (concatenates basename + index) */
void output_set_indexed_value(const char *basename, int index, int value);

/* return the current value for a given output */
INT32 output_get_value(const char *outname);

/* return the current value for a given indexed output */
INT32 output_get_indexed_value(const char *outname, int index);

/* set a notifier on a particular output, or globally if NULL */
void output_set_notifier(const char *outname, output_notifier_func callback, void *param);

/* set a notifier on a particular output, or globally if NULL */
void output_notify_all(output_notifier_func callback, void *param);

/* map a name to a unique ID */
UINT32 output_name_to_id(const char *outname);

/* map a unique ID back to a name */
const char *output_id_to_name(UINT32 id);



/***************************************************************************
    INLINES
***************************************************************************/

INLINE void output_set_led_value(int index, int value)
{
	output_set_indexed_value("led", index, value ? 1 : 0);
}

INLINE void output_set_lamp_value(int index, int value)
{
	output_set_indexed_value("lamp", index, value);
}

INLINE void output_set_digit_value(int index, int value)
{
	output_set_indexed_value("digit", index, value);
}


INLINE INT32 output_get_led_value(int index)
{
	return output_get_indexed_value("led", index);
}

INLINE INT32 output_get_lamp_value(int index)
{
	return output_get_indexed_value("lamp", index);
}

INLINE INT32 output_get_digit_value(int index)
{
	return output_get_indexed_value("digit", index);
}


#endif  /* __OUTPUT_H__ */
=======
typedef void (*output_notifier_func)(const char *outname, s32 value, void *param);

// ======================> output_manager

class output_manager
{
private:
	class output_notify
	{
	public:
		output_notify(output_notifier_func callback, void *param)
			: m_notifier(callback)
			, m_param(param)
		{
		}

		void operator()(char const *outname, s32 value) const { m_notifier(outname, value, m_param); }

	private:
		output_notifier_func    m_notifier;       // callback to call
		void *                  m_param;          // parameter to pass the callback
	};
	using notify_vector = std::vector<output_notify>;

	class output_item
	{
	public:
		output_item(output_item &&) = delete;
		output_item(output_item const &) = delete;
		output_item &operator=(output_item &&) = delete;
		output_item &operator=(output_item const &) = delete;

		output_item(
				output_manager &manager,
				std::string &&name,
				u32 id,
				s32 value);

		std::string const &name() const { return m_name; }
		u32 id() const { return m_id; }
		s32 get() const { return m_value; }
		void set(s32 value) { if (m_value != value) { notify(value); } }
		void notify(s32 value);

		void set_notifier(output_notifier_func callback, void *param) { m_notifylist.emplace_back(callback, param); }

	private:
		output_manager      &m_manager;     // parent output manager
		std::string const   m_name;         // string name of the item
		u32 const           m_id;           // unique ID for this item
		s32                 m_value;        // current value
		notify_vector       m_notifylist;   // list of notifier callbacks
	};

	class item_proxy
	{
	public:
		item_proxy() = default;
		void resolve(device_t &device, std::string const &name);
		operator s32() const { return m_item->get(); }
		s32 operator=(s32 value) { m_item->set(value); return m_item->get(); }
	private:
		output_item *m_item = nullptr;
	};
	template <unsigned M, unsigned... N> struct item_proxy_array { typedef typename item_proxy_array<N...>::type type[M]; };
	template <unsigned N> struct item_proxy_array<N> { typedef item_proxy type[N]; };
	template <unsigned... N> using item_proxy_array_t = typename item_proxy_array<N...>::type;

public:
	template <typename X, unsigned... N> class output_finder
	{
	public:
		template <typename... T> output_finder(device_t &device, std::string &&format, T &&... start_args)
			: m_device(device)
			, m_format(std::move(format))
			, m_start_args{ std::forward<T>(start_args)... }
		{
		}

		auto &operator[](unsigned n) { return m_proxies[n]; }
		auto &operator[](unsigned n) const { return m_proxies[n]; }

		void resolve() { resolve<0U>(m_proxies); }

	private:
		template <unsigned A, unsigned C, typename... T>
		void resolve(item_proxy (&proxies)[C], T &&... i)
		{
			for (unsigned j = 0U; C > j; ++j)
				proxies[j].resolve(m_device, util::string_format(m_format, std::forward<T>(i)..., j + m_start_args[A]));
		}

		template <unsigned A, unsigned C, unsigned D, typename T, typename... U>
		void resolve(T (&proxies)[C][D], U &&... i)
		{
			for (unsigned j = 0U; C > j; ++j)
				resolve<A + 1>(proxies[j], std::forward<U>(i)..., j + m_start_args[A]);
		}

		device_t                    &m_device;
		std::string const           m_format;
		unsigned const              m_start_args[sizeof...(N)];
		item_proxy_array_t<N...>    m_proxies;
	};

	template <typename X> class output_finder<X>
	{
	public:
		output_finder(device_t &device, std::string &&format)
			: m_device(device)
			, m_format(std::move(format))
		{
		}

		operator s32() const { return m_proxy; }
		s32 operator=(s32 value) { return m_proxy = value; }

		void resolve() { m_proxy.resolve(m_device, m_format); }

	private:
		device_t            &m_device;
		std::string const   m_format;
		item_proxy          m_proxy;
	};

	// construction/destruction
	output_manager(running_machine &machine);

	// getters
	running_machine &machine() const { return m_machine; }

	// set the value for a given output
	void set_value(const char *outname, s32 value);

	// set an indexed value for an output (concatenates basename + index)
	void set_indexed_value(const char *basename, int index, int value);

	// return the current value for a given output
	s32 get_value(const char *outname);

	// return the current value for a given indexed output
	s32 get_indexed_value(const char *outname, int index);

	// set a notifier on a particular output, or globally if nullptr
	void set_notifier(const char *outname, output_notifier_func callback, void *param);

	// set a notifier on a particular output, or globally if nullptr
	void notify_all(output_module *module);

	// map a name to a unique ID
	u32 name_to_id(const char *outname);

	// map a unique ID back to a name
	const char *id_to_name(u32 id);


	// helpers
	void set_led_value(int index, int value) { set_indexed_value("led", index, value ? 1 : 0); }
	void set_lamp_value(int index, int value) { set_indexed_value("lamp", index, value); }
	void set_digit_value(int index, int value) { set_indexed_value("digit", index, value); }
	s32 get_led_value(int index) { return get_indexed_value("led", index); }
	s32 get_lamp_value(int index) { return get_indexed_value("lamp", index); }
	s32 get_digit_value(int index) { return get_indexed_value("digit", index); }

	void pause();
	void resume();
private:
	output_item *find_item(const char *string);
	output_item &create_new_item(const char *outname, s32 value);

	// internal state
	running_machine &m_machine;                  // reference to our machine
	std::unordered_map<std::string, output_item> m_itemtable;
	notify_vector m_global_notifylist;
	u32 m_uniqueid;
};

template <unsigned... N> using output_finder = output_manager::output_finder<void, N...>;

#endif  // MAME_EMU_OUTPUT_H
>>>>>>> upstream/master
