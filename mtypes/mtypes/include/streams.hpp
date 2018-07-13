#pragma once

#ifndef LIB_MTYPES_STREAMS_INCLUDE_HPP__
#define LIB_MTYPES_STREAMS_INCLUDE_HPP__

#include "types.hpp"
#include "str.hpp"
#include "array.hpp"

namespace lib
{
	class SerializationStreamIn
	{
	public:
		SerializationStreamIn(string_vector data) : m_data{ std::move(data) } {}

		template <typename T>
		friend SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data);
	private:
		string_vector m_data;
		u32 read{ 0 };
	};

	template <typename T>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data)
	{
		ssi.m_data[ssi.read++] >> data;
		return ssi;
	}

	template <typename T, size_type size>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, array<T,size> &data)
	{
		for (T& element : data) ssi >> element;
		return ssi;
	}

	template <typename T, size_type size>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T data[size])
	{
		for (T& element : data) ssi >> element;
		return ssi;
	}

	class SerializationStreamOut
	{
	public:

		const string_vector &data() const { return m_data; }

		template <typename T>
		friend SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data);
	private:
		string_vector m_data;
	};

	template <typename T>
	SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data)
	{
		str t;
		t << data;
		sso.m_data.push_back(std::move(t));
		return sso;
	}

	template <typename T, size_type size>
	SerializationStreamOut& operator<<(SerializationStreamOut&sso, const array<T,size> &data)
	{
		for (const auto& element : data) sso << element;
		return sso;
	}

	template <typename T, size_type size>
	SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T data[size])
	{
		for (const auto& element : data) sso << element;
		return sso;
	}
}

#endif
