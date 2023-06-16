HAF_PRAGMA_ONCE
#ifndef HAF_TYPES_MATRIX4X4_FUNCTIONS_INCLUDE_HPP
#define HAF_TYPES_MATRIX4X4_FUNCTIONS_INCLUDE_HPP

#include <facil_math/include/math_types.hpp>
#include <facil_math/include/matrix4x4.hpp>

#include <cmath>
#include <cfloat>

namespace fmath
{
[[nodiscard]] Matrix4x4 lookat(vector3df const& eye,
                               vector3df const& center,
                               vector3df const& up);

[[nodiscard]] Matrix4x4 frustum(tps::f32 const left,
                                tps::f32 const right,
                                tps::f32 const bottom,
                                tps::f32 const top,
                                tps::f32 const n,
                                tps::f32 const f);
[[nodiscard]] Matrix4x4 perspective(tps::f32 fovy,
                                    tps::f32 const aspect,
                                    tps::f32 const n,
                                    tps::f32 const f);

[[nodiscard]] Matrix4x4 ortho(tps::f32 const left,
                              tps::f32 const right,
                              tps::f32 const bottom,
                              tps::f32 const top,
                              tps::f32 const n,
                              tps::f32 const f);

}  // namespace fmath

#endif
