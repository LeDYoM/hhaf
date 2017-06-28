#include "../mtypes/include/str.hpp"
#include <sstream>
#include <string>

namespace lib
{
    str::str(std::string &&source) noexcept : str(source.c_str()) {}
	str::str(const std::string &source) noexcept : str(source.c_str()) {}
	str::str(str &&source) noexcept : m_data{ std::move(source.m_data) } {}

	str::str(const unsigned int n) : str{ std::to_string(n).c_str() } {}
	str::str(const signed int n) : str{ std::to_string(n).c_str() } {}
	str::str(const float n) : str{ std::to_string(n) } {}
	str::str(const double n) : str{ std::to_string(n) } {}

	str & str::operator=(const str &source)
	{
		m_data = source.m_data;
		return *this;
	}
	str & str::operator=(str &&source) noexcept
	{
		m_data = std::move(source.m_data);
		return *this;
	}

	str::str(const char c) { m_data.push_back(c); }

	str::str(const str & n) : m_data{ n.m_data } {}
	str::str(const char * n) 
	{
		while (const char_type c{ *n }) {
			m_data.push_back(c);
			++n;
		}
		m_data.push_back(0);
	}

	vector<str> str::split(const char separator) const
	{
		vector<str> result;
		std::stringstream ss((*this).c_str());
		std::string tok;

		while (std::getline(ss, tok, separator)) {
			result.push_back(std::move(tok));
		}
		return result;
	}
	str & str::append(const unsigned int n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const signed int n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const char c)
	{
		m_data.push_back(c);
		return *this;
	}
	str & str::append(const str & n)
	{
		m_data.insert(n.m_data);
		return *this;
	}
	str & str::append(const char * n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const float n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const double n)
	{
		append(str(n));
		return *this;
	}
}
