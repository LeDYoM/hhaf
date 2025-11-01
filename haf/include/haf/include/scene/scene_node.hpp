HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/haf_export.hpp>
#include <haf/include/types/scene_types.hpp>
#include <haf/include/scene/scenenodeparent.hpp>
#include <haf/include/scene/scene_nodes.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/scene/scene_render_context.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/scene_components/transformation.hpp>

namespace haf::scene
{
class Scene;
/**
 * @brief Main class representing all SceneNodes from a @b Scene.
 * This class serves as main entry point in the hierarchy of the scene.
 * To create new SceneNode types, inherit from this class.
 */
class HAF_API SceneNode final : public sys::HasName,
                          public SceneNodeParent,
                          public SceneNodes,
                          public sys::SystemAccess,
                          public component::ComponentContainer,
                          public sys::SubSystemViewer
{
public:
    /**
     * @brief Disabled copy constructor
     */
    SceneNode(SceneNode const&) = delete;

    /**
     * @brief Disabled copy assignment
     */
    SceneNode& operator=(SceneNode const&) = delete;

    /**
     * @brief Defaulted move constructor
     */
    SceneNode(SceneNode&&) noexcept = default;

    /**
     * @brief Defaulted move assignment
     * @return SceneNode& The resulting scene node
     */
    SceneNode& operator=(SceneNode&&) noexcept = default;

    /**
     * @brief Constructor normally used to create a scene node.
     *
     * @param parent Parent of this element.
     * @param name Name of this element.
     */
    SceneNode(htps::rptr<SceneNode> parent, htps::str name);

    /**
     * @brief Destroy the Scene Node object.
     */
    ~SceneNode();

    /**
     * @brief Clear all elements in this scene node
     */
    void clearAll();

    prop::PropertyState<bool> Visible{true};
};

using SceneNodeSPtr = htps::sptr<SceneNode>;
}  // namespace haf::scene

#endif
