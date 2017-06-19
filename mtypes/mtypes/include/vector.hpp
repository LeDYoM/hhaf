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
		using reference = T&;
		using const_reference = const T&;
		using size_t = unsigned int;

		constexpr vector() noexcept : m_capacity{ 0 }, m_size{ 0 }, m_buffer{ nullptr } {}
		vector(size_t size) : m_capacity{ size }, m_size{ size }, m_buffer{ new T[size] } {}
		constexpr vector(std::initializer_list<T> ilist) noexcept : m_capacity{ ilist.size() }, m_size{ m_capacity }, m_buffer{ new T[m_capacity] }
		{
			size_t c{ 0 };
			for (const auto& element : ilist) {
				m_buffer[c++] = element;
			}
		}

		vector(const vector&other) : m_capacity{ other.m_capacity }, m_size{ other.m_size }, m_buffer{new T[m_capacity]}
		{
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

		vector& operator=(const vector&other)
		{
			m_size = other.m_size;

			if (m_capacity < other.m_size) {
				delete[] m_buffer;
				m_buffer = new T[other.m_size];
				m_capacity = other.m_size;
				m_size = other.m_size;
			}

			for (unsigned int i{ 0 }; i < other.m_size; ++i) {
				m_buffer[i] = other.m_buffer[i];
			}
			return *this;
		}

		vector& operator=(vector&&other) noexcept
		{
			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_buffer = other.m_buffer;
			other.m_capacity = 0;
			other.m_size = 0;
			other.m_buffer = nullptr;
			return *this;
		}

		~vector() { 
			if (m_buffer) {
				delete[] m_buffer;
				m_size = 0;
				m_capacity = 0;
			}
		}

		iterator remove_value(const T &value) {
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

		size_t remove_values(const T&value) {
			iterator last_removed{ end() };
			do
			{
				last_removed = remove_value(value);
			} while (last_removed != end());
			return m_size;
		}

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

		reference operator[](const size_t index) { return m_buffer[index]; }
		const_reference operator[](const size_t index) const { return m_buffer[index]; }
		constexpr unsigned int capacity() const noexcept { return m_capacity; }
		constexpr unsigned int size() const noexcept { return m_size; }
		constexpr bool empty() const noexcept { return m_size > 0; }
		constexpr iterator begin() noexcept { return m_buffer; }
		constexpr const_iterator begin() const noexcept { return m_buffer; }
		constexpr iterator end() noexcept { return m_buffer + m_size; }
		constexpr const_iterator end() const noexcept { return m_buffer + m_size; }
		constexpr const_iterator cbegin() const noexcept { return m_buffer; }
		constexpr const_iterator cend() const noexcept { return m_buffer + m_size; }
		T& front() { return m_buffer[0]; }
		T& back() { return m_buffer[m_size > 0 ? (m_size - 1) : 0]; }

		void push_back(const T& value)
		{
			reserve(m_size + 1);
			m_buffer[m_size++] = value;
		}

		void push_back(T&& value)
		{
			reserve(m_size + 1);
			m_buffer[m_size++] = std::move(value);
		}

		void insert(const vector &other) {
			//TO DO: Optimize
			reserve(m_size + other.size());
			for (auto&& element : other) {
				push_back(element);
			}
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
				if (m_buffer)
					delete[] m_buffer;
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

		void clear()
		{
			m_size = 0;
			/*
			if (m_buffer) {
				delete[] m_buffer;
				m_buffer = nullptr;
				m_size = 0;
				m_capacity = 0;
			}
			*/
		}

	private:
		size_t m_capacity;
		size_t m_size;
		T* m_buffer;
	};
}

#endif
