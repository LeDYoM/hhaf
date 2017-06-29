#include "../mtypes/include/str.hpp"
#include <sstream>
#include <string>

namespace lib
{
    str::str(std::string &&source) noexcept : str(source.c_str()) {}
	str::str(const std::string &source) noexcept : str(source.c_str()) {}
	str::str(str &&source) noexcept : m_data{ std::move(source.m_data) } {}

	str::str(const unsigned  n) : str{ std::to_string(n).c_str() } {}
	str::str(const s32 n) : str{ std::to_string(n).c_str() } {}
	str::str(const f32 n) : str{ std::to_string(n) } {}
	str::str(const f64 n) : str{ std::to_string(n) } {}

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

	str::str(const char_type c) { m_data.push_back(c); }

	str::str(const str & n) : m_data{ n.m_data } {}
	str::str(const char_type * n) 
	{
		while (const char_type c{ *n }) {
			m_data.push_back(c);
			++n;
		}
		m_data.push_back(0);
	}

	vector<str> str::split(const char_type separator) const
	{
		vector<str> result;
		std::stringstream ss((*this).c_str());
		std::string tok;

		while (std::getline(ss, tok, separator)) {
			result.push_back(std::move(tok));
		}
		return result;
	}
	str & str::append(const u32 n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const s32 n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const char_type c)
	{
		m_data.push_back(c);
		return *this;
	}
	str & str::append(const str & n)
	{
		m_data.insert(n.m_data);
		return *this;
	}
	str & str::append(const char_type * n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const f32 n)
	{
		append(str(n));
		return *this;
	}
	str & str::append(const f64 n)
	{
		append(str(n));
		return *this;
	}
	void str::convert(u32 & n)
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(s32 & n)
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(f32 & n)
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(f64 & n)
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
}
