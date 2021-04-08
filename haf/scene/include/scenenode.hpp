#ifndef HAF_SCENE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_INCLUDE_HPP

#include <haf/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/scene/include/scenenodeparent.hpp>
#include <haf/scene/include/scenenodes.hpp>
#include <haf/render/include/renderizables.hpp>
#include <haf/scene/include/transformable.hpp>
#include <haf/scene/include/hasname.hpp>
#include <haf/scene/include/componentcontainer.hpp>
#include <haf/scene/include/scenenode_cast.hpp>
#include <haf/scene/include/interface_getter.hpp>
#include <haf/system/include/datawrappercreator.hpp>
#include <haf/system/include/systemaccess.hpp>

namespace haf::scene
{
class Renderizable;
class Scene;
class SceneManager;

struct Visible
{
    using value_type = bool;
};

using SceneNodeProperties = htps::PropertyGroup<Visible>;

/**
 * @brief Main class representing all SceneNodes from a @b Scene.
 * This class serves as main entry point in the hierarchy of the scene.
 * To create new SceneNode types, inherit from this class.
 */
class HAF_API SceneNode : public sys::HasName,
                          public SceneNodeParent,
                          public SceneNodes,
                          public Renderizables,
                          public Transformable,
                          public sys::DataWrapperCreator,
                          public ComponentContainer,
                          public sys::SystemAccess,
                          public InterfaceGetter,
                          public SceneNodeProperties
{
public:
    using SceneNodeProperties::prop;
    using TransformationProperties::prop;

    /**
     * @brief Disabled copy constructor
     */
    SceneNode(const SceneNode&) = delete;

    /**
     * @brief Disabled copy assignment
     */
    SceneNode& operator=(const SceneNode&) = delete;

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
     * @param[in] parent Parent of this element.
     * @param[in] name Name of this element.
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
};

using SceneNodeSPtr = htps::sptr<SceneNode>;
}  // namespace haf::scene

#endif
