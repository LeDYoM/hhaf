#ifndef HAF_SCENE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/scene/scenenodeparent.hpp>
#include <haf/include/scene/scenenode_properties.hpp>
#include <haf/include/scene/scenenodes.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/system/interface_getter.hpp>
#include <haf/include/system/datawrappercreator.hpp>
#include <haf/include/system/systemaccess.hpp>

#include <htypes/include/p_impl_pointer.hpp>

namespace haf::scene
{
class ComponentContainer;
/**
 * @brief Main class representing all SceneNodes from a @b Scene.
 * This class serves as main entry point in the hierarchy of the scene.
 * To create new SceneNode types, inherit from this class.
 */
class HAF_API SceneNode : public sys::HasName,
                          public SceneNodeParent,
                          public SceneNodes,
                          public sys::DataWrapperCreator,
                          public sys::SystemAccess,
                          public sys::InterfaceGetter,
                          public SceneNodeProperties
{
public:
    using SceneNodeProperties::prop;

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
    virtual ~SceneNode();

    /**
     * @brief Method called when adding a new node just after creation.
     * Override it to add code on creation.
     */
    virtual void onCreated() {}

    /**
     * @brief Method called every frame
     */
    virtual void update() {}

    /**
     * @brief Clear all elements in this scene node
     */
    void clearAll();

    ComponentContainer& components();
    ComponentContainer const& components() const noexcept;
    bool hasComponents() const noexcept;

private:
    struct SceneNodePrivate;
    htps::PImplPointer<SceneNodePrivate> p_;
};

using SceneNodeSPtr = htps::sptr<SceneNode>;
}  // namespace haf::scene

#endif
