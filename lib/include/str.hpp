#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#pragma once

#include <string>

namespace lib
{
	class str_const {
	public:
		using size_t = unsigned int;

		template<size_t N>
		constexpr str_const(const char(&a)[N]) noexcept : m_data{ a }, m_size{ N - 1 } {}

		constexpr char operator[](const size_t n) const noexcept { return m_data[n]; }
		constexpr size_t size() const noexcept { return m_size; }
		explicit operator std::string() const { return std::string{ m_data }; }
	private:
		const char* const m_data;
		const size_t m_size;
	};

#define INITIAL_SIZE 15

	class string
	{
	public:
		string(size_t size) : m_data{ new char[size] }, m_size{ size } {}
		string() : string(INITIAL_SIZE) {}

		template<size_t N>
		constexpr string(const char(&a)[N]) noexcept : m_data{ new char[N] }

		string(const char*rhs) {
			if (rhs) {
				int iSize = strlen(rhs) + 1;
				m_data = new char[iSize];
				memset(m_data, 0, iSize);
				m_size = iSize;
				memcpy(m_data, rhs, strlen(rhs));
			}
		}
		string(const string&strInstance) {
			if (strInstance.empty() == false) {
				this->m_data = new char[strInstance.size() + 1];
				this->m_size = strInstance.size() + 1;
				memset(this->m_data, 0, this->m_size);
				memcpy(this->m_data, strInstance.data(), this->m_size);
			}
		}
		string& string::operator=(const string &) {

		}
		string& string::operator+(const string &strInstance);
		int find(const char*);
		bool empty() const {

		}
		int size() const;
		char* data() const;
		~string(void);
	private:
		char *m_data;
		size_t m_size;
		const static int npos = -1;

	};
}

#endif
