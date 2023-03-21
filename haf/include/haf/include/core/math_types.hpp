HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_MATH_TYPES_INCLUDE_HPP
#define HAF_CORE_MATH_TYPES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/vector3d.hpp>
#include <htypes/include/vector4d.hpp>
#include <htypes/include/rect.hpp>

namespace haf
{
namespace core = htps;

template <typename Scalar>
inline static constexpr Scalar const One = static_cast<Scalar>(1.0);

template <typename Scalar>
inline static constexpr Scalar const Zero = static_cast<Scalar>(0.0);

template <typename Scalar>
inline static constexpr core::vector2d<Scalar> Vector2dOnes{One<Scalar>,
                                                            One<Scalar>};

template <typename Scalar>
inline static constexpr core::vector3d<Scalar> Vector3dOnes{
    One<Scalar>, One<Scalar>, One<Scalar>};

template <typename Scalar>
inline static constexpr core::vector4d<Scalar> Vector4dOnes{
    One<Scalar>, One<Scalar>, One<Scalar>, One<Scalar>};

template <typename Scalar>
inline static constexpr core::vector2d<Scalar> Vector2dZeros{Zero<Scalar>,
                                                             Zero<Scalar>};

template <typename Scalar>
inline static constexpr core::vector3d<Scalar> Vector3dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

template <typename Scalar>
inline static constexpr core::vector4d<Scalar> Vector4dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

inline static constexpr auto ZeroF32{Zero<core::f32>};
inline static constexpr auto OneF32{One<core::f32>};

inline static constexpr auto Vector2dZerosF32{Vector2dZeros<core::f32>};
inline static constexpr auto Vector2dOnesF32{Vector2dOnes<core::f32>};
inline static constexpr auto Vector3dZerosF32{Vector3dZeros<core::f32>};
inline static constexpr auto Vector3dOnesF32{Vector3dOnes<core::f32>};
inline static constexpr auto Vector4dZerosF32{Vector4dZeros<core::f32>};
inline static constexpr auto Vector4dOnesF32{Vector4dOnes<core::f32>};

}  // namespace haf

#endif
