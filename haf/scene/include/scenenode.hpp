#pragma once

#ifndef HAF_SCENE_SCENENODE_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <haf/scene/include/scenenodeparent.hpp>
#include <haf/scene/include/scenenodes.hpp>
#include <haf/scene/include/renderizables.hpp>
#include <haf/scene/include/transformable.hpp>
#include <haf/scene/include/hasname.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/scene/include/componentcontainer.hpp>
#include <haf/system/include/datawrappercreator.hpp>
#include <haf/system/include/systemaccess.hpp>

namespace haf::scene
{
class Renderizable;
class IComponent;
class Scene;
class SceneManager;

/// Main class representing all SceneNodes from a Scene.
/// This class serves as main entry point in the hierarchy of the scene.
/// To create new SceneNode types, inherit from this class.
class SceneNode : public sys::HasName,
                  public SceneNodeParent,
                  public SceneNodes,
                  public Renderizables,
                  public Transformable,
                  public sys::DataWrapperCreator,
                  public ComponentContainer,
                  public sys::SystemAccess
{
public:
    /// No copy constructor.
    SceneNode(const SceneNode &) = delete;
    /// No assignment operator
    SceneNode &operator=(const SceneNode &) = delete;

    SceneNode(SceneNode&&) noexcept = default;
    SceneNode& operator=(SceneNode&&) noexcept = default;

    /// Constructor normally used to create a scene node.
    /// @param[in] parent   Parent of this element.
    /// @param[in] name     Name of this element.
    SceneNode(mtps::rptr<SceneNode> parent, mtps::str name);

    /// Virtual destructor.
    virtual ~SceneNode();

    /// Method called when adding a new node just after creation.
    /// Override it to add code on creation.
    /// @see configure
    virtual void onCreated() {}

    void render(bool parentTransformationChanged);
    virtual void update() {}

    mtps::BasicProperty<bool> visible;
    void clearAll();
};

using SceneNodeSPtr = mtps::sptr<SceneNode>;
} // namespace haf::scene

#endif
