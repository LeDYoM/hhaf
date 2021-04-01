#ifndef HAF_SCENE_SCENENODES_INCLUDE_HPP
#define HAF_SCENE_SCENENODES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>

namespace haf::scene
{
class SceneNode;

class SceneNodes
{
public:
    using SceneNodeVector = htps::vector<htps::sptr<SceneNode>>;

    SceneNodes(const htps::rptr<SceneNode> scene_node);

    /**
     * @brief Create a Scene Node object.
     * Since new constructors may be added, it uses variadic forwarding of the
     * arguments.
     * It also adds the new node to the parents list.
     *
     * @tparam T Type to create
     * @return htps::sptr<T> The created object
     */
    template <typename T = SceneNode>
    htps::sptr<T> createSceneNode(htps::str name)
    {
        auto result(htps::msptr<T>(scene_node_, std::move(name)));
        addSceneNode(result);
        return result;
    }

    bool removeSceneNode(htps::sptr<SceneNode> element);
    void clearSceneNodes();

    const SceneNodeVector& sceneNodes() const noexcept;
    SceneNodeVector& sceneNodes() noexcept;

    htps::sptr<SceneNode> groupByName(const htps::str& name) const;

    void for_each_sceneNode(
        SceneNodes& node,
        htps::function<void(htps::sptr<SceneNode> const&)> action);

    void for_each_sceneNode(
        SceneNodes const& node,
        htps::function<void(htps::sptr<SceneNode const> const&)> action);

protected:
    /**
     * @brief Destroy the Scene Nodes object
     */
    ~SceneNodes();

    void addSceneNode(htps::sptr<SceneNode> node);

private:
    const htps::rptr<SceneNode> scene_node_;
    SceneNodeVector scene_nodes_;
};

}  // namespace haf::scene

#endif
