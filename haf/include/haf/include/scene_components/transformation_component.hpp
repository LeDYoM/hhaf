HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/core/math_types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/events/receiver.hpp>

#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::render
{
class MeshRenderContext;
}

namespace haf::scene
{
class GlobalTransformationComponent;
}

namespace haf::scene
{
/**
 * @brief This class adds methods needed for an object to be Transformable,
 * that is, providing a @b Transformation and methods to modify this
 * Transformation.
 * @see Transofrmation
 */
class HAF_API TransformationComponent final
    : public component::ComponentBase<"TransformationComponent",
                                      GlobalTransformationComponent>
{
public:
    using Scalar = math::Matrix4x4::Scalar;  ///< Type Scalar for this class
    static constexpr Scalar const One  = math::Matrix4x4::One;
    static constexpr Scalar const Zero = math::Matrix4x4::Zero;
    static constexpr const core::vector3df DefaultTranslation{
        Vector3dZeros<Scalar>};
    static constexpr const core::vector3df DefaultRotation{
        Vector3dZeros<Scalar>};
    static constexpr const core::vector3df DefaultScale{Vector3dOnes<Scalar>};

    prop::PropertyState<core::vector3df> Position{DefaultTranslation};
    prop::PropertyState<core::vector3df> Rotation{DefaultRotation};
    prop::PropertyState<core::vector3df> Scale{DefaultScale};

    bool hasPendingMatrixUpdate() const noexcept;

    /**
     * @brief Get a copy of the current stored local transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The local transformation.
     */
    math::Matrix4x4 const& matrix() const noexcept;

    evt::emitter<math::Matrix4x4 const&> localMatrixChanged;

private:
    evt::ireceiver m_shared_connection;
    void updateTransform() noexcept;
    void onAttached() override;

    math::Matrix4x4 m_transform;
};

}  // namespace haf::scene

#endif
