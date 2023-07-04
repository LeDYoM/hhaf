FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_MATH_TYPES_INCLUDE_HPP
#define FACIL_MATH_MATH_TYPES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/vector4d.hpp>
#include <facil_math/include/rect.hpp>

namespace fmath
{
namespace tps = htps;

template <typename Scalar>
inline static constexpr Scalar const One = static_cast<Scalar>(1);

template <typename Scalar>
inline static constexpr Scalar const MinusOne = static_cast<Scalar>(-1);

template <typename Scalar>
inline static constexpr Scalar const Zero = static_cast<Scalar>(0);

template <typename Scalar>
inline static constexpr vector2d<Scalar> Vector2dOnes{One<Scalar>, One<Scalar>};

template <typename Scalar>
inline static constexpr vector3d<Scalar> Vector3dOnes{One<Scalar>, One<Scalar>,
                                                      One<Scalar>};

template <typename Scalar>
inline static constexpr vector4d<Scalar> Vector4dOnes{One<Scalar>, One<Scalar>,
                                                      One<Scalar>, One<Scalar>};

template <typename Scalar>
inline static constexpr vector2d<Scalar> Vector2dZeros{Zero<Scalar>,
                                                       Zero<Scalar>};

template <typename Scalar>
inline static constexpr vector3d<Scalar> Vector3dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

template <typename Scalar>
inline static constexpr vector4d<Scalar> Vector4dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

inline static constexpr auto ZeroF32{Zero<tps::f32>};
inline static constexpr auto OneF32{One<tps::f32>};

inline static constexpr auto Vector2dZerosF32{Vector2dZeros<tps::f32>};
inline static constexpr auto Vector2dOnesF32{Vector2dOnes<tps::f32>};
inline static constexpr auto Vector3dZerosF32{Vector3dZeros<tps::f32>};
inline static constexpr auto Vector3dOnesF32{Vector3dOnes<tps::f32>};
inline static constexpr auto Vector4dZerosF32{Vector4dZeros<tps::f32>};
inline static constexpr auto Vector4dOnesF32{Vector4dOnes<tps::f32>};

}  // namespace fmath

#endif
