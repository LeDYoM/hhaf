#ifndef HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP
#define HAF_SCENE_SCENENODEPARENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/cast.hpp>

namespace haf::scene
{
class Scene;

/**
 * @brief Class encapsulating the functionallity related to the parent and
 * ancestors management.
 */
template <typename CRTP>
class SceneNodeParent
{
public:
    /**
     * @brief Constructor.
     * @param[in] parent       The parent of this node.
     */
    constexpr SceneNodeParent(htps::rptr<CRTP> parent) noexcept :
        parent_{std::move(parent)}
    {}

    /**
     * @brief Get the parent of this node
     * @see SceneNode
     * @return Parent or nullptr if no parent
     */
    constexpr htps::rptr<CRTP> parent() noexcept { return parent_; }

    /**
     * @brief Get the constant parent of this node
     * @see SceneNode
     * @return Parent or nullptr if no parent
     */
    constexpr htps::rptr<CRTP const> parent() const noexcept
    {
        return parent_;
    }

    constexpr htps::rptr<CRTP const> cparent() const noexcept
    {
        return parent();
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
        return htps::d_cast<htps::rptr<SceneNodeType>>(parent());
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
        return htps::d_cast<htps::rptr<SceneNodeType const>>(parent());
    }

    template <typename SceneNodeType>
    htps::rptr<SceneNodeType const> cparentAs() const noexcept
    {
        return parentAs<SceneNodeType>();
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

    template <typename T>
    constexpr htps::rptr<T const> const cancestor() const noexcept
    {
        return ancestor<T>();
    }

    constexpr htps::rptr<Scene> sceneParent() noexcept
    {
        return ancestor<Scene>();
    }

    /**
     * @brief Destroy the Scene Node Parent object.
     * We need this class to be polymorphics
     */
    virtual ~SceneNodeParent() {}

private:
    htps::rptr<CRTP> const parent_;
};

}  // namespace haf::scene

#endif
