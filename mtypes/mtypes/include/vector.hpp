#pragma once

#ifndef MTYPES_VECTOR_INCLUDE_HPP
#define MTYPES_VECTOR_INCLUDE_HPP

#include <initializer_list>

namespace lib
{
	template <class T>
	class  vector {
	public:

		using iterator = T*;
		using const_iterator = const T*;
		using size_t = unsigned int;

		constexpr vector() noexcept : m_capacity{ 0 }, m_size{ 0 }, m_buffer{ nullptr } {}
		vector(size_t size) : m_capacity{ size }, m_size{ size }, m_buffer{ new T[m_capacity] } {}
		constexpr vector(std::initializer_list<T> ilist) noexcept : m_capacity{ ilist.size() }, m_size{ m_capacity }, m_buffer{ new T[m_capacity] }
		{
			size_t c{ 0 };
			for (auto&& element : ilist) {
				m_buffer[c++] = element;
			}
		}

		vector(const vector&other) : m_capacity{ other.m_capacity }, m_size{ other.m_size }, m_buffer{new T[m_capacity]}
		{
			for (unsigned int i{ 0 }; i < other.m_size; ++i) {
				m_buffer[i] = other.m_buffer[i];
			}
		}

		vector& operator=(const vector&other) 
		{
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			if (m_capacity < other.m_size) {
				delete m_buffer;
				m_buffer = new T[other.m_size];
			}

			for (unsigned int i{ 0 }; i < other.m_size; ++i) {
				m_buffer[i] = other.m_buffer[i];
			}
		}

		vector(vector&&other) noexcept : m_capacity{ other.m_capacity }, m_size{ other.m_size }, m_buffer{ other.m_buffer }
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.m_buffer = nullptr;
		}

		vector& operator=(vector&&other) noexcept
		{
			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_buffer = other.m_buffer;
			other.m_capacity = 0;
			other.m_size = 0;
			other.m_buffer = nullptr;
		}

		~vector() { delete m_buffer; }

		template<typename ...Args>
		void emplace_back(Args&&... args)
		{
			if (m_size == m_capacity) {
				reserve(m_size + 1);
			}

			m_buffer[m_size++] = T(std::forward<Args>(args)...);

		}

		void shrink_to_fit() {
			if (m_size != m_capacity) {
				*this = vector(*this);
			}
		}
		constexpr unsigned int capacity() const noexcept { return m_capacity; }
		constexpr unsigned int size() const noexcept { return m_size; }
		constexpr bool empty() const noexcept { return m_size > 0; }
		constexpr iterator begin() { return m_buffer; }
		constexpr iterator end() { return m_buffer + m_size; }
		constexpr const_iterator cbegin() const { return m_buffer; }
		constexpr const_iterator cend() const { return m_buffer + m_size; }
		T& front() { return m_buffer[0]; }
		T& back() { return m_buffer[m_size > 0 ? (m_size - 1) : 0]; }

		void push_back(const T& value)
		{
			if (m_size == m_capacity) {
				reserve(m_size + 1);
			}

			m_buffer[m_size++] = value;
		}

		void push_back(const vector &other) {

		}

		void pop_back() noexcept { if (m_size > 0) --m_size; }

		void reserve(const unsigned int capacity)
		{
			if (m_capacity < capacity)
			{
				T *newBuffer{ new T[capacity] };
				for (unsigned int i{ 0 }; i < m_size; ++i) {
					newBuffer[i] = std::move(m_buffer[i]);
				}
				delete m_buffer;
				m_buffer = newBuffer;
				m_capacity = capacity;
			}
		}
		void resize(unsigned int size)
		{
			if (size != m_size) {
				// Delete to shrink
				while (m_size > size) {
					pop_back();
				}

				T temp;

				while (m_size > size) {
					push_back(temp);
				}
			}
		}

		T & operator[](unsigned int index) { return m_buffer[index]; }
		const T & operator[](unsigned int index) const { return m_buffer[index]; }

		void clear()
		{
			if (m_buffer) {
				delete m_buffer;
				m_size = 0;
				m_capacity = 0;
			}
		}
	private:
		size_t m_size;
		size_t m_capacity;
		T* m_buffer;
	};
}

#endif
