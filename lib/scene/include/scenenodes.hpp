#pragma once

#ifndef LIB_SCENE_SCENENODESGROUP_INCLUDE_HPP
#define LIB_SCENE_SCENENODESGROUP_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scenenodes_group.hpp>

namespace haf::scene
{
class SceneNode;

class SceneNodes
{
public:
    SceneNodes(const mtps::rptr<SceneNode> scene_node);

    /**
     * @brief Destroy the Scene Nodes object
     */
    virtual ~SceneNodes();

    /**
     * @brief Create a Scene Node object.
     * Since new constructors may be added, it uses variadic forwarding of the
     * arguments.
     * It also adds the new node to the parents list.
     *
     * @tparam T Type to create
     * @tparam Args Type of the parameters
     * @param args Actual value for the arguments
     * @return mtps::sptr<T> The created object
     */
    template <typename T = SceneNode, typename... Args>
    mtps::sptr<T> createSceneNode(Args&&... args)
    {
        auto result(mtps::msptr<T>(scene_node_, std::forward<Args>(args)...));
        addSceneNode(result);
        return result;
    }

    void removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    void renderGroups(const bool parentTransformationChanged);

    const auto& sceneNodes() const noexcept
    {
        return scene_nodes_group_.sceneNodes();
    }
    
    auto& sceneNodes() noexcept
    {
        return scene_nodes_group_.sceneNodes();
    }

    mtps::sptr<SceneNode> groupByName(const mtps::str& name) const;

protected:
    void addSceneNode(mtps::sptr<SceneNode> node);

private:
    const mtps::rptr<SceneNode> scene_node_;
    SceneNodesGroup scene_nodes_group_;
};

}  // namespace haf::scene

#endif
