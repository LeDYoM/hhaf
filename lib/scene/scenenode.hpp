#pragma once

#ifndef LIB_SCENE_SCENENODE_INCLUDE_HPP
#define LIB_SCENE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/transformable.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/datawrappers/datawrappercreator.hpp>

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
class SceneNode : public core::HasName,
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
    SceneNode(SceneNode *const parent, str name);

    /// Virtual destructor.
    virtual ~SceneNode();

    /// Method called when adding a new node just after creation.
    /// Override it to add code on creation.
    /// @see configure
    virtual void onCreated() {}

    /// Method to create a new SceneNode. Since new constructors
    /// may be added, it uses variadic forwarding of the arguments.
    /// It also adds the new node to the parents list.
    template <typename T = SceneNode, typename... Args>
    sptr<T> createSceneNode(Args &&... args)
    {
        auto result(msptr<T>(this, std::forward<Args>(args)...));
        addSceneNode(result);
        return result;
    }

    /// Method to create a new SceneNode. It is a partial specialization of
    // the general one.
    sptr<SceneNode> createSceneNode(str name);

    bool moveLastBeforeNode(const sptr<SceneNode> &beforeNode);
    void removeSceneNode(sptr<SceneNode> element);
    void clearAll();
    void clearSceneNodes();

    void render(bool parentTransformationChanged);
    virtual void update() {}

    virtual Scene *const parentScene() noexcept
    {
        return m_parent->parentScene();
    }

    virtual const Scene *const parentScene() const noexcept
    {
        return m_parent->parentScene();
    }

    template <typename SceneType>
    SceneType *const parentSceneAs()
    {
        return dynamic_cast<SceneType *>(parentScene());
    }

    template <typename SceneType>
    const SceneType *const parentSceneAs() const
    {
        return dynamic_cast<const SceneType *>(parentScene());
    }

    SceneNode *parent() noexcept { return m_parent; }
    const SceneNode *parent() const noexcept { return m_parent; }

    template <typename SceneNodeType>
    SceneNodeType *parentAs()
    {
        return dynamic_cast<SceneNodeType *>(parent());
    }

    template <typename SceneNodeType>
    const SceneNodeType *parentAs() const
    {
        return dynamic_cast<const SceneNodeType *>(parent());
    }

    template <typename T>
    constexpr T *const snCast() { return dynamic_cast<T *const>(this); }

    template <typename T>
    constexpr const T *const snCast() const { return dynamic_cast<const T *const>(this); }

    BasicProperty<bool> visible;

    constexpr const auto &sceneNodes() const noexcept { return m_groups; }
    constexpr auto &sceneNodes() noexcept { return m_groups; }
    constexpr auto sceneNodesSize() const noexcept { return sceneNodes().size(); }

protected:
    void addSceneNode(sptr<SceneNode> node);

private:
    SceneNode *m_parent;
    vector<sptr<SceneNode>> m_groups;
};

using SceneNodeSPtr = sptr<SceneNode>;
} // namespace lib::scene

#endif
