HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_SCENE_SUBSYSTEM_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_order.hpp>

namespace haf::scene
{
class HAF_PRIVATE SceneSubsystem final
{
public:
    constexpr SceneSubsystem(core::str&& name,
                             component::ComponentOrder::Value index) noexcept :
        m_name{core::move(name)}, m_index{index}
    {}

    constexpr core::str const& name() const noexcept { return m_name; }

    constexpr component::ComponentOrder::Value const index() const noexcept
    {
        return m_index;
    }

private:
    core::str m_name;
    component::ComponentOrder::Value m_index;
};

}  // namespace haf::scene

#endif
