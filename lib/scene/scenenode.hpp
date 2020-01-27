#pragma once

#ifndef LIB_SCENE_SCENENODE_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/scenenodeparent.hpp>
#include <lib/scene/scenenodes.hpp>
#include <lib/scene/transformable.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/icomponent.hpp>
#include <lib/scene/componentcontainer.hpp>
#include <lib/scene/datawrappercreator.hpp>

#include "scenenodeblob.hpp"

namespace lib::scene
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
                  public Transformable,
                  public DataWrapperCreator,
                  public ComponentContainer,
                  public SceneNodeBlob
{
public:
    /// No copy constructor.
    SceneNode(const SceneNode &) = delete;
    /// No assignment operator
    SceneNode &operator=(const SceneNode &) = delete;

    /// Constructor normally used to create a scene node.
    /// @param[in] parent   Parent of this element.
    /// @param[in] name     Name of this element.
    SceneNode(rptr<SceneNode> parent, str name);

    /// Virtual destructor.
    virtual ~SceneNode();

    /// Method called when adding a new node just after creation.
    /// Override it to add code on creation.
    /// @see configure
    virtual void onCreated() {}

    void render(bool parentTransformationChanged);
    virtual void update() {}

    BasicProperty<bool> visible;
    void clearAll();
};

using SceneNodeSPtr = sptr<SceneNode>;
} // namespace lib::scene

#endif
