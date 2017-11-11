#pragma once

#ifndef LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__
#define LIB_MTYPES_AUX_CONTAINER_INCLUDE_HPP__

namespace lib
{
	template <typename Container>
	class AuxContainer final
	{
	public:
		constexpr AuxContainer() = default;
		
		constexpr Container &conainer() noexcept { return (*m_pContainer[0]); }
		constexpr const Container &conainer() const noexcept { return (*m_pContainer[0]); }

		constexpr Container &auxContainer() noexcept { return (*m_pContainer[1]); }
		constexpr const Container &auxContainer() const noexcept { return (*m_pContainer[1]); }

		constexpr void swap() noexcept {
			if (m_normalMode) {
				m_pContainer[0] = &m_container[1];
				m_pContainer[1] = &m_container[0];
				m_normalMode = false;
			} else {
				m_pContainer[0] = &m_container[0];
				m_pContainer[1] = &m_container[1];
				m_normalMode = true;
			}
		}
	private:
		Container m_container[2];
		Container *m_pContainer[2] = { &m_container[0], &m_container[1] };
		bool m_normalMode{ true };
	};
}

#endif
