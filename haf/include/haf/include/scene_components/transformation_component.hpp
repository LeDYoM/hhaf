HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <facil_math/include/math_types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/events/emitter.hpp>

#include <facil_math/include/matrix4x4.hpp>
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
                                           scene::SceneUpdateTime::EndFrame>
{
public:
    static constexpr const core::str_view StaticTypeName{
        "TransformationComponent"};

    TransformationComponent();
    ~TransformationComponent() override;

    using Scalar = fmath::Matrix4x4::Scalar;  ///< Type Scalar for this class
    static constexpr Scalar const One  = fmath::Matrix4x4::One;
    static constexpr Scalar const Zero = fmath::Matrix4x4::Zero;
    static constexpr const fmath::vector3df DefaultTranslation{
        fmath::Vector3dZeros<Scalar>};
    static constexpr const fmath::vector3df DefaultRotation{
        fmath::Vector3dZeros<Scalar>};
    static constexpr const fmath::vector3df DefaultScale{
        fmath::Vector3dOnes<Scalar>};

    prop::PropertyState<fmath::vector3df> Position{DefaultTranslation};
    prop::PropertyState<fmath::vector3df> Rotation{DefaultRotation};
    prop::PropertyState<fmath::vector3df> Scale{DefaultScale};

    bool hasPendingMatrixUpdate() const noexcept;

    /**
     * @brief Get a copy of the current stored local transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The local transformation.
     */
    fmath::Matrix4x4 const& matrix() const noexcept;

    evt::emitter<fmath::Matrix4x4 const&> localMatrixChanged;

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    bool transformationUpdated() const noexcept;
    void updateLocalTransformation() noexcept;
    void onAttached() override;
};

}  // namespace haf::scene

#endif
