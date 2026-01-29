export module facil_math:vector_types;

import :vector2d;
import :vector3d;
import :vector4d;

namespace fmath
{
namespace tps = htps;

export template <tps::u8 Size, typename T>
struct vector_type;

export template <typename T>
struct vector_type<2U, T>
{
    using type = vector2d<T>;
};

export template <typename T>
struct vector_type<3U, T>
{
    using type = vector3d<T>;
};

export template <typename T>
struct vector_type<4U, T>
{
    using type = vector4d<T>;
};

export template <tps::u8 Size, typename T>
using vector_type_t = vector_type<Size, T>::type;

}  // namespace fmath
