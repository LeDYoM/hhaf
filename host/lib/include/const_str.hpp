#ifndef LIB_CONSTSTRING_INCLUDE_HPP__
#define LIB_CONSTSTRING_INCLUDE_HPP__

namespace lib
{
	struct constexpr_str {
		const char const* str;
		std::size_t size;

		// can only construct from a char[] literal
		template <std::size_t N>
		constexpr constexpr_str(char const (&s)[N])
			: str(s)
			, size(N - 1) // not count the trailing nul
		{}
	};
}

#endif
