#pragma once

#ifndef LIB_SERIALIZER_INCLUDE_HPP
#define LIB_SERIALIZER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace lib
{
template <typename T>
class Serializer
{
public:
    static constexpr str serialize(const T &data)
    {
        Object obj;
        obj << data;

        str temp;
        temp << obj;
        return temp;
    }

    static constexpr bool deserialize(const str &data, T &output)
    {
        ObjectCompiler obj_compiler(data);
        if (obj_compiler.compile())
        {
            // The compilation was correct so, at least we
            // have a valid Object.
            obj_compiler.result() >> output;
            return true;
        }
        return false;
    }
};

} // namespace lib

#endif
