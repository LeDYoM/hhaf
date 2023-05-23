HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODES_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODES_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/scene_components/transformation_component.hpp>

namespace haf::scene
{
class HAF_API SceneNodesComponent final
    : public component::ComponentBase<"SceneNodesComponent">
{
public:
    using SceneNodesVector = core::vector<core::sptr<SceneNode>>;
    using size_type        = SceneNodesVector::size_type;

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
    SceneNodeSPtr createSceneNode(core::str_view name);

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
    bool removeSceneNode(SceneNodeSPtr sceneNode);

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
    SceneNodeSPtr getByName(core::str_view name);

    /**
     * @brief Get a SceneNode in the group looking for its index
     *
     * @param index Index to look for
     * @return htps::sptr<SceneNode> Pointer to the node with the
     * specified index or nullptr if not found.
     */
    SceneNodeSPtr getByIndex(size_type const index);

    /**
     * @brief Get the index data from a corresponding SceneNodeSPtr.
     *
     * @param sceneNode The scene node to get the index from.
     * @return core::pair<size_type, bool> A pair where the first member is
     * the index and the second member tells if the node has been found.
     * @note If the second member of the return structure is false, the
     * value of the first member says nothing.
     */
    core::pair<size_type, bool> getIndex(SceneNodeSPtr const& sceneNode);

    /**
     * @brief Execute an action for each scene node in the contained scene
     * nodes.
     *
     * @param f Invokable function with a constant scene node pointer as
     * parameter.
     */
    void forEach(core::function<void(SceneNodeSPtr const&)> f) const;

private:
    void onAttached() override;

    void updateNodes();

    /**
     * @brief Add an already created SceneNode to the group
     * @param node Node to add
     */
    void addSceneNode(core::sptr<SceneNode>& node);

    /**
     * @brief Container of a group of @b SceneNode (s)
     */
    SceneNodesVector m_scene_nodes;
};

}  // namespace haf::scene

#endif
