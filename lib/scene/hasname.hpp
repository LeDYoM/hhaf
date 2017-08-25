#pragma once

#ifndef LIB_CORE_HASNAME_HPP__
#define LIB_CORE_HASNAME_HPP__

#include <mtypes/include/str.hpp>

namespace lib
{
	namespace core
	{
		class HasName
		{
		public:
			constexpr HasName(const str &name) noexcept : m_name{ name } {}
//			HasName(str_const name) noexcept : m_name{ std::move(name) } {}
			constexpr HasName(HasName &&other) = default;
			constexpr HasName(const HasName &other) = default;
			HasName &operator=(HasName &&other) noexcept = default;
			HasName &operator=(const HasName &other) = default;
			virtual ~HasName() = default;
			
			inline const str &name() const noexcept { return m_name; }
		private:
			const str m_name;
		};
	}
}

#endif
