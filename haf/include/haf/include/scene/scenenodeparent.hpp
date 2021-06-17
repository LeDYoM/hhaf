#ifndef HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::scene
{
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
    constexpr SceneNodeParent(htps::rptr<SceneNodeParent> parent) noexcept :
        parent_{std::move(parent)}
    {}

    /**
     * @brief Get the parent of this @b SceneNode
     * @see SceneNode
     * @return constexpr htps::rptr<SceneNode> Parent or nullptr if no parent
     */
//    constexpr htps::rptr<SceneNodeParent> parent() noexcept { return parent_; }

    /**
     * @brief Get the constant parent of this @b SceneNode
     * @see SceneNode
     * @return constexpr htps::rptr<SceneNode> Parent or nullptr if no parent
     */
    constexpr htps::rptr<const SceneNodeParent> parent() const noexcept
    {
        return parent_;
    }

    /**
     * @brief Get the pointer to the parent converted to another type
     * @tparam SceneNodeType Type to what te parent will be converted
     * @return htps::rptr<SceneNodeType> The pointer to the parent converted
     * to the specified type or nullptr if conversion cannot be done
     */
    template <typename SceneNodeType>
    htps::rptr<SceneNodeType> parentAs() noexcept
    {
        return dynamic_cast<htps::rptr<SceneNodeType>>(parent());
    }

    /**
     * @brief Get the const pointer to the parent converted to another type
     * @tparam SceneNodeType Type to what te parent will be converted
     * @return htps::rptr<SceneNodeType> The pointer to the parent converted
     * to the specified type or nullptr if conversion cannot be done
     */
    template <typename SceneNodeType>
    htps::rptr<SceneNodeType const> parentAs() const noexcept
    {
        return dynamic_cast<htps::rptr<SceneNodeType const>>(parent());
    }

    /**
     * @brief Get the first ancestor of a concrete type going up the tree.
     * @tparam T Expected type of the ancestor.
     * @return constexpr htps::rptr<T> Pointer to the ancestor of the
     * specific type or nullptr if none found.
     */
    template <typename T>
    constexpr htps::rptr<T> ancestor() noexcept
    {
        auto const _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto parent_as_type{parentAs<T>()};
            return parent_as_type == nullptr ? _parent->ancestor<T>()
                                             : parent_as_type;
        }
    }

    /**
     * @brief Get the const first ancestor of a concrete type going up the tree.
     * @tparam T Expected type of the ancestor.
     * @return constexpr htps::rptr<T> Pointer to the ancestor of the
     * specific type or nullptr if none found.
     */
    template <typename T>
    constexpr htps::rptr<T const> const ancestor() const noexcept
    {
        auto const _parent{parent()};
        if (_parent == nullptr)
        {
            return nullptr;
        }
        else
        {
            auto parent_as_type{parentAs<T>()};
            return parent_as_type == nullptr ? _parent->ancestor<T>()
                                             : parent_as_type;
        }
    }

    /**
     * @brief Destroy the Scene Node Parent object.
     * We need this class to be polymorphics
     */
    virtual ~SceneNodeParent() {}

private:
    htps::rptr<SceneNodeParent> const parent_;
};

}  // namespace haf::scene

#endif
