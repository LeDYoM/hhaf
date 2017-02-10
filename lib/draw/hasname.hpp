#ifndef LIB_CORE_HASNAME_HPP__
#define LIB_CORE_HASNAME_HPP__

#pragma once

#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		class HasName
		{
		public:
			HasName(str_const name) noexcept : m_name{ std::move(name) } {}
			constexpr HasName(HasName &&other)  noexcept = default;
			constexpr HasName(const HasName &other) = default;
			HasName &operator=(HasName &&other)  noexcept = default;
			HasName &operator=(const HasName &other) = default;
			virtual ~HasName() = default;
			
			inline str_const name() const noexcept { return m_name; }
		private:
			const str_const m_name;
		};
	}
}

#endif
