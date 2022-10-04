HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties/property_state.hpp>

#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{
class HAF_API Transformation
{
public:
    using Scalar       = Matrix4x4::Scalar;
    using VectorScalar = htps::vector2d<Scalar>;
    using RectScalar   = htps::Rect<Scalar>;

    htps::PropertyState<VectorScalar> Position{VectorScalar{0.0F, 0.0F}};
    htps::PropertyState<Scalar> Rotation{Scalar{0.0F}};
    htps::PropertyState<VectorScalar> Scale{VectorScalar{1.0F, 1.0F}};

    Transformation() noexcept;
    virtual ~Transformation();
    Transformation(Transformation const&) = delete;
    Transformation& operator=(Transformation const&)    = delete;
    constexpr Transformation(Transformation&&) noexcept = default;
    constexpr Transformation& operator=(Transformation&&) noexcept = default;

    void setLeftTopPositionScale(VectorScalar const& vector);
    void setRightTopPositionScale(VectorScalar const& vector);
    bool updateTransformIfNecessary() noexcept;

    Matrix4x4 const& matrix() const noexcept;

private:
    void updateTransform();

    Matrix4x4 transform_;
};
}  // namespace haf::scene

#endif
