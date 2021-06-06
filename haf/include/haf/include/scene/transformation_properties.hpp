#ifndef HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_PROPERTIES_INCLUDE_HPP

#include <htypes/include/grouping_property.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
template <typename Scalar>
struct OriginScalar
{
    using value_type = htps::vector2d<Scalar>;
};

template <typename Scalar>
struct RotationScalar
{
    using value_type = Scalar;
};

template <typename Scalar>
struct ScaleScalar
{
    using value_type = htps::vector2d<Scalar>;
    static constexpr auto Ones =
        value_type{static_cast<Scalar>(1), static_cast<Scalar>(1)};
    static constexpr auto Zeros =
        value_type{static_cast<Scalar>(0), static_cast<Scalar>(0)};
};

template <typename Scalar>
struct PositionScalar
{
    using value_type = htps::vector2d<Scalar>;
};

using Origin   = OriginScalar<Matrix4x4::Scalar>;
using Rotation = RotationScalar<Matrix4x4::Scalar>;
using Scale    = ScaleScalar<Matrix4x4::Scalar>;
using Position = PositionScalar<Matrix4x4::Scalar>;

using TransformationProperties =
    htps::PropertyGroup<Origin, Rotation, Scale, Position>;

}  // namespace haf::scene

#endif
