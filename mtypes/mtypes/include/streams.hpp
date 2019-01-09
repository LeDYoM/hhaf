#pragma once

#ifndef LIB_MTYPES_STREAMS_INCLUDE_HPP
#define LIB_MTYPES_STREAMS_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "array.hpp"

namespace lib
{
	class SerializationStreamIn
	{
	public:
        using char_type = char;

        SerializationStreamIn() = default;
        SerializationStreamIn(str&& data) : data_{ std::move(data) } {}

		template <typename T>
		friend SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data);

        constexpr bool eof() const noexcept { return data_.empty(); }

	private:
        inline void remove_whitespaces()
        {
            data_.ltrim();
        }

        inline void advance_data(const size_type increment)
        {
            data_ = data_.substr(increment);
        }

        inline str extract_to_separator_and_update_data()
        {
            remove_whitespaces();

            const auto separator_index(data_.find_first_of(separator_));
            str result(data_.substr(0, separator_index));
            advance_data(separator_index + 1);
            return result;
        }

        str data_;
        char separator_{ ',' };
        bool correct_{ true };
	};

	template <typename T>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data)
	{
        ssi.extract_to_separator_and_update_data() >> data;
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
