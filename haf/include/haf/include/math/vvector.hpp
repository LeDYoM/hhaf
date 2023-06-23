HAF_PRAGMA_ONCE
#ifndef HAF_CORE_MATH_MATH_VVECTOR_INCLUDE_HPP
#define HAF_CORE_MATH_MATH_VVECTOR_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/vvector.hpp>

namespace haf::math
{
HAF_EXPORT_TEMPLATE template class HAF_API fmath::vvector3d<core::f32>;
using vvector3df = fmath::vvector3d<core::f32>;

}  // namespace haf::math

#endif
