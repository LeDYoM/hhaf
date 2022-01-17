#ifndef HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP

#include <haf/include/types/property_group.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
template <typename Scalar>
struct OriginScalar : PropertyStateBase<htps::vector2d<Scalar>> {};

template <typename Scalar>
struct RotationScalar : PropertyStateBase<Scalar> {};

template <typename Scalar>
struct ScaleScalar : PropertyStateBase<htps::vector2d<Scalar>>
{
    static constexpr auto Ones =
        htps::vector2d<Scalar>{static_cast<Scalar>(1), static_cast<Scalar>(1)};
    static constexpr auto Zeros =
        htps::vector2d<Scalar>{static_cast<Scalar>(0), static_cast<Scalar>(0)};
};

template <typename Scalar>
struct PositionScalar : PropertyStateBase<htps::vector2d<Scalar>> {};

using Origin   = OriginScalar<Matrix4x4::Scalar>;
using Rotation = RotationScalar<Matrix4x4::Scalar>;
using Scale    = ScaleScalar<Matrix4x4::Scalar>;
using Position = PositionScalar<Matrix4x4::Scalar>;

using TransformationProperties =
    types::PropertyGroup<Origin, Rotation, Scale, Position>;

}  // namespace haf::scene

#endif
