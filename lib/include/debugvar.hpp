#ifndef LIB_DEBUGVAR_INCLUDE_HPP
#define LIB_DEBUGVAR_INCLUDE_HPP

#include "types.hpp"
#include <lib/include/str.hpp>

#pragma once

namespace lib
{
	class DebugVar
	{
	public:
		DebugVar(str_const_ id, str_const data) : m_id{ std::move(id) }, m_data{ std::move(data) } {}

		inline void setValue(const str_const &nv) noexcept { m_data = nv; }
		inline const str_const operator()() const noexcept { return str_const{ m_id } +": " + m_data; };
		inline const str_const_ id() const noexcept { return m_id; }
	private:
		str_const_ m_id;
		str_const m_data;
	};

	using DebugVarAccessor = sptr<DebugVar>;
}

#endif
