#pragma once

#ifndef MTYPES_ARRAY_INCLUDE_HPP
#define MTYPES_ARRAY_INCLUDE_HPP

#include <initializer_list>
#include <array>

namespace lib
{
	template <class T, unsigned int array_size>
	class  array {
	public:
		using iterator = T*;
		using const_iterator = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_t = unsigned int;

		array() = default;
		constexpr array(std::initializer_list<T> iList) noexcept {
			for (size_t i{ 0 }; i < iList.size() && i < array_size;++i) {
				m_buffer[i] = std::move(*(iList.begin()+i));
			}
		}

		constexpr reference operator[](const size_t index) noexcept { return m_buffer[index]; }
		constexpr const_reference operator[](const size_t index) const noexcept { return m_buffer[index]; }
		constexpr size_t size() const noexcept { return size; }
		constexpr bool empty() const noexcept { return size == 0; }
		constexpr iterator begin() noexcept { return m_buffer; }
		constexpr const_iterator begin() const noexcept { return m_buffer; }
		constexpr iterator end() noexcept { return m_buffer + array_size; }
		constexpr const_iterator end() const noexcept { return m_buffer + array_size; }
		constexpr const_iterator cbegin() const noexcept { return m_buffer; }
		constexpr const_iterator cend() const noexcept { return m_buffer + array_size; }
		constexpr T& front() noexcept { return m_buffer[0]; }
		constexpr T& back() noexcept { return m_buffer[array_size > 0 ? (array_size - 1) : 0]; }

	private:
		T m_buffer[array_size];
	};
}

#endif
