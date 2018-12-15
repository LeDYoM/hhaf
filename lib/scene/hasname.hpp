#pragma once

#ifndef LIB_CORE_HASNAME_HPP
#define LIB_CORE_HASNAME_HPP

#include <mtypes/include/str.hpp>

namespace lib::core
{
	class HasName
	{
	public:
		constexpr HasName(const str &name) noexcept : m_name( name ) {}
		constexpr HasName(HasName &&other) = default;
		constexpr HasName(const HasName &other) = default;
		HasName &operator=(HasName &&other) noexcept = default;
		HasName &operator=(const HasName &other) = default;

		inline const str &name() const noexcept { return m_name; }

    protected:
		~HasName() {}

	private:
		const str m_name;
	};
}

#endif
