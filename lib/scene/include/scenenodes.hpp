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
    SceneNodes(const mtps::rptr<SceneNode> scene_node);
    /// Virtual destructor.
    virtual ~SceneNodes();

    /// Method to create a new SceneNode. Since new constructors
    /// may be added, it uses variadic forwarding of the arguments.
    /// It also adds the new node to the parents list.
    template <typename T = SceneNode, typename... Args>
    mtps::sptr<T> createSceneNode(Args &&... args)
    {
        auto result(mtps::msptr<T>(attached_, std::forward<Args>(args)...));
        addSceneNode(result);
        return result;
    }

    /// Method to create a new SceneNode. It is a partial specialization of
    // the general one.
    mtps::sptr<SceneNode> createSceneNode(mtps::str name);

    bool moveLastBeforeNode(const mtps::sptr<SceneNode> &beforeNode);
    void removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    void renderGroups(const bool parentTransformationChanged);

    constexpr const auto &sceneNodes() const noexcept { return m_groups; }
    constexpr auto &sceneNodes() noexcept { return m_groups; }

    mtps::sptr<SceneNode> groupByName(const mtps::str&name) const;

protected:
    void addSceneNode(mtps::sptr<SceneNode> node);

private:
    const mtps::rptr<SceneNode> attached_;
    mtps::vector<mtps::sptr<SceneNode>> m_groups;
};

} // namespace lib::scene

#endif
