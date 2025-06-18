HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/cast.hpp>

namespace haf::scene
{
class SceneNode;
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
    constexpr SceneNodeParent(htps::rptr<SceneNode> parent) noexcept :
        parent_{htps::move(parent)}
    {}

    /**
     * @brief Get the parent of this node
     * @see SceneNode
     * @return Parent or nullptr if no parent
     */
    constexpr htps::rptr<SceneNode> parent() noexcept { return parent_; }

    /**
     * @brief Get the constant parent of this node
     * @see SceneNode
     * @return Parent or nullptr if no parent
     */
    constexpr htps::rptr<SceneNode const> parent() const noexcept
    {
        return parent_;
    }

    constexpr htps::rptr<SceneNode const> cparent() const noexcept
    {
        return parent();
    }

private:
    htps::rptr<SceneNode> const parent_;
};

}  // namespace haf::scene

#endif
