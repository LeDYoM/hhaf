#pragma once


#ifndef LIB_MTYPES_STREAMS_INCLUDE_HPP__
#define LIB_MTYPES_STREAMS_INCLUDE_HPP__

#include "types.hpp"
#include "str.hpp"

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
		ssi.m_data[sso.read++] >> data;
		return sso;
	}

	class SerializationStreamOut
	{
	public:

		template <typename T>
		friend SerializationStreamOut& operator<<(SerializationStreamOut&ssi, const T&data);
	private:
		string_vector m_data;
	};

	template <typename T>
	SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data)
	{
		str t{ " " };
		t << data;
		sso.m_data.push_back(std::move(t));
		return sso;
	}
}

#endif
