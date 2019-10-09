#pragma once

#ifndef MTYPES_SERIALIZER_INCLUDE_HPP
#define MTYPES_SERIALIZER_INCLUDE_HPP

#include "object.hpp"
#include "types.hpp"
#include "str.hpp"

namespace lib
{
    constexpr Object& operator<<(Object &obj, const KeyValuePair<s64>& kvs)
    {
        obj.set(kvs.first, str::to_str(kvs.second));
    }

    constexpr Object& operator<<(Object &obj, const KeyValuePair<s32>& kvs)
    {
        obj.set(kvs.first, str::to_str(kvs.second));
    }

}

#endif
