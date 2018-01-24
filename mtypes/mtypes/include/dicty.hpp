#ifndef LIB_DICTY_INCLUDE_HPP
#define LIB_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include <utility>
#include <variant>

namespace lib::dicty
{
	class Element;

	class BasicElement
	{
	public:
		inline const str& key() const noexcept { return m_data.first; }
		inline const str& value() const noexcept { return m_data.second; }

	private:
		std::pair<str, str> m_data;
	};

	class Array
	{
	public:

	private:
		vector<Element> data;
	};
}

#endif
