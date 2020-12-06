#ifndef HAF_SCENE_SCENENODES_INCLUDE_HPP
#define HAF_SCENE_SCENENODES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <haf/scene/include/scenenodes_group.hpp>

namespace haf::scene
{
class SceneNode;

class SceneNodes
{
public:
    SceneNodes(const mtps::rptr<SceneNode> scene_node);

    /**
     * @brief Create a Scene Node object.
     * Since new constructors may be added, it uses variadic forwarding of the
     * arguments.
     * It also adds the new node to the parents list.
     *
     * @tparam T Type to create
     * @return mtps::sptr<T> The created object
     */
    template <typename T = SceneNode>
    mtps::sptr<T> createSceneNode(mtps::str name)
    {
        auto result(mtps::msptr<T>(scene_node_, std::move(name)));
        addSceneNode(result);
        return result;
    }

    bool removeSceneNode(mtps::sptr<SceneNode> element);
    void clearSceneNodes();

    const SceneNodesGroup::SceneNodeVector& sceneNodes() const noexcept;
    SceneNodesGroup::SceneNodeVector& sceneNodes() noexcept;

    mtps::sptr<SceneNode> groupByName(const mtps::str& name) const;

protected:
    /**
     * @brief Destroy the Scene Nodes object
     */
    ~SceneNodes();

    void addSceneNode(mtps::sptr<SceneNode> node);

private:
    const mtps::rptr<SceneNode> scene_node_;
    SceneNodesGroup scene_nodes_group_;
};

}  // namespace haf::scene

#endif
