#pragma once

#ifndef MTYPES_STREAMS_INCLUDE_HPP
#define MTYPES_STREAMS_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "array.hpp"
#include <algorithm>

namespace lib
{
    class SerializationStreamOut
    {
    public:

        constexpr const str &data() const { return data_; }

        const str separator(str new_separator)
        {
            std::swap(separator_, new_separator);
            return new_separator;
        }

        template <typename T>
        friend SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data);
        friend SerializationStreamOut& operator<<(SerializationStreamOut&sso, const str& data);

    private:
        void addSeparator(str &data)
        {
            if (!data_.empty())
            {
                data << separator_;
            }
        }
        str data_;
        str separator_ = ",";
    };

    inline SerializationStreamOut& operator<<(SerializationStreamOut&sso, const str& data)
    {
        sso.data_ += data;
        return sso;
    }

    inline SerializationStreamOut& operator<<(SerializationStreamOut&sso, const char* data)
    {
        return sso << str(data);
    }

    template <typename T>
    SerializationStreamOut& operator<<(SerializationStreamOut&sso, const T&data)
    {
        str t;
        sso.addSeparator(t);
        t << data;
        sso.data_ += t;
        return sso;
    }

    template <typename T, size_type size>
    SerializationStreamOut& operator<<(SerializationStreamOut&sso, const array<T,size> &data)
    {
        for (const auto& element : data) sso << element;
        return sso;
    }

    template <typename T, size_type Size>
    constexpr SerializationStreamOut& operator<<(SerializationStreamOut&sso, T(&data)[Size])
    {
        for (const auto& element : data) sso << element;
        return sso;
    }
}

#endif
