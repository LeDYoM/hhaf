#ifndef HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/scene/include/scenenode_cast.hpp>

namespace haf::scene
{
class SceneNode;
class Scene;

/**
 * @brief Class encapsulating the functionallity related to the parent and
 * ancestors management.
 */
class SceneNodeParent
{
public:
    /**
     * @brief Constructor.
     * @param[in] parent       The parent of this node.
     */
    constexpr SceneNodeParent(mtps::rptr<SceneNode> parent) noexcept :
        parent_{std::move(parent)}
    {}

    /**
     * @brief Get the parent of this @b SceneNode
     * @see SceneNode
     * @return constexpr mtps::rptr<SceneNode> Parent or nullptr if no parent
     */
    constexpr mtps::rptr<SceneNode> parent() noexcept { return parent_; }

    /**
     * @brief Get the constant parent of this @b SceneNode
     * @see SceneNode
     * @return constexpr mtps::rptr<SceneNode> Parent or nullptr if no parent
     */
    constexpr const mtps::rptr<const SceneNode> parent() const noexcept
    {
        return parent_;
    }

    /**
     * @brief Get the pointer to the parent converted to another type
     * @tparam SceneNodeType Type to what te parent will be converted
     * @return mtps::rptr<SceneNodeType> The pointer to the parent converted
     * to the specified type or nullptr if conversion cannot be done
     */
    template <typename SceneNodeType>
    mtps::rptr<SceneNodeType> parentAs() noexcept
    {
        return dynamic_cast<mtps::rptr<SceneNodeType>>(parent());
    }

    /**
     * @brief Get the const pointer to the parent converted to another type
     * @tparam SceneNodeType Type to what te parent will be converted
     * @return mtps::rptr<SceneNodeType> The pointer to the parent converted
     * to the specified type or nullptr if conversion cannot be done
     */
    template <typename SceneNodeType>
    mtps::rptr<SceneNodeType const> parentAs() const noexcept
    {
        return dynamic_cast<mtps::rptr<SceneNodeType const>>(parent());
    }

    /**
     * @brief Get the first ancestor of a concrete type going up the tree.
     * @tparam T Expected type of the ancestor.
     * @return constexpr mtps::rptr<T> Pointer to the ancestor of the
     * specific type or nullptr if none found.
     */
    template <typename T = SceneNode>
    constexpr mtps::rptr<T> ancestor() noexcept
    {
        mtps::rptr<SceneNode> _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto parent_as_type{sceneNodeCast<T>(_parent)};
            auto const parent_as_scene_node_parent{
                sceneNodeCast<SceneNodeParent>(_parent)};
            return parent_as_type == nullptr
                ? parent_as_scene_node_parent->ancestor<T>()
                : parent_as_type;
        }
    }

    /**
     * @brief Get the const first ancestor of a concrete type going up the tree.
     * @tparam T Expected type of the ancestor.
     * @return constexpr mtps::rptr<T> Pointer to the ancestor of the
     * specific type or nullptr if none found.
     */
    template <typename T = SceneNode>
    constexpr mtps::rptr<T const> const ancestor() const noexcept
    {
        mtps::rptr<SceneNode const> _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto const parent_as_type{sceneNodeCast<T const>(_parent)};
            auto const parent_as_scene_node_parent{
                sceneNodeCast<SceneNodeParent const>(_parent)};
            return parent_as_type == nullptr
                ? parent_as_scene_node_parent->ancestor<T const>()
                : parent_as_type;
        }
    }

protected:
    /**
     * @brief Destroy the Scene Node Parent object. Only derived classes can
     * use it.
     */
    ~SceneNodeParent() {}

private:
    mtps::rptr<SceneNode> const parent_;
};

}  // namespace haf::scene

#endif
