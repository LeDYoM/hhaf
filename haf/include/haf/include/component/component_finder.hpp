HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_FINDER_INCLUDE_HPP
#define HAF_COMPONENT_FINDER_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{
class HAF_API ComponentFinder final
{
public:
    explicit ComponentFinder(core::rptr<scene::SceneNode> node) noexcept;

    core::sptr<Component> findParentComponent(core::str_view name) const;
    core::sptr<Component> findAncestorComponent(core::str_view name) const;

    template <typename T>
    core::sptr<T> findParentComponent() const
    {
        return core::static_pointer_cast<T>(
            findParentComponent(T::StaticTypeName));
    }

    template <typename T>
    core::sptr<T> findAncestorComponent() const
    {
        return core::static_pointer_cast<T>(
            findAncestorComponent(T::StaticTypeName));
    }

private:
    core::rptr<scene::SceneNode> m_node;
};
}  // namespace haf::component

#endif
