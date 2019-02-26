#pragma once

#ifndef LIB_MTYPES_STREAMS_INCLUDE_HPP
#define LIB_MTYPES_STREAMS_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "array.hpp"
#include <algorithm>

namespace lib
{
	class SerializationStreamOut
	{
	public:

		const str &data() const { return m_data; }

		template <typename T>
		friend SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data);
	private:
		str m_data;
	};

	template <typename T>
	SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data)
	{
		str t;
		t << data;
		sso.m_data += t;
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
