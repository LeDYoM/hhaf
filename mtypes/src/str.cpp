#include "../mtypes/include/str.hpp"
#include <sstream>
#include <string>

namespace lib
{
	str::str(const u32  n) : str{ std::to_string(n).c_str() } {}
	str::str(const s32 n) : str{ std::to_string(n).c_str() } {}
	str::str(const f32 n) : str{ std::to_string(n).c_str() } {}
	str::str(const f64 n) : str{ std::to_string(n).c_str() } {}

	namespace detail
	{
		constexpr size_t _str_len(const char_type *const p_str) noexcept
		{
			const char_type *p_str_copy{ p_str };
			while (*p_str_copy) ++p_str_copy;
			return p_str_copy - p_str;
		}
	}
	str::str(const char_type * n) noexcept : m_data(n, detail::_str_len(n) + 1) {}

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

	vector<str> str::split(const char_type separator) const
	{
		vector<str> result;
		std::stringstream ss((*this).c_str());
		std::string tok;

		while (std::getline(ss, tok, separator)) {
			result.push_back(tok.c_str());
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
		m_data.pop_back();
		m_data.push_back(c);
		m_data.push_back(0);
		return *this;
	}
	str & str::append(const str & n)
	{
		m_data.pop_back();
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
	void str::convert(u32 & n) const
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(s32 & n) const
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(f32 & n) const
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
	void str::convert(f64 & n) const
	{
		std::istringstream tmpstream(c_str());
		tmpstream >> n;
	}
}
