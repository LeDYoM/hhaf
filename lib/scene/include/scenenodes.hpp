#pragma once

#ifndef LIB_SCENE_SCENENODES_INCLUDE_HPP
#define LIB_SCENE_SCENENODES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/scene/include/componentcontainer.hpp>

namespace lib::scene
{
class SceneNode;

class SceneNodes
{
public:
    SceneNodes(const rptr<SceneNode> scene_node);
    /// Virtual destructor.
    virtual ~SceneNodes();

    /// Method to create a new SceneNode. Since new constructors
    /// may be added, it uses variadic forwarding of the arguments.
    /// It also adds the new node to the parents list.
    template <typename T = SceneNode, typename... Args>
    sptr<T> createSceneNode(Args &&... args)
    {
        auto result(msptr<T>(attached_, std::forward<Args>(args)...));
        addSceneNode(result);
        return result;
    }

    /// Method to create a new SceneNode. It is a partial specialization of
    // the general one.
    sptr<SceneNode> createSceneNode(str name);

    bool moveLastBeforeNode(const sptr<SceneNode> &beforeNode);
    void removeSceneNode(sptr<SceneNode> element);
    void clearSceneNodes();

    void renderGroups(const bool parentTransformationChanged);

    constexpr const auto &sceneNodes() const noexcept { return m_groups; }
    constexpr auto &sceneNodes() noexcept { return m_groups; }

    sptr<SceneNode> groupByName(const str &name) const;

protected:
    void addSceneNode(sptr<SceneNode> node);

private:
    const rptr<SceneNode> attached_;
    vector<sptr<SceneNode>> m_groups;
};

} // namespace lib::scene

#endif
