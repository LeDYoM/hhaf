#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#pragma once

#include <string>

namespace lib
{
	class str_const_ {
	public:
		using size_t = unsigned int;

		template<size_t N>
		constexpr str_const_(const char(&a)[N]) noexcept : m_data{ a }, m_size{ N - 1 } {}

		constexpr char operator[](const size_t n) const noexcept { return m_data[n]; }
		constexpr size_t size() const noexcept { return m_size; }
		explicit operator std::string() const { return std::string(m_data); }
	private:
		const char* const m_data;
		const size_t m_size;
	};
}

#endif
