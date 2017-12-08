#pragma once

#ifndef LIB_CORE_HASNAME_HPP__
#define LIB_CORE_HASNAME_HPP__

#include <mtypes/include/str.hpp>
#include <mtypes/include/log.hpp>

namespace lib::core
{
	class HasName
	{
	public:
		constexpr HasName(const str &name) noexcept : m_name( name )
		{
			log_debug_info("Creating object with name: ", m_name);
		}
		constexpr HasName(HasName &&other) = default;
		constexpr HasName(const HasName &other) = default;
		HasName &operator=(HasName &&other) noexcept = default;
		HasName &operator=(const HasName &other) = default;
		virtual ~HasName() {
			log_debug_info("Destroying object with name: ", m_name);
		}
			
		inline const str &name() const noexcept { return m_name; }
	private:
		const str m_name;
	};
}

#endif
