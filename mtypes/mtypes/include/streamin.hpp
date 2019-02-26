#pragma once

#ifndef LIB_MTYPES_STREAMIN_INCLUDE_HPP
#define LIB_MTYPES_STREAMIN_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "array.hpp"
#include <algorithm>

namespace lib
{
	class SerializationStreamIn
	{
	public:
        using char_type = char;

        SerializationStreamIn() = default;
        explicit SerializationStreamIn(str data) : data_{ std::move(data) } {}
        explicit SerializationStreamIn(string_vector data)
        {
            for (const str& line_data : data)
            {
                data_ += line_data;
                data_ += "\n";
            }
        }

		template <typename T>
		friend SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data);

        constexpr bool eof() const noexcept { return data_.empty(); }
        constexpr bool hasError() const noexcept { return !correct_; }
 
        inline void append(const str& data)
        {
            data_.append("\n");
            data_.append(data);
        }

        inline SerializationStreamIn& operator+=(const str& data)
        {
            append(data);
            return *this;
        }

        inline SerializationStreamIn& operator<<(const str& data)
        {
            append(data);
            return *this;
        }

        constexpr SerializationStreamIn& separator(const char_type separator) noexcept
        {
            separator_ = separator;
            return *this;
        }

        inline SerializationStreamIn& disableSeparator()
        {
            return separator(0);
        }

        inline char_type separator() const
        {
            return separator_;
        }

    private:
        inline void remove_lwhitespaces()
        {
            data_.ltrim();
        }

        inline void advance_data(const size_type increment)
        {
            data_ = data_.substr(increment);
        }

        inline str extract_to_separator_and_update_data()
        {
            remove_lwhitespaces();

            const auto separator_index(data_.find_first_of(separator_));
            str result(data_.substr(0, separator_index));
            advance_data(std::max(separator_index, separator_index + 1));
            return result;
        }

        str data_;
        bool correct_{ true };
        char separator_{ ',' };
	};

	template <typename T>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T &data)
	{
        ssi.correct_ &= ssi.extract_to_separator_and_update_data() >> data;
		return ssi;
	}

    template <typename T, size_type Size>
    constexpr SerializationStreamIn& operator>>(SerializationStreamIn&ssi, T(&data)[Size])
    {
        for (T& element : data) 
            ssi >> element;
        return ssi;
    }

	template <typename T, size_type size>
	SerializationStreamIn& operator>>(SerializationStreamIn&ssi, array<T,size> &data)
	{
		for (T& element : data) ssi >> element;
		return ssi;
	}
}

#endif
