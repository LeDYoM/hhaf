FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VECTOR_TYPES_INCLUDE_HPP
#define FACIL_MATH_VECTOR_TYPES_INCLUDE_HPP

#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/vector4d.hpp>

namespace fmath
{
namespace tps = htps;

template <tps::u8 Size, typename T>
struct vector_type;

template <typename T>
struct vector_type<2U, T>
{
    using type = vector2d<T>;
};

template <typename T>
struct vector_type<3U, T>
{
    using type = vector3d<T>;
};

template <typename T>
struct vector_type<4U, T>
{
    using type = vector4d<T>;
};

template <tps::u8 Size, typename T>
using vector_type_t = vector_type<Size, T>::type;

}  // namespace fmath

#endif
