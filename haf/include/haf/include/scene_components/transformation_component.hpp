HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <facil_math/include/math_types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/events/emitter.hpp>
#include <haf/include/math/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
/**
 * @brief This class adds methods needed for an object to be Transformable,
 * that is, providing a @b Transformation and methods to modify this
 * Transformation.
 * @see Transofrmation
 */
class HAF_API TransformationComponent final
    : public component::ComponentBootStrap<TransformationComponent,
                                           "LocalViewUpdaterSubSystem">
{
public:
    static constexpr const core::str_view StaticTypeName{
        "TransformationComponent"};

    TransformationComponent();
    ~TransformationComponent() override;

    using Scalar = math::Matrix4x4::Scalar;  ///< Type Scalar for this class
    static constexpr Scalar const One  = math::Matrix4x4::One;
    static constexpr Scalar const Zero = math::Matrix4x4::Zero;
    static constexpr const math::vector3df DefaultTranslation{
        math::Vector3dZeros<Scalar>};
    static constexpr const math::vector3df DefaultRotation{
        math::Vector3dZeros<Scalar>};
    static constexpr const math::vector3df DefaultScale{
        math::Vector3dOnes<Scalar>};

    prop::PropertyState<math::vector3df> Position{DefaultTranslation};
    prop::PropertyState<math::vector3df> Rotation{DefaultRotation};
    prop::PropertyState<math::vector3df> Scale{DefaultScale};

    bool hasPendingMatrixUpdate() const noexcept;

    /**
     * @brief Get a copy of the current stored local transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The local transformation.
     */
    math::Matrix4x4 const& matrix() const noexcept;

    evt::emitter<math::Matrix4x4 const&> localMatrixChanged;

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    bool addRequirements(
        component::ComponentRequirements& component_requirements) override;

    void updateLocalTransformation() noexcept;
    void onAttached() override;
};

}  // namespace haf::scene

#endif
