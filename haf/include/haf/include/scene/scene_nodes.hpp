#ifndef HAF_SCENE_SCENENODES_INCLUDE_HPP
#define HAF_SCENE_SCENENODES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/scene/scenenode_cast.hpp>

namespace haf::scene
{
class SceneNode;

class SceneNodes
{
public:
    using SceneNodeVector = htps::vector<htps::sptr<SceneNode>>;

    explicit SceneNodes(htps::rptr<SceneNode> const scene_node);

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
    auto createSceneNode(htps::str name)
    {
        auto result{htps::msptr<T>(scene_node_, std::move(name))};
        onNodeCreated(result);
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

    bool autoRemove();

    /**
     * @brief Remove a given SceneNode by name
     *
     * @param element Name of the element to remove
     * @return true The element existed and was removed
     * @return false The element was not on the group list
     */
    bool removeSceneNode(htps::str const& name);

    /**
     * @brief Delete all scene nodes in this group
     */
    void clearSceneNodes();

    /**
     * @return Get a constant reference to the underlying container
     * of scenenodes.
     */
    SceneNodeVector const& sceneNodes() const noexcept;

    /**
     * @return Get a mutable reference to the underlying container
     * of scenenodes.
     */
    SceneNodeVector& sceneNodes() noexcept;

    /**
     * @brief Get a SceneNode in the group looking for its name
     *
     * @param name Name to look for
     * @return htps::sptr<SceneNode> Pointer to the node with the
     * specified name or nullptr if not found.
     */
    htps::sptr<SceneNode> getByName(htps::str const& name);

    template <typename T>
    htps::sptr<T> getByNameAs(htps::str const& name)
    {
        auto node{getByName(name)};
        return ((node != nullptr) ? sceneNodeCast<T>(node) : nullptr);
    }

    htps::sptr<SceneNode> getShared(htps::rptr<SceneNode> node) const;

    /**
     * @brief Execute a mutable action for every SceneNode in the
     * group.
     * @param action Action to perform
     */
    void for_each_sceneNode(
        htps::function<void(htps::sptr<SceneNode> const&)> action);

    /**
     * @brief Execute a constant action for every SceneNode in the
     * group.
     * @param action Action to perform
     */
    void for_each_sceneNode(
        htps::function<void(htps::sptr<SceneNode const> const&)> action) const;

    /**
     * @brief Execute a mutable action for every SceneNode that is a T in the
     * group.
     * @tparam Type to perform actions on
     * @param action Action to perform
     */
    template <typename T>
    constexpr void for_each_sceneNode_as(
        htps::function<void(htps::sptr<T> const&)> action)
    {
        for_each_sceneNode([&action](htps::sptr<SceneNode> const& node) {
            if (auto const tnode = std::dynamic_pointer_cast<T>(node);
                tnode != nullptr)
            {
                action(tnode);
            }
        });
    }

    /**
     * @brief Execute a const action for every SceneNode that is a T in the
     * group.
     * @tparam Type to perform actions on
     * @param action Action to perform
     */
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

    /**
     * @brief Set a property value for each SceneNode object in the group
     *
     * @tparam Tag Name of the property
     * @tparam T Type of the property
     * @param value Value of the property
     */
    template <typename Tag, typename T>
    void set_property_for_each_sceneNode(T const& value)
    {
        for_each_sceneNode(
            [&value](auto& node) { node->template prop<Tag>().set(value); });
    }

    /**
     * @brief Set a property value for each SceneNode object in the group
     * that is convertible to NodeType
     *
     * @tparam NodeType Type to convert the SceneNode to
     * @tparam Tag Name of the property
     * @tparam T Type of the property
     * @param value Value of the property
     */
    template <typename NodeType, typename Tag, typename T>
    void set_property_for_each_sceneNode_as(T const& value)
    {
        for_each_sceneNode_as<NodeType>(
            [&value](auto& node) { node->template prop<Tag>().set(value); });
    }

    bool moveToLastPosition(htps::sptr<SceneNode> const& node);

    htps::emitter<htps::sptr<SceneNode> const&> onNodeCreated;
    htps::emitter<htps::sptr<SceneNode> const&> onNodeAdded;
    htps::emitter<htps::sptr<SceneNode> const&> onNodeReady;

protected:
    /**
     * @brief Destroy the Scene Nodes object
     */
    ~SceneNodes();

    /**
     * @brief Add an already created SceneNode to the group
     * @param node Node to add
     */
    void addSceneNode(htps::sptr<SceneNode> node);

private:
    /**
     * @brief @b SceneNode that owns this group
     */
    htps::rptr<SceneNode> const scene_node_;

    /**
     * @brief Container of a group of @b SceneNode (s)
     */
    SceneNodeVector scene_nodes_;
};

}  // namespace haf::scene

#endif
