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

    /**
     * @brief Remove a given SceneNode
     * 
     * @param element Element to remove
     * @return true The element existed and was removed
     * @return false The element was not on the group list
     */
    bool removeSceneNode(htps::sptr<SceneNode> element);

    /**
     * @brief Remove a given SceneNode by name
     * 
     * @param element Name of the element to remove
     * @return true The element existed and was removed
     * @return false The element was not on the group list
     */
    bool removeSceneNode(htps::str const& name);

    void clearSceneNodes();

    const SceneNodeVector& sceneNodes() const noexcept;
    SceneNodeVector& sceneNodes() noexcept;

    /**
     * @brief Get a SceneNode in the group looking for its name
     * 
     * @param name Name to look for
     * @return htps::sptr<SceneNode> Pointer to the node with the
     * specified name or nullptr if not found. 
     */
    htps::sptr<SceneNode> getByName(const htps::str& name) const;

    void for_each_sceneNode(
        htps::function<void(htps::sptr<SceneNode> const&)> action);

    void for_each_sceneNode(
        htps::function<void(htps::sptr<SceneNode const> const&)> action) const;

    template <typename T>
    constexpr void for_each_sceneNode_as(
        htps::function<void(htps::sptr<T> const&)> action)
    {
        for_each_sceneNode([&action](htps::sptr<SceneNode> const& node) {
            if (auto const tnode = std::dynamic_pointer_cast<T>(node))
            {
                action(tnode);
            }
        });
    }

    template <typename T>
    constexpr void for_each_sceneNode_as(
        htps::function<void(htps::sptr<T const> const&)> action) const
    {
        for_each_sceneNode([&action](htps::sptr<SceneNode const> const& node) {
            if (auto const tnode = std::dynamic_pointer_cast<T const>(node))
            {
                action(tnode);
            }
        });
    }

    template <typename Tag, typename T>
    void set_property_for_each_sceneNode(T const& value)
    {
        for_each_sceneNode_as<SceneNode>(
            [&value](auto& node) { node->template prop<Tag>().set(value); });
    }

    template <typename NodeType, typename Tag, typename T>
    void set_property_for_each_sceneNode_as(T const& value)
    {
        for_each_sceneNode_as<NodeType>(
            [&value](auto& node) { node->template prop<Tag>().set(value); });
    }

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
