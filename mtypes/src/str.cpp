#include "../mtypes/include/str.hpp"
#include <sstream>
#include <string>

namespace lib
{
	str::str(const u32  n) : str{ std::to_string(n).c_str() } {}
	str::str(const s32 n) : str{ std::to_string(n).c_str() } {}
	str::str(const f32 n) : str{ std::to_string(n).c_str() } {}
	str::str(const f64 n) : str{ std::to_string(n).c_str() } {}
	str::str(const unsigned long n) : str{ std::to_string(n).c_str() } {}   

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
