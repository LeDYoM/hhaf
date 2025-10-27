HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/rect.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_order.hpp>

namespace haf::scene
{
class HAF_API Transformation : public component::Component
{
public:
    static constexpr core::str_literal StaticTypeName{
        "TransformationComponent"};
    static constexpr component::ComponentOrder::Value StaticComponentOrder{1U};

    using Scalar       = Matrix4x4::Scalar;
    using VectorScalar = fmath::vector2d<Scalar>;
    using RectScalar   = fmath::Rect<Scalar>;

    prop::PropertyState<VectorScalar> Position{VectorScalar{0.0F, 0.0F}};
    prop::PropertyState<Scalar> Rotation{Scalar{0.0F}};
    prop::PropertyState<VectorScalar> Scale{VectorScalar{1.0F, 1.0F}};

    Transformation() noexcept;

    void setLeftTopPositionScale(VectorScalar const& vector);
    void setRightTopPositionScale(VectorScalar const& vector);
    bool updateTransformIfNecessary() noexcept;

    void update() override;

    Matrix4x4 const& matrix() const noexcept;

    core::str staticTypeName() const noexcept override;

    /**
     * @brief Get a copy of the current stored global transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The global transformation.
     */
    Matrix4x4 const& globalTransform() const noexcept;

    /**
     * @brief Get a copy of the current stored local transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The local transformation.
     */
    Matrix4x4 const& localTransform() const noexcept;

    component::ComponentOrder::Value componentOrder() const noexcept override;

private:
    void updateTransform();

    Matrix4x4 m_transform;
    Matrix4x4 m_global_transform;  ///< Global Transformation Matrix cached
};
}  // namespace haf::scene

#endif
