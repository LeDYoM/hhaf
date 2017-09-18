#pragma once

#ifndef MTYPES_VECTOR_INCLUDE_HPP
#define MTYPES_VECTOR_INCLUDE_HPP

#include <utility>
#include <initializer_list>
#include "mtypes_export.hpp"
#include "function.hpp"

namespace lib
{
	template <class T>
	class  vector {
	public:
		using iterator = T*;
		using const_iterator = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_t = unsigned int;

		constexpr vector() noexcept : m_capacity{ 0 }, m_size{ 0 }, m_buffer{ nullptr } {}
		explicit constexpr vector(size_t size) : m_capacity{ size }, m_size{ size }, m_buffer{ size?new T[size] :nullptr} {}
		constexpr vector(std::initializer_list<T> ilist) noexcept : vector( ilist.size() )
		{
			_copyElements(ilist.begin(), m_size);
		}

		constexpr vector(const T*elements, const size_t size) noexcept : vector(size)
		{
			_copyElements(elements, m_size);
		}

		constexpr vector(const vector&other) noexcept : m_capacity{ other.m_capacity }, m_size{ other.m_size }, m_buffer{new T[m_capacity]}
		{
			_copyElements(other.m_buffer, other.m_size);
		}

		constexpr vector(const vector&other, const size_t size)
			: vector(other.m_buffer, size) {}

		constexpr vector(vector&&other) noexcept : m_capacity{ other.m_capacity }, m_size{ other.m_size }, m_buffer{ other.m_buffer }
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.m_buffer = nullptr;
		}

		constexpr vector& operator=(const vector&other)
		{
			if (this != &other) {
				if (m_capacity < other.m_size) 
					_copyStructure(other);

				_copyElements(other.m_buffer, other.m_size);
			}
			return *this;
		}

		constexpr vector& copyExact(const vector&other)
		{
			if (this != &other) {
				_copyStructure(other);
				_copyElements(other.m_buffer, other.m_size);
			}
			return *this;
		}

		constexpr vector& operator=(vector&&other) noexcept
		{
			_destroy();
			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_buffer = other.m_buffer;
			other.m_capacity = 0;
			other.m_size = 0;
			other.m_buffer = nullptr;
			return *this;
		}

		~vector() {
			_destroy();
		}

		constexpr reference operator[](const size_t index) noexcept { return m_buffer[index]; }
		constexpr const_reference operator[](const size_t index) const noexcept { return m_buffer[index]; }
		constexpr unsigned int capacity() const noexcept { return m_capacity; }
		constexpr unsigned int size() const noexcept { return m_size; }
		constexpr bool empty() const noexcept { return m_size == 0; }
		constexpr iterator begin() noexcept { return m_buffer; }
		constexpr const_iterator begin() const noexcept { return m_buffer; }
		constexpr iterator end() noexcept { return m_buffer + m_size; }
		constexpr const_iterator end() const noexcept { return m_buffer + m_size; }
		constexpr const_iterator cbegin() const noexcept { return m_buffer; }
		constexpr const_iterator cend() const noexcept { return m_buffer + m_size; }
		constexpr T& front() noexcept { return m_buffer[0]; }
		constexpr T& back() noexcept { return m_buffer[m_size > 0 ? (m_size - 1) : 0]; }

		void for_each(function<void(const T&)> f) {
			if (m_size) {
				iterator current{ begin() };
				do {
					f(*current);
				} while (current++ != end());
			}
		}

		constexpr iterator remove_value(const T &value) {
			bool moving{ false };
			iterator where_it_was{ end() };
			for (size_t i{ 0 }; i < m_size; ++i) {
				if (!moving) {
					if (m_buffer[i] == value) {
						moving = true;
						--m_size;
						where_it_was = m_buffer + i;
					}
				}
				else {
					m_buffer[i - 1] = std::move(m_buffer[i]);
				}
			}
			return where_it_was;
		}

		constexpr size_t remove_values(const T&value) {
			iterator last_removed{ end() };
			do
			{
				last_removed = remove_value(value);
			} while (last_removed != end());
			return m_size;
		}

		constexpr size_t remove_all_from(const vector &other) {
			for (auto&& node : other) {
				remove_value(std::forward<T>(node));
			}
		}

		constexpr iterator find(const T&element) noexcept
		{
			auto finder( begin() );
			while (finder != end() && !(*finder == element)) ++finder;
			return finder;
		}

		constexpr const_iterator find(const T&element) const noexcept
		{
			auto finder{ cbegin() };
			while (finder != cend() && !(*finder == element)) ++finder;
			return finder;
		}

		constexpr const_iterator cfind(const T&element) const noexcept
		{
			auto finder{ cbegin() };
			while (finder != cend() && !(*finder == element)) ++finder;
			return finder;
		}

		template<typename ...Args>
		constexpr void emplace_back(Args&&... args)
		{
			if (m_size == m_capacity) {
				reserve(m_size + 1);
			}

			m_buffer[m_size++] = T(std::forward<Args>(args)...);

		}

		constexpr void shrink_to_fit() {
			if (m_size < m_capacity) {
				T*oldBuffer{ m_buffer };
				m_buffer = new T[m_size];
				m_capacity = m_size;
				_moveElements(oldBuffer,m_size);

				delete[] oldBuffer;
			}
		}

		constexpr void push_back(const T& value)
		{
			reserve(m_size + 1);
			m_buffer[m_size++] = value;
		}

		constexpr void push_back(T&& value)
		{
			reserve(m_size + 1);
			m_buffer[m_size++] = std::move(value);
		}

		constexpr void insert(const vector &other) {
			//TO DO: Optimize
			reserve(m_size + other.m_size);
			for (const auto& element : other) {
				push_back(element);
			}
		}

		constexpr vector& operator+=(const vector &other)
		{
			insert(other);
			return *this;
		}

		constexpr void pop_back() noexcept { if (m_size > 0) --m_size; }

		constexpr void reserve(const size_t capacity)
		{
			if (m_capacity < capacity)
			{
				T *oldBuffer{ m_buffer };
				m_capacity = capacity;
				m_buffer = new T[m_capacity];
				_moveElements(oldBuffer, m_size);
				delete[] oldBuffer;
			}
		}

		constexpr void resize(const size_t size)
		{
			if (size != m_size) {
				// Delete to shrink
				while (m_size > size) {
					pop_back();
				}

				while (m_size > size) {
					emplace_back();
				}
			}
		}

		constexpr void clear() noexcept
		{
			m_size = 0;
		}

	private:

		constexpr void _copyStructure(const vector&other)
		{
			_destroy();
			m_buffer = new T[other.m_size];
			m_capacity = other.m_size;
			m_size = other.m_size;
		}

		constexpr void _ensure_reserved(const size_t capacity)
		{
			if (m_capacity < capacity)
			{
				T *newBuffer{ new T[capacity] };
				for (unsigned int i{ 0 }; i < m_size; ++i) {
					newBuffer[i] = std::move(m_buffer[i]);
				}
				if (m_buffer)
					delete[] m_buffer;
				m_buffer = newBuffer;
				m_capacity = capacity;
			}
		}

		constexpr void _copyElements(const T*const source, const size_t s)
		{
			for (size_t i{ 0 }; i < s; ++i) {
				m_buffer[i] = source[i];
			}
		}

		constexpr void _moveElements(T*source, const size_t s) noexcept
		{
			for (size_t i{ 0 }; i < s; ++i) {
				m_buffer[i] = std::move(source[i]);
			}
		}

		constexpr void _destroy()
		{
			if (m_buffer) {
				delete[] m_buffer;
				m_buffer = nullptr;
				m_size = m_capacity = 0;
			}
		}

		size_t m_capacity;
		size_t m_size;
		T* m_buffer;

		template <class A>
		friend constexpr bool operator==(const vector<A>& lhs, const vector<A>& rhs) noexcept;

		template <class A>
		friend constexpr bool operator!=(const vector<A>& lhs, const vector<A>& rhs) noexcept;
	};

	template <class A>
	constexpr bool operator==(const vector<A>& lhs, const vector<A>& rhs) noexcept
	{
		if (lhs.m_size != rhs.m_size) {
			return false;
		} else {
			for (decltype(lhs.m_size) i{ 0 }; i < lhs.m_size;++i) {
				if (lhs.m_buffer[i] != rhs.m_buffer[i]) {
					return false;
				}
			}
			return true;
		}
	}

	template <class A>
	constexpr bool operator!=(const vector<A>& lhs, const vector<A>& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	template <typename T>
	using vector_shared_pointers = vector<sptr<T>>;

	template <typename T>
	using vector_unique_pointers = vector<uptr<T>>;
}

#endif
