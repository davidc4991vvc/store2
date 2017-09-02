// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * poptions.h
 *
 */

#pragma once

#ifndef POPTIONS_H_
#define POPTIONS_H_

<<<<<<< HEAD
#include <cstddef>

#include "pstring.h"
#include "plists.h"

=======
#include "pstring.h"
#include "plists.h"
#include "putil.h"

namespace plib {
>>>>>>> upstream/master
/***************************************************************************
    Options
***************************************************************************/

<<<<<<< HEAD
class poptions;

class poption
{
public:
	poption()
	: m_short(""), m_long(""), m_help(""), m_has_argument(false)
	{}

	poption(pstring ashort, pstring along, pstring help, bool has_argument, poptions *parent = NULL);

	virtual ~poption()
	{
	}

	/* no_argument options will be called with "" argument */

	virtual int parse(ATTR_UNUSED pstring argument) { return 0; }

	pstring m_short;
	pstring m_long;
	pstring m_help;
	bool m_has_argument;
private:
};

class poption_str : public poption
{
public:
	poption_str(pstring ashort, pstring along, pstring defval, pstring help, poptions *parent = NULL)
	: poption(ashort, along, help, true, parent), m_val(defval)
	{}

	virtual int parse(pstring argument) { m_val = argument; return 0; }

	pstring operator ()() { return m_val; }
=======
class options;

class option_base
{
public:
	option_base(options &parent, pstring help);
	virtual ~option_base();

	pstring help() { return m_help; }
private:
	pstring m_help;
};

class option_group : public option_base
{
public:
	option_group(options &parent, pstring group, pstring help)
	: option_base(parent, help), m_group(group) { }
	~option_group();

	pstring group() { return m_group; }
private:
	pstring m_group;
};

class option_example : public option_base
{
public:
	option_example(options &parent, pstring group, pstring help)
	: option_base(parent, help), m_example(group) { }
	~option_example();

	pstring example() { return m_example; }
private:
	pstring m_example;
};


class option : public option_base
{
public:
	option(options &parent, pstring ashort, pstring along, pstring help, bool has_argument);
	~option();

	/* no_argument options will be called with "" argument */

	pstring short_opt() { return m_short; }
	pstring long_opt() { return m_long; }
	bool has_argument() { return m_has_argument ; }
	bool was_specified() { return m_specified; }

	int do_parse(const pstring &argument)
	{
		m_specified = true;
		return parse(argument);
	}

protected:
	virtual int parse(const pstring &argument) = 0;

private:
	pstring m_short;
	pstring m_long;
	bool m_has_argument;
	bool m_specified;
};

class option_str : public option
{
public:
	option_str(options &parent, pstring ashort, pstring along, pstring defval, pstring help)
	: option(parent, ashort, along, help, true), m_val(defval)
	{}

	pstring operator ()() { return m_val; }

protected:
	virtual int parse(const pstring &argument) override;

>>>>>>> upstream/master
private:
	pstring m_val;
};

<<<<<<< HEAD
class poption_str_limit : public poption
{
public:
	poption_str_limit(pstring ashort, pstring along, pstring defval, pstring limit, pstring help, poptions *parent = NULL)
	: poption(ashort, along, help, true, parent), m_val(defval), m_limit(limit, ":")
	{}

	virtual int parse(pstring argument)
	{
		if (m_limit.contains(argument))
		{
			m_val = argument;
			return 0;
		}
		else
			return 1;
	}

	pstring operator ()() { return m_val; }
private:
	pstring m_val;
	pstring_list_t m_limit;
};

class poption_bool : public poption
{
public:
	poption_bool(pstring ashort, pstring along, pstring help, poptions *parent = NULL)
	: poption(ashort, along, help, false, parent), m_val(false)
	{}

	virtual int parse(ATTR_UNUSED pstring argument) { m_val = true; return 0; }

	bool operator ()() { return m_val; }
=======
class option_str_limit : public option
{
public:
	option_str_limit(options &parent, pstring ashort, pstring along, pstring defval, pstring limit, pstring help)
	: option(parent, ashort, along, help, true), m_val(defval)
	, m_limit(plib::psplit(limit, ":"))
	{
	}

	pstring operator ()() { return m_val; }
	const std::vector<pstring> &limit() { return m_limit; }

protected:
	virtual int parse(const pstring &argument) override;

private:
	pstring m_val;
	std::vector<pstring> m_limit;
};

class option_bool : public option
{
public:
	option_bool(options &parent, pstring ashort, pstring along, pstring help)
	: option(parent, ashort, along, help, false), m_val(false)
	{}

	bool operator ()() { return m_val; }

protected:
	virtual int parse(const pstring &argument) override;

>>>>>>> upstream/master
private:
	bool m_val;
};

<<<<<<< HEAD
class poption_double : public poption
{
public:
	poption_double(pstring ashort, pstring along, double defval, pstring help, poptions *parent = NULL)
	: poption(ashort, along, help, true, parent), m_val(defval)
	{}

	virtual int parse(pstring argument)
	{
		bool err = false;
		m_val = argument.as_double(&err);
		return (err ? 1 : 0);
	}

	double operator ()() { return m_val; }
=======
class option_double : public option
{
public:
	option_double(options &parent, pstring ashort, pstring along, double defval, pstring help)
	: option(parent, ashort, along, help, true), m_val(defval)
	{}

	double operator ()() { return m_val; }

protected:
	virtual int parse(const pstring &argument) override;

>>>>>>> upstream/master
private:
	double m_val;
};

<<<<<<< HEAD
class poptions
{
public:

	poptions() {}

	poptions(poption *o[])
	{
		int i=0;
		while (o[i] != NULL)
		{
			m_opts.add(o[i]);
			i++;
		}
	}

	~poptions()
	{
		m_opts.clear();
	}

	void register_option(poption *opt)
	{
		m_opts.add(opt);
	}

	int parse(int argc, char *argv[])
	{
		m_app = argv[0];

		for (int i=1; i<argc; )
		{
			pstring arg(argv[i]);
			poption *opt = NULL;

			if (arg.startsWith("--"))
			{
				opt = getopt_long(arg.substr(2));
			}
			else if (arg.startsWith("-"))
			{
				opt = getopt_short(arg.substr(1));
			}
			else
				return i;
			if (opt == NULL)
				return i;
			if (opt->m_has_argument)
			{
				i++; // FIXME: are there more arguments?
				if (opt->parse(argv[i]) != 0)
					return i - 1;
			}
			else
				opt->parse("");
			i++;
		}
		return argc;
	}

	pstring help()
	{
		pstring ret;

		for (std::size_t i=0; i<m_opts.size(); i++ )
		{
			poption *opt = m_opts[i];
			pstring line = "";
			if (opt->m_short != "")
				line += "  -" + opt->m_short;
			if (opt->m_long != "")
			{
				if (line != "")
					line += ", ";
				else
					line = "     ";
				line += "--" + opt->m_long;
			}
			line = line.rpad(" ", 20).cat(opt->m_help);
			ret = ret + line + "\n";
		}
		return ret;
	}
	pstring app() { return m_app; }

private:

	poption *getopt_short(pstring arg)
	{
		for (std::size_t i=0; i < m_opts.size(); i++)
		{
			if (m_opts[i]->m_short == arg)
				return m_opts[i];
		}
		return NULL;
	}
	poption *getopt_long(pstring arg)
	{
		for (std::size_t i=0; i < m_opts.size(); i++)
		{
			if (m_opts[i]->m_long == arg)
				return m_opts[i];
		}
		return NULL;
	}

	plist_t<poption *> m_opts;
	pstring m_app;
};

poption::poption(pstring ashort, pstring along, pstring help, bool has_argument, poptions *parent)
: m_short(ashort), m_long(along), m_help(help), m_has_argument(has_argument)
{
	if (parent != NULL)
		parent->register_option(this);
}


=======
class option_long : public option
{
public:
	option_long(options &parent, pstring ashort, pstring along, long defval, pstring help)
	: option(parent, ashort, along, help, true), m_val(defval)
	{}

	long operator ()() { return m_val; }

protected:
	virtual int parse(const pstring &argument) override;

private:
	long m_val;
};

class option_vec : public option
{
public:
	option_vec(options &parent, pstring ashort, pstring along, pstring help)
	: option(parent, ashort, along, help, true)
	{}

	std::vector<pstring> operator ()() { return m_val; }

protected:
	virtual int parse(const pstring &argument) override;

private:
	std::vector<pstring> m_val;
};

class options
{
public:

	options();
	explicit options(option *o[]);

	~options();

	void register_option(option_base *opt);
	int parse(int argc, char *argv[]);

	pstring help(pstring description, pstring usage,
			unsigned width = 72, unsigned indent = 20);

	pstring app() { return m_app; }

private:
	static pstring split_paragraphs(pstring text, unsigned width, unsigned indent,
			unsigned firstline_indent);

	option *getopt_short(pstring arg);
	option *getopt_long(pstring arg);

	std::vector<option_base *> m_opts;
	pstring m_app;
};

}

>>>>>>> upstream/master
#endif /* POPTIONS_H_ */
