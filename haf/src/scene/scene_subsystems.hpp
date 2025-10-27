HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_SUBSYSTEMS_INCLUDE_HPP
#define HAF_SCENE_SCENE_SUBSYSTEMS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "haf_private.hpp"
#include "scene_subsystem.hpp"

namespace haf::scene
{
class HAF_PRIVATE SceneSubsystems final
{
public:
    constexpr SceneSubsystem const& operator[](core::u32 index) const noexcept
    {
        return m_scene_subsystems[index];
    }

    constexpr void addSceneSubsystem(SceneSubsystem&& sceneSubsystem)
    {
        m_scene_subsystems.push_back(core::move(sceneSubsystem));
    }

    template <typename Self>
    constexpr decltype(auto) begin(this Self&& self)
    {
        return self.m_scene_subsystems.begin();
    }

    template <typename Self>
    constexpr decltype(auto) end(this Self&& self)
    {
        return self.m_scene_subsystems.end();
    }

private:
    core::vector<SceneSubsystem> m_scene_subsystems;
};

}  // namespace haf::scene

#endif
