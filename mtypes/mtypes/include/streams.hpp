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
		friend SerializationStreamIn& operator<<(SerializationStreamIn&ssi, const u32 data);
	private:
		str m_data;
	};

	SerializationStreamIn& operator<<(SerializationStreamIn&ssi, const u32 data)
	{
		ssi.m_data += str(data);
		return ssi;
	}

	class SerializationStreamOut
	{
	public:
		friend SerializationStreamOut& operator>>(SerializationStreamOut&sso, u32 &data);
	private:
		str m_data;
	};

	SerializationStreamOut& operator>>(SerializationStreamOut&sso, u32 &data)
	{
		sso.m_data += str(data);
		return sso;
	}

}

#endif
