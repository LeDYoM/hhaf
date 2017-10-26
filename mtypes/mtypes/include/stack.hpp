#pragma once

#ifndef MTYPES_STACK_INCLUDE_HPP
#define MTYPES_STACK_INCLUDE_HPP

#include "types.hpp"
#include "vector.hpp"

namespace lib
{
	template <typename T>
	class  stack {
		vector<T> m_data;
	public:
		using iterator = T*;
		using const_iterator = const T*;
		using reference = T&;
		using const_reference = const T&;

		constexpr stack() noexcept = default;
		explicit constexpr stack(const size_type size) : m_data( size ) {}
		constexpr stack(const stack&other) noexcept = default;
		constexpr stack(stack&&other) noexcept = default;
		constexpr stack& operator=(const stack&other) = default;
		constexpr stack& operator=(stack&&other) noexcept = default;
		~stack() = default;

		constexpr size_type capacity() const noexcept { return m_data.capacity(); }
		constexpr size_type size() const noexcept { return m_data.size(); }
		constexpr bool empty() const noexcept { return m_data.empty(); }
		constexpr T& back() noexcept { return m_data.back(); }

		constexpr void swap(stack& other) {
			swap(m_data, other.m_data);
		}

		template<typename ...Args>
		constexpr void emplace_back(Args&&... args) {
			m_data.emplace_back(std::forward<Args>(args)...);
		}

		constexpr void shrink_to_fit() {
			m_data.shrink_to_fit();
		}

		constexpr void push_back(const T& value) {
			m_data.push_back(value);
		}

		constexpr void push_back(T&& value) {
			m_data.push_back(value);
		}

		constexpr void pop_back() noexcept { m_data.pop_back(); }

		constexpr void clear() noexcept {
			m_data.clear();
		}

		template <class A>
		friend constexpr bool operator==(const stack<A>& lhs, const stack<A>& rhs) noexcept;

		template <class A>
		friend constexpr bool operator!=(const stack<A>& lhs, const stack<A>& rhs) noexcept;
	};

	template <class A>
	constexpr bool operator==(const stack<A>& lhs, const stack<A>& rhs) noexcept {
		return lhs.m_data == rhs.m_data;
	}

	template <class A>
	constexpr bool operator!=(const stack<A>& lhs, const stack<A>& rhs) noexcept {
		return lhs.m_data != rhs.m_data;
	}
}

#endif
