// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * pparser.c
 *
 */

<<<<<<< HEAD
#include <cstdarg>

#include "pparser.h"

=======
#include "pparser.h"
#include "palloc.h"
#include "putil.h"

#include <cstdarg>

namespace plib {
>>>>>>> upstream/master
// ----------------------------------------------------------------------------------------
// A simple tokenizer
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
=======
ptokenizer::ptokenizer(plib::putf8_reader &strm)
: m_strm(strm), m_lineno(0), m_cur_line(""), m_px(m_cur_line.begin()), m_unget(0), m_string('"')
{
}

ptokenizer::~ptokenizer()
{
}


>>>>>>> upstream/master
pstring ptokenizer::currentline_str()
{
	return m_cur_line;
}


void ptokenizer::skipeol()
{
	pstring::code_t c = getc();
	while (c)
	{
		if (c == 10)
		{
			c = getc();
			if (c != 13)
<<<<<<< HEAD
				ungetc();
=======
				ungetc(c);
>>>>>>> upstream/master
			return;
		}
		c = getc();
	}
}


pstring::code_t ptokenizer::getc()
{
<<<<<<< HEAD
	if (m_px >= m_cur_line.len())
	{
		if (m_strm.readline(m_cur_line))
		{
			m_cur_line += "\n";
			m_px = 0;
		}
		else
			return 0;
	}
	return m_cur_line.code_at(m_px++);
}

void ptokenizer::ungetc()
{
	m_px--;
=======
	if (m_unget != 0)
	{
		pstring::code_t c = m_unget;
		m_unget = 0;
		return c;
	}
	if (m_px == m_cur_line.end())
	{
		m_lineno++;
		if (m_strm.readline(m_cur_line))
			m_px = m_cur_line.begin();
		else
			return 0;
		return '\n';
	}
	pstring::code_t c = *(m_px++);
	return c;
}

void ptokenizer::ungetc(pstring::code_t c)
{
	m_unget = c;
>>>>>>> upstream/master
}

void ptokenizer::require_token(const token_id_t &token_num)
{
	require_token(get_token(), token_num);
}

<<<<<<< HEAD
void ptokenizer::require_token(const token_t tok, const token_id_t &token_num)
{
	if (!tok.is(token_num))
	{
		error(pfmt("Expected token <{1}> got <{2}>")(m_tokens[token_num.id()])(tok.str()) );
=======
void ptokenizer::require_token(const token_t &tok, const token_id_t &token_num)
{
	if (!tok.is(token_num))
	{
		pstring val("");
		for (auto &i : m_tokens)
			if (i.second.id() == token_num.id())
				val = i.first;
		error(pfmt("Expected token <{1}> got <{2}>")(val)(tok.str()) );
>>>>>>> upstream/master
	}
}

pstring ptokenizer::get_string()
{
	token_t tok = get_token();
	if (!tok.is_type(STRING))
	{
		error(pfmt("Expected a string, got <{1}>")(tok.str()) );
	}
	return tok.str();
}

pstring ptokenizer::get_identifier()
{
	token_t tok = get_token();
	if (!tok.is_type(IDENTIFIER))
	{
		error(pfmt("Expected an identifier, got <{1}>")(tok.str()) );
	}
	return tok.str();
}

pstring ptokenizer::get_identifier_or_number()
{
	token_t tok = get_token();
	if (!(tok.is_type(IDENTIFIER) || tok.is_type(NUMBER)))
	{
<<<<<<< HEAD
		error(pfmt("Expected an identifier, got <{1}>")(tok.str()) );
=======
		error(pfmt("Expected an identifier or number, got <{1}>")(tok.str()) );
>>>>>>> upstream/master
	}
	return tok.str();
}

double ptokenizer::get_number_double()
{
	token_t tok = get_token();
	if (!tok.is_type(NUMBER))
	{
		error(pfmt("Expected a number, got <{1}>")(tok.str()) );
	}
	bool err = false;
	double ret = tok.str().as_double(&err);
	if (err)
		error(pfmt("Expected a number, got <{1}>")(tok.str()) );
	return ret;
}

long ptokenizer::get_number_long()
{
	token_t tok = get_token();
	if (!tok.is_type(NUMBER))
	{
		error(pfmt("Expected a long int, got <{1}>")(tok.str()) );
	}
	bool err = false;
	long ret = tok.str().as_long(&err);
	if (err)
		error(pfmt("Expected a long int, got <{1}>")(tok.str()) );
	return ret;
}

ptokenizer::token_t ptokenizer::get_token()
{
	while (true)
	{
		token_t ret = get_token_internal();
		if (ret.is_type(ENDOFFILE))
			return ret;

		if (ret.is(m_tok_comment_start))
		{
			do {
				ret = get_token_internal();
			} while (ret.is_not(m_tok_comment_end));
		}
		else if (ret.is(m_tok_line_comment))
		{
			skipeol();
		}
		else if (ret.str() == "#")
		{
			skipeol();
		}
		else
		{
			return ret;
		}
	}
}

ptokenizer::token_t ptokenizer::get_token_internal()
{
	/* skip ws */
	pstring::code_t c = getc();
<<<<<<< HEAD
	while (m_whitespace.find(c)>=0)
=======
	while (m_whitespace.find(c) != pstring::npos)
>>>>>>> upstream/master
	{
		c = getc();
		if (eof())
		{
			return token_t(ENDOFFILE);
		}
	}
<<<<<<< HEAD
	if (m_number_chars_start.find(c)>=0)
=======
	if (m_number_chars_start.find(c) != pstring::npos)
>>>>>>> upstream/master
	{
		/* read number while we receive number or identifier chars
		 * treat it as an identifier when there are identifier chars in it
		 *
		 */
		token_type ret = NUMBER;
		pstring tokstr = "";
		while (true) {
<<<<<<< HEAD
			if (m_identifier_chars.find(c)>=0 && m_number_chars.find(c)<0)
				ret = IDENTIFIER;
			else if (m_number_chars.find(c)<0)
=======
			if (m_identifier_chars.find(c) != pstring::npos && m_number_chars.find(c) == pstring::npos)
				ret = IDENTIFIER;
			else if (m_number_chars.find(c) == pstring::npos)
>>>>>>> upstream/master
				break;
			tokstr += c;
			c = getc();
		}
<<<<<<< HEAD
		ungetc();
		return token_t(ret, tokstr);
	}
	else if (m_identifier_chars.find(c)>=0)
	{
		/* read identifier till non identifier char */
		pstring tokstr = "";
		while (m_identifier_chars.find(c)>=0) {
			tokstr += c;
			c = getc();
		}
		ungetc();
		token_id_t id = token_id_t(m_tokens.indexof(tokstr));
		if (id.id() >= 0)
			return token_t(id, tokstr);
		else
		{
			return token_t(IDENTIFIER, tokstr);
		}
=======
		ungetc(c);
		return token_t(ret, tokstr);
	}
	else if (m_identifier_chars.find(c) != pstring::npos)
	{
		/* read identifier till non identifier char */
		pstring tokstr = "";
		while (m_identifier_chars.find(c) != pstring::npos)
		{
			tokstr += c;
			c = getc();
		}
		ungetc(c);
		auto id = m_tokens.find(tokstr);
		if (id != m_tokens.end())
			return token_t(id->second, tokstr);
		else
			return token_t(IDENTIFIER, tokstr);
>>>>>>> upstream/master
	}
	else if (c == m_string)
	{
		pstring tokstr = "";
		c = getc();
		while (c != m_string)
		{
			tokstr += c;
			c = getc();
		}
		return token_t(STRING, tokstr);
	}
	else
	{
		/* read identifier till first identifier char or ws */
		pstring tokstr = "";
<<<<<<< HEAD
		while ((m_identifier_chars.find(c)) < 0 && (m_whitespace.find(c) < 0)) {
			tokstr += c;
			/* expensive, check for single char tokens */
			if (tokstr.len() == 1)
			{
				token_id_t id = token_id_t(m_tokens.indexof(tokstr));
				if (id.id() >= 0)
					return token_t(id, tokstr);
			}
			c = getc();
		}
		ungetc();
		token_id_t id = token_id_t(m_tokens.indexof(tokstr));
		if (id.id() >= 0)
			return token_t(id, tokstr);
		else
		{
			return token_t(UNKNOWN, tokstr);
		}
	}

}

ATTR_COLD void ptokenizer::error(const pstring &errs)
{
	verror("Error: " + errs, currentline_no(), currentline_str());
=======
		while ((m_identifier_chars.find(c) == pstring::npos) && (m_whitespace.find(c) == pstring::npos))
		{
			tokstr += c;
			/* expensive, check for single char tokens */
			if (tokstr.length() == 1)
			{
				auto id = m_tokens.find(tokstr);
				if (id != m_tokens.end())
					return token_t(id->second, tokstr);
			}
			c = getc();
		}
		ungetc(c);
		auto id = m_tokens.find(tokstr);
		if (id != m_tokens.end())
			return token_t(id->second, tokstr);
		else
			return token_t(UNKNOWN, tokstr);
	}
}

void ptokenizer::error(const pstring &errs)
{
	verror(errs, currentline_no(), currentline_str());
>>>>>>> upstream/master
	//throw error;
}

// ----------------------------------------------------------------------------------------
// A simple preprocessor
// ----------------------------------------------------------------------------------------

<<<<<<< HEAD
ppreprocessor::ppreprocessor()
: m_ifflag(0), m_level(0), m_lineno(0)
{
	m_expr_sep.add("!");
	m_expr_sep.add("(");
	m_expr_sep.add(")");
	m_expr_sep.add("+");
	m_expr_sep.add("-");
	m_expr_sep.add("*");
	m_expr_sep.add("/");
	m_expr_sep.add("==");
	m_expr_sep.add(" ");
	m_expr_sep.add("\t");

	m_defines.add("__PLIB_PREPROCESSOR__", define_t("__PLIB_PREPROCESSOR__", "1"));
=======
ppreprocessor::ppreprocessor(std::vector<define_t> *defines)
: m_ifflag(0), m_level(0), m_lineno(0)
{
	m_expr_sep.push_back("!");
	m_expr_sep.push_back("(");
	m_expr_sep.push_back(")");
	m_expr_sep.push_back("+");
	m_expr_sep.push_back("-");
	m_expr_sep.push_back("*");
	m_expr_sep.push_back("/");
	m_expr_sep.push_back("==");
	m_expr_sep.push_back(" ");
	m_expr_sep.push_back("\t");

	m_defines.insert({"__PLIB_PREPROCESSOR__", define_t("__PLIB_PREPROCESSOR__", "1")});
	if (defines != nullptr)
	{
		for (auto & p : *defines)
		{
			m_defines.insert({p.m_name, p});
		}
	}
>>>>>>> upstream/master
}

void ppreprocessor::error(const pstring &err)
{
	throw pexception("PREPRO ERROR: " + err);
}



<<<<<<< HEAD
double ppreprocessor::expr(const pstring_list_t &sexpr, std::size_t &start, int prio)
=======
double ppreprocessor::expr(const std::vector<pstring> &sexpr, std::size_t &start, int prio)
>>>>>>> upstream/master
{
	double val;
	pstring tok=sexpr[start];
	if (tok == "(")
	{
		start++;
		val = expr(sexpr, start, /*prio*/ 0);
		if (sexpr[start] != ")")
			error("parsing error!");
		start++;
	}
	else if (tok == "!")
	{
		start++;
		val = expr(sexpr, start, 90);
		if (val != 0)
			val = 0;
		else
			val = 1;
	}
	else
	{
		tok=sexpr[start];
		val = tok.as_double();
		start++;
	}
	while (start < sexpr.size())
	{
		tok=sexpr[start];
		if (tok == ")")
		{
			// FIXME: catch error
			return val;
		}
		else if (tok == "+")
		{
			if (prio > 10)
				return val;
			start++;
			val = val + expr(sexpr, start, 10);
		}
		else if (tok == "-")
		{
			if (prio > 10)
				return val;
			start++;
			val = val - expr(sexpr, start, 10);
		}
		else if (tok == "*")
		{
			start++;
			val = val * expr(sexpr, start, 20);
		}
		else if (tok == "/")
		{
			start++;
			val = val / expr(sexpr, start, 20);
		}
		else if (tok == "==")
		{
			if (prio > 5)
				return val;
			start++;
			val = (val == expr(sexpr, start, 5)) ? 1.0 : 0.0;
		}
	}
	return val;
}

ppreprocessor::define_t *ppreprocessor::get_define(const pstring &name)
{
<<<<<<< HEAD
	int idx = m_defines.index_of(name);
	if (idx >= 0)
		return &m_defines.value_at(idx);
	else
		return NULL;
=======
	auto idx = m_defines.find(name);
	if (idx != m_defines.end())
		return &idx->second;
	else
		return nullptr;
>>>>>>> upstream/master
}

pstring ppreprocessor::replace_macros(const pstring &line)
{
<<<<<<< HEAD
	pstring_list_t elems = pstring_list_t::splitexpr(line, m_expr_sep);
	pstringbuffer ret = "";
	for (std::size_t i=0; i<elems.size(); i++)
	{
		define_t *def = get_define(elems[i]);
		if (def != NULL)
			ret.cat(def->m_replace);
		else
			ret.cat(elems[i]);
=======
	std::vector<pstring> elems(psplit(line, m_expr_sep));
	pstring ret("");
	for (auto & elem : elems)
	{
		define_t *def = get_define(elem);
		if (def != nullptr)
			ret += def->m_replace;
		else
			ret += elem;
>>>>>>> upstream/master
	}
	return ret;
}

<<<<<<< HEAD
static pstring catremainder(const pstring_list_t &elems, std::size_t start, pstring sep)
{
	pstringbuffer ret = "";
	for (std::size_t i=start; i<elems.size(); i++)
	{
		ret.cat(elems[i]);
		ret.cat(sep);
=======
static pstring catremainder(const std::vector<pstring> &elems, std::size_t start, pstring sep)
{
	pstring ret("");
	for (auto & elem : elems)
	{
		ret += elem;
		ret += sep;
>>>>>>> upstream/master
	}
	return ret;
}

pstring  ppreprocessor::process_line(const pstring &line)
{
<<<<<<< HEAD
	pstring lt = line.replace("\t"," ").trim();
	pstringbuffer ret;
=======
	pstring lt = line.replace_all("\t"," ").trim();
	pstring ret;
>>>>>>> upstream/master
	m_lineno++;
	// FIXME ... revise and extend macro handling
	if (lt.startsWith("#"))
	{
<<<<<<< HEAD
		pstring_list_t lti(lt, " ", true);
=======
		std::vector<pstring> lti(psplit(lt, " ", true));
>>>>>>> upstream/master
		if (lti[0].equals("#if"))
		{
			m_level++;
			std::size_t start = 0;
			lt = replace_macros(lt);
<<<<<<< HEAD
			pstring_list_t t = pstring_list_t::splitexpr(lt.substr(3).replace(" ",""), m_expr_sep);
			int val = expr(t, start, 0);
=======
			std::vector<pstring> t(psplit(lt.substr(3).replace_all(" ",""), m_expr_sep));
			int val = static_cast<int>(expr(t, start, 0));
>>>>>>> upstream/master
			if (val == 0)
				m_ifflag |= (1 << m_level);
		}
		else if (lti[0].equals("#ifdef"))
		{
			m_level++;
<<<<<<< HEAD
			if (get_define(lti[1]) == NULL)
=======
			if (get_define(lti[1]) == nullptr)
>>>>>>> upstream/master
				m_ifflag |= (1 << m_level);
		}
		else if (lti[0].equals("#ifndef"))
		{
			m_level++;
<<<<<<< HEAD
			if (get_define(lti[1]) != NULL)
=======
			if (get_define(lti[1]) != nullptr)
>>>>>>> upstream/master
				m_ifflag |= (1 << m_level);
		}
		else if (lti[0].equals("#else"))
		{
			m_ifflag ^= (1 << m_level);
		}
		else if (lti[0].equals("#endif"))
		{
			m_ifflag &= ~(1 << m_level);
			m_level--;
		}
		else if (lti[0].equals("#include"))
		{
			// ignore
		}
		else if (lti[0].equals("#pragma"))
		{
			if (m_ifflag == 0 && lti.size() > 3 && lti[1].equals("NETLIST"))
			{
				if (lti[2].equals("warning"))
					error("NETLIST: " + catremainder(lti, 3, " "));
			}
		}
		else if (lti[0].equals("#define"))
		{
			if (m_ifflag == 0)
			{
				if (lti.size() != 3)
					error("PREPRO: only simple defines allowed: " + line);
<<<<<<< HEAD
				m_defines.add(lti[1], define_t(lti[1], lti[2]));
=======
				m_defines.insert({lti[1], define_t(lti[1], lti[2])});
>>>>>>> upstream/master
			}
		}
		else
			error(pfmt("unknown directive on line {1}: {2}")(m_lineno)(line));
	}
	else
	{
		lt = replace_macros(lt);
		if (m_ifflag == 0)
		{
<<<<<<< HEAD
			ret.cat(lt);
			ret.cat("\n");
=======
			ret += lt;
>>>>>>> upstream/master
		}
	}
	return ret;
}


<<<<<<< HEAD
postream & ppreprocessor::process_i(pistream &istrm, postream &ostrm)
=======
void ppreprocessor::process(putf8_reader &istrm, putf8_writer &ostrm)
>>>>>>> upstream/master
{
	pstring line;
	while (istrm.readline(line))
	{
		line = process_line(line);
		ostrm.writeline(line);
	}
<<<<<<< HEAD
	return ostrm;
=======
}

>>>>>>> upstream/master
}
