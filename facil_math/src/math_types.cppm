export module facil_math:math_types;

import htypes;
import :vector2d;
import :vector3d;
import :vector4d;
import :rect;

namespace fmath
{
namespace tps = htps;

export template <typename Scalar>
inline constexpr Scalar const One = static_cast<Scalar>(1);

export template <typename Scalar>
inline constexpr Scalar const MinusOne = static_cast<Scalar>(-1);

export template <typename Scalar>
inline constexpr Scalar const Zero = static_cast<Scalar>(0);

export template <typename Scalar>
inline constexpr vector2d<Scalar> Vector2dOnes{One<Scalar>, One<Scalar>};

export template <typename Scalar>
inline constexpr vector3d<Scalar> Vector3dOnes{One<Scalar>, One<Scalar>,
                                                      One<Scalar>};

export template <typename Scalar>
inline constexpr vector4d<Scalar> Vector4dOnes{One<Scalar>, One<Scalar>,
                                                      One<Scalar>, One<Scalar>};

export template <typename Scalar>
inline constexpr vector2d<Scalar> Vector2dZeros{Zero<Scalar>,
                                                       Zero<Scalar>};

export template <typename Scalar>
inline constexpr vector3d<Scalar> Vector3dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

export template <typename Scalar>
inline constexpr vector4d<Scalar> Vector4dZeros{
    Zero<Scalar>, Zero<Scalar>, Zero<Scalar>, Zero<Scalar>};

export inline constexpr auto ZeroF32{Zero<tps::f32>};
export inline constexpr auto OneF32{One<tps::f32>};

export inline constexpr auto Vector2dZerosF32{Vector2dZeros<tps::f32>};
export inline constexpr auto Vector2dOnesF32{Vector2dOnes<tps::f32>};
export inline constexpr auto Vector3dZerosF32{Vector3dZeros<tps::f32>};
export inline constexpr auto Vector3dOnesF32{Vector3dOnes<tps::f32>};
export inline constexpr auto Vector4dZerosF32{Vector4dZeros<tps::f32>};
export inline constexpr auto Vector4dOnesF32{Vector4dOnes<tps::f32>};

}  // namespace fmath
