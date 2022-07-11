HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties/property_state.hpp>

#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/scene/transformation.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_render_context.hpp>

namespace haf::scene
{
/**
 * @brief This class adds methods needed for an object to be Transformable,
 * that is, providing a @b Transformation and methods to modify this
 * Transformation.
 * @see Transofrmation
 */
class HAF_API TransformableSceneNode : public SceneNode, public Transformation
{
    using BaseSceneNode = SceneNode;

public:

    using Scalar = Matrix4x4::Scalar;  ///< Type Scalar for this class
    using VectorScalar =
        htps::vector2d<Scalar>;  ///< Type VectorScalar for this class
    using RectScalar =
        htps::Rect<Scalar>;  ///< Type of RectScalar for this class

    /**
     * @brief Construct a new Transformable object. The object will be
     * initialized with default properties
     * @param parent Parent of this element.
     * @param name Name of this element.
     */
    TransformableSceneNode(htps::rptr<SceneNode> parent, htps::str name);

    /**
     * @brief Destroy the Transformable object
     */
    ~TransformableSceneNode() override;

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

    void postRender(SceneRenderContext& sceneRenderContext) override;

    bool updateLocalTransformationsIfNecessary() noexcept;

private:
    Matrix4x4 local_transform_;   ///< Current local Transformation cached
    Matrix4x4 global_transform_;  ///< Global Transformation Matrix cached
};
}  // namespace haf::scene

#endif
