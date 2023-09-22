HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODES_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODES_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/events/connection.hpp>

namespace haf::component
{
class Component;
}
namespace haf::scene
{
class SceneNode;

class HAF_API SceneNodesGroup
{
public:
    using SceneNodesVector = core::vector<core::sptr<SceneNode>>;
    using size_type        = SceneNodesVector::size_type;

    SceneNodesGroup(core::rptr<SceneNode> sceneNode);

    /**
     * @brief Emitter that will be called when a new node is added
     */
    evt::emitter<core::sptr<SceneNode> const&> onNodeAdded;

    /**
     * @brief Emitter that will be called when a node is removed
     */
    evt::emitter<core::sptr<SceneNode> const&> onNodeRemoved;

    /**
     * @brief Create a SceneNode object
     *
     * @param name The name that should be given to the new node
     * @return core::sptr<SceneNode> The created new node is success or nullptr
     * if some failure happened.
     */
    core::sptr<SceneNode> createSceneNode(core::str_view name);

    core::sptr<component::Component> createSceneNodeWithComponent(
        core::str_view name,
        core::str_view componentName);

    template <typename T>
    core::sptr<T> createSceneNodeWithComponent(core::str_view name)
    {
        return core::static_pointer_cast<T>(
            createSceneNodeWithComponent(core::move(name), T::StaticTypeName));
    }

    /**
     * @brief Remove a SceneNode object
     *
     * @param name Name of the SceneNode to remove
     * @return true The SceneNode was removed successfully
     * @return false Error removing the SceneNode
     */
    bool removeSceneNode(core::str_view name);

    /**
     * @brief Remove a SceneNode object
     *
     * @param sceneNode SceneNode to remove
     * @return true The SceneNode was removed successfully
     * @return false Error removing the SceneNode
     */
    bool removeSceneNode(core::sptr<SceneNode> sceneNode);

    /**
     * @brief Remove a SceneNode object
     *
     * @param index Index of the SceneNode to remove
     * @return true The SceneNode was removed successfully
     * @return false Error removing the SceneNode
     */
    bool removeSceneNode(size_type const index);

    /**
     * @return Get the number of scene nodes in the list
     */
    size_type size() const noexcept;

    /**
     * @return If the list of contained scene nodes is empty or not.
     */
    bool empty() const noexcept;

    /**
     * @brief Get a SceneNode in the group looking for its name
     *
     * @param name Name to look for
     * @return htps::sptr<SceneNode> Pointer to the node with the
     * specified name or nullptr if not found.
     */
    core::sptr<SceneNode> getByName(core::str_view name);

    /**
     * @brief Get a SceneNode in the group looking for its index
     *
     * @param index Index to look for
     * @return htps::sptr<SceneNode> Pointer to the node with the
     * specified index or nullptr if not found.
     */
    core::sptr<SceneNode> getByIndex(size_type const index);

    /**
     * @brief Get the index data from a corresponding SceneNodeSPtr.
     *
     * @param sceneNode The scene node to get the index from.
     * @return core::pair<size_type, bool> A pair where the first member is
     * the index and the second member tells if the node has been found.
     * @note If the second member of the return structure is false, the
     * value of the first member says nothing.
     */
    core::pair<size_type, bool> getIndex(
        core::sptr<SceneNode> const& sceneNode);

    SceneNodesVector const& sceneNodes() const;

    SceneNodesVector::iterator begin() { return m_scene_nodes.begin(); }
    SceneNodesVector::const_iterator begin() const
    {
        return m_scene_nodes.begin();
    }
    SceneNodesVector::const_iterator cbegin() const
    {
        return m_scene_nodes.cbegin();
    }

    SceneNodesVector::iterator end() { return m_scene_nodes.end(); }
    SceneNodesVector::const_iterator end() const { return m_scene_nodes.end(); }
    SceneNodesVector::const_iterator cend() const
    {
        return m_scene_nodes.cend();
    }

private:
    /**
     * @brief Add an already created SceneNode to the group
     * @param node Node to add
     */
    void addSceneNode(core::sptr<SceneNode>& node);

    core::rptr<SceneNode> m_scene_node;

    /**
     * @brief Container of a group of @b SceneNode (s)
     */
    SceneNodesVector m_scene_nodes;
};

}  // namespace haf::scene

#endif
