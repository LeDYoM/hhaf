HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP

#include <htypes/include/property_group.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
template <typename Scalar>
struct RotationScalar : htps::PropertyStateBase<Scalar> {};

template <typename Scalar>
struct ScaleScalar : htps::PropertyStateBase<htps::vector2d<Scalar>>
{
    static constexpr auto Ones =
        htps::vector2d<Scalar>{static_cast<Scalar>(1), static_cast<Scalar>(1)};
    static constexpr auto Zeros =
        htps::vector2d<Scalar>{static_cast<Scalar>(0), static_cast<Scalar>(0)};
};

template <typename Scalar>
struct PositionScalar : htps::PropertyStateBase<htps::vector2d<Scalar>> {};

using Rotation = RotationScalar<Matrix4x4::Scalar>;
using Scale    = ScaleScalar<Matrix4x4::Scalar>;
using Position = PositionScalar<Matrix4x4::Scalar>;

using TransformationProperties =
    htps::PropertyGroup<Rotation, Scale, Position>;

}  // namespace haf::scene

#endif
